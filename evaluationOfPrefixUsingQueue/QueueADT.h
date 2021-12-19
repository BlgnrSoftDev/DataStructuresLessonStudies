#ifndef QUEUEADT_H_INCLUDED
#define QUEUEADT_H_INCLUDED

#include <stdbool.h>

#endif // QUEUEADT_H_INCLUDED

typedef struct node
{
    void* data;
    struct node* link;
}NODE;


typedef struct queue
{

    NODE* front, *rear;
    int count;
}QUEUE;


bool enQueue(void* data, QUEUE* queue);
QUEUE* createQueue();
QUEUE* destroyQueue(QUEUE* queue);
bool deQueue(QUEUE* queue, void** itemPtr);
bool queueFront(QUEUE* queue, void** itemPtr);
bool queueRear(QUEUE* queue, void** itemPtr);
int queueCount(QUEUE* queue);


QUEUE* destroyQueue(QUEUE* queue)
{
    NODE* temp;

    while(queue->front != NULL)
    {
        temp = queue->front;
        free(temp->data);
        queue->front = queue->front->link;
        free(temp);
    }

    free(queue);


    return NULL;

}


int queueCount(QUEUE* queue)
{
    return queue->count;
}

bool queueRear(QUEUE* queue, void** itemPtr)
{
    if( queue->count == 0 || queue == NULL)
    {
        return false;
    }

    *itemPtr = queue->rear->data;
    return true;
}

bool queueFront(QUEUE* queue, void** itemPtr)
{
    if(queue == NULL || queue->count == 0)
    {
        return false;
    }

    *itemPtr = queue->front->data;
    return true;
}


bool deQueue(QUEUE* queue, void** itemPtr)
{
    NODE* deleteLoc;

    if(queue == NULL || queue->count == 0)
    {
        return false;
    }

    deleteLoc = queue->front;
    queue->front = queue->front->link;
    *itemPtr = deleteLoc->data;
    (queue->count)--;
    free(deleteLoc);

    return true;
}

QUEUE* createQueue()
{
    QUEUE* newQueue = (QUEUE*)malloc(sizeof(QUEUE));
    newQueue->count = 0;
    newQueue->front = newQueue->rear = NULL;
}


bool enQueue(void* data, QUEUE* queue)
{
    NODE* newNode = (NODE*)malloc(sizeof(NODE));
    if(!newNode)
        return false;

    newNode->data = data;
    newNode->link = NULL;

    if(!queue)
        return false;

    if( queue->count == 0)
        queue->front = newNode;
    else
        queue->rear->link = newNode;

    queue->rear = newNode;
    queue->count++;
    return true;

}

