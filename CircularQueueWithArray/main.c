#include <stdio.h>
#include <stdlib.h>
#include "QueueADT.h"
#include "StackADT.h"

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
    enQueue(queue, &a);
    printQueue(queue);
    enQueue(queue, &b);
    printQueue(queue);
    enQueue(queue, &c);
    printQueue(queue);
    deQueue(queue, &sth);
    printQueue(queue);
    deQueue(queue, &sth);
    printQueue(queue);
    enQueue(queue, &c);
    printQueue(queue);
    enQueue(queue, &d);
    printQueue(queue);
    return 0;
}

void printQueue(QUEUE* queue)
{
    printf("\n---------------------------\n");
    int i;
    for(i = queue->front; i != queue->rear; )
    {
        i = (i + 1) % queue->SIZE;
        printf(" %d ", *((int*)queue->arr[i]));
    }
}
