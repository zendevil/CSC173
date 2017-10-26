#ifndef _nfa_h
#define _nfa_h
#ifndef _dfa_h
#define _dfa_h
//#ifndef _LinkedList_h
//#define _LinkedList_h
#include <stdio.h>
#include <stdlib.h>
#include "dfa.h"
#include "LinkedList.h"
#include "NFA.h"
#include "IntSet.h"
#include <stdbool.h>
#include "IntSet.h"



DFA *DFANew(int numStates);
bool NFASubExecute(NFA *nfa, IntSet *startStates, char *input);
void NFA_set_accepting(NFA *nfa, int statenum, bool value) ;
bool NFAExecute(NFA *nfa, char *input) ;


//NFA DFA CONVERSION
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
//LinkedListIterator *finalState = LinkedListIterator_next(States);
LinkedListIterator *finalState = LinkedList_iterator(States);
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

//DFAs
DFA *DFANew(int numStates) {
    DFA *dfa = (DFA*)malloc(sizeof(DFA));
    dfa->numStates = numStates;
    dfa->currentState = 0;
    dfa->States = (DFAState*)malloc(numStates*sizeof(DFAState));

  //setting all states to FALSE
  for(int i=0; i<numStates;i++) {
    dfa->States[i].isAccepting = FALSE;
  }
//sets the transition to -1 which means no transiton
  for(int i1 =0;i1<numStates;i1++) {
    for(int j=0;j<128;j++){
      dfa->States[i1].transitions[j] = -1;


    }
  }
  return dfa;
}

int DFAGetTransition(DFA *dfa, int stateNum, char symbol) {
  return dfa->States[stateNum].transitions[symbol];
}

void DFASetTransition(DFA *dfa, int src, char str, int dst) {
  dfa->States[src].transitions[str] = dst;
}

void DFASetAllTransitions(DFA *dfa, int src, int dst) {

    for(int i=0;i<128;i++) {
        DFASetTransition(dfa,src,i,dst);
    }
}

int DFAGetCurrentState(DFA *dfa) {
  return dfa->currentState;
}

void DFASetCurrentState(DFA *dfa, int stateNum) {
  dfa->currentState = stateNum;
}

int DFAGetAccepting(DFA *dfa, int stateNum) {
  return dfa->States[stateNum].isAccepting;
}

void DFASetAccepting(DFA *dfa, int stateNum, BOOLEAN truthValue) {
  dfa->States[stateNum].isAccepting = truthValue;
}


void DFAPrint(DFA *dfa) {

}

int DFAExecute(DFA *dfa, char *input) {
  for(int i=0; input[i] != '\0'; i++) {
    int destination = dfa->States[dfa->currentState].transitions[input[i]];
    DFASetCurrentState(dfa, destination);
    if(dfa->currentState == -1) {
      return FALSE;
    }

  }
  int finalState = dfa->currentState;
  DFASetCurrentState(dfa,0);
  return DFAGetAccepting(dfa, finalState);
}

//only string ab

DFA* funcOnlyAB() {
DFA *onlyAB = DFANew(3);

DFASetTransition(onlyAB, 0,'a',1);
DFASetTransition(onlyAB,1,'b',2);
DFASetAccepting(onlyAB, 2, TRUE);

return onlyAB;


}


DFA* funcStartAB() {
    DFA *startAB = DFANew(3);
    DFASetTransition(startAB,0, 'a', 1);
    DFASetTransition(startAB,1,'b',2);
    DFASetAllTransitions(startAB, 2,2);

    DFASetAccepting(startAB,2,TRUE);

    return startAB;
}

DFA* funcEvenOnes() {

  DFA *evenOnes = DFANew(2);


  DFASetTransition(evenOnes,0,'1',1);
  DFASetTransition(evenOnes,1,'1',0);
  DFASetTransition(evenOnes, 0,'0',0);
  DFASetTransition(evenOnes, 1,'0',1);

  DFASetAccepting(evenOnes,0,TRUE);


  return evenOnes;


}




DFA* funcEvenBoth() {

  DFA *evenBoth = DFANew(4);

  DFASetTransition(evenBoth,0,'0',1);
  DFASetTransition(evenBoth,1,'0',0);
  DFASetTransition(evenBoth,1,'1',2);
  DFASetTransition(evenBoth,2,'1',1);
  DFASetTransition(evenBoth,2,'0',3);
  DFASetTransition(evenBoth,3,'0',2);
  DFASetTransition(evenBoth,3,'1',0);
  DFASetTransition(evenBoth,0,'1',3);
  DFASetAccepting(evenBoth,0,TRUE);

  return evenBoth;


}

