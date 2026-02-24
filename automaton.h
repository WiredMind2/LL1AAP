#ifndef ANALYSEUR_H
#define ANALYSEUR_H

#include <iostream>
#include <deque>
#include <map>
#include <string>
#include "symbole.h"

#ifndef DEBUG
#define DEBUG 0
#endif
const bool DEBUG_ENABLED = (DEBUG != 0);

extern const std::string IdentificateursLabels[];

typedef std::deque<Identificateurs> Pile;

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

inline std::ostream &operator<<(std::ostream &os, const Pile &p)
{
    for (Pile::const_iterator i = p.begin(); i != p.end(); i++)
    {
        os << IdentificateursLabels[*i] << " ";
    }
    return os;
}

typedef std::map<Identificateurs, std::map<Identificateurs, Identificateurs>> Transitions;

bool Existe(Transitions &t, Identificateurs i, Identificateurs j);

bool automaton(const std::deque<SymbolValue> &mot, Transitions &transitions, Identificateurs axiome);

#endif // ANALYSEUR_H
