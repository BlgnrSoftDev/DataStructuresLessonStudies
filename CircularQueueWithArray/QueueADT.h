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
    newQueue->front = newQueue->rear = 0;

    return newQueue;
}


bool enQueue(QUEUE* queue, void* data)
{
    // if queue is full
    if(queue->front == (queue->rear+1) % queue->SIZE)
    {
        return false;
    }

    queue->rear = (queue->rear + 1) % queue->SIZE;
    queue->arr[queue->rear] = data;

    (queue->count)++;

}


bool deQueue(QUEUE* queue, void** dataOutPtr)
{
    // if queue is empty
    if(queue->front == queue->rear)
    {
        return false;
    }


    queue->front = (queue->front + 1) % queue->SIZE;
    *dataOutPtr = queue->arr[queue->front];
    (queue->count)--;
    return true;
}

bool queueFront(QUEUE* queue)
{
    if(queue->count == 0)
        return false;

    return queue->arr[queue->front + 1];
}

bool queueRear(QUEUE* queue)
{
    if(queue->count == 0)
        return false;

    return queue->arr[queue->rear];
}
