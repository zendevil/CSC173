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

TREE makeNode0(char x) {
	TREE root;
	root = (TREE) malloc(sizeof(struct NODE));
	root->label = x;
	root->leftmostChild = NULL;
	root->rightSibling = NULL;
	return root;
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

		if(!matchTerminal('+') && !matchTerminal('-')) return NULL;
		TREE a = tt();
		if(a == NULL) return NULL;
		TREE b = tt();
		if(b == NULL) return NULL;
		return TRUE; // change this to return a tree

	}

}

TREE t() {

	TREE a = f();
	if(a == NULL) return NULL;
	TREE b = ft();
	if(b == NULL) return NULL;
	return TRUE; //need to return the tree instead

}


TREE ft() {
	if(!lookAhead('*') && !lookAhead('/')) {
		return TRUE; //actually a tree;
	} else {
		if(!matchTerminal('*') && !matchTerminal('/')) return NULL;
		TREE a = f();
		if(a == NULL) return NULL;
		TREE b = ft();
		if(b == NULL) return NULL;

		return TRUE;//actually some tree we have to see what

	}

}


TREE f() {
	if(lookAhead('(')) {

		if(!matchTerminal('(')) return NULL;
		TREE a = e();
		if(a == NULL) return NULL;
		if(!matchTerminal(')')) return NULL;
		return TRUE; //actually some tree;

	} else {

		TREE b = n();
		if(n == NULL) return NULL;
		return TRUE;//actually some tree we don't know what

	}
}


TREE n() {
	TREE a = d();
	if(a == NULL) return NULL;
	TREE b = nt();
	if(b == NULL) return NULL;

	return TRUE; //really a tree
}

TREE nt() {//how the fuck do I do this?? // <NT> -> <N> | e

}


TREE d() {

	if(lookahead('0') || lookAhead('1') || lookAhead('2') || lookahead('3') || lookAhead('4') || lookAhead('5') || lookahead('6') || lookAhead('7') || lookAhead('8') ||lookAhead('9')) {
		return TRUE; //some tree really
	} else {
		return NULL;
	}

}






int main() {

	printf("Recursive-descent parser\n");

	while(getchar() != EOF) {

	}



}
