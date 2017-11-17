#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define LSIZE 5
#include "mydatabase.h"

typedef struct Tuple {
  int nAttr;
  char **attr;
  char *key;
  Tuple *next;
} Tuple;
typedef struct Tuple* List;
typedef List Hashtable[LSIZE];

typedef struct Node* Tree;

struct Node {
  char name[30];
  List toTuple; /*really a pointer to a tuple*/
  Tree lc;
  Tree rc;
} Node;

int hash(char* key) {

  int sum = 0;
  for (int i = 0; key[i] != '\0'; i++) {
    sum += key[i];
  }
  return sum % LSIZE;
}


void bucketInsert(Tuple x, List *l) {
  if(*l == NULL) {
    (*l) = (List) malloc(sizeof(List));
    *l[0] = x;
    (*l)->next = NULL;
  } else {
      bucketInsert(x, &((*l)->next));
  }
}

void insert(Tuple *a, Hashtable *b) {
  bucketInsert(*a, b[hash(a->key)]);
}


int main(void) {

  Hashtable *csg = (Hashtable*)malloc(sizeof(Hashtable));
  Tuple *a = (Tuple*)malloc(sizeof(Tuple));
  a->nAttr = 3;
  a->attr[0] = "CSC173";
  a->attr[1] = "Luke Skywalker";
  a->attr[2] = "A";
  a->key = a->attr[0];
  insert(a, csg);

  return 0;
}
