//This is a C file

#include <stdio.h>
#include <stdlib.h>
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
    (root->leftmostChild)->parent = root;

    return root;
}

TREE makeNode2(char x, TREE t1, TREE t2) {
	TREE root;
	root = makeNode1(x, t1);
	t1->rightSibling = t2;
    (t1->rightSibling)->parent = t1;
	return root;
}

TREE makeNode3(char x, TREE t1, TREE t2, TREE t3) {
	TREE root;
	root = makeNode2(x, t1,t2);
	t2->rightSibling = t3;
    (t2->rightSibling)->parent = t2;
    return root;
}

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
		return makeNode3('E',makeNode0('('), a, makeNode0(')')); //actually some tree;

	} else {

		TREE b = N();
		if(b == NULL) return NULL;
		return makeNode1('N', b);//actually some tree we don't know what

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
	if(a == NULL) return makeNode1('P', makeNode0('e'));
	else return makeNode1('P', a);

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
int addSubTree(TREE*parserTree, TREE temp, stackElement leaf) {

    printf("temp->label: %c\n", temp->label);
		printf("parserTree->label: %c\n", (*parserTree)->label);
		printf("This is the temp tree\n" );
		printParseTree(temp,0);
		printf("This is the parserTree\n");
		printParseTree(*parserTree,0);

    //satisfying condition where we add the subtree
    if((((*parserTree)->label) == leaf) && (((*parserTree)->leftmostChild) == NULL)){

			// TREE *temp1 = malloc(sizeof(TREE*));
			// temp1 = parserTree;
			//
			// *parserTree = temp; //add the subtree to the relevant leaf position
			// (*parserTree)->rightSibling = (*temp1)->rightSibling;

		(*parserTree)->leftmostChild = temp; //add the subtree to the relevant leaf position

		printf("This is the parserTree after assignment\n");
		printParseTree(*parserTree,0);

		// if((*parserTree)->rightSibling == NULL) {
		// 	printf("rightSibling doesn't exist for: %c", (*parserTree)->label);
		// } else {
		// 	printf("rightSibling exists for: %c and is %c!\n", (*parserTree)->label,(*parserTree)->rightSibling->label );
		// }
		return TRUE; // we wouldn't need the value of this return I think

    }
    //if it's not the leaf
    else if(((*parserTree)->leftmostChild) != NULL){

        printf("This is leftmostChild: %c\n", ((*parserTree)->leftmostChild)->label);

        //printf("Right sibling is still intact: %c\n",((*parserTree)->leftmostChild)->rightSibling->label);

        if(!addSubTree(&((*parserTree)->leftmostChild),temp, leaf)) {
					addSubTree(&(*parserTree)->rightSibling,temp,leaf);
				}

	}
    //if it's a terminal with siblings then move to the right sibling
    else if(isTerminal((*parserTree)->label) && (*parserTree)->rightSibling != NULL) {

        //		printf("We come here!3\n" );
        printf("this is the right sibling right now: %c", ((*parserTree)->rightSibling)->label);
        addSubTree(&((*parserTree)->rightSibling),temp, leaf);

    }
   //if it's a terminal with no right siblings then move to the parent
    else if((*parserTree)->rightSibling == NULL && isTerminal((*parserTree)->label)) {
        //addSubTree(&(((*parserTree)->parent)->rightSibling), temp);
				return FALSE;

    }

    return FALSE; //we wouldn't really use the value of this return I think
}




int parsingTable[8][17] = {
	{0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,0,0},
	{0,0,3,12,0,0,0,0,0,0,0,0,0,0,0,0,2},
	{0,0,0,0,4,4,4,4,4,4,4,4,4,4,4,0,0},
	{6,13,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5},
	{0,0,0,0,8,8,8,8,8,8,8,8,8,8,7,0,0},
	{0,0,0,0,9,9,9,9,9,9,9,9,9,9,0,0,0},
	{0,0,0,0,11,11,11,11,11,11,11,11,11,11,0,0,10},
	{0,0,0,0,14,15,16,17,18,19,20,21,22,23,0,0,0}
};


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



int lookUp(stackElement poppedElement, char nextTerminal) {
	unsigned int i,j;

	if(poppedElement == 'E') {
		i = 0;
	} else if (poppedElement == 'U') {
		i = 1;
	} else if (poppedElement == 'T') {
		i = 2;
	} else if (poppedElement == 'G') {
		i = 3;
	} else if (poppedElement == 'F') {
		i = 4;
	} else if (poppedElement == 'N') {
		i = 5;
	} else if (poppedElement == 'P') {
		i = 6;
	} else if (poppedElement == 'D') {
		i = 7;
	} else {
		i = -1;
		printf("Something is wrong in lookUp. poppedElement was not matched");
	}

	if(nextTerminal == '*') {
		j = 0;
	} else if(nextTerminal == '/') {
		j = 1;
	} else if(nextTerminal == '+') {
		j = 2;
	} else if(nextTerminal == '-') {
		j = 3;
	} else if(nextTerminal == '0') {
		j = 4;
	} else if(nextTerminal == '1') {
		j = 5;
	} else if(nextTerminal == '2') {
		j = 6;
	} else if(nextTerminal == '3') {
		j = 7;
	} else if(nextTerminal == '4') {
		j = 8;
	} else if(nextTerminal == '5') {
		j = 9;
	} else if(nextTerminal == '6') {
		j = 10;
	} else if(nextTerminal == '7') {
		j = 11;
	} else if(nextTerminal == '8') {
		j = 12;
	} else if(nextTerminal == '9') {
		j = 13;
	} else if(nextTerminal == '(') {
		j = 14;
	} else if(nextTerminal == ')') {
		j = 15;
	}

	//for the null cases

	if((poppedElement == 'U' && nextTerminal != '+' && nextTerminal != '-') || (poppedElement == 'G' && nextTerminal != '*' && nextTerminal != '/') || (poppedElement == 'P' && !isNumber(nextTerminal))) {
		j=16;
	}

	return parsingTable[i][j];
}


TREE getTreeFromTable(int production, STACK * parserStack) {

	TREE temp;
	TREE rightSibling1 = malloc(sizeof(TREE));
	TREE rightSibling2 = malloc(sizeof(TREE));
	//TREE rightSibling3 = malloc(sizeof(TREE));
	switch(production) {



		case 1:
			stackPush(parserStack, 'U');
			stackPush(parserStack, 'T');

			//temp = makeNode2('E', makeNode0('T'), makeNode0('U'));
			temp = makeNode0('T');
			rightSibling1 = makeNode0('U');
			temp->rightSibling = rightSibling1;
			break;

		case 2:

			//temp = makeNode1('U', makeNode0('e'));

			temp =  makeNode0('e');

			break;

		case 3:
			stackPush(parserStack,'U');
			stackPush(parserStack,'T');
			stackPush(parserStack,'+');

			//temp = makeNode3('U', makeNode0('+'), makeNode0('T'), makeNode0('U'));
			temp = makeNode0('+');
			rightSibling1 = makeNode0('T');
			rightSibling2 = makeNode0('U');
			temp->rightSibling = rightSibling1;
			rightSibling1->rightSibling = rightSibling2;
			break;

		case 4:
			stackPush(parserStack,'G');
			stackPush(parserStack,'F');

			//temp = makeNode2('T', makeNode0('F'), makeNode0('G'));
			temp = makeNode0('F');
			rightSibling1 = makeNode0('G');
			temp->rightSibling = rightSibling1;



			break;

		case 5:
			//temp = makeNode1('G', makeNode0('e'));
			temp = makeNode0('e');

		case 6:
			stackPush(parserStack,'G');
			stackPush(parserStack,'F');
			stackPush(parserStack,'*');

			///temp = makeNode3('G', makeNode0('*'), makeNode0('F'), makeNode0('G'));
			temp = makeNode0('*');
			rightSibling1 = makeNode0('F');
			rightSibling2 = makeNode0('G');
			temp->rightSibling = rightSibling1;
			rightSibling1->rightSibling = rightSibling2;
			break;

		case 7:
			stackPush(parserStack,')');
			stackPush(parserStack,'E');
			stackPush(parserStack,'(');

			//temp = makeNode3('F', makeNode0('('), makeNode0('E'), makeNode0(')'));

			temp = makeNode0('(');
			rightSibling1 = makeNode0('E');
			rightSibling2 = makeNode0(')');
			temp->rightSibling = rightSibling1;
			rightSibling1->rightSibling = rightSibling2;

			break;

		case 8:
			stackPush(parserStack,'N');

			//temp = makeNode1('F', makeNode0('N'));

			temp = makeNode0('N');

			break;

		case 9:
			stackPush(parserStack,'P');
			stackPush(parserStack,'D');

			//temp = makeNode2('N', makeNode0('D'), makeNode0('P'));

			temp = makeNode0('D');
			rightSibling1 = makeNode0('P');
			temp->rightSibling = rightSibling1;



			break;

		case 10:

			//temp = makeNode1('P', makeNode0('e'));

			temp = makeNode0('e');
			break;


		case 11:
			stackPush(parserStack,'N');

			//temp = makeNode1('P', makeNode0('N'));
			temp = makeNode0('N');


			break;

		case 12:
			stackPush(parserStack,'U');
			stackPush(parserStack,'T');
			stackPush(parserStack,'-');

			//temp = makeNode3('U', makeNode0('-'), makeNode0('T'), makeNode0('U'));
			temp = makeNode0('-');
			rightSibling1 = makeNode0('T');
			rightSibling2 = makeNode0('U');
			temp->rightSibling = rightSibling1;
			rightSibling1->rightSibling = rightSibling2;

			break;

		case 13:
			stackPush(parserStack,'G');
			stackPush(parserStack,'F');
			stackPush(parserStack,'/');

			//temp = makeNode3('G', makeNode0('/'), makeNode0('F'), makeNode0('G'));
			temp = makeNode0('/');
			rightSibling1 = makeNode0('F');
			rightSibling2 = makeNode0('G');
			temp->rightSibling = rightSibling1;
			rightSibling1->rightSibling = rightSibling2;
			break;

		case 14:
			stackPush(parserStack,'0');

			//temp = makeNode1('D', makeNode0('0'));
			temp = makeNode0('0');


			break;

		case 15:
			stackPush(parserStack,'1');

			//temp = makeNode1('D', makeNode0('1'));
			temp = makeNode0('1');

			break;

		case 16:
			stackPush(parserStack,'2');

			//temp = makeNode1('D', makeNode0('2'));
			temp = makeNode0('2');

			break;

		case 17:
			stackPush(parserStack,'3');

			//temp = makeNode1('D', makeNode0('3'));
			temp = makeNode0('3');

			break;

		case 18:
			stackPush(parserStack,'4');

			//temp = makeNode1('D', makeNode0('4'));
			temp = makeNode0('4');
			break;

		case 19:
			stackPush(parserStack,'5');

			//temp = makeNode1('D', makeNode0('5'));
			temp = makeNode0('5');
			break;

		case 20:
			stackPush(parserStack,'6');

			//temp = makeNode1('D', makeNode0('6'));
			temp = makeNode0('6');
			break;

		case 21:
			stackPush(parserStack,'7');

			//temp = makeNode1('D', makeNode0('7'));
			temp = makeNode0('7');
			break;

		case 22:
			stackPush(parserStack,'8');

			//temp = makeNode1('D', makeNode0('8'));
			temp = makeNode0('8');

			break;

		case 23:
			stackPush(parserStack,'9');

			//temp = makeNode1('D', makeNode0('9'));
			temp = makeNode0('9');

			break;

	}


	return temp;

}




TREE tableDrivenParser(){
	TREE TDParserTree = makeNode0('E'); //initialize the tree with syntactic category at the root
	STACK parserStack;

	stackInit(&parserStack, MAX_SIZE);
	stackPush(&parserStack, 'E');
	int production;

	while(!stackIsEmpty(&parserStack) /*&& nextTerminal != '\0'*/){

		//popping the element from the stack
		stackElement poppedElement = stackPop(&parserStack);
		printf("Popped: %c\n", poppedElement);
		printf("current terminal: %c\n", *nextTerminal);

		if(isTerminal(poppedElement)) {
			if(!matchTerminal(poppedElement)) {
				printf("It doesn't work\n" );
				//break;
			}
			//matchTerminal(poppedElement);

		} else {
			//printf("\nSending this poppedElement to lookUp: %c. nextTerminal: %c\n",poppedElement,*nextTerminal );
				production = lookUp(poppedElement, *nextTerminal);
				printf("production: %d\n", production);
				if(production==0) {
					printf("Breaking bad 1\n" );
					break;
				}


				TREE temp = getTreeFromTable(production, &parserStack);

				//printf("Checking if the U exists: %c", TDParserTree->leftmostChild->rightSibling->label);

				printf("Going to addSubTree....................\n");
				addSubTree(&TDParserTree, temp, poppedElement);
				printf("Returning from addSubTree..............\n");

				printf("the TDParserTree:\n");
				printParseTree(TDParserTree,0);
				printf("\n\n\n\n");
		}

        //printf("Do we ever come here?");

	}
	//printf("We're out of the while loop\n" );

	if(*nextTerminal == '\0') {
		printf("Entire input was consumed\n");

	} else {
		printf("It failed sorry, the nextTerminal value is actually: %c\n", *nextTerminal );
	}
    //printf("Do we ever come here????????");
    //printf("Checking if the U exists: %c", TDParserTree->leftmostChild->rightSibling->label);
    return TDParserTree;
}





/* int eval(TREE n){ */
    /* int val1, val2; */
/* } */



//code for problem 3
/*
void treeEval(*TREE t) {
    TREE left = *t -> leftMostChild;
    //TREE center = t -> center;
    TREE right = t -> rightSibling;

    if (leftMostChild != NULL && left -> label == 0)
	evaluate_tree(left);
  //  if (center != NULL && center -> terminal == 0)
	//evaluate_tree(center);
    if (rightSibling  != NULL && rightSibling -> t == 0)
	evaluate_tree(right);

    if (left != NULL && strcmp(left -> data, "empty string") == 0) {
        free(left);
        t -> left = NULL;
    } if (center != NULL && strcmp(center->data, "empty string") == 0) {
        free(center);
        t->center = NULL;
    } if (right != NULL && strcmp(right->data, "empty string") == 0) {
        free(right);
        t->right = NULL;
    }

    left = t -> left;
    center = t -> center;
    right = t -> right;

*/







int main() {

	nextTerminal  = malloc(sizeof(char *));
// printf("Recursive descent parser (Press return key to continue)");
//
// while(getchar()!=EOF) {
// 	printf("Expression: ");
//
// 	scanf("%s", nextTerminal);
//
// 	parseTree = E();
// 	if(parseTree == NULL){
// 		printf("Expression is not well formed\n");
// 	} else {
// 		printParseTree(parseTree,0);
// 	}
//
// }

	printf("Table driven parser (Press return key to continue)\n");
while(getchar()!=EOF) {
	printf("Input Expression: ");

	scanf("%s", nextTerminal);
	printf("\n\n\n\n" );


	TREE parseTree0 = tableDrivenParser();

	if(parseTree0 == NULL) {
		printf("Expression is not well formed\n");
	} else {

        //printf("Trying to print the tree in the main function\n");
				printf("Parsed tree using table driven parsing: \n");
        printParseTree(parseTree0,0);
	}


}






}
