#include <iostream>
#include "lexer.h"
#include "automaton.h"

int main(void)
{
   Transitions trans;
   Pile epsilon;
#define Trans(x, y, z) trans[Identificateurs(x)][Identificateurs(y)] = mkPile z
#define ETrans(x, y) trans[Identificateurs(x)][Identificateurs(y)] = epsilon
#include "transitions.h"
#undef Trans
   std::deque<SymbolValue> mot;

   string chaine("(1+34)*123");

   Lexer l(chaine);

   Symbole *s;
   while (*(s = l.Consulter()) != FIN)
   {
      s->Affiche();
      cout << endl;
      mot.push_back({(Identificateurs)(int)*s, s->getValeur()});
      l.Avancer();
   }

   if (LL1AAP(mot, trans, S0))
   {
      cout << "Succes : Expression valide" << endl;
   }
   else
   {
      cout << "Erreur : Expression invalide" << endl;
   }
   return 0;
}