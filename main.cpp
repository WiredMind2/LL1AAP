#include <iostream>
#include "lexer.h"
#include "automaton.h"

int main(void)
{
#include "transitions.h"
   std::deque<SymbolValue> mot;

   string chaine("(1+34)*123+5+3+4+(56*8+4*3+5+6*7*5)*9+4+((1+2)*3+4)*5");

   Lexer l(chaine);

   Symbole *s;
   while (*(s = l.Consulter()) != FIN)
   {
      if (DEBUG_ENABLED) {
         s->Affiche();
         cout << endl;
      }
      mot.push_back({(Identificateurs)(int)*s, s->getValeur()});
      l.Avancer();
   }

   automaton(mot, trans, S0);
   return 0;
}