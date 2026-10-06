#pragma once
#include "echipa_service.h"
#include <string>
#include <iostream>
#include <stdexcept>
#include <list>
using namespace std;

class receptioner: public echipa_service{
    list<int> cereri;
    public:
    receptioner();
    receptioner(int, const string&, const string&, const string&, const date&, const string&);
    void adaugaCerere(int idCerere);
    void afisare(ostream& out) const override;

};