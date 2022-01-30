#include <stdio.h>
#include <stdlib.h>
#include "QueueADT.h"
typedef struct nxde
{
    int key, childrenSize, last;
    struct nxde** children;
    bool z;

}NODE_;

typedef struct _nxde
{
    int key;
    struct _nxde* left, *right;
}BINARYNODE;



NODE_* createNode_();
BINARYNODE* createBNode();

int main()
{

    NODE_* nodeA = createNode_(1);
    NODE_* nodeB = createNode_(2);
    NODE_* nodeC = createNode_(3);
    NODE_* nodeD = createNode_(4);
    NODE_* nodeE = createNode_(5);
    NODE_* nodeF = createNode_(6);
    NODE_* nodeG = createNode_(7);
    NODE_* nodeH = createNode_(8);
//    NODE_* nodeI = createNode_(9);
//    NODE_* nodeJ = createNode_(10);
//    NODE_* nodeK = createNode_(11);
//    NODE_* nodeL = createNode_(12);

    nodeA->children[0] = nodeB;
    nodeA->children[1] = nodeC;
    nodeA->children[2] = nodeD;
    nodeA->childrenSize = 3;
    nodeA->last = 2;

    nodeB->children[0] = nodeE;
    nodeB->children[1] = nodeF;
    nodeB->children[2] = nodeG;
    nodeB->childrenSize = 3;
    nodeB->last = 2;


    nodeC->children[0] = nodeH;
    nodeC->childrenSize = 1;
    nodeC->last = 0;

    QUEUE* queue = createQueue();
    convertToBinaryTree(nodeA, queue);

    BINARYNODE* newRoot =createBNode();
    makeFullBinary(nodeA, newRoot);
    infixOrigial(newRoot);

//
//    printf("\n%d", ((NODE_*)nodeI->children[0])->key);
//    printf("\n%d", ((NODE_*)nodeI->children[1])->key);


    return 0;
}

BINARYNODE* createBNode()
{
    BINARYNODE* newNode = (BINARYNODE*)malloc(sizeof(BINARYNODE));
    newNode->left = newNode->right = NULL;

    return newNode;
}

void makeFullBinary(NODE_* root, BINARYNODE* newRoot)
{

    if(root != NULL)
    {
        newRoot->key = root->key;
        if(root->children[0])
        {
            newRoot->left = createBNode();
        }
        if(root->children[1])
        {
            newRoot->right = createBNode();
        }

        makeFullBinary(root->children[0], newRoot->left);
        makeFullBinary(root->children[1], newRoot->right);
    }
}


NODE_* createNode_(int key)
{
    NODE_* newNode =(NODE_*)malloc(sizeof(NODE_));
    newNode->children = (NODE_**)malloc(sizeof(NODE_*) * 11);

    for(int i = 0; i < 11; ++i)
        newNode->children[i] = NULL;

    newNode->childrenSize = 0;
    newNode->key = key;
    newNode->last = -1;
    newNode->z = false;
    return newNode;
}

void convertToBinaryTree(NODE_* root, QUEUE* queue)
{
    int last;

    for(int k = 0; k < root->childrenSize; ++k)
    {
        enQueue(root->children[k], queue);
    }

    for(int i = 0; i < root->childrenSize-1; ++i)
    {
        last = root->children[i]->last;

        root->children[i]->children[last+1] = root->children[i+1];
        root->children[i]->last++;
        root->children[i]->childrenSize++;
        root->children[i]->z = true;
    }

    root->children[root->last]->childrenSize++;
    root->children[root->last]->last++;


    root->children[1] = NULL;
    root->childrenSize = 1;
    root->last = 0;

    NODE_* temp;
    while(queue->count != 0)
    {
        deQueue(queue, (void**)&temp);

        for(int k = 0; k < temp->childrenSize-1; ++k)
        {
            enQueue(temp->children[k], queue);
        }

        for(int k = 0; k < temp->childrenSize-2; ++k)
        {
            last = temp->children[k]->last;

            temp->children[k]->children[last+1] = temp->children[k+1];
            temp->children[k]->last++;
            temp->children[k]->childrenSize++;
            temp->children[k]->z = true;
        }

        if(temp->z == false)
        {
            temp->childrenSize = 1;
            temp->children[1] = NULL;
            temp->last= 0;
        }
        else if( temp->last > 1)
        {
            temp->children[1] = temp->children[temp->last];
            temp->children[temp->last] = NULL;
            temp->childrenSize = 2;
            temp->last = 1;
        }




    }
}


void infix(NODE_* root)
{
    if(root != NULL)
    {


        infix(root->children[0]);
        printf(" %d ", root->key);
        infix(root->children[1]);
    }
}

void infixOrigial(BINARYNODE* nn)
{
    if(nn != NULL)
    {
        infixOrigial(nn->left);
        printf(" %d ", nn->key);
        infixOrigial(nn->right);
    }
}

