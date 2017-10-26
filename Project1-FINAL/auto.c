#ifndef _nfa_h
#define _nfa_h
#ifndef _dfa_h
#define _dfa_h
#ifndef _LinkedList_h
#define _LinkedList_h
#include <stdio.h>
#include <stdlib.h>
#include "dfa.h"
#include "LinkedList.h"
#include "NFA.h"
#include "IntSet.h"
#include <stdbool.h>
#include "IntSet.h"
void NFA_set_accepting(NFA *nfa, int statenum, bool value);
//intset

struct IntSet {
    struct IntSetNode *first;
    struct IntSetNode *last;
};

struct IntSetIterator {
    struct IntSetNode *node;
};

/**
 * Structure for each element in an IntSet, stored as a linked list.
 */
typedef struct IntSetNode {
    int value;
    struct IntSetNode *next;
} IntSetNode;

/**
 * Allocate, initialize and return a new (empty) IntSet.
 */
IntSet *
IntSet_new() {
    IntSet *set = (IntSet*)malloc(sizeof(IntSet));
    set->first = set->last = NULL;
    return set;
}

/**
 * Free the memory used for the given IntSet and all its elements.
 */
void
IntSet_free(IntSet *set) {
    // Free the elements
    IntSetNode *elt = set->first;
    while (elt != NULL) {
	IntSetNode *next = elt->next;
	free(elt);
	elt = next;
    }
    // Free the set (list)
    free(set);
}

/**
 * Allocate and initialize a new IntSetNode storing the given int value.
 */
static IntSetNode *
IntSetNode_new(int value) {
    IntSetNode *node = (IntSetNode*)malloc(sizeof(IntSetNode));
    if (node == NULL) {
	abort();
    }
    node->value = value;
    node->next = NULL;
    return node;
}

/**
 * Return true if the given IntSet is empty.
 */
bool
IntSet_is_empty(const IntSet *set) {
    return set->first == NULL;
}

/**
 * Add given int to the given IntSet (if it's not already there).
 */
void
IntSet_add(IntSet *set, int value) {
    if (!IntSet_contains(set, value)) {
	// Add at front
	IntSetNode *node = IntSetNode_new(value);
	node->next = set->first;
	set->first = node;
    }
}

/**
 * Return true if the given IntSet contains the given int value.
 */
bool
IntSet_contains(const IntSet *set, int value) {
    for (IntSetNode *node=set->first; node != NULL; node=node->next) {
	if (node->value == value) {
	    return true;
	}
    }
    return false;
}

/**
 * Add the contents of IntSet set2 to IntSet set1 (adding those elements
 * that aren't already in set1). This will modify set1 unless set2 is empty
 * (or all its elements are already in set1).
 */
void
IntSet_union(IntSet *set1, const IntSet *set2) {
    for (IntSetNode *node=set2->first; node != NULL; node=node->next) {
	IntSet_add(set1, node->value);
    }
}

/**
 * Return true if the first IntSet contains every member of the second
 * IntSet.
 */
bool
IntSet_contains_all(IntSet *set1, IntSet *set2) {
    for (IntSetNode *node2=set2->first; node2 != NULL; node2=node2->next) {
	if (!IntSet_contains(set1, node2->value)) {
	    return false;
	}
    }
    return true;
}

/**
 * Return true if the two given IntSets contain exactly the same members,
 * otherwise false.
 */
bool
IntSet_equals(IntSet *set1, IntSet *set2) {
    return IntSet_contains_all(set1, set2) && IntSet_contains_all(set2, set1);
}

/**
 * Call the given function on each element of given IntSet, passing the
 * int value to the function.
 */
void
IntSet_iterate(const IntSet *set, void (*func)(int)) {
    for (IntSetNode *node=set->first; node != NULL; node=node->next) {
	func(node->value);
    }
}

/**
 * Return an IntSetIterator for the given IntSet.
 * Don't forget to free() this when you're done iterating.
 */

