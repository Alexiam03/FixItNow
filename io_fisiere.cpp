#include <fstream>
#include "io_fisier.h"

void citesteAngajati(service& s, const string& numeFisier){
    ifstream fin(numeFisier);
    if (!fin.is_open()){
        cout << "Eroare la deschiderea fisierului de angajati " << numeFisier << endl;
        return;
    }

    int id, zi, luna, an;
    char tip; //R = receptioner, T = tehnician, S = supervizor
    string nume, prenume, cnp, oras;

    while (fin >> id >> tip >> nume >> prenume >> cnp >> zi >> luna >> an >> oras)
    {
        try{
            date d(zi, luna, an);
            echipa_service* e = nullptr;

            if (tip == 'R')
                e = new receptioner(id, nume, prenume, cnp, d, oras);
            else if (tip == 'T')
                e = new tehnician(id, nume, prenume, cnp, d, oras);
            else if (tip == 'S')
                e = new supervizor(id, nume, prenume, cnp, d, oras);
            else {
                cout << "Tipul angajatului este necunoscut: " << tip << endl;
                continue;
            }

            s.adaugareAngajat(e);
        } catch (const exception& exc){
            cout << "Eroare la citirea unui angajat din fisier: " << exc.what() << endl;
        }
    }
}

void citesteElectrocasnice(service& s, const string& numeFisier){
    ifstream fin(numeFisier);
    if (!fin.is_open()) {
        cout << "Eroare la deschiderea fisierului de electrocasnice " << numeFisier << endl;
        return;
    }

    char tip;
    string marca, model;
    int an;
    double pret;
    double detaliu; //fie diagonala, capacitatea, etc

    while (fin >> tip >> marca >> model >> an >> pret >> detaliu ){
        try{
            electrocasnic* e = nullptr;

            if (tip == 'T'){
                double diagonala = detaliu;
                e = new televizor(marca, model, an, pret, diagonala);
            }
            else if ( tip == 'F'){
                bool areCongelator = detaliu;
                e = new frigider(marca, model, an, pret, areCongelator);
            }
            else if (tip == 'M'){
                double capacitate = detaliu;
                e = new masinaDeSpalat(marca, model, an, pret, capacitate);
            }
            else{
                cout << "Tipul electrocasnicului e necunoscut: " << tip << endl;
                continue;
            }

            s.adaugaElectrocasnic(e);
        } catch (const exception& exc){
            cout << "Eroare la citirea unui electrocasnic din fisier: " << exc.what() << endl;
        }
    }
}

void citesteCereri(service& s, receptioner& r, const string& numeFisier){
    ifstream fin(numeFisier);
    if (!fin.is_open()){
        cout << "Eroare la deschiderea fisierului de cereri " << numeFisier << endl;
        return;
    }

    int id, zi, luna, an, ora, minut, complexitate;
    char tip;
    string marca, model;
    
    while (fin >> id >> tip >> marca >> model >> zi >> luna >> an >> ora >> minut >> complexitate)
    {
        try{
            string nume;
            if (tip == 'T') 
                nume = "Televizor";
            else if (tip == 'F')
                nume = "Frigider";
            else if (tip == 'M')
                nume = "Masina de spalat";
            else{
                cout << "Tipul aparatului e necunoscut: " << tip << endl;
                continue;
            }

            date d(zi, luna, an);
            dateTime dt(d, ora, minut, 0);

            cerere_reparatie c(id, nume, marca, model, dt);
            c.setComplexitate(complexitate);

            const electrocasnic* e = s.cautaElectrocasnic(nume, marca, model);
            c.calculeazaDurataPret(e);

            s.inregistreazaCerere(c, r);
        } catch (const exception& exc) {
            cout << "Eroare la citirea unei cereri din fisier: " << exc.what() << endl;
        }
    }
}