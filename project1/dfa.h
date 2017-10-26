#ifndef _dfa_h_gf
#define _dfa_h_gf
typedef int BOOLEAN;
typedef struct {

  int transitions[128];
  BOOLEAN isAccepting;

}DFAState;



typedef struct  {
  int numStates;
  DFAState *States;
  int currentState;
}DFA;


#endif
