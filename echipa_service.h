#pragma once
#include <string>
#include <iostream>
#include "date.h"
using namespace std;

class echipa_service{
private:
    int id;
    string nume;
    string prenume;
    string cnp;
    date dataAngajare;
    string orasDomiciliu;
public:

    echipa_service();
    echipa_service(int, string, string, string, date, string);
    virtual ~echipa_service() = default;
    virtual double salariu() const;

    int getId() const;
    string getNume()const;
    string getPrenume()const;
    string getCnp()const;
    date getDataAngajare()const;
    string getOrasDomiciliu()const;

    void setNume(const string&);
    void setPrenume(const string&);

    bool cnpValid(const string&);

    virtual void afisare(ostream&) const;
    friend ostream& operator << (ostream& out, const echipa_service &e);
};