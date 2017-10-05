//This is a C file

#include <stdio.h>

#define TRUE 1
#define FALSE 0
typedef int BOOLEAN;


typedef struct NODE *TREE;
typedef struct NODE {

	char label;
	TREE leftmostChild, rightSibling;
};

struct NODE* new_node() {

}


TREE e() {
	TREE a = t();
	if(a == NULL) return NULL;
	TREE b = tt();
	if(b == NULL) return NULL;
	return TRUE; // change this to return a tree
}

TREE tt() {

	if(!lookAhead('+') && !lookAhead('-')) {
		return TRUE; //change this to return a tree
	} else {

		if(!matchTerminal('+') && !matchTerminal('-')) return 0;
		TREE a = tt();
		if(a == NULL) return NULL;
		TREE b = tt();
		if(b == NULL) return NULL;
		return TRUE; // change this to return a tree

	}

}

TREE t() {

}







int main() {

	printf("Recursive-descent parser\n");

	while(getchar() != EOF) {

	}



}
