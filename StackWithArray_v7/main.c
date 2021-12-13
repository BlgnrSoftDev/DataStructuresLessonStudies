#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "StackADT.h"

void printAllElement(STACK* stack);
int main()
{
    int a = 1, b = 2, c = 3, d = 4, e = 5;
    STACK* stack = createStack(5);
    pushStack(&a, stack);
    printAllElement(stack);
    pushStack(&b, stack);
    printAllElement(stack);
    pushStack(&c, stack);
    printAllElement(stack);
    pushStack(&d, stack);
    printAllElement(stack);
    pushStack(&e, stack);
    printAllElement(stack);

    popStack(stack);
    printAllElement(stack);
    popStack(stack);
    printAllElement(stack);
    popStack(stack);
    printAllElement(stack);
    popStack(stack);
    printAllElement(stack);
    popStack(stack);
    printAllElement(stack);
    return 0;
}


void printAllElement(STACK* stack)
{
    int i = 0;
    printf("\n###########");
    while(i <= stack->top)
    {
        printf("\n------");
        printf("\n| %d |", *((int*)stack->arr[i++]));
        printf("\n------");
    }
    printf("\n###########\n\n");
}
