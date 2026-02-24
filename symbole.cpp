#include "symbole.h"
#include <iostream>

const string IdentificateursLabels[] = { "(", ")", "+", "*", "nb", "$", "ERREUR", "E", "T", "F", "S0", "S1", "S2", "S3", "S4", "S5", "S6", "S7", "S8", "S9", "R1", "R2", "R3", "R4", "R5", "E_", "END" };

void Symbole::Affiche() {
   cout<<IdentificateursLabels[ident];
}

void Entier::Affiche() {
   Symbole::Affiche();
   cout<<"("<<valeur<<")";
}

