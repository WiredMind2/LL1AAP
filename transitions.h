#include "automaton.h"

Trans(E_,OPENPAR,(T_,Ep_));
Trans(E_,INT,(T_,Ep_));
Trans(E_,id_,(T_,Ep_));
Trans(Ep_,PLUS,(PLUS,T_,Ep_));
ETrans(Ep_,CLOSEPAR);
ETrans(Ep_,FIN);
Trans(T_,OPENPAR,(F_,Tp_));
Trans(T_,INT,(F_,Tp_));
Trans(T_,id_,(F_,Tp_));
ETrans(Tp_,PLUS);
Trans(Tp_,MULT,(MULT,F_,Tp_));
ETrans(Tp_,CLOSEPAR);
ETrans(Tp_,FIN);
Trans(F_,OPENPAR,(OPENPAR,E_,CLOSEPAR));
Trans(F_,INT,(INT));
Trans(F_,id_,(id_));