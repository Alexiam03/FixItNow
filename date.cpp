#include "date.h"
#include <stdexcept>

//constr fara parametrii
date:: date(): zi(1), luna(1), an(2000) {}

//constr cu parametrii
date:: date(int zi, int luna, int an){
    if (an <= 0)
        throw invalid_argument("An invalid");

    if (luna < 1 || luna > 12)
        throw invalid_argument("Luna invalida");
    
    int zile[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int ziMax = zile[luna - 1];

    if (luna == 2 && ((an % 4 == 0 && an % 100 != 0) || an % 400 == 0))
        ziMax = 29; //daca e an bisect luna a 2-a are 29 de zile

    if (zi < 1 || zi > ziMax)
        throw invalid_argument("Zi invalida");
    
    this->zi = zi;
    this->luna = luna;
    this->an = an;
}

int date:: getZi() const{
    return zi;
}

int date:: getLuna() const {
    return luna;
}

int date:: getAn() const{
    return an;
}

ostream& operator <<(ostream& out, const date& d){
    out << d.zi << "-" << d.luna << "-" << d.an;
    return out;
}