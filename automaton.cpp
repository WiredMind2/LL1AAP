#include <iostream>
#include <deque>
#include <map>
#include "automaton.h"
using namespace std;

// Array of string labels for the different symbols (terminals and non-terminals) used in the grammar
// (Moved to symbole.h)

// Helper functions to create a stack (Pile) from 1, 2, or 3 symbols.
// These are typically used to push the right-hand side of a production rule onto the stack.
Pile mkPile(Identificateurs t1, Identificateurs t2, Identificateurs t3)
{
    Pile p;
    p.push_front(t3);
    p.push_front(t2);
    p.push_front(t1);
    return p;
}
Pile mkPile(Identificateurs t1, Identificateurs t2)
{
    Pile p;
    p.push_front(t2);
    p.push_front(t1);
    return p;
}
Pile mkPile(Identificateurs t)
{
    Pile p;
    p.push_front(t);
    return p;
}
Pile mkPile()
{
    Pile p;
    return p;
}

// Overload the << operator to easily print the contents of a Pile (stack or input queue)
ostream &operator<<(ostream &os,
                    const Pile &p)
{
    Pile::const_iterator i;
    for (i = p.begin(); i != p.end(); i++)
    {
        os << IdentificateursLabels[*i] << " ";
    }
    return os;
}

// Function to print a Pile to standard output
void AffichePile(Pile p)
{
    Pile::iterator i;
    for (i = p.begin(); i != p.end(); i++)
    {
        cout << IdentificateursLabels[*i] << " ";
    }
}

// Checks if a transition exists in the parsing table for a given non-terminal 'i' and terminal 'j'
bool Existe(Transitions &t, Identificateurs i, Identificateurs j)
{
    return (t.find(i) != t.end()) and
           (t[i].find(j) != t[i].end());
}

struct Rule {
    Identificateurs lhs;
    int rhsLen;
};

const Rule rules[] = {
    {ERREUR, 0}, 
    {E, 1},      // R1: E' -> E
    {E, 3},      // R2: E -> E + E
    {E, 3},      // R3: E -> E * E
    {E, 3},      // R4: E -> ( E )
    {E, 1}       // R5: E -> val
};

// Fonction principale pour l'analyseur Decalage-Reduction (LR)
bool LL1AAP(const std::deque<SymbolValue> &mot,
            Transitions &transitions,
            Identificateurs axiome)
{
    Etat etat;
    // etat initial de l'automate
    etat.pile.push_front(S0);
    
    etat.alire = mot;
    if (etat.alire.empty() || etat.alire.back().id != FIN)
    {
        etat.alire.push_back({FIN, 0});
    }

    while (true)
    {
        Identificateurs s = etat.pile.front(); 
        Identificateurs a = etat.alire.front().id;
        int valA = etat.alire.front().value;

        cout << "Etat : " << IdentificateursLabels[s] << " | Lookahead : " << IdentificateursLabels[a] << endl;

        if (!Existe(transitions, s, a))
        {
            cout << "Transition non trouvee pour l'etat " << IdentificateursLabels[s] << " et le symbole " << IdentificateursLabels[a] << endl;
            return false;
        }

        Pile action = transitions[s][a];

        if (action.empty())
        {
            if (a == FIN) {
                cout << "Succes : Mot reconnu" << endl;
                if (!etat.valStack.empty()) {
                    cout << "Resultat : " << etat.valStack.front() << endl;
                }
                return true;
            }
            return false;
        }

        Identificateurs target = action.front();

        // DeCALAGE (SHIFT)
        if (target >= S0 && target <= S9)
        {
            cout << "Decalage " << IdentificateursLabels[target] << endl;
            etat.pile.push_front(a);      
            etat.pile.push_front(target); 
            etat.valStack.push_front(valA);
            etat.alire.pop_front();       
        }
        // ReDUCTION (REDUCE)
        else if (target >= R1 && target <= R5)
        {
            int ruleIndex = target - R1 + 1;
            Rule r = rules[ruleIndex];
            cout << "Reduction Regle " << ruleIndex << " (LHS: " << IdentificateursLabels[r.lhs] << ", Longueur: " << r.rhsLen << ")" << endl;

            // Recuperation des valeurs associees aux symboles reduits
            std::deque<int> ruleVals;
            for (int i = 0; i < r.rhsLen; i++) {
                ruleVals.push_front(etat.valStack.front());
                etat.valStack.pop_front();
            }

            // Calcul semantique selon la regle
            int res = 0;
            switch(ruleIndex) {
                case 1: res = ruleVals[0]; break; // E' -> E
                case 2: res = ruleVals[0] + ruleVals[2]; break; // E -> E + E
                case 3: res = ruleVals[0] * ruleVals[2]; break; // E -> E * E
                case 4: res = ruleVals[1]; break; // E -> ( E )
                case 5: res = ruleVals[0]; break; // E -> val
            }

            // Depilement de 2 * rhsLen (paires etat/symbole)
            for (int i = 0; i < 2 * r.rhsLen; ++i)
            {
                if (etat.pile.empty()) return false;
                etat.pile.pop_front();
            }

            // Regarder l'etat maintenant au sommet de la pile
            Identificateurs s_prev = etat.pile.front();
            
            // Recherche de la transition GOTO(s_prev, lhs)
            if (!Existe(transitions, s_prev, r.lhs)) {
                cout << "Erreur GOTO : Pas de transition pour le non-terminal " << IdentificateursLabels[r.lhs] << " dans l'etat " << IdentificateursLabels[s_prev] << endl;
                return false;
            }

            Identificateurs s_next = transitions[s_prev][r.lhs].front();
            cout << "Goto " << IdentificateursLabels[s_next] << endl;
            
            etat.pile.push_front(r.lhs);   
            etat.pile.push_front(s_next);  
            etat.valStack.push_front(res);
        }
        else if (target == FIN || target == END)
        {
             cout << "Succes : Mot reconnu" << endl;
             if (!etat.valStack.empty()) {
                 cout << "Resultat : " << etat.valStack.front() << endl;
             }
             return true;
        }
        
        cout << "Pile : " << etat.pile << endl;
    }
}
