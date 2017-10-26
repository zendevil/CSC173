#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "NFA.h"
#include "dfa.h"
#include "IntSet.h"
#include <math.h>
#include "LinkedList.h"
#include "NFAtoDFA.h"

//#ifndef _LinkedList_h_gf
#define _LinkedList_h_gf
#ifndef _NFA_h
#define _NFA_h

DFAState *DFAStatenew(){
DFAState *d=(DFAState*)malloc(sizeof(DFAState));
d->isAccepting=FALSE;
for(int symbol=0;symbol<128;symbol++){
    d->transitions[symbol]=-1;
    //initialize transitions to -1
}
return d;
}

//convert NFA to DFA
DFA *NFAtoDFA(NFA *nfa){
LinkedList *States=LinkedList_new();//Linked List for states
LinkedList *intSet=LinkedList_new();//Linked List for intsets

DFAState *state0=DFAStatenew();
LinkedList_add_at_end(States,state0);
IntSet *firstIntSet=IntSet_new();
IntSet_add(firstIntSet,0);
LinkedList_add_at_end(intSet, firstIntSet);

int numStates=1;
LinkedListIterator *iterate=LinkedList_iterator(States);
LinkedListIterator *intSetIterate=LinkedList_iterator(intSet);

while(LinkedListIterator_has_next(iterate)){
  DFAState *currentState=LinkedListIterator_value(iterate);
  IntSet *currentIntSet=LinkedListIterator_value(intSetIterate);
  for(int s=0;s<128;s++){
    IntSet *dst=IntSet_new();
    IntSetIterator *currentStateIter=IntSet_iterator(currentIntSet);
    while(IntSetIterator_has_next(currentStateIter)){
        int tempS=IntSetIterator_next(currentStateIter);
        IntSet_union(dst, nfa->States[tempS].transitions[s]);
        if(nfa->States[tempS].isAccepting){
            currentState->isAccepting=TRUE;
        }

    }
    free(currentStateIter);

    int setInt=-1;
    int count=0;
    LinkedListIterator *tempIT=LinkedList_iterator(intSet);
    while(LinkedListIterator_has_next(tempIT)){
        IntSet *tempIS=LinkedListIterator_next(tempIT);
        if(IntSet_equals(tempIS, dst)){
            setInt=count;
        }count++;

    }
    free(tempIT);

    if(setInt<0&&(!(IntSet_is_empty(dst)))){
        DFAState *stateK = DFAStatenew();
        currentState->transitions[s]=numStates;

        LinkedList_add_at_end(States,stateK);
        LinkedList_add_at_end(intSet,dst);
        numStates+=1;
    }
    else if(!(IntSet_is_empty(dst))){
        currentState->transitions[s]=setInt;
    }

  }
  DFAState *nextState = LinkedListIterator_next(iterate);
  IntSet *next = LinkedListIterator_next(intSetIterate);
}

//create new DFA
DFA *newDFA = DFANew(numStates);
LinkedListIterator *finalState = LinkedListIterator_next(States);
for(int p=0; p<numStates; p++){
    DFAState *oneState = LinkedListIterator_next(finalState);
    newDFA->States[p] = *oneState;
    free(oneState);
}
free(finalState);
free(iterate);
free(intSetIterate);
return newDFA;
}

#endif

int main(){

}
