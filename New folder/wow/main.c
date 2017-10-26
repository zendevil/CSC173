#include <stdio.h>
#include <stdlib.h>

typedef struct  NODE{
    int value;
    struct NODE *leftChild;
    struct NODE *rightChild;
    struct NODE *parent;

}NODE;


typedef struct TREE {
    struct NODE *root;
    struct NODE *currentNode;
}TREE;

void addInt(TREE *tree, int value) {

    if(tree->root->value == NULL) {
        tree->root->value = value;
    } else {

        tree->currentNode = tree->root;

        while(1) {
                if(value < tree->currentNode->value && tree->currentNode->leftChild == NULL) {
                    tree->currentNode->rightChild->value = value;
                    break;
                }
                if(value > tree->currentNode->value && tree->currentNode->leftChild == NULL) {
                    tree->currentNode->leftChild->value = value;
                    break;
                }

            if(value <  tree->currentNode->value) {
                    tree->currentNode = tree->currentNode->leftChild;

            } else if(value > tree->currentNode->value){

                tree->currentNode = tree->currentNode->rightChild;

            }



        }


    }



}


int main()
{

    TREE *tree = (TREE*)malloc(sizeof(*tree));
    addInt(tree,1);
    addInt(tree,2);
    addInt(tree,3);

    return 0;

}
