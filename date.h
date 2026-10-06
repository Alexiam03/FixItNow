#pragma once
#include <iostream>
using namespace std;

class date{
    private:
        int zi, luna, an;
    public:
        date();
        date(int zi, int luna, int an);

        int getZi() const;
        int getLuna() const;
        int getAn() const;

        friend ostream& operator <<(ostream& out, const date& d);
};