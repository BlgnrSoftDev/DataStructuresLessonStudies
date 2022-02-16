#ifndef STACKADT_H_INCLUDED
#define STACKADT_H_INCLUDED

#include <stdbool.h>

#endif // STACKADT_H_INCLUDED


typedef struct node_
{
    void* data;
    struct node_* link;
}node_;

typedef struct stack
{
    node_* top;
    int count;

}STACK;


STACK* createStack();
bool pushStack(STACK* stack, void* data);
void* popStack(STACK* stack);
bool isFullStack(STACK* stack);
bool isEmptyStack(STACK* stack);
void destroyStack(STACK* stack);


void destroyStack(STACK* stack)
{
    node_* tmp;
    while(stack->top != NULL)
    {
        tmp = stack->top;
        stack->top = stack->top->link;
        free(tmp);
    }

    free(stack);
}
bool isFullStack(STACK* stack)
{
    node_* temp = (node_*)malloc(sizeof(node_));
    return temp == NULL ;
}
bool isEmptyStack(STACK* stack)
{
    return stack->count == 0;
}
void* popStack(STACK* stack)
{
    if(stack->top == NULL)
    {
        return NULL;
    }

    node_* temp = stack->top;
    void* d = temp->data;
    stack->top = stack->top->link;
    free(temp);
    stack->count--;

    return d;
}

bool pushStack(STACK* stack, void* data)
{

    node_* newNode = (node_*) malloc(sizeof(node_));
    if( !newNode)
    {
        return false;
    }

    newNode->data = data;
    newNode->link = stack->top;
    stack->top = newNode;
    stack->count++;

    return true;
}

STACK* createStack()
{
    STACK* stack = (STACK*) malloc(sizeof(STACK));
    if(stack)
    {
        stack->count = 0;
        stack->top = NULL;

        return stack;
    }

    return NULL;
}




