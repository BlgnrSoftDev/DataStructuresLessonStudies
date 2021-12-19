#include <stdio.h>
#include <stdlib.h>
#include "StackADT.h"

int main()
{
    int arr[10] = {0};
    STACK* st1 = createStack();
    STACK* st2 = createStack();

    for(int i = 0; i < 10; ++i)
    {
        arr[i] = 10 - i;
    }


    int i = 0;
    while(i < 5)
    {
        pushStack(st2, &arr[i]);
        ++i;
    }

    while(i < 10)
    {
        pushStack(st1, &arr[i]);
        ++i;
    }

    printf("BEFORE : \n");
    printStack(st1);
    printStack(st2);

    printf("AFTER : \n");
    catStack(st1, st2);
    printStack(st1);


    return 0;
}

void printStack(STACK* stack)
{
    if(stack ==  NULL)
        printf("\nSTACK IS EMPTY.");
    NODE* tr = stack->top;
    printf("Numbers: ");
    while(tr != NULL)
    {
        printf(" %d ", *((int*)tr->data));
        tr = tr->link;
    }
    printf("\n");
}

void dontMessWithMinusOne(int* numbers, int size)
{
    STACK* stack = (STACK*)malloc(sizeof(STACK));
    if(!stack)
    {
        printf("Memory cannot be allocated for Stack.."), exit(100);
    }

    int i = 0;
    while(i < size)
    {
        if(numbers[i] >= 0)
        {
            pushStack(stack, &numbers[i]);
        }
        else
        {
            if(stack->count < 5)
            {
                printf("Error: There are less than five numbers...."), exit(404);
            }
            for(int j = 0, num; j < 5; ++j)
            {
                num = *((int*)popStack(stack));
                printf(" %d ", num);
            }
        }

        ++i;
    }
}
