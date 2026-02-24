#ifndef ANALYSEUR_H
#define ANALYSEUR_H

#include <iostream>
#include <deque>
#include <map>
#include <string>
#include "symbole.h"

extern const std::string IdentificateursLabels[];

typedef std::deque<Identificateurs> Pile;

Pile mkPile(Identificateurs t1, Identificateurs t2, Identificateurs t3);
Pile mkPile(Identificateurs t1, Identificateurs t2);
Pile mkPile(Identificateurs t);
Pile mkPile();

struct SymbolValue {
    Identificateurs id;
    int value;
};

struct Etat
{
    Pile pile;
    std::deque<int> valStack; 
    std::deque<SymbolValue> alire;
};

std::ostream &operator<<(std::ostream &os, const Pile &p);

void AffichePile(Pile p);

typedef std::map<Identificateurs, std::map<Identificateurs, Pile>> Transitions;

bool Existe(Transitions &t, Identificateurs i, Identificateurs j);

bool LL1AAP(const std::deque<SymbolValue> &mot, Transitions &transitions, Identificateurs axiome);

#endif // ANALYSEUR_H
