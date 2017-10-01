#include <stdio.h>
#include <stdlib.h>

typedef struct  NODE{
    int value;
    struct NODE *leftChild;
    struct NODE *rightCHIld;
    struct NODE *parent;

}NODE;


typedef struct TREE {
    struct NODE *root;
    struct NODE *currentNode;
}TREE;

void addInt(TREE *tree, int value) {
    tree->root->value = value;


}


int main()
{

    TREE *tree = (TREE*)malloc(sizeof(*tree));
    addInt(tree,1);

    return 0;

}
