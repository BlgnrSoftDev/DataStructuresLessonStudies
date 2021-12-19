#ifndef QUEUEADT_H_INCLUDED
#define QUEUEADT_H_INCLUDED

#include <stdbool.h>

#endif // QUEUEADT_H_INCLUDED


typedef struct queue
{
    int count, front, rear;
    int SIZE;
    void** arr;
}QUEUE;


QUEUE* createQueue(int size)
{
    QUEUE* newQueue = (QUEUE*)malloc(sizeof(QUEUE));
    if(!newQueue)
    {
        return NULL;
    }

    newQueue->SIZE = size;
    newQueue->count = 0;
    newQueue->arr = (void**)malloc(sizeof(void*)* size);
    newQueue->front = newQueue->rear = -1;

    return newQueue;
}


bool enQueue(QUEUE* queue, void* data)
{
    // if queue is full
    if(queue->count == queue->SIZE || queue->rear == queue->SIZE - 1)
    {
        return false;
    }

    queue->rear++;
    queue->arr[queue->rear] = data;

    if(queue->count == 0)
    {
        queue->front = queue->rear;
    }

    (queue->count)++;

}


bool deQueue(QUEUE* queue, void** dataOutPtr)
{
    // if queue is empty
    if(queue->rear < queue->front || queue->count == 0)
    {
        return false;
    }

    *dataOutPtr = queue->arr[queue->front];

    if(queue->count != 0 && queue->front == queue->SIZE - 1)
    {
        static int a = -1;
        queue->count = 0;
        queue->arr[queue->front] = &a;
    }
    else
    {
        queue->front++;
        (queue->count)--;
    }

    return true;
}

bool queueFront(QUEUE* queue)
{
    if(queue->count == 0)
        return false;

    return queue->arr[queue->front];
}

bool queueRear(QUEUE* queue)
{
    if(queue->count == 0)
        return false;

    return queue->arr[queue->rear];
}
