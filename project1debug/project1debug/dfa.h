#ifndef _dfa_h_gf
#define _dfa_h_gf

typedef int BOOLEAN;


typedef struct {

  int transitions[128];
  BOOLEAN isAccepting;


} DFAState;



typedef struct  {
  int numStates;
  DFAState *states;
  int currentState;
} DFA;

#endif // _dfa_h_gf
