#pragma once
#include "electrocasnic.h"

class televizor: public electrocasnic{
    double diagonala; //in cm

    public:
    televizor();
    televizor(string, string, int, double, double);

    double getDiagonala() const;
    void afisare(ostream& out) const override;
};