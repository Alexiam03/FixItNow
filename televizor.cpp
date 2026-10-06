#include "televizor.h"

//constructor fara param
televizor::televizor() : electrocasnic("Televizor", "", "", 0, 0.0), diagonala(0.0){}

//constructor cu param
televizor::televizor(string ma, string mo, int af, double pc, double d)
    : electrocasnic("Televizor", ma, mo, af, pc), diagonala(d){
        if(diagonala <= 0)
            throw invalid_argument("Diagonala invalida.");
}

//getter
double televizor:: getDiagonala() const{
    return diagonala;
}

//afisare
void televizor:: afisare(ostream& out) const{
    out << "Televizor\n";
    electrocasnic::afisare(out);
    out << "Diagonala: " << diagonala << "cm\n";
}