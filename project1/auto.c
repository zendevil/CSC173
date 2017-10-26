//DFA NFA Conversion
#include <stdio.h>
#include<stdlib.h>

#define TRUE 1
#define FALSE 0
typedef int BOOLEAN;


typedef struct DFAState{

  int transitions[128];
  BOOLEAN isAccepting;


};



typedef struct DFA {
  int numStates;
  DFAState *states;
  int currentState;
};


DFA *DFANew(int numStates) {
  DFA *dfa = (*DFA)malloc(sizeof(DFA));
  dfa->numStates = numStates;
  dfa->currentState = 0;
  dfa->states = (DFA_State*)malloc(n*sizeof(DFA_State));

  //setting all states to FALSE
  for(int i=0; i<numStates;i++) {
    dfa->states[i].isAccepting = FALSE;
  }
//sets the transition to -1 which means no transiton
  for(int i =0;i<n;i++) {
    for(int j=0;j<128;i++){
      dfa->states[i].transitions[j] = -1;


    }
  }
  return dfa;
}

int DFAGetTransition(DFA *dfa, int stateNum, char symbol) {
  return dfa->states[stateNum].transition[symbol];
}

void DFASetTransition(DFA *dfa, int src, char *str, int dst) {

  dfa->states[src].transition[symbol] = dst;
}

int DFAGetCurrentState(DFA *dfa) {
  return dfa->currentState = stateNum;
}

void DFASetCurrentState(DFA *dfa, int stateNum) {
  dfa->currentState = stateNum;
}

int DFAGetAccepting(DFA *dfa, int stateNum) {
  return dfa->states[stateNum].isAccepting;
}

void DFASetAccepting(DFA *dfa, int stateNum, BOOLEAN truthValue) {
  dfa->states[stateNum].isAccepting = truthValue;
}


void DFAFree(DFA *dfa) {
  free(dfa->states);
  free(dfa);
}

void DFAPrint(DFA *dfa) {

}

