#pragma once

#include <string>
using namespace std;

enum Identificateurs { OPENPAR, CLOSEPAR, PLUS, MULT, INT, FIN, ERREUR, E, T, F, S0, S1, S2, S3, S4, S5, S6, S7, S8, S9, R1, R2, R3, R4, R5, E_, END };

extern const string IdentificateursLabels[];

class Symbole {
   public:
      Symbole(int i) : ident(i) {  }
      virtual ~Symbole() { }
      operator int() const { return ident; }
      virtual void Affiche();
      virtual int getValeur() { return 0; }

   protected:
      int ident;
};

class Entier : public Symbole {
   public:
      Entier(int v) : Symbole(INT), valeur(v) { }
      ~Entier() { }
      virtual void Affiche();
      virtual int getValeur() override { return valeur; }
   protected:
      int valeur;
};

