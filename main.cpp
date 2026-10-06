#include <iostream>
#include <limits>
#include <stdexcept>

#include "io_fisier.h"
#include "service.h"
using namespace std;

void meniuAngajati(service& s) {
    int optiune;
    do {
        cout << "\n------------ GESTIUNE ANGAJATI ------------\n";
        cout << "1. Adauga angajat\n";
        cout << "2. Modifica nume angajat (dupa CNP)\n";
        cout << "3. Sterge angajat\n";
        cout << "4. Afiseaza toti angajatii\n";
        cout << "0. Inapoi\n";

        cin >> optiune;
        if (optiune == 1){ //adaugare angajat

            cout << "Alege tipul angajatului: \n";
            cout << "1. Receptioner\n";
            cout << "2. Tehnician\n";
            cout << "3. Supervizor\n";

            int tip;
            cin >> tip;
            
            int id, zi, luna, an;
            string nume, prenume, cnp, oras;

            cout << "ID: ";
            cin >> id;
            cin.ignore();

            cout << "Nume: ";
            getline(cin, nume);

            cout << "Prenume: ";
            getline(cin, prenume);

            cout << "CNP: ";
            getline(cin, cnp);

            cout << "Data angajarii (zi luna an): ";
            cin >> zi >> luna >> an;
            cin.ignore();

            cout << "Oras domiciliu: ";
            getline(cin, oras);

            try{
                date d(zi, luna, an);
                echipa_service* e = nullptr;

                if (tip == 1)
                    e = new receptioner(id, nume, prenume, cnp, d, oras);
                else if (tip == 2)
                    e = new tehnician(id, nume, prenume, cnp, d, oras);
                else if (tip == 3)
                    e = new supervizor(id, nume, prenume, cnp, d, oras);
                else {
                    cout << "Tip invalid! Angajatul nu a putut fi creat. \n";
                    continue;
                }

                s.adaugareAngajat(e);
                cout << "Angajat adaugat cu succes.\n";
            } catch (const exception& exc){
                cout << "EROARE: Nu s-a putut adauga angajatul: " << exc.what() << endl;
            }
        } else if (optiune == 2) { //modifica nume angajat
            string cnp, numeNou;
            cin.ignore();

            cout << "CNP angajat: ";
            getline(cin, cnp);

            cout << "Nume nou: ";
            getline(cin, numeNou);

            try {
                s.modificaNume(cnp, numeNou);
                cout << "Numele a fost modificat cu succes.\n";
            } catch (const exception& exc){
                cout << "EROARE: Nu s-a putut modifica numele: " << exc.what() << endl;
            }

        } else if (optiune == 3) {
            string cnp;
            cin.ignore();

            cout << "CNP angajat de sters: ";
            getline(cin, cnp);

            try{
                s.stergeDupaCnp(cnp);
                cout << "Stergerea angajatului a fost efectuata cu succes.\n";
            } catch (const exception& exc){
                cout << "EROARE: Nu s-a putut sterge angajatul: " << exc.what() << endl;
            }
        } else if (optiune == 4) {
            cout << "\n----- Lista angajatilor: \n";
            s.afiseazaAngajati(cout);
        }

    } while (optiune != 0);
}

void meniuElectrocasnice(service& s){
    int optiune;
    do {
        cout << "\n------------ GESTIUNE ELECTROCASNICE ------------\n";
        cout << "1. Adauga model reparabil\n";
        cout << "2. Sterge model reparabil\n";
        cout << "3. Afiseaza electrocasnicele reparabile";
        cout << "0. Inapoi\n";

        cin >> optiune;

        if (optiune == 1) {
            cout << "Tipul aparatului de adaugat: \n";
            cout << "1. Frigider" << endl;
            cout << "2. Televizor" << endl;
            cout << "3. Masina de spalat" << endl;

            int tip;
            cin >> tip;
            cin.ignore();

            string marca, model;
            int an;
            double pret;

            cout << "Marca: ";
            getline(cin, marca);

            cout << "Model: ";
            getline(cin, model);

            cout << "An fabricatie: ";
            cin >> an;

            cout << "Pret de catalog: ";
            cin >> pret;

            electrocasnic* e = nullptr;

            if (tip == 1) {
                bool areCongelator;
                cout << "Are congelator? (1 = da / 0 = nu): ";
                cin >> areCongelator;

                e = new frigider(marca, model, an, pret, areCongelator);
            } else if (tip == 2) {
                double diagonala;
                cout << "Diagonala (in cm): ";
                cin >> diagonala;

                e = new televizor(marca, model, an, pret, diagonala);
            } else if (tip == 3) {
                double capacitate;
                cout << "Capacitate (kg): ";
                cin >> capacitate;

                e = new masinaDeSpalat(marca, model, an, pret, capacitate);
            } else {
                cout << "Tip invalid de electrocasnic. Electrocasnicul nu a fost adaugat.\n";
                continue;
            }

            try{
                s.adaugaElectrocasnic(e);
                 cout << "Electrocasnic adaugat in catalog.\n";
            } catch (const exception& exc){
                cout << "EROARE: Nu s-a putut adauga electrocasnicul: " << exc.what() << endl;
            }
 
        } else if (optiune == 2) {
            string tip, marca, model;
            cin.ignore();

            cout << "Tip (frigider/televizor/masina de spalat): ";
            getline(cin, tip);

            cout << "Marca: ";
            getline(cin, marca);

            cout << "Model: ";
            getline(cin, model);

            try{
                s.stergeElectrocasnic(tip, marca, model);
                cout << "Electrocasnic sters din catalog.\n";
            } catch (const exception& exc){
                cout << "EROARE: Nu s-a putut sterge electrocasnicul: " << exc.what() << endl;
            }

        } else if (optiune == 3) {
            cout << "\n------ Catalog electrocasnice reparabile ------\n";
            s.afiseazaElectrocasnice(cout);
        }

    } while (optiune != 0);
}

