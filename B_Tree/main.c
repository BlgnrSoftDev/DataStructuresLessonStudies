#include <stdio.h>
#include <stdlib.h>
#include "B_TreeADT.h"

void process(void* data);
int compare(void* arg1, void* arg2);

int main()
{
    int a = 15, b = 99, c = 42, d = 48, e = 13, f = 24, g = 31, h = 52, i = 69;
    BTREE* newTree = BTree_Create(compare);
    BTree_Insert(newTree, &a);
    BTree_Insert(newTree, &b);
    BTree_Insert(newTree, &c);
    BTree_Insert(newTree, &d);
    BTree_Insert(newTree, &e);
    BTree_Insert(newTree, &f);
    BTree_Insert(newTree, &g);


    BTree_Delete(newTree, &g);
    BTree_Traverse(newTree, process);
    printf("\n");
    BTree_Delete(newTree, &c);
    BTree_Traverse(newTree, process);
    printf("\n");
    BTree_Delete(newTree, &b);
    BTree_Traverse(newTree, process);
    printf("\n");
    BTree_Delete(newTree, &d);
    BTree_Traverse(newTree, process);
    printf("\n");
    BTree_Delete(newTree, &e);
    BTree_Traverse(newTree, process);
    printf("\n");
    BTree_Delete(newTree, &f);
    BTree_Traverse(newTree, process);
    printf("\n");
    BTree_Delete(newTree, &a);
    BTree_Traverse(newTree, process);
    printf("\n");
//    printf("\n%d", *((int*)newTree->root->firstPtr->entries[0].dataPtr));
//    printf("\n%d", newTree->root->firstPtr->numEntries);

    return 0;
}


void process(void* data)
{
    printf(" %d ", *((int*)data));
}

int compare(void* arg1, void* arg2)
{
    int a = *((int*)arg1);
    int b = *((int*)arg2);
    if(a > b)
        return 1;
    else if(a == b)
        return 0;
    else
        return -1;

}
