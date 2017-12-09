#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdarg.h>
#include<assert.h>
#define NBUCKETS 5
#include "mydatabase.h"

typedef struct Tuple {
  int nAttr;
  char **attr;
  char *key;
  char *secIndex;
  Tuple *next;
} Tuple;
typedef struct Tuple* List;
typedef List Hashtable[NBUCKETS];

typedef struct Node* Tree;

typedef struct Node {
  char* secIndex; //calling it secondary attribute
  Tuple toTuple[NBUCKETS*2]; //really a pointer to multiple tuples
  Tree lc;
  Tree rc;
} Node;


Node* nodeNew(char* secIndex, Tuple* toTuple){
	Node *n = (Node*)malloc(sizeof(Node));
	n->secIndex = secIndex;
	//n->toTuple = malloc(sizeof(char*)*NBUCKETS*2);
	
		for(int i=0; i<NBUCKETS*2; i++) {
			if(toTuple)
				n->toTuple[i]\
				= toTuple[i];
		}
	/*int i=0;
	while(toTuple[i]!=NULL){
		n->toTuple[i]\
		= toTuple[i];
		i++;
	}*/

	//n->toTuple = toTuple;
	n->lc = NULL;
	n->rc = NULL;
	return n;
}
/*
List* treeSearch(Tuple t, Tree root){
	if(root == NULL) return NULL;
	else if(!strcmp(root->secIndex, t.secIndex) && t.toTuple == root->toTuple) return root->toTuple;
	else if(strcmp(t.secIndex, root->secIndex) <= 0) return treeSearch(t, root->lc);
	else return treeSearch(t, root->rc);
}*/

Node* treeSearch(Tuple t, Tree root) {
	if(root == NULL) return root;
	else if(!strcmp(root->secIndex, t.secIndex)) return root;
	else if(strcmp(t.secIndex, root->secIndex) <= 0) return treeSearch(t, root->lc);
	else return treeSearch(t, root->rc);
}

Tree findMin(Tree root) {
	while(root->lc != NULL) root = root->lc;
	return root;
}
Tree treeDelete(Node n, Tree root) {
	if(root == NULL) return root;
	else if(strcmp(n.secIndex, root->secIndex) < 0) root->lc = treeDelete(n, root->lc);
	else if(strcmp(n.secIndex, root->secIndex) > 0) root->rc = treeDelete(n, root->rc);
	else {
		//case 1: no child
		if(root->lc == NULL && root->rc == NULL) {
			free(root);
			root = NULL;
		
		} else if(root->lc == NULL) {
			Tree temp = root;
			root =  root->rc;
			free(temp);
		} else if(root->rc == NULL) {
			Tree temp = root;
			root = root->lc;
			free(temp);
			
		} else {
			Tree temp = findMin(root->rc);
			root->secIndex = temp->secIndex;
			root->rc = treeDelete(*temp, root->rc);
		}
	}
	return root;
}

Tree treeInsert(Node n, Tree root) {
	if(root == NULL){
		root = nodeNew(n.secIndex, n.toTuple);
	} else if(strcmp(n.secIndex,root->secIndex) <= 0 ) {
		root->lc = treeInsert(n, root->lc);
	} else {
		root->rc = treeInsert(n, root->rc);
		}
		return root;
}
/*
Tree treeSearch(Tree root, char* arg) {
	if(root == NULL) return NULL;
	else if(strcmp(arg, root->secIndex) < 0) {
		root->lc = treeSearch(root->lc, arg);
	} else if(strcmp(arg, root->secIndex) > 0) {
		root->rc = treeSearch(root->rc, arg);
	}
	return root;
}
*/
Tuple tupleNew(int index, int secIndex, int nAttr, ...) {
  va_list valist;
  va_start(valist, nAttr); // initialize valist for nAttr number of arguments

  Tuple t;

  t.nAttr = nAttr;
  t.next = NULL;
  t.attr = malloc(sizeof(char*) * nAttr);

  for(int i = 0; i< nAttr; i++) {
	  
    t.attr[i] = va_arg(valist, char*);
	

  }
  
  t.key = t.attr[index];
  t.secIndex = t.attr[secIndex];
  va_end(valist);
  return t;

}