//for indentifying if string starts with $ sign
//Useful for checking if it's an amount of money.
//Would return false if any character after dollar sign is not a number
//Easy to implement

DFA* funcStartDolSign() {
    DFA *startDolSign = DFANew(2);



   // DFASetAllTransitions(startDolSign,0,0);
   // DFASetAllTransitions(startDolSign,1,1);
    DFASetTransition(startDolSign,0,'$',1);
    //iterating over all ascii
    //values for number characters
    for(int i =48;i<=57;i++) {
        DFASetTransition(startDolSign,1,i,1);

    }

    DFASetAccepting(startDolSign,1,TRUE);

    return startDolSign;

}



//NFAs
NFA *NFA_new(int n) {
    NFA *nfa = (NFA*)malloc(sizeof(NFA));
    nfa->nstates = n;
    IntSet *start = IntSet_new();
    IntSet_add(start, 0);
    nfa->currentStates = start;
    nfa->States = (NFAState*)malloc(n*sizeof(NFAState));
    for(int i=0; i<n; i++) {
        for(int j=0; j<128; j++) {
            nfa->States[i].transitions[j] = IntSet_new();
        }
        nfa->States[i].isAccepting = FALSE;
    }
    return nfa;
}

//returns number of states in the NFA
int NFA_get_size(NFA *nfa) {
	return nfa->nstates;
}

//returns set of transitions for an NFA on a given state for a given symbol
IntSet *NFA_get_transitions(NFA *nfa, int statenum, char symbol) {
	return nfa->States[statenum].transitions[symbol];
}

//adds a transition from a source state to a destination state on a given symbol
void NFA_add_transition(NFA *nfa, int src, char symbol, int dst) {
    IntSet_add(nfa->States[src].transitions[symbol], dst);
}


void NFA_add_transition_str(NFA *nfa, int src, char *str, int dst) {
    for(int i=0; str[i] != '\0'; i++) {
        IntSet_add(nfa->States[src].transitions[str[i]], dst);
    }
}

void NFA_add_transition_all(NFA *nfa, int src, int dst) {
    for(int i=0; i<128; i++) {
        IntSet_add(nfa->States[src].transitions[i], dst);
    }
}

IntSet *NFA_get_current_states(NFA *nfa) {
    return nfa->currentStates;
}

void NFA_set_current_states(NFA *nfa, IntSet *states) {
    nfa->currentStates = states;
}

void NFA_set_current_state(NFA *nfa, int state) {
    IntSet *current = IntSet_new();
    IntSet_add(current, state);
    nfa->currentStates = current;
}
//strings ending in man
NFA funcEndMAN(){
    NFA *endMAN = NFA_new(4);
    NFA_set_current_state(endMAN,0);
    NFA_add_transition(endMAN, 0, 'm', 1);
    NFA_add_transition(endMAN, 1, 'a', 2);
    NFA_add_transition(endMAN, 1, 'n', 3);
    NFA_set_accepting(endMAN, 3, TRUE);

}

NFA *funcWashington () {
	//printf(" \n Problem 2 (b) \n");
    //printf("Strings that contain more than one each of the letters in \"washington\" other than n, or more than two n\'s \n");

    NFA *problem2_b = NFA_new(20);
    NFA_add_transition_all(problem2_b, 0, 0);

    NFA_add_transition(problem2_b, 0, 'a', 1);
    NFA_add_transition_all(problem2_b, 1, 1);
    NFA_add_transition(problem2_b, 1, 'a', 2);
    NFA_add_transition_all(problem2_b, 2, 2);

    NFA_add_transition(problem2_b, 0, 'g', 3);
    NFA_add_transition_all(problem2_b, 3, 3);
    NFA_add_transition(problem2_b, 3, 'g', 4);
    NFA_add_transition_all(problem2_b, 4, 4);

    NFA_add_transition(problem2_b, 0, 'h', 5);
    NFA_add_transition_all(problem2_b, 5, 5);
    NFA_add_transition(problem2_b, 5, 'h', 6);
    NFA_add_transition_all(problem2_b, 6, 6);

    NFA_add_transition(problem2_b, 0, 'i', 7);
    NFA_add_transition_all(problem2_b, 7, 7);
    NFA_add_transition(problem2_b, 7, 'i', 8);
    NFA_add_transition_all(problem2_b, 8, 8);

    NFA_add_transition(problem2_b, 0, 'n', 9);
    NFA_add_transition_all(problem2_b, 9, 9);
    NFA_add_transition(problem2_b, 9, 'n', 10);
    NFA_add_transition_all(problem2_b, 10, 10);
    NFA_add_transition(problem2_b, 10, 'n', 11);
    NFA_add_transition_all(problem2_b, 11, 11);

    NFA_add_transition(problem2_b, 0, 'o', 12);
    NFA_add_transition_all(problem2_b, 12, 12);
    NFA_add_transition(problem2_b, 12, 'o', 13);
    NFA_add_transition_all(problem2_b, 13, 13);

    NFA_add_transition(problem2_b, 0, 's', 14);
    NFA_add_transition_all(problem2_b, 14, 14);
    NFA_add_transition(problem2_b, 14, 's', 15);
    NFA_add_transition_all(problem2_b, 15, 15);

    NFA_add_transition(problem2_b, 0, 't', 16);
    NFA_add_transition_all(problem2_b, 16, 16);
    NFA_add_transition(problem2_b, 16, 't', 17);
    NFA_add_transition_all(problem2_b, 17, 17);

    NFA_add_transition(problem2_b, 0, 'w', 18);
    NFA_add_transition_all(problem2_b, 18, 18);
    NFA_add_transition(problem2_b, 18, 'w', 19);
    NFA_add_transition_all(problem2_b, 19, 19);

    NFA_set_accepting(problem2_b, 2, TRUE);
    NFA_set_accepting(problem2_b, 4, TRUE);
    NFA_set_accepting(problem2_b, 6, TRUE);
    NFA_set_accepting(problem2_b, 8, TRUE);
    NFA_set_accepting(problem2_b, 11, TRUE);
    NFA_set_accepting(problem2_b, 13, TRUE);
    NFA_set_accepting(problem2_b, 15, TRUE);
    NFA_set_accepting(problem2_b, 17, TRUE);
    NFA_set_accepting(problem2_b, 19, TRUE);



    return problem2_b;
}

