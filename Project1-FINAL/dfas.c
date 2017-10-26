#include <stdio.h>
#include "dfa.h"

findChar(char **a, char c) {

  if(**a == c)
  return 1;
  else {
    return 0;
  }

}

int match_char(char **inp, char target) {
 while (**inp != target && **inp != '\0'){
 (*inp)++;}
 return (**inp != '\0');
}

//e
int matchPrik(char *in) {
 if(match_char(&in, 'p') &&
 match_char(&in, 'r') &&
 match_char(&in, 'i') &&
 match_char(&in, 'k')==1){
 return 1;}
 else{
 return 0;
    }
}

//a
int onlyAB(char *p) {
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

int evenAs(char *p) {
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
int even1s(char *p) {
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
  int even0s(char *c){
  int zeroCounter = 0;
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
  int even1sAnd0s(char *x){
      if(even1s(x)==1&&even0s(x)==1){
        return 1;
      }else return 0;}

main(){
    printf("%d\n",even1s("11"));
    printf("%d\n",even0s("00"));
    printf("%d\n",even1sAnd0s("1010"));
    printf("%d\n%d\n",matchPrik("aparesiadk"),evenAs("Aphrodisiac"));
    printf("%d\n",onlyAB("ab"));
}
