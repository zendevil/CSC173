#include<stdio.h>
#include<stdlib.h>
#define LSIZE 5
#include "mydatabase.h"

typedef struct tuple {
  int nAttr;
  char **attr;
  tuple *next;
} tuple;
typedef struct tuple* table;



int hash(int key) {
  return key % LSIZE;
}


void insert(tuple tu, table ta) {

}


int main() {

  table csg = malloc(sizeof(table));
  csg[0].nAttr = 3;
  csg[0].attr[0] = "CSC173";
  csg[0].attr[1] = "George Ferguson";
  csg[0].attr[2] = "D";

  printf("number of attributes: %s\n", csg[0].attr[0]);

  //
  // t1[0].id = 184;
  // t1[1].id = 123;
  // t1[2].id = 857;
  //
  // int i0 = hash(t1[0].id);
  // int i1 = hash(t1[1].id);
  // int i2 = hash(t1[2].id);
  //
  // printf("hash1: %d\n", i0);
  // printf("hash2: %d\n", i1);
  // printf("hash3: %d\n", i2);






  // printf("index: %d\n", hash(t1[0].id));
  // int index = hash(t1[0].id);
  // HSNAP[index] =  t1;
  // printf("%d\n", t1[0].id);

//adding values in row 1 of the table t
  // t[0].course = "CSC173";
  // t[0].id = 12345;
  // t[0].grade = "A";



//adding values in row 2 of the table t
  // t[1].course = "CSC171";
  // t[1].id = 12345;
  // t[1].grade = "A-";
  //
  // printf("%s\n", t[0].course);
  // printf("%d\n", t[0].id);
  // printf("%s\n", t[0].grade);
  //
  //
  // printf("%s\n", t[1].course);
  // printf("%d\n", t[1].id);
  // printf("%s\n", t[1].grade);
  return 0;
}