//queries whether given state is accepting
bool NFA_get_accepting(NFA *nfa, int statenum) {
    return nfa->States[statenum].isAccepting;
}

//set accepting state for given NFA
void NFA_set_accepting(NFA *nfa, int statenum, bool value) {
    nfa->States[statenum].isAccepting = value;
}

//executes nfa on input string
bool NFASubExecute(NFA *nfa, IntSet *startStates, char *input) {
    IntSetIterator *current_s_iterator = IntSet_iterator(startStates); /*creates iterator of possible current states*/
    while(IntSetIterator_has_next(current_s_iterator)) { /*condition makes sure the intset isn't empty*/

        int tempState = IntSetIterator_next(current_s_iterator);

        if(input[0] != '\0') {
           bool tempBool = NFASubExecute(nfa, nfa->States[tempState].transitions[input[0]], (input+1));
           if(tempBool) {
            free(current_s_iterator);
            return TRUE;
           }
        }

        else if(nfa->States[tempState].isAccepting) {
            free(current_s_iterator);
            return TRUE;
        }
    }
    free(current_s_iterator);
    return FALSE;
}

bool NFAExecute(NFA *nfa, char *input) {
    return NFASubExecute(nfa, nfa->currentStates, input);
}


#endif
#endif // _nfa_h



int main(int argc,char* argv[]){
//Testing DFas
char *inputString1 = "ab";
  char *inputString2 = "abg";
  char *inputString3 = "babcdef";
  char *inputString4 = "111001";
  char *inputString5 = "1101101";
  char *inputString6 = "$150";
  char *inputString7 = "15a0";
  char *inputString8 = "washington";



  printf("funcOnlyAB(%s) = %d\n", inputString1, DFAExecute(funcOnlyAB(),inputString1));
  printf("funcOnlyAB(%s) = %d\n", inputString2, DFAExecute(funcOnlyAB(), inputString2));
  printf("funcStartAB(%s) = %d\n", inputString2, DFAExecute(funcStartAB(),inputString2));
  printf("funcStartAB(%s) = %d\n", inputString3, DFAExecute(funcStartAB(),inputString3));
  printf("funcEvenOnes(%s) = %d\n", inputString4, DFAExecute(funcEvenOnes(),inputString4));
  printf("funcEvenOnes(%s) = %d\n", inputString5, DFAExecute(funcEvenOnes(),inputString5));
  printf("funcEvenBoth(%s) = %d\n", inputString4, DFAExecute(funcEvenBoth(),inputString4));
  printf("funcEvenBoth(%s) = %d\n", inputString5, DFAExecute(funcEvenBoth(),inputString5));
  printf("funcStartDolSign(%s) = %d\n", inputString6, DFAExecute(funcStartDolSign(),inputString6));
  printf("funcStartDolSign(%s) = %d\n", inputString7, DFAExecute(funcStartDolSign(),inputString7));
  printf("funcWashington(%s) = %d\n", inputString8, NFAExecute(funcWashington(),inputString8));
}
