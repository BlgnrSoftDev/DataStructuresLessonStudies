#include <stdio.h>
#include <stdlib.h>
#include "UnorderedLinkedList.h"
#include <stdbool.h>

// my huffman tree algorithm.

typedef struct vertex
{
    struct vertex* left, *right;
    bool isBranch;
    int value;
    char* label;

}VERTEX;

VERTEX* huffmanAlgorithm(VERTEX** vertexArr, int arrSize, LIST* list);
VERTEX* createVertex();

int main()
{
    VERTEX** vertexArr = (VERTEX**)malloc(sizeof(VERTEX*) * 14);
    LIST* list = createList();

    vertexArr[2] = createVertex();
    vertexArr[2]->isBranch = false;
    vertexArr[2]->value = 10;
    vertexArr[2]->label[0] = 'A';


    vertexArr[11] = createVertex();
    vertexArr[11]->isBranch = false;
    vertexArr[11]->value = 3;
    vertexArr[11]->label[0] = 'C';


    vertexArr[9] = createVertex();
    vertexArr[9]->isBranch = false;
    vertexArr[9]->value = 4;
    vertexArr[9]->label[0] = 'D';

    vertexArr[0] = createVertex();
    vertexArr[0]->isBranch = false;
    vertexArr[0]->value = 15;
    vertexArr[0]->label[0] = 'E';

    vertexArr[12] = createVertex();
    vertexArr[12]->isBranch = false;
    vertexArr[12]->value = 2;
    vertexArr[12]->label[0] = 'G';

    vertexArr[8] = createVertex();
    vertexArr[8]->isBranch = false;
    vertexArr[8]->value = 4;
    vertexArr[8]->label[0] = 'I';

    vertexArr[13] = createVertex();
    vertexArr[13]->isBranch = false;
    vertexArr[13]->value = 2;
    vertexArr[13]->label[0] = 'K';

    vertexArr[10] = createVertex();
    vertexArr[10]->isBranch = false;
    vertexArr[10]->value = 3;
    vertexArr[10]->label[0] = 'M';

    vertexArr[5] = createVertex();
    vertexArr[5]->isBranch = false;
    vertexArr[5]->value = 6;
    vertexArr[5]->label[0] = 'N';

    vertexArr[3] = createVertex();
    vertexArr[3]->isBranch = false;
    vertexArr[3]->value = 8;
    vertexArr[3]->label[0] = 'O';

    vertexArr[4] = createVertex();
    vertexArr[4]->isBranch = false;
    vertexArr[4]->value = 7;
    vertexArr[4]->label[0] = 'R';


    vertexArr[6] = createVertex();
    vertexArr[6]->isBranch = false;
    vertexArr[6]->value = 5;
    vertexArr[6]->label[0] = 'S';

    vertexArr[1] = createVertex();
    vertexArr[1]->isBranch = false;
    vertexArr[1]->value = 12;
    vertexArr[1]->label[0] = 'T';

    vertexArr[7] = createVertex();
    vertexArr[7]->isBranch = false;
    vertexArr[7]->value = 5;
    vertexArr[7]->label[0] = 'U';

    VERTEX* newroot = huffmanAlgorithm(vertexArr, 14, list);
    printf(" %d", newroot->value);


    return 0;
}

int compare(void* arg, void* arg2)
{
    if( ((VERTEX*)arg)->value ==  ((VERTEX*)arg2)->value )
    {
        return 1;
    }
    else
        return 0;
}


VERTEX* huffmanAlgorithm(VERTEX** vertexArr, int arrSize, LIST* list)
{

    bool okey = false;
    for(int i = 0; i < arrSize; ++i)
    {
        insertNode(vertexArr[i], list);
    }

    int min;
    VERTEX* left, *right;
    while(list->count > 1)
    {
        min = 999999999;
        for(int i = 0; i < arrSize; ++i)
        {
            NODE* root = list->head;
            for(int k = 0; k < i; ++k)
            {
                root = root->next;
            }

            NODE* temp = root;

            while(temp->next)
            {
                temp = temp->next;
                if( (((VERTEX*)root->data)->value + ((VERTEX*)temp->data)->value) < min)
                {
                    min = (((VERTEX*)root->data)->value + ((VERTEX*)temp->data)->value);
                    left = (VERTEX*)root->data;
                    right = (VERTEX*)temp->data;
                }
            }
        }

            VERTEX* newBranch = createVertex();
            newBranch->isBranch = true;
            newBranch->value = min;
            newBranch->left = left;
            newBranch->right = right;

            removeNode(left, list, compare);
            removeNode(right, list, compare);
            insertNode(newBranch, list);
            arrSize--;

        printf(" %d ", newBranch->value);

    }

    return (VERTEX*)list->head->data;

}

VERTEX* createVertex()
{
    VERTEX* newVertex = (VERTEX*)malloc(sizeof(VERTEX));
    newVertex->isBranch = false;
    newVertex->left = newVertex->right = NULL;
    newVertex->value = 0;
    newVertex->label = (char*)malloc(sizeof(char) * 2);
    newVertex->label[1] = '\0';

    return newVertex;
}
