#include <stdlib.h>
#include<stdbool.h>
#include<stdio.h>
typedef struct NODE *TREE;
struct NODE {
  char label;
  TREE leftmostChild, rightSibling, parent;
};
TREE E();
TREE G();
TREE S();
void print(char* s);
