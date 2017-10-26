#include <stdio.h>
#include <stdlib.h>
#include "dfa.h"
#define TRUE 1
#define FALSE 0

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

BOOLEAN funcOnlyAB() {
DFA *onlyAB = DFANew(3);

DFASetTransition(onlyAB, 0,'a',1);
DFASetTransition(onlyAB,1,'b',2);
DFASetAccepting(onlyAB, 2, TRUE);

return onlyAB;


}


BOOLEAN funcStartAB() {
    DFA *startAB = DFANew(3);
    DFASetTransition(startAB,0, 'a', 1);
    DFASetTransition(startAB,1,'b',2);
    DFASetAllTransitions(startAB, 2,2);

    DFASetAccepting(startAB,2,TRUE);

    return startAB;
}

BOOLEAN funcEvenOnes() {

  DFA *evenOnes = DFANew(2);


  DFASetTransition(evenOnes,0,'1',1);
  DFASetTransition(evenOnes,1,'1',0);
  DFASetTransition(evenOnes, 0,'0',0);
  DFASetTransition(evenOnes, 1,'0',1);

  DFASetAccepting(evenOnes,0,TRUE);


  return evenOnes;


}




BOOLEAN funcEvenBoth() {

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

BOOLEAN funcStartDolSign() {
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




int main() {



  char *inputString1 = "ab";
  char *inputString2 = "abg";
  char *inputString3 = "babcdef";
  char *inputString4 = "111001";
  char *inputString5 = "1101101";
  char *inputString6 = "$150";
  char *inputString7 = "15a0";
  char *inputString8 = "man";



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
 // printf("%d", DFAExecute(funcEndMAN(),inputString8));

}
