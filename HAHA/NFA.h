#include "IntSet.h"
#include <stdbool.h>
#define TRUE 1
#define FALSE 0
#ifndef _NFA_h
#define _NFA_h

typedef struct {
    IntSet *transitions[128];
    bool isAccepting;
} NFAState;



typedef struct {
    int nstates;
    NFAState *States;
    IntSet *currentStates;
} NFA;
#endif
