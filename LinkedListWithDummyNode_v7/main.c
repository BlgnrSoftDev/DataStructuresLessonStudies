#include <stdio.h>
#include <stdlib.h>
#include "ListADT.h"

int compare(void* param1, void* param2);

int main()
{
    void* dataPointer;
    int a = 9, b = 7, c = 4, d = 10, e = 5;
    LIST* yeniListe = createList(&compare);
    int f = addNode(yeniListe, &a);
    printAllNodes(yeniListe);
    addNode(yeniListe, &c);
    printAllNodes(yeniListe);
    addNode(yeniListe, &e);
    printAllNodes(yeniListe);
    addNode(yeniListe, &d);
    printAllNodes(yeniListe);
    removeNode(yeniListe, &c);
    printAllNodes(yeniListe);
    removeNode(yeniListe, &a);
    printAllNodes(yeniListe);
    if( traverse(yeniListe, 0, &dataPointer) )
        printf("%d", *((int*)yeniListe->pos->data));
    return 0;
}


int compare(void* param1, void* param2)
{
    if( *((int*)param1) > *((int*)param2))
    {
        return 1;
    }
    else if( *((int*)param1) == *((int*)param2))
    {
        return 0;
    }
    else
    {
        return -1;
    }

}
