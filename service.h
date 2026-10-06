#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <stdexcept>
#include <algorithm>
using namespace std;

#include "echipa_service.h"
#include "tehnician.h"
#include "receptioner.h"
#include "supervizor.h"

#include "electrocasnic.h"
#include "frigider.h"
#include "televizor.h"
#include "masina_de_spalat.h"

#include "cerere_reparatie.h"

struct cerereActiva{
    cerere_reparatie* c;
    tehnician* t;
    int timpRamas;
};

class service{
    //vector cu toti angajatii indiferent de postul ocupat
    vector<echipa_service* > angajati;

    //vectori separati pentru fiecare post
    vector<tehnician* > tehnicieni;
    vector<receptioner* > receptioneri;
    vector<supervizor* > supervizori;

    //vector cu toate electrocasnicele ce pot fi reparate in service
    vector<electrocasnic*> electrocasnice;

    
    vector<cerere_reparatie*>cereriValide; //vector cu toate cererile valide
    vector<cerere_reparatie> cereriInvalide; //vector cu toate cererile nereparabile
    vector<cerere_reparatie*> cereriAsteptare; //pointer la cererile valide dar care inca nu pot fi executate
    vector<cerereActiva> cereriActive; //vector de structura care contine informatiile despre cererile in lucru

    //pentru rapoarte
    tehnician* tehnicianRecord = nullptr;
    int durataMaxima = 0;
public:

    service();
    ~service();

    //GESTIUNE SERVICE--------------------------------------
    //service-ul functioneaza daca are minim 3 tehnicieni, 1 receptioner, 1 supervizor
    bool poateFunctiona() const; 

    //GESTIUNE ANGAJATI-------------------------------------

    void adaugareAngajat(echipa_service* e); //adaugare angajat
    echipa_service* cautaDupaCnp(const string& ) const; //cautarea unui angajat dupa cnp
    void stergeDupaCnp(const string& ); //stergerea unui angajat dupa cnp
    void modificaNume(const string& cnp, const string& numeNou); //modificarea numelui in cazul casatoriei
    void afiseazaAngajati(ostream& out) const;

    //getteri
   const vector<tehnician* >& getTehnicieni() const;
   const vector<receptioner* >& getReceptioneri() const;
   const vector<supervizor* >& getSupervizori() const;

   //GESTIUNE ELECTROCASNICE-------------------------------------

   void adaugaElectrocasnic(electrocasnic* e);
   void stergeElectrocasnic(const string& tip, const string& marca, const string& model);
   //cauta un electrocasnic in lista
   const electrocasnic* cautaElectrocasnic(const string& tip, const string& marca, const string& model)const;
   void afiseazaElectrocasnice(ostream& out) const;

   struct AparatNereparabil{
    string tip, marca, model;
    int nrAparitii;
   };

   void afiseazaElectrocasniceNereparabile(ostream& out) const;

   //GESTIUNE CERERI-------------------------------------
   
   //inregistreaza o cerere in sistem(indiferent de tipul ei), si adauga id-ul ei in lista receptionerului
   void inregistreazaCerere(const cerere_reparatie& c, receptioner& r);

   //simularea/afisarea reparatiilor pana la timpMax unitati
   void simuleazaReparatii(int timpMax, ostream& out);

   //alege tehnicianul potrivit
   tehnician* alegeTehnician(const cerere_reparatie& c) const;

   //numara cererile active ale unui tehnician
   int nrCereriActive(tehnician* t) const;

   //suma timpului ramas pt un tehnician
   int timpRamasTehnician(tehnician* t)const;


   //pentru rapoarte
   void raportTop3Salarii(const string& numeFisier) const;
   void raportTehnicianDurataMax(const string& numeFisier) const;
   void raportCereriAsteptare(const string& numeFisier) const;
};