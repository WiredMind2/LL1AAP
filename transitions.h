#include "automaton.h"

Trans(S0, INT, (S3));
Trans(S0, OPENPAR, (S2));
Trans(S0, E, (S1));

Trans(S1, PLUS, (S4));
Trans(S1, MULT, (S5));
Trans(S1, FIN, ()); // acceptation

Trans(S2, INT, (S3));
Trans(S2, OPENPAR, (S2));
Trans(S2, E, (S6));

Trans(S3, PLUS, (R5)); // reduction E -> val
Trans(S3, MULT, (R5)); 
Trans(S3, CLOSEPAR, (R5)); 
Trans(S3, FIN, (R5)); 

Trans(S4, INT, (S3));
Trans(S4, OPENPAR, (S2));
Trans(S4, E, (S7));

Trans(S5, INT, (S3));
Trans(S5, OPENPAR, (S2));
Trans(S5, E, (S8));

Trans(S6, PLUS, (S4));
Trans(S6, MULT, (S5));
Trans(S6, CLOSEPAR, (S9));

Trans(S7, PLUS, (R2)); // Conflit r2/d4 -> r2 (+ est associatif à gauche)
Trans(S7, MULT, (S5)); // Conflit r2/d5 -> d5 (* a la priorite sur +)
Trans(S7, CLOSEPAR, (R2)); 
Trans(S7, FIN, (R2)); 

Trans(S8, PLUS, (R3)); // Conflit r3/d4 -> r3 (* a la priorite sur +)
Trans(S8, MULT, (R3)); // Conflit r3/d5 -> r3 (* est associatif à gauche)
Trans(S8, CLOSEPAR, (R3)); 
Trans(S8, FIN, (R3)); 

Trans(S9, PLUS, (R4)); // reduction E -> ( E )
Trans(S9, MULT, (R4)); 
Trans(S9, CLOSEPAR, (R4)); 
Trans(S9, FIN, (R4));