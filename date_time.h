#pragma once
#include "date.h"
#include <iostream>
#include <stdexcept>
using namespace std;

class dateTime{
    date data;
    int ora;
    int minut;
    int secunda;

    public:
        dateTime();
        dateTime(const date&, int, int, int);

        const date& getDate() const;
        int getOra() const;
        int getMinut() const;
        int getSecunda() const;

        bool operator<(const dateTime& dt) const;

        friend ostream& operator<<(ostream& out, const dateTime& dt);
};