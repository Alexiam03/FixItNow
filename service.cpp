#include "service.h"
#include <algorithm>
#include <fstream>
//constructor fara param
service::service(){}

//destructor
service::~service() {
    //STERGEREA ANGAJATILOR
    for (auto it = angajati.begin(); it != angajati.end(); it++)
        delete *it;
    angajati.clear();

    //STERGEREA ELECTROCASNICELOR  
    for (auto it = electrocasnice.begin(); it != electrocasnice.end(); it++)
        delete *it;
    electrocasnice.clear();

    //STERGEREA CERERILOR VALIDE
    for (auto it = cereriValide.begin(); it != cereriValide.end(); it++)
        delete *it;
    cereriValide.clear();
}

//verif daca service-ul poate functiona
bool service::poateFunctiona() const {
    if (tehnicieni.size() >= 3 && receptioneri.size() >= 1 && supervizori.size() >= 1)
        return true;
    else
        return false;
}

//GESTIUNE ANGAJATI-------------------------------------

//adaugare angajat
void service::adaugareAngajat(echipa_service* e){
    if (e == nullptr)
        throw invalid_argument("Angajatul este null.");

    angajati.push_back(e);

    tehnician* t = dynamic_cast<tehnician*>(e);
    receptioner* r = dynamic_cast<receptioner*>(e);
    supervizor* s = dynamic_cast<supervizor*>(e);
    if (t != nullptr )
        tehnicieni.push_back(t);
    else if (r != nullptr)
        receptioneri.push_back(r);
    else if (s != nullptr)
        supervizori.push_back(s);
}

//cauta un angajat dupa cnp
echipa_service* service::cautaDupaCnp(const string& cnp) const{
    for (auto it = angajati.begin(); it != angajati.end(); it++)
        if((*it)->getCnp() == cnp)
            return (*it);

    return nullptr;
}

//sterge un angajat dupa cnp
void service::stergeDupaCnp(const string& cnp){
    for (auto it = angajati.begin(); it != angajati.end(); it++)
        {
                if((*it)->getCnp() == cnp)
            {

                tehnician* t = dynamic_cast<tehnician*>(*it);
                receptioner* r = dynamic_cast<receptioner*>(*it);
                supervizor* s = dynamic_cast<supervizor*>(*it);

                if (t != nullptr )
                    {
                        auto i = tehnicieni.begin();
                        while(i != tehnicieni.end())
                        {
                            if (*i == t)
                                i = tehnicieni.erase(i);
                            else
                                i++;
                        }
                    }
                else if (r != nullptr)
                {
                        auto i = receptioneri.begin();
                        while(i != receptioneri.end())
                        {
                            if (*i == r)
                                i = receptioneri.erase(i);
                            else
                                i++;
                        }
                    }
                else if (s != nullptr)
                {
                        auto i = supervizori.begin();
                        while(i != supervizori.end())
                        {
                            if (*i == s)
                                i = supervizori.erase(i);
                            else
                                i++;
                        }
                }

                delete *it;
                //scoatem din lista cu toti angajatii
                it = angajati.erase(it);
                return;
            }
        }
}

//modificarea numelui
void service::modificaNume(const string& cnp, const string& numeNou){
    echipa_service* e = cautaDupaCnp(cnp);

    if (e == nullptr)
        throw runtime_error("Nu exista angajat cu acest CNP.");
    else
        e->setNume(numeNou);
}

//afisare lista angajati
void service::afiseazaAngajati(ostream& out) const{
    if (angajati.empty()) {
        out << "Nu exista angajati.\n";
    }
    else{
        out << "Lista angajati: \n";
        for( auto it = angajati.begin(); it != angajati.end(); it++)
            out << **it << "\n";
    }
}

//getteri
const vector<tehnician* >& service:: getTehnicieni() const{
    return tehnicieni;
}

const vector<receptioner* >& service:: getReceptioneri() const{
    return receptioneri;
}

const vector<supervizor* >& service:: getSupervizori()const{
    return supervizori;
}

//GESTIUNE ELECTROCASNICE-------------------------------------

