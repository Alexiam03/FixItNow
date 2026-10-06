#include "supervizor.h"
#include <string>
#include <iostream>
using namespace std;

//constructor fara param
supervizor::supervizor(): echipa_service(){}

//constructor cu param
supervizor:: supervizor(int i, const string& n, const string& p, const string& c, const date& da, const string& o)
    : echipa_service(i, n, p, c, da, o){}

double supervizor::salariu() const{
    double salariuBaza = 4000.0;
    double salariu = echipa_service::salariu();

    //spor de conducere 20% din salariul de baza
    salariu += 0.20 * salariuBaza;
    return salariu;
}

void supervizor::afisare(ostream& out) const{
    out << "Supervizor \n";
    echipa_service::afisare(out);
}