#include <stdio.h>
#include <stdlib.h>
#include "HeapTreeADT.h"

int compare(void* arg1, void* arg2);

int main()
{
    int a = 1, b = 2, c = 3, d = 4, e = 5, f = 6, g = 7;
    void* dataPtr;
    HEAP* heap = heapCreate(10, compare);

    heapInsert(heap, &a);
    heapInsert(heap, &e);
    heapInsert(heap, &b);
    heapInsert(heap, &f);
    heapInsert(heap, &d);
    heapInsert(heap, &g);
    heapInsert(heap, &c);

    int size = heap->size;

    void** array= (void**)malloc(sizeof(void*) * 10);
    array[0]= &e;
    array[1]= &b;
    array[2]= &a;
    array[3]= &d;
    array[4]= &c;
    array[5]= &g;
    array[6]= &f;

    HEAP* nnmx = buildHeap(array, 7, compare);

    for(int i = 0; i < size; ++i)
    {
        heapDelete(nnmx, &dataPtr);
        printf("%d, ", *((int*)dataPtr));
    }

    return 0;
}


int compare(void* arg1, void* arg2)
{
    int arg_1 = *((int*)arg1);
    int arg_2 = *((int*)arg2);
    if(arg_1 > arg_2)
        return 1;
    else if(arg_1 == arg_2)
        return 0;
    else
        return -1;

}
