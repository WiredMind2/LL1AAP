#include "automaton.h"

Trans(S0, INT, (S3));
Trans(S0, OPENPAR, (S2));
Trans(S0, E_, (S1));

Trans(S1, PLUS, (S4));
Trans(S1, MULT, (S5));
Trans(S1, FIN, ()); // accepter

Trans(S2, INT, (S3));
Trans(S2, OPENPAR, (S2));
Trans(S2, E_, (S6));

Trans(S3, PLUS, (S5)); // reduction
Trans(S3, MULT, (S5)); // reduction
Trans(S3, CLOSEPAR, (S5)); // reduction
Trans(S3, FIN, (S5)); // reduction

Trans(S4, INT, (S3));
Trans(S4, OPENPAR, (S2));
Trans(S4, E_, (S7));

Trans(S5, INT, (S3));
Trans(S5, OPENPAR, (S2));
Trans(S5, E_, (S8));

Trans(S6, PLUS, (S4));
Trans(S6, MULT, (S5));
Trans(S6, CLOSEPAR, (S9));

Trans(S7, PLUS, (S2)); // reduction, conflict with 4
Trans(S7, MULT, (S5)); // conflict with 2 (reduction)
Trans(S7, CLOSEPAR, (S2)); // reduction
Trans(S7, FIN, (S2)); // reduction

Trans(S8, PLUS, (S3)); // reduction, conflict with 4
Trans(S8, MULT, (S3)); // reduction, conflict with 5
Trans(S8, CLOSEPAR, (S3)); // reduction
Trans(S8, FIN, (S3)); // reduction

Trans(S9, PLUS, (S4)); // reduction
Trans(S9, MULT, (S4)); // reduction
Trans(S9, CLOSEPAR, (S4)); // reduction
Trans(S9, FIN, (S4)); // reduction