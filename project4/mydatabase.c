#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdarg.h>
#define NBUCKETS 5
#include "mydatabase.h"

typedef struct Tuple {
  int nAttr;
  char **attr;
  char *key;
  Tuple *next;
} Tuple;
typedef struct Tuple* List;
typedef List Hashtable[NBUCKETS];

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
  //printf("%s is hashed to %d\n",*key, sum % NBUCKETS);
  return sum % NBUCKETS;
}


void delete(Tuple *t, Hashtable *h ) {

}


void bucketInsert(Tuple x, List *l) {

  if(*l == NULL) {
    *l = (List) malloc(sizeof(Tuple));
    *l[0] = x;
    (*l)->next = NULL;
  } else {
      bucketInsert(x, &((*l)->next));
  }
}

void insert(Tuple t, Hashtable h) {
  printf("Inserting tuple with key %s into this index: %d\n", t.key, hash(t.key));
  bucketInsert(t, &(h[hash(t.key)]));
}

Tuple tuple_new(char *key, int nAttr, ...) {
  va_list valist;

  va_start(valist, nAttr); // initialize valist for nAttr number of arguments

  Tuple *t = (Tuple*)malloc(sizeof(Tuple));

  t->nAttr = nAttr;
  t->key = key;
  t->next = NULL;
  t->attr = malloc(sizeof(char*) * nAttr);

  for(int i = 0; i< nAttr; i++) {
    t->attr[i] = va_arg(valist, char*);
  }

  va_end(valist);
  return *t;

}

int main(void) {
  Hashtable csg;

  for(int i = 0; i< NBUCKETS; i++) {
	  
    csg[i] = NULL;
  }

  
  Tuple c = tuple_new("John", 3, "CSC282", "John", "A-");
  insert(c, csg);
 

  Tuple a = tuple_new("Luke Skywalker", 3,"CSC173", "Luke Skywalker", "A");

  insert(a, csg);

  Tuple b = tuple_new("Luke Skywalker", 3,"MTH201", "Luke Skywalker", "B");

  insert(b, csg);
  
  Tuple d = tuple_new("George Eastman", 3, "MUR110", "George Eastman", "A+");
  insert(d, csg);
  



  return 0;
}
