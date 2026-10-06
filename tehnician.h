#pragma once
#include <list>
#include <string>
#include <iostream>
#include "echipa_service.h"
using namespace std;

struct repar{
    string tip;
    string marca;
};

class tehnician: public echipa_service{
    list<repar> reparatii;
    //totalul valorilor reparatiilor efectuate de tehnician
    double valoareReparatii;

    public:
    tehnician();
    tehnician(int, const string&, const string&, const string&, const date&, const string&);
    
    void adaugSpecializare(const string&, const string&);
    bool poateRepara(const string&, const string&) const;
    void adaugReparatie(double);

    double salariu() const override;
    void afisare(ostream& out) const override;
};