IntSetIterator *
IntSet_iterator(const IntSet *set) {
    IntSetIterator *iterator = (IntSetIterator*)malloc(sizeof(IntSetIterator));
    iterator->node = set->first;
    return iterator;
}

/**
 * Return the next int from the given IntSetIterator and increment it
 * to point to the next element.
 * This will cause a crash if there is no such element.
 * You could make a safe version with a pass-by-reference (int*) parameter
 * for the int and boolean return value that indicates whether the operation
 * succeeded or not. Ah, the goold old days...
 */
bool
IntSetIterator_has_next(const IntSetIterator *iterator) {
    return iterator != NULL && iterator->node != NULL;
}

int
IntSetIterator_next(IntSetIterator *iterator) {
    if (iterator == NULL || iterator->node == NULL) {
	abort();
    } else {
	int value = iterator->node->value;
	iterator->node = iterator->node->next;
	return value;
    }
}

/**
 * Print the given IntSet to stdout.
 */
void
IntSet_print(IntSet *set) {
    for (IntSetNode *node=set->first; node != NULL; node=node->next) {
	printf("%d", node->value);
	if (node->next != NULL) {
	    printf(" ");
	}
    }
    printf("\n");
}


//linkedlist
struct LinkedList {
    struct LinkedListNode *first;
    struct LinkedListNode *last;
};

/**
 * Structure for each element of a doubly-linked LinkedList.
 */
typedef struct LinkedListNode {
    void *data;
    struct LinkedListNode *next;
    struct LinkedListNode *prev;
} LinkedListNode;

/**
 * Allocate, initialize and return a new (empty) LinkedList.
 */
LinkedList *
LinkedList_new() {
    LinkedList *list = (LinkedList*)malloc(sizeof(LinkedList));
    list->first = list->last = NULL;
    return list;
}

static LinkedListNode *
LinkedListNode_new(void *data) {
    LinkedListNode *node = (LinkedListNode*)malloc(sizeof(LinkedListNode));
    if (node == NULL) {
	abort();
    }
    node->data = data;
    node->next = node->prev = NULL;
    return node;
}

/**
 * Free the memory used for the given LinkedList.
 * If boolean free_data_also is true, also free the data associated with
 * each element.
 */
void
LinkedList_free(LinkedList *list, bool free_data_also) {
    // Free the elements
    LinkedListNode *elt = list->first;
    while (elt != NULL) {
	LinkedListNode *next = elt->next;
	if (free_data_also && elt->data != NULL) {
	    free(elt->data);
	}
	free(elt);
	elt = next;
    }
    // Free the list itself
    free(list);
}

/**
 * Return true if the given LinkedList is empty.
 */
bool
LinkedList_is_empty(const LinkedList *list) {
    return list->first == NULL;
}

/**
 * Add the given void* value at the front of the given LinkedList.
 */
void
LinkedList_add_at_front(LinkedList *list, void *data) {
    LinkedListNode *node = LinkedListNode_new(data);
    node->next = list->first;
    if (list->first != NULL) {
	list->first->prev = node;
    }
    list->first = node;
    if (list->last == NULL) {
	list->last = node;
    }
}

/**
 * Add the given void* value at the end of the given LinkedList.
 */
void
LinkedList_add_at_end(LinkedList *list, void *data) {
    LinkedListNode *node = LinkedListNode_new(data);
    node->prev = list->last;
    if (list->last != NULL) {
	list->last->next = node;
    }
    list->last = node;
    if (list->first == NULL) {
	list->first = node;
    }
}

/**
 * Return true if then given LinkedList contains given void* value.
 */
int
LinkedList_contains(const LinkedList *list, void *data) {
    int i=0;
    for (LinkedListNode *node=list->first; node != NULL; node=node->next) {
        i++;
	   if (node->data == data) {
	       return i;
	   }
    }
    return -1;
}

/**
 * Remove the given void* value from the given LinkedList if it is there.
 * Note that this does not free the data associated with the element.
 */
