#include "date_time.h"

//constr fara parametrii
dateTime::dateTime(): data(), ora(0), minut(0), secunda(0) {}

//constr cu parametrii
dateTime::dateTime(const date& d, int o, int m, int s): data(d) {
    if(o < 0 || o > 23)
        throw invalid_argument("Ora invalida.");
    ora = o;

    if (m < 0 || m > 59)
        throw invalid_argument("Minut invalid.");
    minut = m;

    if (s < 0 || s > 59)
        throw invalid_argument("Secunda invalida.");
    secunda = s;
}

//getteri
const date& dateTime:: getDate() const{
    return data;
}

int dateTime:: getMinut() const{
    return minut;
}

int dateTime:: getOra() const{
    return ora;
}

int dateTime:: getSecunda() const{
    return secunda;
}

bool dateTime:: operator<(const dateTime &dt) const{
    if (data.getAn() != dt.data.getAn())
        return data.getAn() < dt.data.getAn();

    if (data.getLuna() != dt.data.getLuna())
        return data.getLuna() < dt.data.getLuna();

    if (data.getZi() != dt.data.getZi())
        return data.getZi() < dt.data.getZi();

    if (ora != dt.ora)
        return ora < dt.ora;

    if (minut != dt.minut)
        return minut < dt.minut;

    if (secunda != dt.secunda)
        return secunda < dt.secunda;

    return false;
}

ostream& operator <<(ostream& out, const dateTime& dt){
    out << dt.data << " ";
    out << (dt.ora < 10 ? "0" : "") << dt.ora << ":";
    out << (dt.minut < 10 ? "0" : "") << dt.minut << ":";
    out << (dt.secunda < 10 ? "0" : "") << dt.secunda;

    return out;
}