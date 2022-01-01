#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "StackADT.h"
#include <math.h>

bool isOperator(char token);


typedef struct treeNode
{
    void* data;
    struct treeNode* leftSubtree, *rightSubtree;

}TREE_NODE;

TREE_NODE* deleteAllLeaf(TREE_NODE* root);
void Infix(TREE_NODE* root);
int findHeightOfBinaryTree(TREE_NODE* root);
bool isCompleteBinaryTree(TREE_NODE* root);
bool isNearlyComplete(TREE_NODE* root);
void preorderTraversal(TREE_NODE* root, STACK* stack);
int computeBalanceFactorOfBinaryTree(TREE_NODE* root);

int main()
{
    // ***************** Constructing Algorithm **************************
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
    // ***************** END **************************************************


    Infix(root);
    printf("\n");

    int* num = (int*)malloc(sizeof(int));
    *num = 0;
    countNumberOfNodes(root, num);
    printf("%d\n\n", *num);

    TREE_NODE* ancestor = NULL;
    char dr = '0';
    printf("\n");
    STACK* st = createStack();
    inorderTraversal(root, st);
    printf("\n");
    preorderTraversal(root, st);
//Infix(root);
    printf("\n");
    *num = 0;
    countNumberOfNodes(root, num);
    printf("%d\n\n", *num);
    *num = 0;

    if( isCompleteBinaryTree(root))
        printf("Complete tree'dir...");
    if( isNearlyComplete(root))
        printf("Nearly Complete Tree'dir...");


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

void convertToParen(TREE_NODE* root)
{
    printf("%c", *((char*)root->data));

    if(root->leftSubtree != NULL || root->rightSubtree != NULL)
    {
        printf("(");

        if(root->leftSubtree != NULL)
            convertToParen(root->leftSubtree);

        if(root->rightSubtree != NULL)
            convertToParen(root->rightSubtree);

        printf(")");
    }


}



int calculateMaximumNodeNum(int height)
{
    if( height == 1)
    {
        return 1;
    }


    return 2 * calculateMaximumNodeNum(height-1) + 1;

}



void countNumberOfNodes(TREE_NODE* root, int* num)
{

    if(root)
    {
        countNumberOfNodes(root->leftSubtree, num);
        countNumberOfNodes(root->rightSubtree, num);
        *num += 1;
    }

}


TREE_NODE* deleteAllLeaf(TREE_NODE* root)
{
    if(root == NULL)
        return NULL;

    if(root->leftSubtree == NULL && root->rightSubtree == NULL)
        return NULL;


    root->leftSubtree = deleteAllLeaf(root->leftSubtree);
    root->rightSubtree = deleteAllLeaf(root->rightSubtree);
}



void deleteAllLeaf_v2(TREE_NODE* root, TREE_NODE* ancestor, char direction)
{
    if(root == NULL)
        return;
    if(root->leftSubtree == NULL && root->rightSubtree == NULL)
    {
        if(direction == 'r')
        {
            ancestor->rightSubtree = NULL;
        }
        else if(direction == 'l')
        {
            ancestor->leftSubtree = NULL;
        }

        return;
    }

    direction = 'l';
    deleteAllLeaf_v2(root->leftSubtree, root, direction);

    direction = 'r';
    deleteAllLeaf_v2(root->rightSubtree, root, direction);

}


bool isCompleteBinaryTree(TREE_NODE* root)
{
    int* num = (int*)malloc(sizeof(int));
    *num = 0;
    countNumberOfNodes(root, num);
    int height = findHeightOfBinaryTree(root);


    return ((*num) == ((int)pow(2.0, height)) - 1);
}

bool isNearlyComplete(TREE_NODE* root)
{
    int* num = (int*)malloc(sizeof(int));
    *num = 0;
    countNumberOfNodes(root, num);
    int height = findHeightOfBinaryTree(root);

    if( *num > (((int) pow(2, height-1)) - 1) && *num < (((int) pow(2, height)) - 1))
        return true;
    else
        return false;

}


int findHeightOfBinaryTree(TREE_NODE* root)
{

    if( root == NULL)
        return 0;

    int leftHeight = findHeightOfBinaryTree(root->leftSubtree);
    int rightHeight = findHeightOfBinaryTree(root->rightSubtree);

    if(leftHeight > rightHeight)
        return leftHeight + 1;
    else
        return rightHeight + 1;
}

void inorderTraversal(TREE_NODE* root, STACK* stack)
{
    TREE_NODE* temp = root;
    pushStack(stack, root);

    int j = 0;
    while(stack->count != 0)
    {

            while(temp->leftSubtree)
            {
                if(isOperator(*((char*)temp->leftSubtree->data)))
                    printf("(");
                pushStack(stack, temp->leftSubtree);
                temp = temp->leftSubtree;
            }

            temp = (TREE_NODE*)popStack(stack);
            printf("%c", *((char*)temp->data));
            j++;

            if(temp->rightSubtree)
            {
                pushStack(stack, temp->rightSubtree);
                temp = temp->rightSubtree;
            }

            if(j == 3)
            {
                printf(")");
                j = 1;
            }


    }
}

int computeBalanceFactorOfBinaryTree(TREE_NODE* root)
{
    int leftHeight = findHeightOfBinaryTree(root->leftSubtree);
    int rightHeight = findHeightOfBinaryTree(root->rightSubtree);

    return leftHeight - rightHeight;
}
