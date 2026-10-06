#include "masina_de_spalat.h"
#include <stdexcept>

//constructor fara param
masinaDeSpalat::masinaDeSpalat(): electrocasnic("Masina de spalat", "", "", 0, 0.0), capacitate(0.0){}

//constructor cu param
masinaDeSpalat::masinaDeSpalat(string ma, string mo, int af, double pc, double c)
    : electrocasnic("Masina de spalat", ma, mo, af, pc), capacitate(c){

        if (capacitate <= 0)
            throw invalid_argument("Capacitate invalida.");
}

//getter
double masinaDeSpalat::getCapacitate() const{
    return capacitate;
}

//afisare
void masinaDeSpalat:: afisare(ostream& out) const{
    out << "Masina de spalat\n";
    electrocasnic::afisare(out);
    out << "Capacitate: " << capacitate << "kg\n";
}