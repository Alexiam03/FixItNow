#pragma once
#include <string>
#include <iostream>
#include "echipa_service.h"
using namespace std;

class supervizor : public echipa_service{
    public:
    supervizor();
    supervizor(int, const string&, const string&, const string&, const date&, const string&);

    double salariu() const override;
    void afisare(ostream& out )const override;
};