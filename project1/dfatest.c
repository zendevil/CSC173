#include <stdio.h>
#include "dfa.h"

#define TRUE 1
#define FALSE 0
typedef int DFA;


/*typedef struct DFA *DFA{
int numStates;
ptr int*;
};

DFA DFA_new(int nstates){
ptr=(int*)calloc(nstates, sizeof(int));
return DFA;
};*/

void findChar(char **a, char c) {

  if(**a == c)
  return 1;
  else {
    return 0;
  }

}

DFA match_char(char **inp, char target) {
 while (**inp != target && **inp != '\0'){
 (*inp)++;}
 return (**inp != '\0');
}

//e
DFA matchPrik(char *in) {
 if(match_char(&in, 'p') &&
 match_char(&in, 'r') &&
 match_char(&in, 'i') &&
 match_char(&in, 'k')==1){
 return 1;}
 else{
 return 0;
    }
}

DFA testDFA(DFA test, char* input){
return test(input);}

//a
DFA onlyAB(char *p) {
  if(findChar(&p, 'a')) {
    p++;
    if(findChar(&p, 'b') ) {
      p++;
      if(findChar(&p, '\0'))
        return 1;
    }
  }else{
  return 0;}

}

DFA evenAs(char *p) {
  int evenCounter=0;
   while (*p != '\0'){
    if(*p=='a'||*p=='A')
        {evenCounter++;}
        p++;
    }

  if(evenCounter % 2 == 0) {
    return 1;
  } else if(evenCounter%2!=0) {
    return 0;
  }}


//c
DFA even1s(char *p) {
  int evenCounter=0;
   while (*p != '\0'){
    if(*p=='1')
        {evenCounter++;}
        p++;
    }

  if(evenCounter % 2 == 0) {
    return 1;
  } else if(evenCounter%2!=0) {
    return 0;
  }}

  //0s parity
  DFA even0s(char *c){
  DFA zeroCounter = 0;
   while (*c != '\0'){
        if(*c=='0')
        {zeroCounter++;}
        c++;
    }

  if(zeroCounter % 2 == 0) {
    return 1;
  } else if(zeroCounter%2!=0) {
    return 0;
  }}

  //d
  DFA even1sAnd0s(char *x){
      if(even1s(x)==1&&even0s(x)==1){
        return 1;
      }else return 0;}

int main(){
    DFA onesParity=DFA_new(2);
    printf("%d\n",even1s("11"));
    printf("%d\n",even0s("00"));
    printf("%d\n",even1sAnd0s("1100"));
    printf("%d\n%d\n",matchPrik("aparesiadk"),evenAs("Aphrodisiac"));
    printf("%d\n",onlyAB("ab"));
}
