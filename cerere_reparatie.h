#pragma once
#include <string>
#include <iostream> 
#include <stdexcept>
#include "date_time.h"
#include "electrocasnic.h"
using namespace std;

class cerere_reparatie{
    int id;
    string tip;
    string marca;
    string model;
    dateTime timestamp;

    //0 = nu poate fi reparat, altfel 1-5
    int complexitate;

    //durata = vechimea aparatului * complexitate
    int durataReparatie;

    //pret = pretul de catalog al aparatului * durata estimata
    double pretReparatie;

    public:
    cerere_reparatie();
    cerere_reparatie(int, string, string, string, dateTime);

    //calculam campurile necesare
    void setComplexitate(int c);
    void calculeazaDurataPret(const electrocasnic* e);

    //getteri
    int getId() const;
    string getTip() const;
    string getMarca() const;
    string getModel() const;
    dateTime getTimestamp() const;
    int getComplexitate() const;
    int getDurata() const;
    double getPret() const;

    //afisare
    void afisare(ostream& out) const;
    friend ostream& operator<<(ostream& out, cerere_reparatie& c);

};