#ifndef STACKADT_H_INCLUDED
#define STACKADT_H_INCLUDED

#include <stdbool.h>
typedef struct node
{
    void* data;
    struct node* link;
}NODE;

typedef struct stack
{
    NODE* top;
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
    NODE* tmp;
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
    NODE* temp = (NODE*)malloc(sizeof(NODE));
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

    NODE* temp = stack->top;
    void* d = temp->data;
    stack->top = stack->top->link;
    free(temp);
    stack->count--;

    return d;
}

bool pushStack(STACK* stack, void* data)
{

    NODE* newNode = (NODE*) malloc(sizeof(NODE));
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

#endif // STACKADT_H_INCLUDED


