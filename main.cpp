#include <iostream>
#include "lexer.h"
#include "automaton.h"

int main(void)
{
   Transitions trans;
#define Trans(x, y, z) trans[Identificateurs(x)][Identificateurs(y)] = Identificateurs z
#include "transitions.h"
#undef Trans
   std::deque<SymbolValue> mot;

   string chaine("(1+34)*123+5+3+4+(56*8+4*3+5+6*7*5)*9+4+((1+2)*3+4)*5");

   Lexer l(chaine);

   Symbole *s;
   while (*(s = l.Consulter()) != FIN)
   {
      s->Affiche();
      cout << endl;
      mot.push_back({(Identificateurs)(int)*s, s->getValeur()});
      l.Avancer();
   }

   if (automaton(mot, trans, S0))
   {
      cout << "Succes : Expression valide" << endl;
   }
   else
   {
      cout << "Erreur : Expression invalide" << endl;
   }
   return 0;
}