int DFAExecute(DFA *dfa, char *input) {
  for(int i=0; input[i] != '\0'; i++) {
    int destination = dfa->states[dfa->currentState].transitions[input[i]];
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
struct DFA *onlyAB = DFANew(3);
// int lAccepting[] = {2};
// onlyAB->numStates = 3;
//onlyAB->accepting = lAccepting;

DFASetTransition(onlyAB, 0,'a',1);
DFASetTransition(onlyAB,1,'b',2);
DFASetAccepting(onlyAB, 2, TRUE);

return onlyAB;

/*while(*inputString != '\0') {

  switch(onlyAB->currentState) {
    case 0:
      if(*inputString == 'a') {
        onlyAB->currentState = 1;

      } else {
        return FALSE;
      }

        break;

    case 1:

      if(*inputString == 'b') {
        onlyAB->currentState = 2;
      } else {
        return FALSE;
      }

        break;

    case 2:

        //since accepting state we return TRUE


        if(*inputString != '\0' || *inputString != 'b')
          return FALSE;
        break;

  }//switch ends


  inputString++;
}//while ends
  return TRUE;*/

}


BOOLEAN funcStartAB(char *inputString) {

  struct DFA *startAB = malloc(sizeof(*startAB));
  // int lAccepting[] = {2};
  // startAB->numStates = 3;
  //startAB->accepting = lAccepting;
  startAB->currentState = 0;

  while(*inputString != '\0') {

    switch(startAB->currentState) {
      case 0:
        if(*inputString == 'a') {

          startAB->currentState = 1;

        } else {

          return FALSE;
        }

          break;

      case 1:

        if(*inputString == 'b') {
          startAB->currentState = 2;
        } else {
          return FALSE;
        }

          //break;

      case 2:

          //since accepting state we return TRUE


            return TRUE;
          break;





    }//switch ends




    inputString++;
  }

  return FALSE;

}

BOOLEAN funcEvenOnes(char *inputString) {

  struct DFA *evenOnes = malloc(sizeof(*evenOnes));

  evenOnes->currentState = 0;

  while(*inputString != '\0') {

    switch(evenOnes->currentState) {

      case 0:

      if(*inputString == '1') {
        evenOnes->currentState = 1;

      }

      break;


      case 1:
      if(*inputString == '1') {
        evenOnes->currentState = 0;

      }
      break;


    }//switch ends


    inputString++;
  }


  //2 is the accepting state
  if(evenOnes->currentState == 0) {
    return TRUE;
  } else {
    return FALSE;
  }


}

BOOLEAN funcEvenBoth(char *inputString) {

  struct DFA *evenBoth = malloc(sizeof(*evenBoth));

  while(*inputString != '\0') {
    switch(evenBoth->currentState) {
      case 0:
        if(*inputString == '1') {
          evenBoth->currentState = 1;
        } else if(*inputString == '0') {
          evenBoth->currentState = 3;
        }
        break;
      case 1:
        if(*inputString == '1') {
          evenBoth->currentState = 0;
        } else if(*inputString == '0') {
          evenBoth->currentState = 2;
        }

        case 2:
        if(*inputString == '1') {
          evenBoth->currentState = 3;
        } else if(*inputString == '0') {
          evenBoth->currentState = 1;
        }

        case 3:
        if(*inputString == '1') {
          evenBoth->currentState = 2;
        } else if(*inputString == '0') {
          evenBoth->currentState = 0;
        }

    }//switch ends

    inputString++;

  }//while ends

  if(evenBoth->currentState == 0) {
    return TRUE;
  } else {
    return FALSE;
  }
}

//for indentifying if string starts with $ sign
//Useful for checking if it's an amount of money.
//Easy to implement
BOOLEAN funcStartDolSign(char *inputString) {
  struct DFA *startDolSign = malloc(sizeof(*startDolSign));
  startDolSign->currentState = 0;
  while(*inputString != '\0') {

    switch(startDolSign->currentState) {

      case 0:
        if(*inputString == '$') {
          startDolSign->currentState = 1;
        }
        break;

      case 1:
        printf("");
        BOOLEAN notNum = TRUE;
        for(int i = 0; i<=9; i++) {

          if(*inputString == (i+'0')) {
            notNum = FALSE;
          }

        }

        if(notNum) {
          //send it to non-accepting state if there's even one
          startDolSign->currentState = 0;
        }


    }
    inputString++;
  }//while ends

  if(startDolSign->currentState == 1) {
    return TRUE;
  } else {
    return FALSE;
  }
}




int main() {



  char *inputString1 = "ab";
  char *inputString2 = "abg";
  char *inputString3 = "babcdef";
  char *inputString4 = "110110";
  char *inputString5 = "1101101";
  char *inputString6 = "$150";
  char *inputString7 = "15a0";



  printf("funcOnlyAB(%s) = %d\n", inputString1, DFAExecute(funcOnlyAB(),inputString1));
  printf("funcOnlyAB(%s) = %d\n", inputString2, DFAExecute(funcOnlyAB(), inputString2));
  // printf("funcStartAB(%s) = %d\n", inputString2, DFAExecute(funcStartAB(),inputString2));
  // printf("funcStartAB(%s) = %d\n", inputString3, DFAExecute(funcStartAB(),inputString3));
  // printf("funcEvenOnes(%s) = %d\n", inputString4, DFAExecute(funcEvenOnes(),inputString4));
  // printf("funcEvenOnes(%s) = %d\n", inputString5, DFAExecute(funcEvenOnes(),inputString5));
  // printf("funcEvenBoth(%s) = %d\n", inputString4, DFAExecute(funcEvenBoth(),inputString4));
  // printf("funcEvenBoth(%s) = %d\n", inputString5, DFAExecute(funcEvenBoth(),inputString5));
  // printf("funcStartDolSign(%s) = %d\n", inputString6, DFAExecute(funcStartDolSign(),inputString6));
  // printf("funcStartDolSign(%s) = %d\n", inputString7, DFAExecute(funcStartDolSign(),inputString7));


  return 0;
}