//adauga un electrocasnic intr-o lista
void service::adaugaElectrocasnic(electrocasnic* e) {
    if (e == nullptr)
        throw invalid_argument("Electrocasnicul este null.");
    electrocasnice.push_back(e);
}

//sterge un electrocasnic dintr-o lista
void service::stergeElectrocasnic(const string& tip, const string& marca, const string& model) {
    for( auto it = electrocasnice.begin(); it != electrocasnice.end(); it++)
    {
        electrocasnic* e = *it;
        if ( e->getTip() == tip && e->getMarca() == marca && e->getModel() == model)
        {
            delete e;
            electrocasnice.erase(it);
            return;
        }
    }
}

//cauta un electrocasnic intr-o lista
const electrocasnic* service:: cautaElectrocasnic(const string& tip, const string& marca, const string& model) const{
    for(auto it = electrocasnice.begin(); it != electrocasnice.end(); it++ )
    {
        electrocasnic* e = *it;
        if ( e->getTip() == tip && e->getMarca() == marca && e->getModel() == model)
            return e;
    }

    return nullptr;
}

//afiseaza lista cu toate electrocasnicele
void service::afiseazaElectrocasnice(ostream& out) const{
    if (electrocasnice.empty()) 
        out << "Vectorul cu electrocasnice este gol.\n";
    else {
        out << "Lista cu electrocasnicele reparabile: \n";
        for(auto it = electrocasnice.begin(); it != electrocasnice.end(); it++ )
        {
            electrocasnic* e = *it;
            out << *e << "\n";
        }
    }
}

//afiseaza lista cu toate electrocasnicele care nu au putut fi reparate (solicitate in cereri)
void service:: afiseazaElectrocasniceNereparabile(ostream& out) const{
    if (cereriInvalide.empty())
        out << "Nu exista aparate care nu au putut fi reparate.\n";
    else {
        vector<AparatNereparabil> ap;

        for (auto itc = cereriInvalide.begin(); itc != cereriInvalide.end(); itc++)
        {
            //presupunem ca nu am gasit nimic la inceput
            bool gasit = false;

            for (auto ita = ap.begin(); ita != ap.end(); ita++)
            {
                if ((*ita).tip == (*itc).getTip() && (*ita).marca == (*itc).getMarca() && (*ita).model == (*itc).getModel())
                    {
                        (*ita).nrAparitii ++;
                        gasit = true;
                        break;
                    }
            }

            if (gasit == false)
            {
                AparatNereparabil s;
                s.tip = (*itc).getTip();
                s.marca = (*itc).getMarca();
                s.model = (*itc).getModel();
                s.nrAparitii = 1;
                ap.push_back(s);
            }
        }

        //sortam descrescator dupa nr aparitii
            sort(ap.begin(), ap.end(),
                     [](const AparatNereparabil& a, const AparatNereparabil& b){
                        return a.nrAparitii > b.nrAparitii;
                     });

        //afisarea
        out << "Aparate din cereri care nu au putut fi reparate.\n";
        for (auto it = ap.begin(); it != ap.end(); it++)
        {
            out << "Tip: " << (*it).tip;
            out << ", Marca: " << (*it).marca;
            out << ", Model: " << (*it).model;
            out << ", Aparitii: " << (*it).nrAparitii << "\n";
        }

    }
}

//GESTIUNE CERERI-------------------------------------

//numara cererile active ale unui tehnician
int service::nrCereriActive(tehnician* t) const{
    int cnt = 0;
    for( auto it = cereriActive.begin(); it != cereriActive.end(); it++)
        if((*it).t == t)
            cnt++;
    return cnt;
}

//calculeaza timpul ramas de lucru al unui tehnician
int service::timpRamasTehnician(tehnician* t) const{
    int suma = 0;
    for( auto it = cereriActive.begin(); it != cereriActive.end(); it++)
        if((*it).t == t)
            suma += (*it).timpRamas;
    return suma;
}

