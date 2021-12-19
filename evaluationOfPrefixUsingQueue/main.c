#include <stdio.h>
#include <stdlib.h>
#include "QueueADT.h"
#include <stdbool.h>
#include <string.h>

typedef struct expr
{
    bool isOperator;
    char symbol;
    int value;

}EXPRESSION;


bool evaluatePrefix(char* strIn, QUEUE* queue);
int calculate(char operator_, int param1, int param2);
bool checkExpr(EXPRESSION** arr);
bool isOperator(char ch);

int main()
{
    char* str = (char*)malloc(sizeof(char)*11);
    printf("Enter Prefix Expression: \n==>");
    gets(str);

    QUEUE* queue = createQueue();
    evaluatePrefix(str,queue);
    return 0;
}


bool evaluatePrefix(char* strIn, QUEUE* queue)
{
    EXPRESSION** arr = (EXPRESSION**)malloc(sizeof(EXPRESSION*)*3);

    //firstly add all characters in string to queue.
    for(int i = 0; i < strlen(strIn); ++i)
    {
        EXPRESSION* ch = (EXPRESSION*)malloc(sizeof(EXPRESSION));
        ch->symbol = strIn[i];
        if(isOperator(strIn[i]))
        {
            ch->isOperator = true;
            ch->value = 0;
        }
        else
        {
            ch->isOperator = false;
            ch->value = strIn[i] - 48;
        }

        enQueue(ch, queue);
    }

    if(queue->count < 3)
        return false;

    printQueue(queue);

    while(queue->count > 1)
    {
        NODE* temp = queue->front;

        for(int i = 0; i < 3; ++i)
        {
            arr[i] = (EXPRESSION*)(temp->data);
            temp = temp->link;
        }

        void* ref;

        if( checkExpr(arr) )
        {
            int val = calculate(arr[0]->symbol, arr[1]->value, arr[2]->value);
            deQueue(queue, &ref);
            deQueue(queue, &ref);
            deQueue(queue, &ref);

            EXPRESSION* newValue = (EXPRESSION*)malloc(sizeof(EXPRESSION));
            newValue->isOperator = false;
            newValue->symbol = 'd';
            newValue->value = val;

            enQueue(newValue, queue);
        }
        else
        {
            deQueue(queue, &ref);
            enQueue(ref, queue);

        }

        printQueue(queue);
    }

    void* ref;
    deQueue(queue, &ref);
    printf("TOTAL : %d", ((EXPRESSION*)ref)->value);
}

void printQueue(QUEUE* queue)
{
    NODE* temp;

    if(queue == NULL)
    {
        printf("HATA!"), exit(100);
    }

    temp = queue->front;
    EXPRESSION* data;
    printf("----------------------------------------\n");

    while( temp != NULL)
    {
        data = (void*)temp->data;
        if(data->isOperator)
            printf(" %c ", data->symbol);
        else
            printf(" %d ", data->value);
        temp = temp->link;
    }

    printf("\n");

}

int calculate(char operator_, int param1, int param2)
{
    if(operator_ == '/')
    {
        return param1/param2;
    }
    else if(operator_ == '*')
    {
        return param1 * param2;
    }
    else if(operator_ == '+')
    {
        return param1 + param2;
    }
    else if(operator_ == '-')
        return param1 - param2;
}

bool checkExpr(EXPRESSION** arr)
{
    if( arr[0]->isOperator )
    {
        if( !arr[1]->isOperator )
        {
            if( !arr[2]->isOperator)
            {
                return true;
            }
        }
    }

    return false;
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



