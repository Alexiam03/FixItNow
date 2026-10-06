#include "cerere_reparatie.h"

//constructor fara param
cerere_reparatie::cerere_reparatie()
    : id(0), tip(""), marca(""), model(""), timestamp(), complexitate(0), durataReparatie(0), pretReparatie(0){}

//constructor cu param
cerere_reparatie::cerere_reparatie(int i, string t, string ma, string mo, dateTime ts)
    : id(i), tip(t), marca(ma), model(mo), timestamp(ts){
        if (id <= 0)
            throw invalid_argument("Id-ul cererii este invalid.");

        if(tip.empty())
            throw invalid_argument("Tipul cererii este invalid.");
        
        if(marca.empty())
            throw invalid_argument("Marca din cerere este invalida.");

        if(model.empty())
            throw invalid_argument("Modelul din cerere este invalid");
}

//calculul campurilor
void cerere_reparatie::setComplexitate(int c){
    //0 = nu poate fi reparat
    //1-5 = complexitatea celor care pot fi reparate
    if (c < 0 || c > 5)
        throw invalid_argument("Complexitate invalida.");
    complexitate = c;
}

void cerere_reparatie::calculeazaDurataPret(const electrocasnic* e){
    //daca nu avem aparat sau complexitate = 0 => nereparabila
    if (e == nullptr || complexitate == 0)
    {
        complexitate = 0;
        durataReparatie = 0;
        pretReparatie = 0.0;
        return;
    }

    int anCerere = timestamp.getDate().getAn();
    int anFabr = e->getAn();
    int vechime = anCerere-anFabr;
    if (vechime < 1)
        vechime = 1;
    
    durataReparatie = vechime * complexitate;
    pretReparatie = e->getPret() * durataReparatie;
}

//getteri
int cerere_reparatie:: getId() const{
    return id;
}

string cerere_reparatie:: getTip() const{
    return tip;
}

string cerere_reparatie:: getMarca() const{
    return marca;
}

string cerere_reparatie:: getModel() const{
    return model;
}

dateTime cerere_reparatie:: getTimestamp() const{
    return timestamp;
}

int cerere_reparatie:: getComplexitate() const{
    return complexitate;
}

int cerere_reparatie:: getDurata() const{
    return durataReparatie;
}

double cerere_reparatie:: getPret() const{
    return pretReparatie;
}

//afisare
void cerere_reparatie:: afisare(ostream& out) const{
    out <<"ID cerere reparatie: " << id << "\n";
    out << "Data si ora depunerii: " << timestamp << "\n";
    out << "Detaliile aparatului: " << tip << " " << marca << " " << model << "\n";
    out << "Complexitatea reparatiei: " << complexitate << "\n";
    out << "Durata estimata a reparatiei: " << durataReparatie << "\n";
    out << "Pretul reparatiei: " << pretReparatie << "\n";
}

ostream& operator<<(ostream& out, cerere_reparatie& c){
    c.afisare(out);
    return out;
}