void
LinkedList_remove(LinkedList *list, void *data) {
    for (LinkedListNode *node=list->first; node != NULL; node=node->next) {
	if (node->data == data) {
	    if (node == list->first) {
		list->first = node->next;
	    }
	    if (node == list->last) {
		list->last = node->prev;
	    }
	    if (node->prev != NULL) {
		node->prev->next = node->next;
	    }
	    if (node->next != NULL) {
		node->next->prev = node->prev;
	    }
	    free(node);
	    return;
	}
    }
}

/**
 * Return the void* value at the given index in the given LinkedList, or
 * NULL if there is no such.
 * Note that this means you can't store NULL in a LinkedList. C'est la vie.
 */
void *
LinkedList_element_at(LinkedList *list, int index) {
    int i = 0;
    for (LinkedListNode *node=list->first; node != NULL; node=node->next) {
	if (i == index) {
	    return node->data;
	}
	i += 1;
    }
    return NULL;
}

/**
 * Remove and return the first element from the given LinkedList.
 * Returns NULL if the list is empty.
 */
void *
LinkedList_pop(LinkedList *list) {
    void *data = LinkedList_element_at(list, 0);
    if (data != NULL) {
	LinkedList_remove(list, data); // Removes first occurrence
    }
    return data;
}

/**
 * Call the given function on each element of given LinkedList, passing the
 * void* value to the function.
 */
void
LinkedList_iterate(const LinkedList *list, void (*func)(void *)) {
    for (LinkedListNode *node=list->first; node != NULL; node=node->next) {
	func(node->data);
    }
}

/**
 * Return an LinkedListIterator for the given LinkedList.
 * Don't forget to free() this when you're done iterating.
 */
LinkedListIterator *
LinkedList_iterator(const LinkedList *list) {
    LinkedListIterator *iterator = (LinkedListIterator*)malloc(sizeof(LinkedListIterator));
    *iterator = list->first;
    return iterator;
}

/**
 * Return true if the given LinkedListIterator will return another element
 * if LinkedListIterator_next() is called.
 */
bool
LinkedListIterator_has_next(const LinkedListIterator *iterator) {
    return iterator != NULL && *iterator != NULL;
}

/**
 * Return the next value from the given LinkedListIterator and increment it
 * to point to the next element.
 * Will return NULL if there is no such element.
 * This means that you can't store NULL in a LinkedList. C'est la vie.
 * It would be easy to allow it and signal `no such element' some other way...
 */
void *
LinkedListIterator_next(LinkedListIterator *iterator) {
    if (iterator == NULL || *iterator == NULL) {
	return NULL;
    } else {
	void *data = (*iterator)->data;
	*iterator = (*iterator)->next;
	return data;
    }
}

void *
LinkedListIterator_value(LinkedListIterator *iterator) {
    if (iterator == NULL || *iterator == NULL) {
    return NULL;
    } else {
    void *data = (*iterator)->data;
    return data;
    }
}

/**
 * Print the given LinkedList to stdout, assuming that the values are
 * all null-terminated strings.
 */
void
LinkedList_print_string_list(LinkedList *list) {
    for (LinkedListNode *node=list->first; node != NULL; node=node->next) {
	//printf("%s", node->data);
	if (node->next != NULL) {
	    printf(" ");
	}
    }
    printf("\n");
}
#endif // _LinkedList_h

DFA *DFANew(int numStates);

//NFA DFA CONVERSION
DFAState *DFAStatenew(){
DFAState *d=(DFAState*)malloc(sizeof(DFAState));
d->isAccepting=FALSE;
for(int symbol=0;symbol<128;symbol++){
    d->transitions[symbol]=-1;
    //initialize transitions to -1
}
return d;
}

