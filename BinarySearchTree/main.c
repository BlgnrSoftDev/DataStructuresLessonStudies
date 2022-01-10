#include <stdio.h>
#include <stdlib.h>
#include "BSTADT.h"
#include <stdbool.h>
#include "StackADT.h"

int compare(void* p, void* n);
void process(void* inf);


int main()
{
    int a = 1, b = 2, c = 3, d = 4, e = 5, f = 6, g = 7;


    BST_TREE* newTree = create_BST(compare);

    insert_BST(newTree, &c);
    traverse_BST(newTree, process);
    printf("\n");
//    insert_BST(newTree, &d);
//    traverse_BST(newTree, process);
//    printf("\n");
//    insert_BST(newTree, &g);
//    traverse_BST(newTree, process);
//    printf("\n");
//    insert_BST(newTree, &a);
//    traverse_BST(newTree, process);
//    printf("\n");
//    insert_BST(newTree, &e);
//    traverse_BST(newTree, process);
//    printf("\n");
//
//    insert_BST(newTree, &b);
//    traverse_BST(newTree, process);
//    printf("\n");
//
//    insert_BST(newTree, &f);
//    traverse_BST(newTree, process);
//    printf("\n");

//    delete_BST(newTree, &a);
//    traverse_BST(newTree, process);
//    printf("\n");
//
//    delete_BST(newTree, &e);
//    traverse_BST(newTree, process);
//    printf("\n");
//
//    delete_BST(newTree, &g);
//    traverse_BST(newTree, process);
//    printf("\n");
//
//    delete_BST(newTree, &d);
//    traverse_BST(newTree, process);
//    printf("\n");
//
//    delete_BST(newTree, &c);
//    traverse_BST(newTree, process);
//    printf("\n");

    STACK* st = createStack();
    printTree(newTree, st);

    printf("\n\n");

    printTree_V2(newTree);

    return 0;
}

int compare(void* p, void* n)
{
    if(*((int*)p) > *((int*)n))
        return 1;
    else if(*((int*)p) == *((int*)n))
        return 0;
    else
        return -1;
}

void process(void* inf)
{
    printf("%d ", *((int*)inf));
}


void printTree(BST_TREE* tree, STACK* stack)
{
    int level = 0;
    NODE* temp;
    pushStack(stack, tree->root);
    tree->root->level = 0;
    while(!isEmptyStack(stack))
    {
        temp = ((NODE*)popStack(stack));

        for(int i = 0; i < temp->level; ++i)
            printf(" ");

        printf("%d. {[%d]}", temp->level, *((int*)temp->data));

        if(temp->rightSubTree)
        {
            pushStack(stack, temp->rightSubTree);
            temp->rightSubTree->level = level+1;
        }

        if(temp->leftSubTree)
        {
            pushStack(stack, temp->leftSubTree);
            temp->leftSubTree->level = level+1;
        }


        printf("\n");
        ++level;
    }
}


void printTree_V2(BST_TREE* tree)
{
    int level = 0;
    _internalRecursion(level, tree->root);

}


void _internalRecursion(int level, NODE* root)
{
    if(root)
    {
        root->level = level;

        if(root->rightSubTree)
            _internalRecursion(level+1, root->rightSubTree);

        for(int i = 0; i < root->level; ++i)
            printf("  ");

        printf("%d. {[%d]}", root->level, *((int*)root->data));
        printf("\n");
        if(root->leftSubTree)
            _internalRecursion(level+1, root->leftSubTree);

    }

}






