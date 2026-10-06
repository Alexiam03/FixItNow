#include "receptioner.h"
#include <iostream>
using namespace std;

//constructor fara param
receptioner::receptioner() : echipa_service(){}

//constr cu param
receptioner::receptioner(int i, const string& n, const string& p, const string& c, const date& da, const string& o)
    : echipa_service(i, n, p, c, da, o){}

//afisare
void receptioner::afisare(ostream& out) const{
    out <<"Receptioner \n";

    echipa_service::afisare(out);
    out << "Cereri inregistrate: ";

    if (cereri.empty()) {
        out << "nicio cerere";
    } else {
        list <int>::const_iterator it = cereri.begin();
        while(it != cereri.end())
            {
                out << *it << " ";
                it++;
            }
    }
}

//inregistrarea unei cereri in lista
void receptioner::adaugaCerere(int idCerere){
    cereri.push_back(idCerere);
}