void meniuCereri(service& s){
    int optiune;
    do {
        cout << "\n------PROCESARE CERERI ------\n";
        cout << "1. Incarca cereri din fisier\n";
        cout << "2. Simuleaza reparatiile\n";
        cout << "0. Inapoi\n";

        cin >> optiune;

        if (optiune == 1) {
            auto& receptioneri = s.getReceptioneri();
            if (receptioneri.empty()) {
                cout << "Nu exista receptioner in service. Cererile nu pot fi inregistrate.\n";
                continue;
            }

            string numeFisier;
            cin.ignore();

            cout << "Numele fisierului din care se vor citi date (cereri_valid.txt / cereri_invalid.txt / cereri_mixt.txt): ";
            getline(cin, numeFisier);

            try{
                citesteCereri(s, *receptioneri[0], numeFisier);
                cout << "Cererile au fost incarcate cu succes.\n";
            } catch (const exception& exc){
                cout << "EROARE: Nu s-au putut citi cererile: " << exc.what() << endl;
            }
            
        } else if (optiune == 2) {
            int timpMax;
            cout << "Timpul maxim de simulare: ";
            cin >> timpMax;

            try{
                cout << "\n------ SIMULARE REPARATII ------";
                s.simuleazaReparatii(timpMax, cout);
            } catch (const exception& exc) {
                cout << "EROARE: Nu s-a putut realiza simularea: " << exc.what() << endl;
            }
        }

    } while (optiune != 0);
}

void meniuRaportare (service& s){
    int optiune;
    do{
        cout << "\n------RAPORTARI------\n";
        cout << "1. Top 3 angajati cu cel mai mare salariu\n";
        cout << "2. Tehnicianul cu cea mai de durata reparatie\n";
        cout << "3. Cererile încă în așteptare grupate pe tipuri de electrocasnice, mărci și modele (sortate alfabetic)\n";
        cout << "0. Inapoi\n";

        cin >> optiune;

        if (optiune == 1) {
            try{
                s.raportTop3Salarii("raport_top_3.csv");
                cout << "Raport generat in raport_top_3.csv\n"; 
            } catch (const exception& exc) {
                cout << "EROARE: " << exc.what() << "\n";
            }
        } else if (optiune == 2) {
            try{
                s.raportTehnicianDurataMax("raport_tehnician.csv");
                cout << "Raport generat in raport_tehnician.csv\n";
            } catch (const exception& exc) {
                cout << "EROARE: " << exc.what() << "\n";
            }
        } else if (optiune == 3) {
            try {
                s.raportCereriAsteptare("raport_cereri.csv");
                cout << "Raport generat in raport_cereri.csv\n";
            } catch (const exception& exc) {
                cout << "EROARE: " << exc.what() << "\n";
            }

        } else if (optiune == 0){
            break;
        } else {
            cout << "Optiune inexistenta.\n";
        }
    } while (optiune != 0);
}

void meniuPrincipal(service& s){
    int optiune;
    do{
        cout << "\n------------ MENIU PRINCIPAL ------------\n";
        cout << "1. Gestiune angajati\n";
        cout << "2. Gestiune electrocasnice\n";
        cout << "3. Procesare cereri\n";
        cout << "4. Raportare\n";
        cout << "0. Iesire\n";
        cout << "------------------------------------------";

        cin >> optiune;

        if (optiune == 1)
            meniuAngajati(s);
        else if (optiune == 2)
            meniuElectrocasnice(s);
        else if (optiune == 3)
            meniuCereri(s);
        else if (optiune == 4)
            meniuRaportare(s);
        else if (optiune == 0)
        {
            cout << "Iesire din aplicatie.\n";
            break;
        }
        else 
            cout << "Optiunea este inexistenta. Alege un numar de la 0-4" << endl;
            

    }while (optiune != 0);
}


int main() {

    service s;
    citesteAngajati(s, "tests/angajati_mixt.txt");

    auto& tehnicieni = s.getTehnicieni();
    for (auto t = tehnicieni.begin(); t != tehnicieni.end(); t++) {
        
        (*t)->adaugSpecializare("Televizor", "Samsung");
        (*t)->adaugSpecializare("Televizor", "LG");
        (*t)->adaugSpecializare("Televizor", "Sony");
        
        (*t)->adaugSpecializare("Frigider", "Arctic");
        (*t)->adaugSpecializare("Frigider", "Beko");
        (*t)->adaugSpecializare("Frigider", "Samsung");

        (*t)->adaugSpecializare("Masina de spalat", "Whirlpool");
        (*t)->adaugSpecializare("Masina de spalat", "Indesit");

        (*t)->adaugSpecializare("Masina de spalat", "Bosch");
    }

    citesteElectrocasnice(s, "tests/electrocasnice_valid.txt");

    auto& receptioneri = s.getReceptioneri();
    if (!receptioneri.empty()){
        citesteCereri(s, *receptioneri[0], "tests/cereri_valid.txt");
    }
    else {
        cout << "Nu exista receptioner." << endl;
    }

    meniuPrincipal(s);
    return 0;
}