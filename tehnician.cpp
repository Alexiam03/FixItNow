#include "tehnician.h"

//constr fara parametrii
tehnician::tehnician() : echipa_service(), valoareReparatii(0) {}

//constr cu parametrii
tehnician:: tehnician(int i, const string& n, const string& p, const string& c, const date& da, const string& o)
    : echipa_service(i, n, p, c, da, o), valoareReparatii(0) {}

//fctie care verif daca o marca poate fi reparata sau nu de tehnician
bool tehnician :: poateRepara(const string& tip, const string& marca) const{
    list<repar> :: const_iterator it = reparatii.begin();
    while (it != reparatii.end()) {
        if(it->tip == tip && it->marca == marca)
            return true;
        ++it;
    }

    return false;
}

//pentru a adauga noi marci si tipuri de reparat
void tehnician :: adaugSpecializare(const string& tip, const string& marca){
    if(tip.size() == 0 || marca.size() == 0)
        throw invalid_argument("Nu exista specializare noua de adaugat.");

    repar r;
    r.tip = tip;
    r.marca = marca;

    reparatii.push_back(r);
}

//adaugam pe parcurs valoarea fiecarei reparatii efectuate
void tehnician:: adaugReparatie(double valoare){
    if(valoare < 0)
        throw invalid_argument("Valoarea reparatiei e nula.");
    else
        valoareReparatii += valoare;
}

double tehnician :: salariu() const{
    double salariu = echipa_service::salariu();

    salariu += 0.02 * valoareReparatii;

    return salariu;
}

void tehnician:: afisare(ostream& out) const{
    out << "Tehnician \n";
    echipa_service::afisare(out);

    out << "Valoarea totala a reparatiilor efectuate: " << valoareReparatii << "\n";
    out << "Marcile si tipurile pe care stie sa le repare: ";

    if (reparatii.empty())
        out <<"Nicio reparatie efectuata.";
    else {
        list<repar>::const_iterator it = reparatii.begin();
        while (it != reparatii.end()) {
            out << it->marca << " model " << it->tip << "|";
            ++it;
        }
    
    out << "\n";
    }
}