//convert NFA to DFA
DFA *NFAtoDFA(NFA *nfa){
LinkedList *States=LinkedList_new();//Linked List for states
LinkedList *intSet=LinkedList_new();//Linked List for intsets

DFAState *state0=DFAStatenew();
LinkedList_add_at_end(States,state0);
IntSet *firstIntSet=IntSet_new();
IntSet_add(firstIntSet,0);
LinkedList_add_at_end(intSet, firstIntSet);

int numStates=1;
LinkedListIterator *iterate=LinkedList_iterator(States);
LinkedListIterator *intSetIterate=LinkedList_iterator(intSet);

while(LinkedListIterator_has_next(iterate)){
  DFAState *currentState=LinkedListIterator_value(iterate);
  IntSet *currentIntSet=LinkedListIterator_value(intSetIterate);
  for(int s=0;s<128;s++){
    IntSet *dst=IntSet_new();
    IntSetIterator *currentStateIter=IntSet_iterator(currentIntSet);
    while(IntSetIterator_has_next(currentStateIter)){
        int tempS=IntSetIterator_next(currentStateIter);
        IntSet_union(dst, nfa->States[tempS].transitions[s]);
        if(nfa->States[tempS].isAccepting){
            currentState->isAccepting=TRUE;
        }

    }
    free(currentStateIter);

    int setInt=-1;
    int count=0;
    LinkedListIterator *tempIT=LinkedList_iterator(intSet);
    while(LinkedListIterator_has_next(tempIT)){
        IntSet *tempIS=LinkedListIterator_next(tempIT);
        if(IntSet_equals(tempIS, dst)){
            setInt=count;
        }count++;

    }
    free(tempIT);

    if(setInt<0&&(!(IntSet_is_empty(dst)))){
        DFAState *stateK = DFAStatenew();
        currentState->transitions[s]=numStates;

        LinkedList_add_at_end(States,stateK);
        LinkedList_add_at_end(intSet,dst);
        numStates+=1;
    }
    else if(!(IntSet_is_empty(dst))){
        currentState->transitions[s]=setInt;
    }

  }


}

//create new DFA
DFA *newDFA = DFANew(numStates);
LinkedListIterator *finalState = LinkedList_iterator(States);
for(int p=0; p<numStates; p++){
    DFAState *oneState = LinkedListIterator_next(finalState);
    newDFA->States[p] = *oneState;
    free(oneState);
}
free(finalState);
free(iterate);
free(intSetIterate);
return newDFA;
}

//DFAs
DFA *DFANew(int numStates) {
    DFA *dfa = (DFA*)malloc(sizeof(DFA));
    dfa->numStates = numStates;
    dfa->currentState = 0;
    dfa->States = (DFAState*)malloc(numStates*sizeof(DFAState));

  //setting all states to FALSE
  for(int i=0; i<numStates;i++) {
    dfa->States[i].isAccepting = FALSE;
  }
//sets the transition to -1 which means no transiton
  for(int i1 =0;i1<numStates;i1++) {
    for(int j=0;j<128;j++){
      dfa->States[i1].transitions[j] = -1;


    }
  }
  return dfa;
}

int DFAGetTransition(DFA *dfa, int stateNum, unsigned char symbol) {
  return dfa->States[stateNum].transitions[symbol];
}

void DFASetTransition(DFA *dfa, int src, unsigned char str, int dst) {
  dfa->States[src].transitions[str] = dst;
}

void DFASetAllTransitions(DFA *dfa, int src, int dst) {

    for(int i=0;i<128;i++) {
        DFASetTransition(dfa,src,i,dst);
    }
}

int DFAGetCurrentState(DFA *dfa) {
  return dfa->currentState;
}

void DFASetCurrentState(DFA *dfa, int stateNum) {
  dfa->currentState = stateNum;
}

int DFAGetAccepting(DFA *dfa, int stateNum) {
  return dfa->States[stateNum].isAccepting;
}

void DFASetAccepting(DFA *dfa, int stateNum, BOOLEAN truthValue) {
  dfa->States[stateNum].isAccepting = truthValue;
}


void DFAPrint(DFA *dfa) {

}

int DFAExecute(DFA *dfa, char *input) {
  for(int i=0; input[i] != '\0'; i++) {
    int destination = dfa->States[dfa->currentState].transitions[(int)input[i]];
    DFASetCurrentState(dfa, destination);
    if(dfa->currentState == -1) {
      return FALSE;
    }

  }
  int finalState = dfa->currentState;
  DFASetCurrentState(dfa,0);
  return DFAGetAccepting(dfa, finalState);
}

