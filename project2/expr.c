//This is a C file

#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<errno.h>
#define MAX_SIZE 200

#define TRUE 1
#define FALSE 0
typedef int BOOLEAN;


typedef struct NODE *TREE;

char *nextTerminal;
TREE parseTree;


TREE D(); //D
TREE P(); //P
TREE N(); // N
TREE F(); //F
TREE G(); //G
TREE T(); //T
TREE U(); //U

struct NODE {

	char label;
	TREE leftmostChild, rightSibling, parent;

};


BOOLEAN lookAhead(char c) {
	return *nextTerminal == c;
}

BOOLEAN matchTerminal(char c) {

	if(*nextTerminal == c) {
		nextTerminal++;
		return TRUE;
	} else {
		return FALSE;
	}

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


//Recursive descent parser function start here
TREE E() {
	TREE a = T();
	if(a == NULL) return NULL;
	TREE b = U();
	if(b == NULL) return NULL;
	return makeNode2('E', a,b);
}


TREE U() {

	if(!lookAhead('+') && !lookAhead('-')) {
		return makeNode1('U', makeNode0('e')); //E to denote condition that succeeds immeditately
	} else if(matchTerminal('+')){


		//&& !matchTerminal('-')) return NULL;
		TREE a = T();
		if(a == NULL) return NULL;
		TREE b = U();
		if(b == NULL) return NULL;
		return makeNode3('U',makeNode0('+'), a,b); // change this to return a tree

	} else if(matchTerminal('-')) {

		TREE a = U();
		if(a == NULL) return NULL;
		TREE b = U();
		if(b == NULL) return NULL;
		return makeNode3('U', makeNode0('-'), a, b); // change this to return a tree

	} else return NULL;
}

TREE T() {

	TREE a = F();
	if(a == NULL) return NULL;
	TREE b = G();
	if(b == NULL) return NULL;
	return makeNode2('T', a,b); //need to return the tree instead

}


TREE G() {
	if(!lookAhead('*') && !lookAhead('/')) {
		return makeNode1('G', makeNode0('e')); //actually a tree;
	} else if(matchTerminal('*')){

		TREE a = F();
		if(a == NULL) return NULL;
		TREE b = G();
		if(b == NULL) return NULL;

		return makeNode3('G',makeNode0('*'), a, b);//actually some tree we have to see what


	} else if(matchTerminal('/')) {
		TREE a = F();
		if(a == NULL) return NULL;
		TREE b = G();
		if(b == NULL) return NULL;

		return makeNode3('G',makeNode0('/'), a, b);//actually some tree we have to see what



	} else return NULL;

}


TREE F() {
	if(lookAhead('(')) {

		if(!matchTerminal('(')) return NULL;
		TREE a = E();
		if(a == NULL) return NULL;
		if(!matchTerminal(')')) return NULL;
		return makeNode3('F',makeNode0('('), a, makeNode0(')')); //actually some tree;

	} else {

		TREE b = N();
		if(b == NULL) return NULL;
		return makeNode1('F', b);//actually some tree we don't know what
		//return makeNode0('N');
	}
}


TREE N() {
	TREE a = D();
	if(a == NULL) return NULL;
	TREE b = P();
	if(b == NULL) return NULL;

	return makeNode2('N', a, b); //really a tree
}

TREE P() {//how the fuck do I do this?? // <P> -> <N> | e

	TREE a = N();
	if(a == NULL) {
		return makeNode1('P', makeNode0('e'));
	}

		return makeNode1('P', a);

}


TREE D() {


	//printf("i changed this\n" );

	if(matchTerminal('0')) {
		return makeNode1('D',makeNode0('0'));
	} else if(matchTerminal('1')) {
			return makeNode1('D',makeNode0('1'));
	} else if(matchTerminal('2')) {
			return makeNode1('D',makeNode0('2'));
	} else if(matchTerminal('3')) {
			return makeNode1('D',makeNode0('3'));
	} else if(matchTerminal('4')) {
			return makeNode1('D',makeNode0('4'));
	} else if(matchTerminal('5')) {
			return makeNode1('D',makeNode0('5'));
	} else if(matchTerminal('6')) {
			return makeNode1('D',makeNode0('6'));
	} else if(matchTerminal('7')) {
			return makeNode1('D',makeNode0('7'));
	} else if(matchTerminal('8')) {
			return makeNode1('D',makeNode0('8'));
	} else if(matchTerminal('9')) {
			return makeNode1('D',makeNode0('9'));
	} else {
			return NULL;
	}


}


void printParseTree(TREE parseTree, int level) {

	//printf("\n");

	TREE c; //child of parse tree root

	for(int i = 0; i<=level; i++) {
		printf("       ");
	}
	printf("%c\n", parseTree->label);
	c = parseTree->leftmostChild;
	while(c!=NULL) {
		printParseTree(c, level+1);
		c = c->rightSibling;
	}

}

/*
*Code for the table driven parser hereon
*
*/

BOOLEAN isTerminal(char a){

	//printf("Value of char a in isTerminal = %c", a);
	char b[16] = {'0','1','2','3','4','5','6','7','8','9','(',')','*','/','+','-'};
	for(int i=0;i<16;i++) {
		if(b[i] == a){
			return TRUE;
			//printf("Returning TRUE from isTerminal\n" );
		}
	}
//printf("Returning FALSE from isTerminal\n");
	return FALSE;
}

BOOLEAN isNumber(char a){

	//printf("Value of char a in isTerminal = %c", a);
	char b[16] = {'0','1','2','3','4','5','6','7','8','9'};
	for(int i=0;i<16;i++) {
		if(b[i] == a){
			return TRUE;
			//printf("Returning TRUE from isTerminal\n" );
		}
	}
//printf("Returning FALSE from isTerminal\n");
	return FALSE;
}

typedef char stackElement;
typedef struct  {
	stackElement *contents;
	int top;
	int maxSize;
} STACK;

void stackInit(STACK *stack, int maxSize);
void stackDestroy(STACK *stack);
BOOLEAN stackIsEmpty(STACK *stack);
BOOLEAN stackIsFull(STACK *stack);
void stackPush(STACK *stack, stackElement element);
stackElement stackPop(STACK *stack);
int lookUp(stackElement poppedElement, char nextTerminal);

void stackInit(STACK *stack, int maxSize) {
	stackElement *newContents;
	newContents = (stackElement *) malloc(sizeof(stackElement) * maxSize);

	if(newContents == NULL) {
		fprintf(stderr, "Insufficient memory to initialize the stack. \n");
		exit(1);
	}

	stack->contents = newContents;
	stack->maxSize = maxSize;
	stack->top=-1;
}

void stackDestroy(STACK *stack) {
	free(stack->contents);
	stack->contents = NULL;
	stack->maxSize = 0;
	stack->top = -1;


}


BOOLEAN stackIsEmpty(STACK *stack) {
	return stack->top < 0;
}

BOOLEAN stackIsFull(STACK *stack) {
	return stack->top >= stack->maxSize -1;

}

void stackPush(STACK *stack, stackElement element) {
	if(stackIsFull(stack)) {
		printf("Can't push on stack because it's full!\n");
	} else {
		stack->contents[++stack->top] = element;
	}

}

stackElement stackPop(STACK *stack){
	if(stackIsEmpty(stack)) {
		printf("Stack is empty!");
		return '!';
	} else {
		return stack->contents[stack->top--];
	}

}


STACK parserStack;

TREE tableDrivenParser(stackElement element) {
	TREE t;
	if(!stackIsEmpty(&parserStack)) {
		/*stackElement popped =*/ stackPop(&parserStack);
		//printf("Popped: %c Element: %c nextTerminal: %c\n", popped, element, *nextTerminal);

		if(element == 'E') {
			if(lookAhead('0') ||lookAhead('1')||lookAhead('2') ||lookAhead('3') ||lookAhead('4')||lookAhead('5') || lookAhead('6') ||lookAhead('7')||lookAhead('8') || lookAhead('9') || lookAhead('(')){
			stackPush(&parserStack, 'U');
			stackPush(&parserStack, 'T');
			t = makeNode1('E', tableDrivenParser('T'));
			t->leftmostChild->rightSibling = tableDrivenParser('U');
		} else if(lookAhead('s')) {

stackPush(&parserStack, 'E');
			stackPush(&parserStack, 's');
			matchTerminal('s');
			t = makeNode1('E', makeNode0('s'));
			t->leftmostChild->rightSibling = tableDrivenParser('E');

		} else if(lookAhead('c')) {
			stackPush(&parserStack, 'E');
			stackPush(&parserStack, 'c');
			matchTerminal('c');
			t = makeNode1('E', makeNode0('c'));
			t->leftmostChild->rightSibling = tableDrivenParser('E');

		} else if(lookAhead('t')) {
			stackPush(&parserStack, 'E');
			stackPush(&parserStack, 't');
			matchTerminal('t');
			t = makeNode1('E', makeNode0('t'));
			t->leftmostChild->rightSibling = tableDrivenParser('E');
		}
		else {
			perror("Not parsable by table driven parser! Try a well formed expression");
			//exit(EXIT_FAILURE);
			//printf("An error occured at E");
		}
	}

		if(element == 'U' ){
			if(lookAhead('+')) {
				matchTerminal('+');
				stackPush(&parserStack,'U');
				stackPush(&parserStack, 'T');
				stackPush(&parserStack, '+');
				t = makeNode1('U', makeNode0('+'));
				t->leftmostChild->rightSibling = tableDrivenParser('T');
				t->leftmostChild->rightSibling->rightSibling = tableDrivenParser('U');

			}
			else if(element == 'U' && *nextTerminal == '-') {
			matchTerminal('-');
			stackPush(&parserStack,'U');
			stackPush(&parserStack, 'T');
			stackPush(&parserStack, '-');
			t = makeNode1('U', makeNode0('-'));
			t->leftmostChild->rightSibling = tableDrivenParser('T');
			t->leftmostChild->rightSibling->rightSibling = tableDrivenParser('U');
		} else {
			t = makeNode1('U',makeNode0('e'));
		}
	}

		if(element == 'T'){
			if(lookAhead('0') ||lookAhead('1')||lookAhead('2') ||lookAhead('3') ||lookAhead('4')||lookAhead('5') || lookAhead('6') ||lookAhead('7')||lookAhead('8') || lookAhead('9') || lookAhead('(')){
			stackPush(&parserStack, 'G');
			stackPush(&parserStack, 'F');
			t = makeNode1('T',tableDrivenParser('F'));
			t->leftmostChild->rightSibling = tableDrivenParser('G');
			//printf("%c\n", t->label);
		} else {
			perror("Not parsable by table driven parser! Try a well formed expression");
			//exit(EXIT_FAILURE);
			//printf("An error occured at T");
		}

	}

		if(element == 'G' ) {
			if(lookAhead('*')){
			matchTerminal('*');
			stackPush(&parserStack, 'G');
			stackPush(&parserStack, 'F');
			stackPush(&parserStack, '*');
			t = makeNode1('G',makeNode0('*'));
			t->leftmostChild->rightSibling = tableDrivenParser('F');
			t->leftmostChild->rightSibling->rightSibling = tableDrivenParser('G');
		} else if(lookAhead('/')) {
			matchTerminal('/');
			stackPush(&parserStack, 'G');
			stackPush(&parserStack, 'F');
			stackPush(&parserStack, '/');
			t = makeNode1('G',makeNode0('/'));
			t->leftmostChild->rightSibling = tableDrivenParser('F');
			t->leftmostChild->rightSibling->rightSibling = tableDrivenParser('G');

		} else {
			t = makeNode1('G', makeNode0('e'));
		}
	}

		if(element == 'F'){
			if(lookAhead('0') ||lookAhead('1')||lookAhead('2') ||lookAhead('3') ||lookAhead('4')||lookAhead('5') || lookAhead('6') ||lookAhead('7')||lookAhead('8') || lookAhead('9')){
				stackPush(&parserStack, 'N');
				t = makeNode1('F',tableDrivenParser('N'));
			} else if(lookAhead('(')) {
				matchTerminal('(');
				stackPush(&parserStack, ')');
				stackPush(&parserStack, 'E');
				stackPush(&parserStack, '(');
				t = makeNode1('F',makeNode0('('));

				t->leftmostChild->rightSibling = tableDrivenParser('E');
				t->leftmostChild->rightSibling->rightSibling = makeNode0(')');
				matchTerminal(')');
			} else {
				perror("Not parsable by table driven parser! Try a well formed expression");
				//exit(EXIT_FAILURE);
				//printf("Error at F\n" );
			}
		}

			if(element == 'N'){
				if(lookAhead('0') ||lookAhead('1')||lookAhead('2') ||lookAhead('3') ||lookAhead('4')||lookAhead('5') || lookAhead('6') ||lookAhead('7')||lookAhead('8') || lookAhead('9')){
					stackPush(&parserStack, 'P');
					stackPush(&parserStack, 'D');
					t = makeNode1('N',tableDrivenParser('D'));
					t->leftmostChild->rightSibling = tableDrivenParser('P');


				} else {
					perror("Not parsable by table driven parser! Try a well formed expression");
					//exit(EXIT_FAILURE);
					//printf("Error at N");
				}
			}

				if(element == 'P') {
					if(lookAhead('0') ||lookAhead('1')||lookAhead('2') ||lookAhead('3') ||lookAhead('4')||lookAhead('5') || lookAhead('6') ||lookAhead('7')||lookAhead('8') || lookAhead('9')){
						stackPush(&parserStack, 'N');
						t = makeNode1('P',tableDrivenParser('N'));
					} else {
						t = makeNode1('P', makeNode0('e'));
					}
				}

					if(element == 'D') {
						if(lookAhead('0')) {
						matchTerminal('0');
						t = makeNode1('D', makeNode0('0'));
					} else if (element == 'D' && *nextTerminal == '1') {
						matchTerminal('1');
						t = makeNode1('D', makeNode0('1'));
					} else if (element == 'D' && *nextTerminal == '2') {
						matchTerminal('2');
						t = makeNode1('D', makeNode0('2'));
					} else if (element == 'D' && *nextTerminal == '3') {
						matchTerminal('3');
						t = makeNode1('D', makeNode0('4'));
					}  else if (element == 'D' && *nextTerminal == '4') {
						matchTerminal('4');
						t = makeNode1('D', makeNode0('4'));
					} else if (element == 'D' && *nextTerminal == '5') {
						matchTerminal('5');
						t = makeNode1('D', makeNode0('5'));
					} else if (element == 'D' && *nextTerminal == '6') {
						matchTerminal('6');
						t = makeNode1('D', makeNode0('6'));
					} else if (element == 'D' && *nextTerminal == '7') {
						matchTerminal('7');
						t = makeNode1('D', makeNode0('7'));
					} else if (element == 'D' && *nextTerminal == '8') {
						matchTerminal('8');
						t = makeNode1('D', makeNode0('8'));
					} else if (element == 'D' && *nextTerminal == '9') {
						matchTerminal('9');
						t = makeNode1('D', makeNode0('9'));
					} else {
						perror("Not parsable by table driven parser! Try a well formed expression");

					}
				}




	}

	return t;
}


double calcTree(TREE t) {

if (t->label == 'E') {
   return calcTree(t->leftmostChild) + calcTree(t->leftmostChild->rightSibling);
}

if (t->label == 'T') {
   return calcTree(t->leftmostChild) * calcTree(t->leftmostChild->rightSibling);
}

if (t->label == 'F') {
   if (t -> leftmostChild->label != '(') {
		 return calcTree(t->leftmostChild); //N
	 } else {
		 //printf("Leaving the (E) guy\n" );
		 return calcTree(t->leftmostChild->rightSibling); //E
	 }
}

if (t->label == 'N') {

   if (t -> leftmostChild-> rightSibling -> leftmostChild->label == 'e') {
      return calcTree(t->leftmostChild);
   } else {
      return (calcTree(t->leftmostChild)+ 10*calcTree(t->leftmostChild->rightSibling));
}
}

if (t->label == 'P') {
   if(t->leftmostChild->label == 'e'){
          //return NULL;  //return empty string
				 return 0;
   }
   else {
    return calcTree(t->leftmostChild);
   }
}

if (t->label == 'G') {
        if(t->leftmostChild->label=='e') {
            return 1;
						//return NULL;
        }
        else if(t->leftmostChild->label=='*'){
           return calcTree(t->leftmostChild->rightSibling) * calcTree(t->leftmostChild->rightSibling->rightSibling);
        }
        else if(t->leftmostChild->label=='/'){
           return 1/(calcTree(t->leftmostChild->rightSibling) * calcTree(t->leftmostChild->rightSibling->rightSibling));
        }

}

if(t->label=='D'){
    if(t->leftmostChild->label=='0'){
       return 0;
		 }
    else if(t->leftmostChild->label=='1'){
        return 1;
    }
    else if(t->leftmostChild->label=='2'){
        return 2;
    }
     else if(t->leftmostChild->label=='3'){
        return 3;
    } else if(t->leftmostChild->label=='4'){
        return 4;
    } else if(t->leftmostChild->label=='5'){
        return 5;
    } else if(t->leftmostChild->label=='6'){
        return 6;
    } else if(t->leftmostChild->label=='7'){
        return 7;
    } else if(t->leftmostChild->label=='8'){
        return 8;
    } else if(t->leftmostChild->label=='9'){
        return 9;
    }
}

if(t->label == 'U'){
    if(t->leftmostChild->label=='e'){
          return 0;
					//return NULL;
    }
    else if(t->leftmostChild->label=='+'){
        return calcTree(t->leftmostChild)+calcTree(t->leftmostChild->rightSibling);
    }
    else if(t->leftmostChild->label=='-'){
        return -(calcTree(t->leftmostChild)+calcTree(t->leftmostChild->rightSibling));
    }

}


//printf("We are at the end\n" );
return 0;
}


char *nextTerminal0, *nextTerminal1;


int main() {

	nextTerminal  = malloc(sizeof(char *));
	nextTerminal0 = malloc(sizeof(char *));
	nextTerminal1 = malloc(sizeof(char *));
printf("Press return key to continue.");

while(getchar()!=EOF) {
	printf("Expression: ");
	stackInit(&parserStack, MAX_SIZE);
	stackPush(&parserStack, 'E');

	scanf("%s", nextTerminal);
	strcpy(nextTerminal0, nextTerminal);
	strcpy(nextTerminal1, nextTerminal);

	parseTree = E();
	nextTerminal = nextTerminal0;
	TREE parseTree0 = tableDrivenParser('E');
	nextTerminal = nextTerminal1;

	if(parseTree0 == NULL){
		printf("Not parsable by recursive descent parser! Try a well formed expression.\n");
	} else {
		double ans = calcTree(parseTree);

		printf("Recursive descent parser tree:\n");
		printParseTree(parseTree,0);
		printf("Table driven parser tree:\n" );

		printParseTree(parseTree0,0);
		char *a;
		sprintf(a,"%f", ans);

		printf("Answer: %f\n", strrev(a));
		stackDestroy(&parserStack);
	}

}

}
