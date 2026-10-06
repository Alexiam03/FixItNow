#pragma once
#include <string>
#include <iostream>
using namespace std;

class electrocasnic{
    string tip;
    string marca;
    string model;
    int anFabricatie;
    double pretCatalog;

    public:
    electrocasnic();
    electrocasnic(const string&,const string&,const string&, int, double);
    virtual ~electrocasnic();

    //getteri
    const string& getTip()const;
    const string& getMarca()const;
    const string& getModel()const;
    int getAn() const;
    double getPret()const;

    virtual void afisare(ostream& out) const;
    friend ostream& operator<<(ostream& out, const electrocasnic& e);
};