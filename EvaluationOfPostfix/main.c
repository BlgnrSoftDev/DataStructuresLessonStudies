#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "StackADT.h"
#include <string.h>


/*

this algorithm converts a infix expression which has been taken from user to postfix then evaluates expression and prints console.

int this algorithm, numbers in infix expr. must be 0-9 digit and also is allowed to use parenthesis.

example: (9/3)*5+1 = 16


if you want to stack's state in every iteraton you can uncomment printStack and printStack2 functions.

*/
bool isOperator(char token);
int evaluatePostfix(STACK* stack, char* strIn);
int process(int operand1, int operand2, char operator_);
void printStack(STACK* stack);
bool isParenthesesMatched(STACK* stack, char* text);
int getPriority(char s);

int main()
{
    char* strIn;
    char* strOut;
    char *chPtr;
    char temp[2], token;
    STACK* stack;

    printf(" Enter text :\n\n==> ");
    strIn = (char*) malloc(sizeof(char)* 10);
    gets(strIn);

    strOut = (char*) calloc(11, sizeof(char));
    temp[1] = '\0';

    stack = createStack();
    if(!stack)
        return -1;

    STACK* tempt = createStack();
    if(!isParenthesesMatched(tempt, strIn))
    {
        printf("parentheses mismatched"), exit(101);
    }

    for(int i = 0; i < strlen(strIn); ++i)
    {
        token = strIn[i];
        if(strIn[i] == '(')
        {
            chPtr = (char*)malloc(sizeof(char));
            *chPtr = token;
            pushStack( stack, chPtr);
        }
        else if( strIn[i] == ')')
        {
            chPtr = (char*)popStack(stack);
            while( *chPtr != '(')
            {
                temp[0] = *chPtr;
                strcat(strOut, temp);
                chPtr = (char*)popStack(stack);
            }
        }
        else
        {
            if( getPriority(strIn[i]) == -1)
            {
                temp[0] = strIn[i];
                strcat(strOut, temp);
            }
            else
            {
                int priority = getPriority(strIn[i]);
                if( (stackTop(stack)) == NULL )
                {
                    chPtr = (char*)malloc(sizeof(char));
                    *chPtr = token;
                    pushStack(stack, chPtr);
                    continue;
                }

                chPtr = (char*)stackTop(stack);
                int priority2 = getPriority(*chPtr);

                while(priority <= priority2)
                {
                    chPtr = (char*)popStack(stack);
                    temp[0] = *chPtr;
                    strcat(strOut, temp);

                    if( (stackTop(stack)) == NULL )
                    {
                        break;
                    }
                    chPtr = (char*)stackTop(stack);
                    priority2 = getPriority(*chPtr);

                }


                chPtr = (char*)malloc(sizeof(char));
                *chPtr = token;
                pushStack(stack, chPtr);
            }
        }
//        printStack2(stack);
    }

    while( !isEmptyStack(stack) )
    {
        temp[0] = *((char*)popStack(stack));
        strcat(strOut, temp);
    }
    printf("\n\n%s\n\n", strOut);

    printf("\nTOTAL: %d", evaluatePostfix(stack, strOut));

    return 0;
}

int evaluatePostfix(STACK* stack, char* strIn)
{
    for(int i = 0; i < strlen(strIn); ++i)
    {
        if( isOperator(strIn[i]) )
        {

            int* operand2 = (int*)popStack(stack);
            int* operand1 = (int*)popStack(stack);
            *operand1 = process(*operand1, *operand2, strIn[i]);
            pushStack(stack, operand1);
        }
        else
        {
            char* ch = (char*)malloc(sizeof(char));
            *ch = strIn[i];
            int* val = (int*)malloc(sizeof(int));
            *val = *ch - 48;
            pushStack(stack, val);
        }
//        printStack(stack);
    }

    if( stack->count > 1)
    {
        printf("HATA"), exit(100);
    }

    return *((int*)popStack(stack));
}

bool isOperator(char token)
{
    switch(token)
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


int process(int operand1, int operand2, char operator_)
{
    if( operator_ == '+')
        return operand1 + operand2;
    else if( operator_ == '-')
        return operand1 - operand2;
    else if(operator_ == '/')
        return operand1 / operand2;
    else
        return operand1 * operand2;
}

/*
void printStack(STACK* stack)
{
    NODE* tr = stack->top;
    printf("---> ");
    while(tr != NULL)
    {
        printf("%d,", *((int*)tr->data));
        tr = tr->link;
    }
    printf("\n\n");
}

void printStack2(STACK* stack)
{
    NODE* tr = stack->top;
    printf("---> ");
    while(tr != NULL)
    {
        printf("%c,", *((char*)tr->data));
        tr = tr->link;
    }
    printf("\n\n");
}
*/

bool isParenthesesMatched(STACK* stack, char* text)
{
    for(int i = 0; i < strlen(text); ++i)
    {
        if( text[i] == '(')
        {
            pushStack(stack, text[i]);
        }
        else if(text[i] == ')')
        {
            if( isEmptyStack(stack) )
            {
                return false;
            }

            popStack(stack);
        }
    }

    if( !isEmptyStack(stack) )
    {
        return false;
    }

    destroyStack(stack);
    return true;

}

int getPriority(char s)
{
    switch(s)
    {
    case '*':
    case '/':
        return 2;
        break;
    case '+':
    case '-':
        return 1;
        break;
    case '(':
    case ')':
        return 0;
        break;
    default:
        return -1;
        break;

    }
}