//only string ab

DFA* funcOnlyAB() {
DFA *onlyAB = DFANew(3);

DFASetTransition(onlyAB, 0,'a',1);
DFASetTransition(onlyAB,1,'b',2);
DFASetAccepting(onlyAB, 2, TRUE);

return onlyAB;


}


DFA* funcStartAB() {
    DFA *startAB = DFANew(3);
    DFASetTransition(startAB,0, 'a', 1);
    DFASetTransition(startAB,1,'b',2);
    DFASetAllTransitions(startAB, 2,2);

    DFASetAccepting(startAB,2,TRUE);

    return startAB;
}

DFA* funcEvenOnes() {

  DFA *evenOnes = DFANew(2);


  DFASetTransition(evenOnes,0,'1',1);
  DFASetTransition(evenOnes,1,'1',0);
  DFASetTransition(evenOnes, 0,'0',0);
  DFASetTransition(evenOnes, 1,'0',1);

  DFASetAccepting(evenOnes,0,TRUE);


  return evenOnes;


}




DFA* funcEvenBoth() {

  DFA *evenBoth = DFANew(4);

  DFASetTransition(evenBoth,0,'0',1);
  DFASetTransition(evenBoth,1,'0',0);
  DFASetTransition(evenBoth,1,'1',2);
  DFASetTransition(evenBoth,2,'1',1);
  DFASetTransition(evenBoth,2,'0',3);
  DFASetTransition(evenBoth,3,'0',2);
  DFASetTransition(evenBoth,3,'1',0);
  DFASetTransition(evenBoth,0,'1',3);
  DFASetAccepting(evenBoth,0,TRUE);

  return evenBoth;


}

//for indentifying if string starts with $ sign
//Useful for checking if it's an amount of money.
//Would return false if any character after dollar sign is not a number
//Easy to implement

DFA* funcStartDolSign() {
    DFA *startDolSign = DFANew(2);



   // DFASetAllTransitions(startDolSign,0,0);
   // DFASetAllTransitions(startDolSign,1,1);
    DFASetTransition(startDolSign,0,'$',1);
    //iterating over all ascii
    //values for number characters
    for(int i =48;i<=57;i++) {
        DFASetTransition(startDolSign,1,i,1);

    }

    DFASetAccepting(startDolSign,1,TRUE);

    return startDolSign;

}



//NFAs
NFA *NFA_new(int n) {
    NFA *nfa = (NFA*)malloc(sizeof(NFA));
    nfa->nstates = n;
    IntSet *start = IntSet_new();
    IntSet_add(start, 0);
    nfa->currentStates = start;
    nfa->States = (NFAState*)malloc(n*sizeof(NFAState));
    for(int i=0; i<n; i++) {
        for(int j=0; j<128; j++) {
            nfa->States[i].transitions[j] = IntSet_new();
        }
        nfa->States[i].isAccepting = FALSE;
    }
    return nfa;
}

//returns number of states in the NFA
int NFA_get_size(NFA *nfa) {
	return nfa->nstates;
}

//returns set of transitions for an NFA on a given state for a given symbol
IntSet *NFA_get_transitions(NFA *nfa, int statenum, unsigned char symbol) {
	return nfa->States[statenum].transitions[symbol];
}

//adds a transition from a source state to a destination state on a given symbol
void NFA_add_transition(NFA *nfa, int src, unsigned char symbol, int dst) {
    IntSet_add(nfa->States[src].transitions[symbol], dst);
}


void NFA_add_transition_str(NFA *nfa, int src, unsigned char *str, int dst) {
    for(int i=0; str[i] != '\0'; i++) {
        IntSet_add(nfa->States[src].transitions[str[i]], dst);
    }
}

void NFA_add_transition_all(NFA *nfa, int src, int dst) {
    for(int i=0; i<128; i++) {
        IntSet_add(nfa->States[src].transitions[i], dst);
    }
}

