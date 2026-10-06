#pragma once
#include "electrocasnic.h"

class masinaDeSpalat: public electrocasnic{
    double capacitate; //in kg

    public:
    masinaDeSpalat();
    masinaDeSpalat(string, string, int, double, double);

    double getCapacitate() const;
    void afisare(ostream& out) const override;
};