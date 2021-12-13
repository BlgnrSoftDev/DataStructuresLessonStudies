#ifndef LISTADT_H_INCLUDED
#define LISTADT_H_INCLUDED

#include <stdbool.h>

#endif // LISTADT_H_INCLUDED

/*
    this version of linked list is different from general linked list implementation by using a dummy node.
    dummy node made code much more simpler than before. By using dummy node we eliminate conditions which are insert at beginning, delete at beginning, insert empty list.

*/
typedef struct node
{
    void* data;
    struct node* link;

}NODE;

typedef struct listADT
{
    NODE* pHead;
    NODE* rear;
    NODE* pos;

    int count;
    int (* compare) (void*, void*);

}LIST;

static bool _insert(LIST* pList, NODE* pPre, NODE* pLoc, void* dataInPtr);
static bool _search(LIST* pList, NODE** pPre, NODE** pLoc, void* pArgu);
static bool _delete(LIST* pList, NODE* pPre, NODE* pLoc);
bool removeNode(LIST* pList, void* keyPtr);



LIST* createList(int (* compare) (void*, void*))
{
    LIST* newList;
    NODE* dummyNode;

    if( (newList = (LIST*) malloc(sizeof(LIST))) )
    {
        dummyNode = (NODE*) malloc(sizeof(NODE));
        dummyNode->data = NULL;
        dummyNode->link = NULL;

        newList->count = 0;
        newList->compare = compare;
        newList->pHead = dummyNode;
        newList->pos = NULL;
        newList->rear = NULL;
    }

    return newList;
}

LIST* destroyList(LIST* pList)
{
    if(pList)
    {
       _destroy(pList->pHead);
       free(pList);
    }
    return pList;
}

void _destroy(NODE* pHead)
{
    _destroy(pHead->link);
    free(pHead->data);
    free(pHead);
}

int addNode(LIST* pList, void* data)
{
    bool found, success;
    NODE* pPre;
    NODE* pLoc;

    if( (found = _search(pList, &pPre, &pLoc, data)) )
    {
        return 1;
    }
    else
    {
        if( (success = _insert(pList, pPre, pLoc, data)) )
        {
            pList->count++;
            return 0;
        }
        else
            return -1;
    }
}

bool removeNode(LIST* pList, void* keyPtr)
{
    bool found, success;
    NODE* pPre;
    NODE* pLoc;

    if(pList->count == 0)
    {
        return false;
    }

    if( !(found = _search(pList, &pPre, &pLoc, keyPtr)) )
    {
        return false;
    }
    else
    {
        if( (success = _delete(pList, pPre, pLoc)))
        {
            return success;
        }
        else
        {
            return false;
        }
    }

}

bool searchList(LIST* pList, void* pArgu, void** pDataOut)
{
    bool found;
    NODE* pPre;
    NODE* pLoc;

    if( found =  _search(pList, &pPre, &pLoc, pArgu) )
    {
        *pDataOut = pLoc->data;
    }
    else
    {
        *pDataOut = NULL;
    }

    return found;


}

bool retrieveNode(LIST* pList, void* pArgu, void** dataOutPtr)
{
    bool found;
    NODE* pPre;
    NODE* pLoc;

    if( pList->count == 0)
        return false;

    if( (found = _search(pList, &pPre, &pLoc, pArgu)))
        *dataOutPtr = pLoc->data;
    else
        *dataOutPtr = NULL;

    return true;
}

bool traverse(LIST* pList, int fromWhere, void** dataOutPtr)
{
    NODE** traverser = &(pList->pos);

    if(pList->count == 0)
        return false;

    if(fromWhere == 0)
        *traverser = pList->pHead;

    if( (*traverser) == NULL)
        return false;

    *traverser = (*traverser)->link;
    *dataOutPtr = (*traverser)->data;

    return true;
}

int listCount(LIST* pList)
{
    return pList->count;
}

bool emptyList(LIST* pList)
{
    return pList->count == 0 || pList == NULL ;
}

bool fullList(LIST* pList)
{
    NODE* newNode;

    if( !(newNode = (NODE*) malloc(sizeof(NODE))) )
    {
        return false;
    }
}

static bool _insert(LIST* pList, NODE* pPre, NODE* pLoc, void* dataInPtr)
{
    NODE* newNode;
    if( !( newNode = (NODE*) malloc(sizeof(NODE)) ) )
    {
        return false;
    }

    newNode->data = dataInPtr;

    if(pLoc == NULL)
    {
        newNode->link = NULL;
        pList->rear = newNode;
    }
    else if(pLoc != NULL)
    {
        newNode->link = pLoc;
    }

    pPre->link = newNode;

    return true;
}

static bool _search(LIST* pList, NODE** pPre, NODE** pLoc, void* pArgu)
{
    #define COMPARE (((* pList->compare) (pArgu, (*pLoc)->data)))
    #define COMPARE_LAST (((* pList->compare) (pArgu, pList->rear->data)))

    (*pPre) = pList->pHead;
    (*pLoc) = (*pPre)->link;

    if( pList->count == 0)
    {
        return false;
    }
    if( COMPARE_LAST > 0)
    {
        *pPre = pList->rear;
        *pLoc = NULL;
        return false;
    }

    else
    {
        int isEqual;
        while( (isEqual = COMPARE) > 0 )
        {
            *pPre = *pLoc;
            *pLoc = (*pLoc)->link;
        }

        if(isEqual == 0)
            return true;
        else
            return false;
    }
}

static bool _delete(LIST* pList, NODE* pPre, NODE* pLoc)
{

    pPre->link = pLoc->link;
    pList->count--;


    if(pLoc->link == NULL)
    {
        pList->rear = NULL;

        if(pPre == pList->pHead)
        {
            pList->rear = pPre;
        }
    }

    free(pLoc);
    return true;
}

void printAllNodes(LIST* pList)
{
    NODE* iterate = pList->pHead->link;

    while(iterate != NULL)
    {
        printf(" %d ---> ", *((int*)iterate->data));
        iterate = iterate->link;
    }
    printf(" --END-- \n\n");
}
