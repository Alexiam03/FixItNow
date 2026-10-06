#include "electrocasnic.h"
#include <stdexcept>

//constructor fara param
electrocasnic::electrocasnic(): tip(""), marca(""), model(""), anFabricatie(0), pretCatalog(0.0){}

//constructor cu param
electrocasnic::electrocasnic(const string& t, const string& ma, const string& mo, int af, double pc)
    :tip(t), marca(ma), model(mo), anFabricatie(af), pretCatalog(pc){

        if(tip.size() == 0)
            throw invalid_argument("Tip electrocasnic invalid.");
        if(marca.size() == 0)
            throw invalid_argument("Marca electrocasnic invalida.");
        if(model.size() == 0)
            throw invalid_argument("Model electrocasnic invalid.");
        if(anFabricatie <= 0)
            throw invalid_argument("An fabricatie invalid.");
        if(pretCatalog <= 0)
            throw invalid_argument("Pret catalog invalid.");
}

electrocasnic::~electrocasnic(){

}

//getteri
const string& electrocasnic:: getTip()const{
    return tip;
}

const string& electrocasnic:: getMarca()const{
    return marca;
}

const string& electrocasnic:: getModel()const{
    return model;
}

int electrocasnic:: getAn() const{
    return anFabricatie;
}

double electrocasnic:: getPret() const{
    return pretCatalog;
}

//afisare
void electrocasnic::afisare(ostream& out) const{
    out << "Tip: " << tip << "\n";
    out << "Marca: " << marca << "\n";
    out << "Model: " << model << "\n";
    out << "An fabricatie: " << anFabricatie << "\n";
    out << "Pret catalog: " << pretCatalog << "\n";
}

ostream& operator<<(ostream& out, const electrocasnic& e){
    e.afisare(out);
    return out;
}