#include <stdio.h>
#include <stdlib.h>
#include "AV_Tree_ADT.h"

int compare(void* p, void* n);
void process(void* inf);

int main()
{
    AVL_TREE* newTree = create_AVL(compare);
    int x = 5, a = 10, b = 20, c = 30, d = 40, e = 50, f = 60, g = 70, h = 80, i = 90;




    insert_AVL(newTree, &c);
    traverse_AVL(newTree, process);
    printf("\n");

    insert_AVL(newTree, &a);
    traverse_AVL(newTree, process);
    printf("\n");

    insert_AVL(newTree, &d);
    traverse_AVL(newTree, process);
    printf("\n");

    insert_AVL(newTree, &b);
    traverse_AVL(newTree, process);
    printf("\n");

    insert_AVL(newTree, &x);
    traverse_AVL(newTree, process);
    printf("\n");

//    insert_AVL(newTree, &b);
//    traverse_AVL(newTree, process);
//    printf("\n");

    printf("%d\n", *((int*)newTree->root->data));
    printf("%d\n\n", newTree->count);

    delete_AVL(newTree, &d);
    traverse_AVL(newTree, process);
    printf("\n");

    printf("%d\n", *((int*)newTree->root->data));
    printf("%d", newTree->count);
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

