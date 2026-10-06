#include "frigider.h"

//constructor fara parametrii
frigider::frigider(): electrocasnic("Frigider", "", "", 0, 0.0), areCongelator(0){}

//constructor cu parametrii
frigider::frigider(string ma, string mo, int af, double pc, bool ac)
    : electrocasnic("Frigider", ma, mo, af, pc), areCongelator(ac){}

//getter
bool frigider:: getAreCongelator() const{
    return areCongelator;
}

//afisare
void frigider:: afisare(ostream& out) const{
    out << "Frigider \n";
    electrocasnic::afisare(out);
    if (areCongelator)
        out << "Are congelator\n";
    else
        out << "Nu are congelator\n";
}