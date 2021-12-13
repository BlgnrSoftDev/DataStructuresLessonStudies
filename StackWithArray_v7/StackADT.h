#ifndef STACKADT_H_INCLUDED
#define STACKADT_H_INCLUDED

#include <stdbool.h>

#endif // STACKADT_H_INCLUDED

typedef struct stack_
{
    int top;
    int size;
    void** arr;

}STACK;




STACK* createStack(int size);
bool pushStack(void* data, STACK* stack);
void* popStack(STACK* stack);
bool isEmptyStack(STACK* stack);
bool isFullStack(STACK* stack);
void* stackTop(STACK* stack);
void destroyStack(STACK* stack);



void destroyStack(STACK* stack)
{
    free(stack->arr);
    free(stack);

}
void* stackTop(STACK* stack)
{
    if( stack->top == -1)
        return NULL;

    return stack->arr[stack->top];
}

bool isEmptyStack(STACK* stack)
{
    return stack->top == -1;
}
bool isFullStack(STACK* stack)
{
    return stack->top == stack->size;
}

void* popStack(STACK* stack)
{
    if( stack )
    {
        if(stack->top == -1)
        {
            return NULL;
        }

        return stack->arr[(stack->top)--];
    }
}

bool pushStack(void* data, STACK* stack)
{
    if( stack )
    {
        if(stack->top == stack->size)
        {
            return false;
        }

        stack->arr[++(stack->top)] = data;
    }
}

STACK* createStack(int size)
{
    STACK* newStack = (STACK*) malloc(sizeof(STACK));
    newStack->arr = (void**) malloc(sizeof(void*)*size);
    newStack->top = -1;
    newStack->size = size;
}



