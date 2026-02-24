#include <iostream>
#include <deque>
#include <map>
#include "automaton.h"
using namespace std;

// Array of string labels for the different symbols (terminals and non-terminals) used in the grammar
const string IdentificateursLabels[] = {
    "(", ")", "+", "*", "nb", "$", "ERREUR", "E", "E'", "T", "id", "F", "T'"
};

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

// Main function for the LL(1) predictive parser (Analyseur Automate à Pile)
// Takes the input word (mot), the parsing table (transitions), and the start symbol (axiome)
bool LL1AAP(const Pile &mot,
            Transitions &transitions,
            Identificateurs axiome)
{
    Etat etat;
    // Initialize the stack with the start symbol
    etat.pile.push_front(axiome);
    // Initialize the input queue with the word to parse
    etat.alire = mot;
    Identificateurs a, b;
    
    // Ensure the input ends with the end-of-file/end-of-input marker (FIN)
    if (etat.alire.back() != FIN)
    {
        etat.alire.push_back(FIN);
    }
    
    // Loop until the stack is empty
    while (!etat.pile.empty())
    {
        a = etat.pile.front(); // Top of the stack (expected symbol)
        b = etat.alire.front(); // Front of the input (current symbol being read)
        
        // If the top of the stack matches the current input symbol
        if (a == b)
        {
            cout << "Lecture de " << IdentificateursLabels[a] << endl;
            // Consume the symbol from both the stack and the input
            etat.pile.pop_front();
            etat.alire.pop_front();
        }
        // If there is no valid transition in the parsing table for (a, b)
        else if (!Existe(transitions, a, b))
        {
            cout << "Transition non trouvée" << endl;
            // Syntax error: reject the input
            // si on veut juste rejeter le symbole
            // on peut faire ça
            // etat.pile.pop_front();
            return false;
        }
        // If a valid transition exists
        else
        {
            // Pop the non-terminal from the stack
            etat.pile.pop_front();
            cout << "Transition" << endl;
            
            // Push the right-hand side of the production rule onto the stack in reverse order
            // so that the first symbol of the production ends up on top of the stack
            Pile::const_reverse_iterator i;
            for (i = transitions[a][b].rbegin(); i != transitions[a][b].rend(); i++)
            {
                etat.pile.push_front(*i);
            }
        }
        // Print the current state of the stack and the remaining input
        cout << "Pile : " << etat.pile << endl;
        cout << "A lire : " << etat.alire << endl;
    }
    // If the stack is empty, the input has been successfully parsed
    return true;
}
