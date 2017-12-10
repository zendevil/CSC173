#include "Tree.h"

char *nextTerminal;
TREE parseTree;

bool lookAhead(char c) {
  return *nextTerminal == c;
}

bool matchTerminal(char c) {
  if(*nextTerminal == c) {
    nextTerminal++;
    return true;
  }
  return false;
}

TREE makeNode0(char x) {
  TREE root;
  root = (TREE) malloc(sizeof(struct NODE));
  root->label = x;
  root->leftmostChild = NULL;
  root->rightSibling = NULL;
  return root;
}

TREE makeNode1(char x, TREE t) {
  TREE root;
  root = makeNode0(x);
  root->leftmostChild = t;
    return root;
}

TREE makeNode2(char x, TREE t1, TREE t2) {
  TREE root;
  root = makeNode1(x, t1);
  t1->rightSibling = t2;
  return root;
}

TREE makeNode3(char x, TREE t1, TREE t2, TREE t3) {
  TREE root;
  root = makeNode2(x, t1,t2);
  t2->rightSibling = t3;
  return root;
}

TREE E() {
  TREE a = G();
  if(a == NULL) return NULL;
  TREE b = S();
  if(b == NULL) return NULL;
  return makeNode2('E', a, b);
}

TREE S() {
  if(!lookAhead('A') && !lookAhead('O')) {
    return makeNode1('S', makeNode0('e'));
  } else {
      TREE madeNode;
      if(matchTerminal('A')) {
        madeNode = makeNode0('A');
      } else if(matchTerminal('O')) {
        madeNode = makeNode0('O');
      }
      TREE a = G();
      if(a == NULL) return NULL;
      TREE b = S();
      if(b == NULL) return NULL;
      return makeNode3('S', madeNode, a, b);
    }
}

TREE G() {
  if(!lookAhead('N') && !lookAhead('(') && lookAhead('T') && lookAhead('F')) {
    return makeNode1('G', makeNode0('e'));
  } else if(matchTerminal('N')) {
    TREE a = G();
    if(a == NULL) return NULL;
    return makeNode2('G', makeNode0('N'), a);
  } else if(matchTerminal('(')) {
    TREE a = E();
    if(a == NULL) return NULL;
    if(!matchTerminal(')')) return NULL;
    return makeNode3('G', makeNode0('('), a, makeNode0(')'));
  } else if(matchTerminal('T')) {
    return makeNode1('G', makeNode0('T'));
  } else if(matchTerminal('F')) {
    return makeNode1('G', makeNode0('F'));
  } else {
    return NULL;
  }
}

void printParseTree(TREE parseTree, int level) {
  TREE c; //child of parse tree root
  for(int i = 0; i<=level; i++) {
    printf("       ");
	}
  printf("%c\n", parseTree->label);
  c = parseTree->leftmostChild;
  while(c != NULL) {
    printParseTree(c, level+1);
    c = c->rightSibling;
  }
}

void print(char* s) {
  nextTerminal = s;
  parseTree = E();
  printParseTree(parseTree, 0);
}

Circuit make_Circuit(Tree t) {
  if(t->label == 'E') {
    if(t->leftmostChild->leftmostChild == 'A')
    return make_Circuit(t->leftmostChild) *and* make_Circuit(t->leftmostChild->rightSibling);
  } else if(t->leftmostChild->leftmostChild == 'O') {
    return make_Circuit(t->leftmostChild) *or* make_Circuit(t->leftmostChild->rightSibling);
  } else if(t->label == 'S') {
    if(t->lk)
  }
}
