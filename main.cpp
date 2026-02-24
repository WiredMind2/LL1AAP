#include <iostream>
#include "lexer.h"
#include "automaton.h"

int main(void)
{
   Transitions trans;
   Pile epsilon;
#define Trans(x, y, z) trans[x][y] = mkPile z
#define ETrans(x, y) trans[x][y] = epsilon
#include "transitions.h"
#undef Trans
   Pile mot;

   string chaine("(1+34)*123");

   Lexer l(chaine);

   Symbole *s;
   while (*(s = l.Consulter()) != FIN)
   {
      s->Affiche();
      cout << endl;
      mot.push_back((Identificateurs)(int)*s);
      l.Avancer();
   }

   if (LL1AAP(mot, trans, S0))
   {
      cout << "Mot reconnu" << endl;
   }
   else
   {
      cout << "Mot non reconnu" << endl;
   }
   return 0;
}