IntSet *NFA_get_current_states(NFA *nfa) {
    return nfa->currentStates;
}

void NFA_set_current_states(NFA *nfa, IntSet *states) {
    nfa->currentStates = states;
}

void NFA_set_current_state(NFA *nfa, int state) {
    IntSet *current = IntSet_new();
    IntSet_add(current, state);
    nfa->currentStates = current;
}
//strings ending in man
NFA* funcEndMAN(){
    NFA *endMAN = NFA_new(4);
    NFA_set_current_state(endMAN,0);
    NFA_add_transition(endMAN, 0, 'm', 1);
    NFA_add_transition(endMAN, 1, 'a', 2);
    NFA_add_transition(endMAN, 2, 'n', 3);
    NFA_add_transition_all(endMAN,0,0);
    NFA_set_accepting(endMAN, 3, TRUE);
    return endMAN;

}

NFA* funcWashington() {
    NFA *washington = NFA_new(20);

    NFA_add_transition_all(washington, 0, 0);
    NFA_add_transition(washington, 0, 'a', 1);
    NFA_add_transition_all(washington, 1, 1);
    NFA_add_transition(washington, 1, 'a', 2);
    NFA_add_transition_all(washington, 2, 2);
    NFA_add_transition(washington, 0, 'g', 3);
    NFA_add_transition_all(washington, 3, 3);
    NFA_add_transition(washington, 3, 'g', 4);
    NFA_add_transition_all(washington, 4, 4);
    NFA_add_transition(washington, 0, 'h', 5);
    NFA_add_transition_all(washington, 5, 5);
    NFA_add_transition(washington, 5, 'h', 6);
    NFA_add_transition_all(washington, 6, 6);
    NFA_add_transition(washington, 0, 'i', 7);
    NFA_add_transition_all(washington, 7, 7);
    NFA_add_transition(washington, 7, 'i', 8);
    NFA_add_transition_all(washington, 8, 8);
    NFA_add_transition(washington, 0, 'n', 9);
    NFA_add_transition_all(washington, 9, 9);
    NFA_add_transition(washington, 9, 'n', 10);
    NFA_add_transition_all(washington, 10, 10);
    NFA_add_transition(washington, 10, 'n', 11);
    NFA_add_transition_all(washington, 11, 11);
    NFA_add_transition(washington, 0, 'o', 12);
    NFA_add_transition_all(washington, 12, 12);
    NFA_add_transition(washington, 12, 'o', 13);
    NFA_add_transition_all(washington, 13, 13);
    NFA_add_transition(washington, 0, 's', 14);
    NFA_add_transition_all(washington, 14, 14);
    NFA_add_transition(washington, 14, 's', 15);
    NFA_add_transition_all(washington, 15, 15);
    NFA_add_transition(washington, 0, 't', 16);
    NFA_add_transition_all(washington, 16, 16);
    NFA_add_transition(washington, 16, 't', 17);
    NFA_add_transition_all(washington, 17, 17);
    NFA_add_transition(washington, 0, 'w', 18);
    NFA_add_transition_all(washington, 18, 18);
    NFA_add_transition(washington, 18, 'w', 19);
    NFA_add_transition_all(washington, 19, 19);

    NFA_set_accepting(washington, 2, TRUE);
    NFA_set_accepting(washington, 4, TRUE);
    NFA_set_accepting(washington, 6, TRUE);
    NFA_set_accepting(washington, 8, TRUE);
    NFA_set_accepting(washington, 11, TRUE);
    NFA_set_accepting(washington, 13, TRUE);
    NFA_set_accepting(washington, 15, TRUE);
    NFA_set_accepting(washington, 17, TRUE);
    NFA_set_accepting(washington, 19, TRUE);

     return washington;

}

//nfa accepts any number of a's rejects if anything else
NFA* funcAtLeastOneA() {
    NFA *washington = NFA_new(2);
    NFA_set_accepting(washington, 1, TRUE);
    NFA_add_transition(washington, 0, 'a',1);
    NFA_add_transition(washington, 0,'a',0);

    return washington;



}

