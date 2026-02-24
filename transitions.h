#include "automaton.h"

Transitions(E_,open_,(T_,Ep_));
Transitions(E_,nb_,(T_,Ep_));
Transitions(E_,id_,(T_,Ep_));
Transitions(Ep_,plus_,(plus_,T_,Ep_));
Transitions(Ep_,moins_,(moins_,T_,Ep_));
ETrans(Ep_,close_);
ETrans(Ep_,end_);
Transitions(T_,open_,(F_,Tp_));
Transitions(T_,nb_,(F_,Tp_));
Transitions(T_,id_,(F_,Tp_));
ETrans(Tp_,plus_);
ETrans(Tp_,moins_);
Transitions(Tp_,div_,(div_,F_,Tp_));
Transitions(Tp_,mult_,(mult_,F_,Tp_));
ETrans(Tp_,close_);
ETrans(Tp_,end_);
Transitions(F_,open_,(open_,E_,close_));
Transitions(F_,nb_,(nb_));
Transitions(F_,id_,(id_));