//alegerea tehnicianului potrivit in functie de tipul electrocasnicului si/sau de incarcarea de lucru
tehnician* service::alegeTehnician(const cerere_reparatie& c) const{
    tehnician* ales = nullptr;
    int incarcare = 0; //in minute

    for(auto it = tehnicieni.begin(); it != tehnicieni.end(); it++)
    {
        //verificam daca poate repara acel electrocasnic
        if ((*it)->poateRepara(c.getTip(), c.getMarca()))
        {
            int nrActive = nrCereriActive(*it);
            //verificam sa nu aiba mai mult de 3 cereri active sau chiar 3 cereri active
            if(nrActive < 3)
            {
                int timp = timpRamasTehnician(*it);
                if (ales ==nullptr || timp < incarcare)
                    {
                        ales = *it;
                        incarcare = timp;
                    }
            }
        }
    }

    return ales;
}

void service:: inregistreazaCerere(const cerere_reparatie& c, receptioner& r){
    //adaugam in lista receptionerului doar id-ul cererii
    r.adaugaCerere(c.getId());

    //cereri invalide
    if (c.getComplexitate() == 0)
        cereriInvalide.push_back(c);
    else{
        //cerere valida
        cerere_reparatie* copie = new cerere_reparatie(c);
        cereriValide.push_back(copie);
        cereriAsteptare.push_back(copie);

    }
}

void service::simuleazaReparatii(int timpMax, ostream& out){
    //sortam cererile in asteptare dupa timestamp
    sort(cereriAsteptare.begin(), cereriAsteptare.end(),
        [](cerere_reparatie* a, cerere_reparatie* b){
            return a->getTimestamp() < b->getTimestamp();
        });

    for (int timp = 1; timp <= timpMax; timp++)
    {
        out << "[Timp " << timp << "]\n";

        //procesam cererile active
        for (auto it = cereriActive.begin(); it != cereriActive.end(); it++)
        {
            (*it).timpRamas--;
            if ((*it).timpRamas > 0)
            {
                out << "Tehnician " << (*it).t->getId();
                out <<" proceseaza cererea cu id " << (*it).c->getId();
                out << " (raman " << (*it).timpRamas << " minute)\n";
            }
        }

        //finalizam cererile ajunse la timpul de executie = 0
        for (auto it = cereriActive.begin(); it != cereriActive.end(); )
        {
            if((*it).timpRamas <= 0)
            {
                out << "Tehnician " << (*it).t->getId();
                out << " finalizeaza cererea " << (*it).c->getId() << "\n";

                //adaugam valoarea reparatiei la tehnician pentru bonusul la salariu
                (*it).t->adaugReparatie((*it).c->getPret());

                //stergem cererea care tocmai a fost procesata
                it = cereriActive.erase(it);
            }
            else
                it++;
        }

        //alocam cererile din lista de asteptare
        //bool daca am reusit sa atribuim cuiva vreo cerere
        bool atribuit = true;
        while (atribuit && !cereriAsteptare.empty())
        {
            atribuit = false;

            //luam prima cerere din asteptare(adica cea mai veche ptc le am sortat in functie de timestamp)
            cerere_reparatie* c = cereriAsteptare.front();
            tehnician* tech = alegeTehnician(*c);

            if (tech != nullptr)
            {//am gasit tehnician => facem atribuirea

                cerereActiva ca;
                ca.c = c;
                ca.t = tech;
                ca.timpRamas = c->getDurata();

                cereriActive.push_back(ca);

                out << " Tehnician " << tech->getId() << " primeste cererea " << c->getId() << "\n";
                
                //stergem cererea din lista de asteptare
                cereriAsteptare.erase(cereriAsteptare.begin());
                atribuit = true;

                //doar pt raportul final
                if (c->getDurata() > durataMaxima){
                    durataMaxima = c->getDurata();
                    tehnicianRecord = tech;
                }
            }
            else //nu exista tehnician pentru prima cerere => ne oprim si nu sarim peste ea
                break;
        }

        //afisam la final cererile in asteptare
        out << " Cereri in asteptare: ";
        if (cereriAsteptare.empty())
            out << "-";
        else {
            for (auto it = cereriAsteptare.begin(); it != cereriAsteptare.end(); it++)
                out << (*it)->getId() << " ";
        }
        out << "\n\n";

        //daca nu mai e nimic de procesat ne oprim
        if (cereriActive.empty() && cereriAsteptare.empty())
            break; 
    }
}