DFA *funcDFAEndMAN(NFA *nfa){

    DFA *dfa = NFAtoDFA(nfa);
    return dfa;

}





//queries whether given state is accepting
bool NFA_get_accepting(NFA *nfa, int statenum) {
    return nfa->States[statenum].isAccepting;
}

//set accepting state for given NFA
void NFA_set_accepting(NFA *nfa, int statenum, bool value) {
    nfa->States[statenum].isAccepting = value;}


//executes nfa on input string
bool NFASubExecute(NFA *nfa, IntSet *startStates,  char *input) {
    IntSetIterator *current_s_iterator = IntSet_iterator(startStates); /*creates iterator of possible current states*/
    while(IntSetIterator_has_next(current_s_iterator)) { /*condition makes sure the intset isn't empty*/

        int tempState = IntSetIterator_next(current_s_iterator);

        if(input[0] != '\0') {
           bool tempBool = NFASubExecute(nfa, nfa->States[tempState].transitions[(int)input[0]], (input+1));
           if(tempBool) {
            free(current_s_iterator);
            return TRUE;
           }
        }

        else if(nfa->States[tempState].isAccepting) {
            free(current_s_iterator);
            return TRUE;
        }
    }
    free(current_s_iterator);
    return FALSE;
}

bool NFAExecute(NFA *nfa, char *input) {
    return NFASubExecute(nfa, nfa->currentStates, input);
}



#endif
#endif // _nfa_h



int main(int argc,char* argv[]){
//Testing DFas
char *inputString1 = "ab";
  char *inputString2 = "abg";
  char *inputString3 = "babcdef";
  char *inputString4 = "111001";
  char *inputString5 = "1101101";
  char *inputString6 = "$150";
  char *inputString7 = "15a0";
  char *inputString8 = "man";
  char *inputString9 = "www";
  char *inputString10 = "washington";
  char *inputString11 = "a";



  //Testing DFAs
  printf("funcOnlyAB(%s) = %d\n", inputString1, DFAExecute(funcOnlyAB(),inputString1));
  printf("funcOnlyAB(%s) = %d\n", inputString2, DFAExecute(funcOnlyAB(), inputString2));
  printf("funcStartAB(%s) = %d\n", inputString2, DFAExecute(funcStartAB(),inputString2));
  printf("funcStartAB(%s) = %d\n", inputString3, DFAExecute(funcStartAB(),inputString3));
  printf("funcEvenOnes(%s) = %d\n", inputString4, DFAExecute(funcEvenOnes(),inputString4));
  printf("funcEvenOnes(%s) = %d\n", inputString5, DFAExecute(funcEvenOnes(),inputString5));
  printf("funcEvenBoth(%s) = %d\n", inputString4, DFAExecute(funcEvenBoth(),inputString4));
  printf("funcEvenBoth(%s) = %d\n", inputString5, DFAExecute(funcEvenBoth(),inputString5));
  printf("funcStartDolSign(%s) = %d\n", inputString6, DFAExecute(funcStartDolSign(),inputString6));
  printf("funcStartDolSign(%s) = %d\n", inputString7, DFAExecute(funcStartDolSign(),inputString7));
  //Testing NFAs
  printf("funcWashington(%s) = %d\n", inputString9, NFAExecute(funcWashington(), inputString9));
  printf("funcWashington(%s) = %d\n", inputString10,  NFAExecute(funcWashington(), inputString10));
  printf("funcEndMAN(%s) = %d\n", inputString8, NFAExecute(funcEndMAN(), inputString8));
  printf("funcAtLeastOneA(%s) = %d\n", inputString11, NFAExecute(funcAtLeastOneA(), "a"));
  printf("funcDFAEndMan(man) = %d\n",DFAExecute(funcDFAEndMAN(funcEndMAN()),"man"));
  printf("funcDFAEndMan(abcd) = %d\n",DFAExecute(funcDFAEndMAN(funcEndMAN()),"abcd"));




}
