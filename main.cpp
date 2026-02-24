#include <iostream>
#include "lexer.h"

int main(void)
{
   string chaine("(1+34)*123");

   Lexer l(chaine);

   Symbole *s;
   while (*(s = l.Consulter()) != FIN)
   {
      s->Affiche();
      cout << endl;
      l.Avancer();
   }
   return 0;
}

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
      mot.push_back(s);
      l.Avancer();
   }

   if (LL1AAP(mot, trans, E_))
   {
      cout << "Mot reconnu" << endl;
   }
   else
   {
      cout << "Mot non reconnu" << endl;
   }
   return 0;
}