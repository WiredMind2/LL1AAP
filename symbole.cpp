#include "symbole.h"
#include <iostream>

const string IdentificateursLabels[] = { "(", ")", "+", "*", "nb", "$", "ERREUR", "E", "E'", "T", "id", "F", "T'", "S0", "S1", "S2", "S3", "S4", "S5", "S6", "S7", "S8", "S9", "E_", "END" };

void Symbole::Affiche() {
   cout<<IdentificateursLabels[ident];
}

void Entier::Affiche() {
   Symbole::Affiche();
   cout<<"("<<valeur<<")";
}

