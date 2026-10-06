#include "echipa_service.h"
#include <stdexcept>

//constr fara param
echipa_service:: echipa_service() : id(0), nume(""), prenume(""), cnp(""), dataAngajare(), orasDomiciliu("") {}

void echipa_service:: setNume(const string& n){
    if(n.length() < 3 || n.length() > 30){
        throw invalid_argument("Nume invalid.");
    }

    nume = n;
}

void echipa_service:: setPrenume(const string& p){
    if(p.length() < 3 || p.length() > 30){
        throw invalid_argument("Prenume invalid.");
    }

    prenume = p;
}

bool echipa_service:: cnpValid(const string &c){
    if(c.length() != 13)
        return false;

    //verificam daca sunt toate cifre
    for(int i = 0; i < 13; i++)
        if(c[i] < '0' || c[i] > '9')
            return false;
    
    //verificam secolul
    int s = c[0] -'0';
    if(s < 1 || s > 8)
        return false;

    //calculm anul pt verificarea anului bisect
    int aa = (c[1] - '0')*10 + (c[2] - '0');
    int an;
    if ( s == 1 || s == 2) an = 1900 + aa;
    else if (s == 3 || s == 4 ) an = 1800 + aa;
    else an = 2000 + aa;

    //verificam luna
    int ll = (c[3] -'0') * 10 + (c[4] - '0');
    if (ll < 1 || ll > 12)
        return false;

    //verificam ziua
    int zz = (c[5] - '0') * 10 + (c[6] - '0');
    //cate zile are fiecare luna
    int zileLuna[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int maxZi = zileLuna[ll - 1];
    if (ll == 2 && ((an % 4 == 0 && an % 100 != 0) || an % 400 ==0))
        maxZi = 29;
    if(zz < 1 || zz > maxZi)
        return false;

    //verificam validitatea judetului
    int jj = (c[7] - '0')*10 + (c[8] - '0');
    if(jj < 1 || (jj > 52 && jj != 70))
        return false;

    //verificam cu cifra de control
    int control[] = {2, 7, 9, 1, 4, 6, 3, 5, 8, 2, 7, 9};
    int suma = 0;

    for(int i = 0; i < 12; i++)
        suma += (c[i] - '0') * control[i];

    int rest = suma % 11;
    int cifraControl;
    if(rest == 10)
        cifraControl = 1;
    else 
        cifraControl = rest;

    if(cifraControl == (c[12] - '0'))
        return true;
    else
        return false;
}

//constr cu param
echipa_service :: echipa_service(int i, string n, string p, string c, date da, string od): id(i), dataAngajare(da), orasDomiciliu(od) {
    setNume(n);
    setPrenume(p);

    if(!cnpValid(c))
        throw invalid_argument("CNP invalid.");
    cnp = c;
}

int echipa_service::getId() const{ 
    return id;
}

string echipa_service:: getNume() const{
    return nume;
}

string echipa_service:: getPrenume() const{
    return prenume;
}

string echipa_service:: getCnp() const{
    return cnp;
}

date echipa_service:: getDataAngajare() const{
    return dataAngajare;
}

string echipa_service:: getOrasDomiciliu() const{
    return orasDomiciliu;
}

double echipa_service::salariu() const{
    double salariuBaza = 4000.0;
    int anCurent = 2026;
    int aniVechime = anCurent - getDataAngajare().getAn();
    double bonus = 0.05 * salariuBaza;

    int salariuActual;
    salariuActual = salariuBaza + bonus * (aniVechime / 3);
    //prima de transport
    if(orasDomiciliu != "Bucuresti" && orasDomiciliu.size() != 0)
        salariuActual += 400.0;
    return salariuActual;
}

void echipa_service:: afisare(ostream& out) const{
    out << "ID: " << id << "\n";
    out << "Nume: " << nume << "\n";
    out << "Prenume: " << prenume << "\n";
    out << "CNP: " << cnp << "\n";
    out << " Data angajarii: " << dataAngajare << "\n";
    out << "Oras domiciliu: " << orasDomiciliu << "\n";
    out << "Salariu: " << salariu() << "\n";
}

ostream& operator<< (ostream& out, const echipa_service& e){
    e.afisare(out);
    return out;
}
