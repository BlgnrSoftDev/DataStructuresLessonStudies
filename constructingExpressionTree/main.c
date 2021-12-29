#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "StackADT.h"

bool isOperator(char token);

typedef struct treeNode
{
    void* data;
    struct treeNode* leftSubtree, *rightSubtree;

}TREE_NODE;


void Infix(TREE_NODE* root);
int main()
{

    char* str = (char*)malloc(sizeof(char) * 15);

    printf("please enter postfix expression: ");
    gets(str);
    STACK* newStack = createStack();
    if(!newStack)
        return -1;

    for(int i = 0; i < strlen(str); ++i)
    {
        if( !isOperator(str[i]))
        {
            TREE_NODE* node_ = (TREE_NODE*)malloc(sizeof(TREE_NODE));
            node_->data = (void*)&str[i];
            node_->rightSubtree = node_->leftSubtree = NULL;
            pushStack(newStack, node_);
        }
        else
        {
            TREE_NODE* internalNode = (TREE_NODE*)malloc(sizeof(TREE_NODE));
            internalNode->data = (void*) &str[i];
            internalNode->rightSubtree = (TREE_NODE*)popStack(newStack);
            internalNode->leftSubtree = (TREE_NODE*)popStack(newStack);

            pushStack(newStack, internalNode);
        }

    }


    TREE_NODE* root = (TREE_NODE*)popStack(newStack);
    Infix(root);
    printf("\n\n");
    printPrefix(root);

    return 0;
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



void Infix(TREE_NODE* root)
{
    if(root != NULL)
    {

        if(!isOperator(*((char*)root->data)))
        {
            printf("%c", *((char*)root->data));
            return;
        }


        printf("(");
        Infix(root->leftSubtree);
        printf("%c", *((char*)root->data));
        Infix(root->rightSubtree);
        printf(")");
    }
}


void printPrefix(TREE_NODE* root)
{
    if(root == NULL)
    {
        return;
    }

    printf("%c", *((char*)root->data));
    printPrefix(root->leftSubtree);
    printPrefix(root->rightSubtree);



}

