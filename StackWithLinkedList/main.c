#include <stdio.h>
#include <stdlib.h>
#include "StackADT.h"
#include <stdbool.h>
int main()
{
    int a = 1, b = 2, c = 3, d = 4, e = 5, f = 6;
    STACK* stack = createStack();
    pushStack(stack, &a);
    printAllElement(stack);
    pushStack(stack, &b);
    printAllElement(stack);
    pushStack(stack, &c);
    printAllElement(stack);
    pushStack(stack, &d);
    printAllElement(stack);
    pushStack(stack, &e);
    printAllElement(stack);
    pushStack(stack, &f);
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
    popStack(stack);
    printAllElement(stack);

    return 0;
}

void printAllElement(STACK* stack)
{
    NODE* tmp = stack->top;
    printf("\n###########");
    while(tmp != NULL)
    {
        printf("\n------");
        printf("\n| %d |", *((int*)tmp->data));
        printf("\n------");
        tmp = tmp->link;
    }
    printf("\n###########\n\n");
}
