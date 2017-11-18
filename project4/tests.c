#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "mydatabase.h"
#define LSIZE 5
typedef struct Tuple {
  int nAttr;
  char **attr;
  char *key;
  Tuple *next;
} Tuple;
typedef struct Tuple* List;


int main(int argc, char const *argv[]) {
  List x = (List)malloc(sizeof(Tuple));
  x->next = NULL;

  if(x->next == NULL)
    printf("*x == NULL\n");
  else
    printf("*x!=NULL\n" );
  return 0;
}
