#include <iostream>
#include <deque>
#include <map>
using namespace std;


const string IdentificateursLabels[] =
    {"E", "E’", "T", "T’", "F", "nb", "id",
     "+", "-", "*", "/", "(", ")", "$"};

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

void AffichePile(Pile p)
{
    Pile::iterator i;
    for (i = p.begin(); i != p.end(); i++)
    {
        cout << IdentificateursLabels[*i] << " ";
    }
}

bool Existe(Transitions &t, Identificateurs i, Identificateurs j)
{
    return (t.find(i) != t.end()) and
           (t[i].find(j) != t[i].end());
}

bool LL1AAP(const Pile &mot,
            Transitions &transitions,
            Identificateurs axiome)
{
    Etat etat;
    etat.pile.push_front(axiome);
    etat.alire = mot;
    Identificateurs a, b;
    if (etat.alire.back() != FIN)
    {
        etat.alire.push_back(FIN);
    }
    while (!etat.pile.empty())
    {
        a = etat.pile.front();
        b = etat.alire.front();
        if (a == b)
        {
            cout << "Lecture de " << a << endl;
            etat.pile.pop_front();
            etat.alire.pop_front();
        }
        else if (!Existe(transitions, a, b))
        {
            cout << "Transition non trouvée" << endl;
            // si on veut juste rejeter le symbole
            // on peut faire ça
            // etat.pile.pop_front();
            return false;
        }
        else
        {
            etat.pile.pop_front();
            cout << "Transition" << endl;
            Pile::const_reverse_iterator i;
            for (i = transitions[a][b].rbegin();
                 i != transitions[a][b].rend(); i++)
            {
                etat.pile.push_front(*i);
            }
        }
        cout << "Pile : " << etat.pile << endl;
        cout << "A lire : " << etat.alire << endl;
    }
    return true;
}
