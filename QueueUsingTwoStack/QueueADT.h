#ifndef QUEUEADT_H_INCLUDED
#define QUEUEADT_H_INCLUDED

#include "StackADT.h"
#include <stdbool.h>


#endif // QUEUEADT_H_INCLUDED



typedef struct queue
{
    STACK* bucketOne, *bucketTwo;
    int count;
    NODE* rear, *front;
}QUEUE;

static bool _transferStack(STACK* bucketOne, STACK* bucketTwo);
QUEUE* createQueue();
bool enQueue(QUEUE* queue, void* data);
bool deQueue(QUEUE* queue, void** dataOutPtr);
bool queueFront(QUEUE* queue, void** itemPtr);
bool queueRear(QUEUE* queue, void** itemPtr);

QUEUE* createQueue()
{
    QUEUE* newQueue = (QUEUE*)malloc(sizeof(QUEUE));
    newQueue->bucketOne = createStack();
    newQueue->bucketTwo = createStack();
    newQueue->count = 0;
    newQueue->front = newQueue->rear = NULL;

    return newQueue;
}

bool enQueue(QUEUE* queue, void* data)
{
    pushStack(queue->bucketOne, data);
    queue->rear = queue->bucketOne->top;
    (queue->count)++;

    return true;
}

bool deQueue(QUEUE* queue, void** dataOutPtr)
{
    if( isEmptyStack(queue->bucketTwo))
    {
        if(isEmptyStack(queue->bucketOne))
            return false;

        _transferStack(queue->bucketOne, queue->bucketTwo);
    }

    (*dataOutPtr) = popStack(queue->bucketTwo);
    queue->front = queue->bucketTwo->top;
    (queue->count)--;

    return true;
}

static bool _transferStack(STACK* bucketOne, STACK* bucketTwo)
{
    void* data;
    while( !isEmptyStack(bucketOne))
    {
        data = popStack(bucketOne);
        pushStack(bucketTwo, data);
    }

    return true;
}

bool queueFront(QUEUE* queue, void** itemPtr)
{
    *itemPtr = queue->front->data;
    return true;
}

bool queueRear(QUEUE* queue, void** itemPtr)
{
    *itemPtr = queue->rear->data;
    return true;
}