Tuple tupleNew2(int index1, int index2, int secIndex, int nAttr, ...) {
	
  va_list valist;
  va_start(valist, nAttr); // initialize valist for nAttr number of arguments
  
  Tuple t;

  t.nAttr = nAttr;
  t.next = NULL;
  t.attr = malloc(sizeof(char*) * nAttr);

  for(int i = 0; i< nAttr; i++) {
	  
    t.attr[i] = va_arg(valist, char*);
  }
  
  char *key;
  int len=0;
  len = strlen(t.attr[index1]) + strlen(t.attr[index2]);
  key = (char*)malloc(len+1);
  
  strcpy(key, t.attr[index1]);
  strcat(key, t.attr[index2]);
  //printf("key:%s\n", key);
  t.key = key; 
  t.secIndex = t.attr[secIndex];
  
  va_end(valist);
  //printf("t.key=%s\n", t.key);
  return t;

}

int matchSpecs(Tuple ct, Tuple lt) {
	if(ct.nAttr != lt.nAttr) {
		printf("Tuples have different length so cannot compare specs\n");
		
	} else {
		for(int i=0; i<ct.nAttr; i++) {
			if(strcmp(ct.attr[i], "*") && strcmp(ct.attr[i], lt.attr[i])) {
				printf("The specs don't match?\n");
				return 0;
			}
		}
		
		return 1;
	}
}

int hash(char* key) {

  int sum = 0;
  for (int i = 0; key[i] != '\0'; i++) {
    sum += key[i];
  }
  
  return sum % NBUCKETS;
}

int keyExists(char* key, List *l) {
	 List curr = *l;
	
	while(curr != NULL) {
		printf("key:%s, (*l)->key:%s\n", key, curr->key);
		if(!strcmp(key, curr->key))
			return 1;
		curr = curr->next;
	}

	return 0;
}
void addTuplePtr(Tree root, List *l) {
	for(int i=0; i<NBUCKETS*2; i++) {
		if(root->toTuple[i] == NULL)
			root->toTuple[i] = *l;
			break;
	}	
	printf("We came out. this is seriously bad\n");
}

Tree myTree;

void bucketInsert(Tuple t, List *l) {

  if(*l == NULL) {
    *l = (List) malloc(sizeof(Tuple));
    **l = t; //*l[0] = t;
	if(treeSearch(t, myTree) != NULL) {
		printf("secIndex found in tree\n");
		addTuplePtr(treeSearch(t, myTree), l);
	} else {
		printf("secIndex not found in tree\n");
		Node* node = nodeNew(t.secIndex,l); //a node which stores secIndex as domain; points to where *l points to
		myTree = treeInsert(*node, myTree);
		(*l)->next = NULL;
	}

  } else {
      bucketInsert(t, &((*l)->next));
  }
  
}

void insert(Tuple t, Hashtable h) {
  //printf("Inserting tuple with key %s into this index: %d\n", t.key, hash(t.key));
  printf("t.key in insert function: %s\n", t.key);
  if(keyExists(t.key, &h[hash(t.key)])) {
	  printf("cannot insert because key already exists\n");
  } else {
	  printf("inserting...\n");
	  bucketInsert(t, &(h[hash(t.key)]));
  }
  
}

int tupleCmp(Tuple a, Tuple b) {
	if(a.nAttr == b.nAttr && a.key == b.key) {
		for(int i=0; i< a.nAttr; i++) {
			//returns false if any of the attributes do not match
			if(a.attr[i] != b.attr[i]) {
				return 0;
			}
		}
		//if the above condition is 
		//never satisfied in the for loop, we return 1
		return 1;
	} else {
		printf("Number of attributes or keys don't match\n");
	}
	
	return 0;

}

void tuplePrint(Tuple t){
	//printf("tuple(");
	printf("%s, ", t.key);
	//printf("%d, ", t.nAttr);
	
	int i=0;
	for(; i<t.nAttr-1; i++) {
		if(t.key == t.attr[i])
			printf("(k)");
		if(t.secIndex == t.attr[i])
			printf("(k2)");
		printf("%s, ", t.attr[i]);

	}
	printf("%s", t.attr[i]);
	printf("\n");

}

