#include <stdio.h>
#include <stdlib.h>
#include "QueueADT.h"
#include "StackADT.h"

int main()
{
    int a = 1, b = 2, c = 3, d = 4, e = 5, f = 6;
    void* data;
    QUEUE* queue = createQueue();
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
    deQueue(queue, &data);
    printQueue(queue);
    deQueue(queue, &data);
    printQueue(queue);
    deQueue(queue, &data);
    printQueue(queue);
    enQueue(queue, &f);
    printQueue(queue);
    deQueue(queue, &data);
    printQueue(queue);
    deQueue(queue, &data);
    printQueue(queue);
    deQueue(queue, &data);
    printQueue(queue);
    deQueue(queue, &data);
    printQueue(queue);
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
    return 0;
}

void printQueue(QUEUE* queue)
{
    NODE* top;
    printf("\n------------------------------\n");
    top = queue->front;
    while(top != NULL)
    {
        printf(" %d ", *((int*)top->data));
        top = top->link;
    }
    top = queue->bucketTwo;
    printRecursive(queue->bucketOne->top);
}


void printRecursive(NODE* temp)
{
    if(temp == NULL)
    {
        printf("");
    }
    else
    {
        printRecursive(temp->link);
        printf(" %d ", *((int*)temp->data));
    }

}
