#pragma once
#include <string>
#include <iostream>
#include <string>
#include "service.h"
#include "receptioner.h"

using namespace std;

void citesteAngajati(service& s, const string& numeFisier);
void citesteElectrocasnice(service& s, const string& numeFisier);
void citesteCereri(service& s, receptioner& r, const string& numeFisier);