void tablePrint(Hashtable h) {
	for(int i=0; i<NBUCKETS; i++) {
		Tuple *curr = h[i];
		while(curr != NULL) {
			tuplePrint(*curr);
			curr = curr->next;
		}
	}
}



void bucketDelete(Tuple t, List *head) {
	if(*head == NULL) {
		printf("Cannot delete from empty list\n");
	} else {
		Tuple *curr = *head;
		Tuple *trail = NULL;
		
		while(curr != NULL) {
			if(matchSpecs(t, *curr)) {
				break;
			} else {
				trail = curr;
				curr = curr->next;
			}
		}
		//case 2 not found tuple
		if(curr == NULL) {
			printf("tuple was not found\n");
		} else {
			//case 3 delete from head node
			if(*head == curr) {
				Node *n = nodeNew((*head)->attr[0], head);
				treeDelete(*n, myTree);
				*head = (*head)->next;				
		} else {//case 4 delete beyond head
			
			//Node *n = nodeNew(trail->next->attr[0], *head);
			//treeDelete(*n, myTree);
			trail->next = curr->next;
			
		}
		free(curr);
		}
	}
}



void delete(Tuple t, Hashtable h ) {
	printf("deleting...\n");
	if(!strcmp(t.key, "*")) {
		//find the tuple from secondary index
		
		/*Node *n = nodeNew(t.attr[0], NULL);
		if(*n == NULL) {
			printf("Nothing was found in the BST\n");
		}*/
		
		//passing in a tuple
		Node* n= treeSearch(t,myTree); //it does return the right node
		
		
		/*for(int i=0; i< NBUCKETS*2; i++) {
			*n->toTuple[i] = 0;
		}*/
		
		
		for(int i=0; i<NBUCKETS*2; i++) {
			if(matchSpecs(t,*n->toTuple[i])) { //segfaulting here
				bucketDelete(t, &n->toTuple[i]);
			}
		}
			//*n++; //let's try this
			
			printf("Trying to print t, %s\n", t.attr[0]);
			int i=0;
			while(n->toTuple[i]){
				if(matchSpecs(t, *(n->toTuple[i]))) {
					bucketDelete(t, &n->toTuple[i]);
				}
				i++;
		
			}
		
	} else {
		bucketDelete(t, &h[hash(t.key)]);
		
	}
}

Tuple bucketLookup(Tuple t, List *head) {
	if(*head == NULL) {
		printf("Cannot lookup from empty list\n");
	} else {
		Tuple *curr = *head;
		Tuple *trail = NULL;

		while(curr != NULL) {
			if(matchSpecs(t, *curr)) {
				tuplePrint(t);
				tuplePrint(**head);
				printf("specs are somehow matched\n");
				return **head;
				break;
			} else {
				trail = curr;
				curr = curr->next;
			}
		}
		//case 2 not found tuple
		if(curr == NULL) {
			printf("tuple was not found\n");
		}
		free(curr);
		}

}


Tuple lookup(Tuple t, Hashtable h){
	printf("\n\n");
    printf("looking up tuples that match the specs of ");
	tuplePrint(t);
	printf("\n");
    Tuple t1 = bucketLookup(t, &h[hash(t.key)]);
	return t1;
}


char* getGrade(char* studentName, char* courseName, Hashtable snap) {
	Tuple t = tupleNew(0,1,3, "*", studentName, "*" );
	Tuple t1 = lookup(t, snap);
	
	tuplePrint(t1);
	printf("t1.attr[0]=%s\n", t1.attr[0]);
	Tuple t2 = tupleNew2(0,1,2,3, courseName, t1.attr[0], "*");
	return t2.attr[2];
	
}

