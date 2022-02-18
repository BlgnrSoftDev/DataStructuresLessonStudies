#include <stdio.h>
#include <stdlib.h>
#include "GraphADT.h"

int compare(void* p, void* n);
void process(void* inf);


int main()
{
    int a = 1, b = 2, c = 3, d = 4, e = 5, f = 6, k;
    GRAPH* newGraph = createGraph(compare);
    graphInsertVertex(newGraph, &a);
    graphInsertVertex(newGraph, &b);
    graphInsertVertex(newGraph, &c);
    graphInsertVertex(newGraph, &d);
    graphInsertVertex(newGraph, &e);
    graphInsertVertex(newGraph, &f);

    graphInsertArc(newGraph, &a, &b, 5);
    graphInsertArc(newGraph, &a, &c, 7);
    graphInsertArc(newGraph, &b, &c, 9);
    graphInsertArc(newGraph, &b, &e, 10);
    graphInsertArc(newGraph, &c, &d, 3);
    graphInsertArc(newGraph, &c, &f, 1);
    graphInsertArc(newGraph, &f, &d, 2);

//    printf("%d", newGraph->count);
    primSpanningTree(newGraph, &a);
//    graphBFS(newGraph, process, &a);




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