//rapoarte

void service :: raportTop3Salarii(const string& numeFisier) const {
    ofstream fout(numeFisier);
    if (!fout.is_open()){
        throw runtime_error("Nu s-a putut deschide fisierul\n");
    }

    struct top{
        int id;
        string nume, prenume, cnp;
        double salariu;
    };

    vector <top> v;
    for(auto it = angajati.begin(); it != angajati.end(); it++)
    {
        top ang;
        ang.id = (*it)->getId();
        ang.nume = (*it)->getNume();
        ang.prenume = (*it)->getPrenume();
        ang.cnp = (*it)->getCnp();
        ang.salariu = (*it)->salariu();

        v.push_back(ang);
    }

    if (v.empty()) {
        cout << "Nu exista angajati.\n";
        return;
    }

    //sortare dupa salariu descrescator
    sort(v.begin(), v.end(), [](const top&a, const top& b){
        return a.salariu > b.salariu;
    });

    //pastram doar primii 3
    if (v.size() > 3)
        v.resize(3);

    //acum ii ordonam alfabetic
    sort(v.begin(), v.end(), [](const top& a, const top& b){
        if (a.nume == b.nume)
            return a.prenume < b.prenume;
        return a.nume < b.nume;
    });

    //scriem in fisier
    for (auto it = v.begin(); it != v.end(); it++)
        fout << (*it).id << ", " << (*it).nume << ", " << (*it).prenume << ", " << (*it).cnp << ", " << (*it).salariu << "\n";
    
}

void service:: raportTehnicianDurataMax(const string& numeFisier) const{
    ofstream fout(numeFisier);
    if (!fout.is_open()){
        throw runtime_error("Nu s-a putut deschide fisierul \n");
    }

    if (tehnicianRecord != nullptr) {
        fout << tehnicianRecord->getId() << ", " << tehnicianRecord->getNume() << ", " <<tehnicianRecord->getPrenume() << ", " <<tehnicianRecord->getCnp() << ", " <<tehnicianRecord->salariu() << ", cu durata maxima de: " << durataMaxima << "\n";
    } else {
        fout << "Nu s-au efectuat reparatii inca. \n";
    }

    fout.close();
}

void service:: raportCereriAsteptare(const string& numeFisier) const{
    ofstream fout(numeFisier);
    if (!fout.is_open()) {
        throw runtime_error("Nu s-a putut deschide fisierul.\n");
    }

    if (cereriAsteptare.empty())
    {
        fout << "Nu exista cereri in asteptare.\n";
        return;
    }

    struct grup {
        string tip, marca, model;
        int nr;
    };

    vector <grup> grupuri;

    //parcurgem cererile in asteptare si le grupam
    for (auto it = cereriAsteptare.begin(); it != cereriAsteptare.end(); it++)
    {
        if ((*it) == nullptr)
            continue;

        string tip = (*it)->getTip();
        string marca = (*it)->getMarca();
        string model = (*it)->getModel();

        bool gasit = false;
        for (auto g = grupuri.begin(); g != grupuri.end(); g++)
        {
            if ((*g).tip == tip && (*g).marca == marca && (*g).model == model)
            {
                (*g).nr++;
                gasit = true;
                break;
            }
        }

        if (gasit == false)
        {
            grup g;
            g.tip = tip;
            g.marca = marca;
            g.model = model;
            g.nr = 1;
            grupuri.push_back(g);
        }
    }

    //sortare alfabetica: dupa tip apoi marca apoi model
    sort(grupuri.begin(), grupuri.end(), [](const grup& a, const grup& b){
        if (a.tip != b.tip)
            return a.tip < b.tip;
        if (a.marca != b.marca )
            return a.marca < b.marca;
        return a.model < b.model;
    });

    //scriem in fisier
    for (auto it = grupuri.begin(); it != grupuri.end(); it++){
        fout << (*it).tip << ", " << (*it).marca << ", " << (*it).model << ", cu nr de aparitii: " << (*it).nr << "\n";
    }
}