int main(void) {
	Hashtable csg, snap, cp, cdh, cr;
	for(int i = 0; i< NBUCKETS; i++) {
	  
    csg[i] = NULL;
	snap[i] = NULL;
	cp[i] = NULL;
	cdh[i] = NULL;
	cr[i] = NULL;
  }


	Tuple g[6];
	
	g[0] = tupleNew2(0,1,2,3, "CSC101", "12345", "A");
	g[1] = tupleNew2(0,1,2,3, "CSC101", "67890", "B");
	g[2] = tupleNew2(0,1,2,3, "EE200", "12345", "C");
	g[3] = tupleNew2(0,1,2,3, "EE200", "22222", "B+");
	g[4] = tupleNew2(0,1,2,3, "CS101", "33333", "A-");
	g[5] = tupleNew2(0,1,2,3, "PH100", "67890", "C+");
	for(int i=0;i<6;i++)
		insert(g[i], csg);

	
	Tuple s[3];
    s[0] = tupleNew(0, 1, 4, "12345", "C. Brown", "12 Apple St.", "555-1234");
    s[1]= tupleNew(0, 1, 4, "67890", "L. Van Pelt", "34 Pear Ave.", "555-5678");
    s[2] = tupleNew(0, 1, 4, "22222", "P. Patty", "56 Grape Blvd.", "555-9999");
	printf("s[0].key: %s\n", s[0].key);
	
	for(int i=0;i<3;i++)
		insert(s[i], snap);
	
	//delete(tupleNew(0,1,4,"*", "C. Brown", "*", "*"), snap);
    
	Tuple c[8];
	
	
  
    c[0] = tupleNew2(0,1, 1, 2, "CS101", "CS100");
    c[1] = tupleNew2(0,1, 1, 2, "EE200", "EE005");
    c[2] = tupleNew2(0,1, 1, 2, "EE200", "CS100");
    c[3] = tupleNew2(0,1, 1, 2, "CS120", "CS101");
    c[4] = tupleNew2(0,1, 1, 2, "CS121", "CS120");
    c[5] = tupleNew2(0,1, 1, 2, "CS205", "CS101");
    c[6] = tupleNew2(0,1, 1, 2, "CS206", "CS121");
    c[7] = tupleNew2(0,1, 1, 2, "CS206", "CS205");
	printf("c[0].key: %s\n", c[0].key);
	
	for(int i=0;i<8;i++)
		insert(c[i], cp);
	
	
	Tuple d[6];
	d[0]= tupleNew2(0,1, 2, 3, "CS101", "M", "9AM");
    d[1] = tupleNew2(0,1, 2, 3, "CS101", "W", "9AM");
    d[2] = tupleNew2(0,1, 2, 3, "CS101", "F", "9AM");
    d[3] = tupleNew2(0,1, 2, 3, "EE200", "Tu", "10AM");
    d[4] = tupleNew2(0,1, 2, 3, "EE200", "W", "1PM");
    d[5] = tupleNew2(0,1,2, 3, "EE200", "Th", "10AM");
	for(int i=0;i<6;i++)
		insert(d[i], cdh);
	
	
	Tuple r[3];
	
	r[0] = tupleNew(0,1,2,"CS101", "Turing Aud.");
	r[1] = tupleNew(0,1,2,"EE200", "25 Ohm Hall");
	r[2] = tupleNew(0,1,2,"PH100", "Newton Lab.");
	//inserting
	for(int i=0;i<3;i++)
		insert(r[i], cr);
	
	
	
	
	printf("\n\nSNAP\n\n");
	tablePrint(snap);
	printf("\n\nCourse-Prereq\n\n");
	tablePrint(cp);

	printf("\n\nCourse-Day-Hour\n\n");
	tablePrint(cdh);
	
	printf("\n\nCourse-Room\n\n");
	tablePrint(cr);
	
	Tuple a1 = tupleNew(0,1,2, "CS101", "*");
	delete(a1, cr);
	
	Tuple a2 = tupleNew2(0,1,1,2, "CS205", "CS120");
	insert(a2, cp);
	
	Tuple a3 = tupleNew2(0,1,1,2, "CS205", "CS101");
	insert(a3, cp);
	
	
	
	printf("\n\nSNAP\n\n");
	tablePrint(snap);
	printf("\n\nCourse-Prereq\n\n");
	tablePrint(cp);

	printf("\n\nCourse-Day-Hour\n\n");
	tablePrint(cdh);
	
	printf("\n\nCourse-Room\n\n");
	tablePrint(cr);
	
	
	Tuple a4 = tupleNew2(0,1,2,3, "CSC101", "12345", "*");
	
	lookup(a4, csg);
	
	Tuple a5 = tupleNew2(0,1,1,2, "CS205", "CS120");
	
	lookup(a5, cp);
	
	
	printf("Grade of Charlie brown in EE200: %s",getGrade("C. Brown", "EE200", snap));
  
  
  return 0;
}

