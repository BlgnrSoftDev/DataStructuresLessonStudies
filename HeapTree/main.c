#include <stdio.h>
#include <stdlib.h>
#include "HeapTreeADT.h"

int compare(void* arg1, void* arg2);

int main()
{
    int a = 1, b = 2, c = 3, d = 4, e = 5, f = 6, g = 7;
    void* dataPtr;
    HEAP* heap = heapCreate(10, compare);

    heapInsert(heap, &e);
    heapInsert(heap, &a);
    heapInsert(heap, &c);
    heapInsert(heap, &f);
    heapInsert(heap, &d);
    heapInsert(heap, &g);
    heapInsert(heap, &b);

    int size = heap->size;
    for(int i = 0; i < size; ++i)
    {
        heapDelete(heap, &dataPtr);
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
