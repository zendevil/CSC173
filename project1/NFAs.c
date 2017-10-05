#ifndef _nfa_h
#define _nfa_h
#include <stdio.h>
#include<stdlib.h>
#include "NFA.h"
#include "IntSet.h"
#include <stdbool.h>

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
IntSet *NFA_get_transitions(NFA *nfa, int statenum, char symbol) {
	return nfa->States[statenum].transitions[symbol];
}

//adds a transition from a source state to a destination state on a given symbol
void NFA_add_transition(NFA *nfa, int src, char symbol, int dst) {
    IntSet_add(nfa->States[src].transitions[symbol], dst);
}


void NFA_add_transition_str(NFA *nfa, int src, char *str, int dst) {
    for(int i=0; str[i] != '\0'; i++) {
        IntSet_add(nfa->States[src].transitions[str[i]], dst); /
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
NFA funcEndMAN(){
    NFA *endMAN = NFA_new(4);
    NFA_set_current_state(endMAN,0);
    NFA_add_transition(endMAN, 0, 'm', 1);
    NFA_add_transition(endMAN, 1, 'a', 2);
    NFA_add_transition(endMAN, 1, 'n', 3);
    NFA_set_accepting(endMAN, 3, TRUE);

}

//queries whether given state is accepting
bool NFA_get_accepting(NFA *nfa, int statenum) {
    return nfa->States[statenum].isAccepting;
}

//set accepting state for given NFA
void NFA_set_accepting(NFA *nfa, int statenum, bool value) {
    nfa->states[statenum].is_accepting = value;


//executes nfa on input string
bool NFASubExecute(NFA *nfa, IntSet *startStates, char *input) {
    IntSetIterator *current_s_iterator = IntSet_iterator(startStates); /*creates iterator of possible current states*/
    while(IntSetIterator_has_next(current_s_iterator)) { /*condition makes sure the intset isn't empty*/

        int tempState = IntSetIterator_next(current_s_iterator);

        if(input[0] != '\0') {
           bool tempBool = NFA_subExecute(nfa, nfa->states[tempState].transitions[input[0]], (input+1));
           if(tempBool) {
            free(current_s_iterator);
            return TRUE;
           }
        }

        else if(nfa->states[tempState].is_accepting) {
            free(current_s_iterator);
            return TRUE;
        }
    }
    free(current_s_iterator);
    return FALSE;
}

bool NFAExecute(NFA *nfa, char *input) {
    return NFA_subExecute(nfa, nfa->current_states, input);
}
int main(){
printf("%d", NFAExecute(funcEndMAN(), "man"));
return 0;
}}


#endif
