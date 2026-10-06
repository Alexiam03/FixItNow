#pragma once
#include "electrocasnic.h"

class frigider: public electrocasnic{
    bool areCongelator;

    public:
    frigider();
    frigider(string, string, int, double, bool);
    bool getAreCongelator() const;
    void afisare(ostream& out)const override;
};