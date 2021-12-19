#include <stdio.h>
#include <stdlib.h>
#include "QueueADT.h"


void printQueue(QUEUE* queue);


int main()
{
    int a = 1, b = 2, c = 3, d = 4, e = 5;
    void* sth;
    QUEUE* queue = createQueue(5);
    enQueue(queue, &a);
    printQueue(queue);
    enQueue(queue, &b);
    printQueue(queue);
    enQueue(queue, &c);
    printQueue(queue);
    enQueue(queue, &d);
    printQueue(queue);
    enQueue(queue, &e);
    printQueue(queue);
    deQueue(queue, &sth);
    printQueue(queue);
    deQueue(queue, &sth);
    printQueue(queue);
    deQueue(queue, &sth);
    printQueue(queue);
    deQueue(queue, &sth);
    printQueue(queue);
    deQueue(queue, &sth);
    printQueue(queue);

    return 0;
}


void printQueue(QUEUE* queue)
{
    printf("\n---------------------------\n");
    for(int i = queue->front; i <= queue->rear; i+=1)
    {
        printf(" %d ", *((int*)queue->arr[i]));
    }
}
