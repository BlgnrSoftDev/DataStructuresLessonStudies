#include <stdio.h>
#include <stdlib.h>
#include "QueueADT.h"
#include <string.h>

bool isOperator(char ch);
char calculate(char param1, char param2, char operator_);

int main()
{
    int a = 1, b = 2, c= 3, d= 4, e = 5, f = 6;
    void* m;
//    QUEUE* queue = createQueue();
//    enQueue(&a, queue);
//    printQueue(queue);
//    enQueue(&b, queue);
//    printQueue(queue);
//    enQueue(&c, queue);
//    printQueue(queue);
//    enQueue(&d, queue);
//    printQueue(queue);
//    enQueue(&e, queue);
//    printQueue(queue);
//    enQueue(&f, queue);
//    printQueue(queue);
//    deQueue(queue, &m);
//    printQueue(queue);
//    deQueue(queue, &m);
//    printQueue(queue);
//    deQueue(queue, &m);
//    printQueue(queue);
//    deQueue(queue, &m);
//    printQueue(queue);
//    deQueue(queue, &m);
//    printQueue(queue);
//    deQueue(queue, &m);
//    printQueue(queue);
//    deQueue(queue, &m);
//    printQueue(queue);
//    deQueue(queue, &m);

    char* strIn = (char*)malloc(sizeof(char)* 10);
    gets(strIn);
    QUEUE* queue = createQueue();

    prefixEvaluation(queue, strIn);



   return 0;
}


int prefixEvaluation(QUEUE* queue, char* strIn)
{
    void* dataOutPtr;
    char* token, *op1, *op2, *ch;

    for(int i = 0; i < strlen(strIn); ++i)
    {
        ch = (char*)malloc(sizeof(char));
        *ch = strIn[i];
        enQueue(ch, queue);
    }


    while(queue->count >1)
    {
        deQueue(queue, &dataOutPtr);
        token = (char*)malloc(sizeof(char));
        *token = *((char*)dataOutPtr);

        if(isOperator(*token))
        {
            queueFront(queue, &dataOutPtr);
            op1 = (char*)malloc(sizeof(char));
            *op1 = *((char*)dataOutPtr);

            if(!isOperator(*op1))
            {
                deQueue(queue, &dataOutPtr);
                *op1 = *((char*)dataOutPtr);

                queueFront(queue, &dataOutPtr);
                op2 = (char*)malloc(sizeof(char));
                *op2 = *((char*)dataOutPtr);

                if(!isOperator(op2))
                {
                    deQueue(queue, &dataOutPtr);
                    *op2 = *((char*)dataOutPtr);

                    *token = calculate(*op1, *op2, *token) + 48;
                    enQueue(token, queue);
                }
                else
                {
                    enQueue(token, queue);
                    enQueue(op1, queue);
                }
            }
            else
            {
                enQueue(token, queue);
            }
        }
        else
        {
            enQueue(token, queue);
        }
    printQueue(queue);
    }

    if(queue->count == 1)
    {
        deQueue(queue, &token);
        printf("TOTAL : %d", *((char*)token) - 48);
    }
}

char calculate(char param1, char param2, char operator_)
{
    int op1 = param1 - 48;
    int op2 = param2 - 48;
    if(operator_ == '/')
    {
        return op1/op2;
    }
    else if(operator_ == '*')
    {
        return op1 * op2;
    }
    else if(operator_ == '+')
    {
        return op1 + op2;
    }
    else if(operator_ == '-')
        return op1 - op2;
}

bool isOperator(char ch)
{
    switch(ch)
    {
    case '+':
    case '-':
    case '/':
    case '*':
        return true;
    default:
        return false;
    }
}

void printQueue(QUEUE* queue)
{
    NODE* temp;

    if(queue == NULL)
    {
        printf("HATA!"), exit(100);
    }

    temp = queue->front;

    printf("------------------\n");
    while( temp != NULL)
    {
        printf(" %c ", *((char*)temp->data));
        temp = temp->link;
    }

    printf("\n");

}
