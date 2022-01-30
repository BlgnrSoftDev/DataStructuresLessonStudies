#ifndef HEAPTREEADT_H_INCLUDED
#define HEAPTREEADT_H_INCLUDED



#endif // HEAPTREEADT_H_INCLUDED

#include <stdbool.h>

typedef struct heap
{
    void** heapArr;
    int last, size, maxSize;
    int (*compare) (void*, void*);

}HEAP;


HEAP* heapCreate(int maxSize, int (*compare) (void* arg1, void* arg2));
bool heapInsert(HEAP* heap, void* dataPtr);
bool heapDelete(HEAP* heap, void** dataOutPtr);
int heapCount(HEAP* heap);
bool heapFull(HEAP* heap);
void printKth(HEAP* heap, int k);
bool heapEmpty(HEAP* heap);
void heapDestroy(HEAP* heap);


static void _reheapUp(HEAP* heap, int childLoc);
static void _reheapDown(HEAP* heap, int root);



HEAP* heapCreate(int maxSize, int (*compare) (void* arg1, void* arg2))
{
    HEAP* newHeap = (HEAP*)malloc(sizeof(HEAP));
    if(newHeap)
    {
        newHeap->heapArr = (void**)malloc(sizeof(void*)* 10);
        newHeap->compare = compare;
        newHeap->maxSize = maxSize;
        newHeap->last = -1;
        newHeap->size = 0;
    }

    return newHeap;
}

bool heapInsert(HEAP* heap, void* dataPtr)
{
    if(!heap)
        return false;

    if(heap->size < heap->maxSize)
    {
        heap->last++;
        heap->heapArr[heap->last] = dataPtr;
        heap->size++;
        _reheapUp(heap, heap->last);

        return true;
    }

    return false;
}

static void _reheapUp(HEAP* heap, int childLoc)
{
    if(childLoc != 0)
    {
        int parentLoc = (childLoc - 1) / 2;

        if(heap->compare(heap->heapArr[childLoc], heap->heapArr[parentLoc]) > 0)
        {
            void* temp = heap->heapArr[childLoc];
            heap->heapArr[childLoc]= heap->heapArr[parentLoc];
            heap->heapArr[parentLoc]= temp;

            _reheapUp(heap, parentLoc);
        }
    }
}


bool heapDelete(HEAP* heap, void** dataOutPtr)
{
    if(!heap)
        return false;

    if(heap->size != 0)
    {
        void* temp = heap->heapArr[0];
        heap->heapArr[0] = heap->heapArr[heap->last];
        heap->heapArr[heap->last] = temp;
        *dataOutPtr = heap->heapArr[heap->last];
        heap->last--;
        heap->size--;
        _reheapDown(heap, 0);
    }
}

static void _reheapDown(HEAP* heap, int root)
{
    int leftChildLoc = 2 * root + 1;
    int rightChildLoc = 2 * root + 2;
    int biggerChildLoc;
    if(leftChildLoc < heap->size)
    {
        if(rightChildLoc < heap->size)
        {
            if(heap->compare(heap->heapArr[leftChildLoc], heap->heapArr[rightChildLoc]) > 0)
            {
                biggerChildLoc = leftChildLoc;
            }
            else
            {
                biggerChildLoc = rightChildLoc;
            }
        }
        else
        {
            biggerChildLoc = leftChildLoc;
        }
        if(heap->compare(heap->heapArr[root],heap->heapArr[biggerChildLoc]) < 0)
        {
            void* temp = heap->heapArr[root];
            heap->heapArr[root] = heap->heapArr[biggerChildLoc];
            heap->heapArr[biggerChildLoc] = temp;
            _reheapDown(heap, biggerChildLoc);
        }
    }
}

int heapCount(HEAP* heap)
{
    if(!heap)
        return 0;

    return heap->size;
}
bool heapFull(HEAP* heap)
{
    if(!heap)
        return false;

    return (heap->size == heap->maxSize);
}
bool heapEmpty(HEAP* heap)
{
    if(!heap)
        return true;

    return heap->size == 0;
}
void heapDestroy(HEAP* heap)
{
    if(heap)
    {
        for(int i = 0; i < heap->size; ++i)
        {
            free(heap->heapArr[i]);
        }
        free(heap->heapArr);
        free(heap);
    }
}


void printKth(HEAP* heap, int k)
{

    if(k > heap->size)
        return NULL;

    void* temp;
    for(int i = 0; i < k; ++i)
    {
        heapDelete(heap, &temp);
        heap->heapArr[heap->size] = temp;
    }

    printf("element is %d\n", *((int*)temp));

    int x = 0;
    while(x < 3)
    {
        heap->last++;
        heap->size++;
        _reheapUp(heap, heap->last);

        ++x;
    }
}


HEAP* buildHeap(void** heapArr, int size, int (*compare)(void*, void*))
{
    int n = size/2 - 1;

    HEAP* newHeap = heapCreate(size * 20, compare);
    newHeap->last = size-1;
    newHeap->heapArr = heapArr;
    newHeap->size = size;

    while(n >= 0)
    {
        _reheapDown(newHeap, n);
        n--;
    }


    return newHeap;
}


