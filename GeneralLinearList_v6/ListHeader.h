#ifndef LISTHEADER_H_INCLUDED
#define LISTHEADER_H_INCLUDED

#endif // LISTHEADER_H_INCLUDED
#include <stdbool.h>

typedef struct node
{
    void* data;
    struct node* link;
}Node;

typedef struct list
{
    int count;
    int (*compare) (void*, void*);
    Node* head;
    Node* pos;
    Node* rear;

}ListADT;


// prototype declarations
ListADT* createList(int (* compare) (void*, void*));

ListADT* destroyList(ListADT* pList);

int addNode(ListADT* pList, void* data);

bool removeNode(ListADT* pList, void* keyPtr, void** dataOutPtr);

bool searchList(ListADT* pList, void* pArgu, void** pDataOut);

bool retrieveNode(ListADT* pList, void* pArgu, void** dataOutPtr);

bool traverse(ListADT* pList, int fromWhere, void** dataOutPtr);

int listCount(ListADT* pList);

bool emptyList(ListADT* pList);

bool fullList(ListADT* pList);

static bool _insert(ListADT* pList, Node* pPre, void* dataInPtr);

static bool _search(ListADT*, Node** pPre, Node** pLoc, void* pArgu);

static void _delete(ListADT* pList, Node* pPre, Node* pLoc, void** dataOutPtr);

// end of prototype declarations.


/*
 ======== createList =========
allocates dynamic memory for a list head node and returns its adress to caller.

Pre: compare parameter is address of compare function used to compare two nodes.

Post: head node allocated or error returned.

Return: head node pointer or null if overflow.
*/

ListADT* createList(int (* compare) (void*, void*))
{
    ListADT* list = ( ListADT* ) malloc(sizeof( ListADT ));
    if(list != NULL)
    {
        (*list).count = 0;
        (*list).head = NULL;
        (*list).rear = NULL;
        (*list).pos = NULL;
        (*list).compare = compare;
    }

    return list;
}// createList

/*
======== addNode ==========
#inserts data into list

Pre: pList is pointer to valid list.
     dataInPtr is pointer to insertion data.

Post:
     data inserted or error.

Return:
     -1 if overflow
     0 if succesful
     1 if duplicate key
*/

int addNode(ListADT* pList, void* dataInPtr)
{
    bool found, success;
    Node* pPre;
    Node* pLoc;

    found = _search(pList, &pPre, &pLoc, dataInPtr);
    if(found)
    {
        return 1;
    }
    else
    {
        success = _insert(pList, pPre, dataInPtr);
        if(!success)
        {
            return -1;
        }
        else
        {
            return 0;
        }
    }
}// addNode


/*
=========== _insert ========

inserts data pointer into a new node.

Pre: pPre is pointer to data's predecessor.
     pList is pointer to a valid list.
     dataInPtr is pointer to data to be inserted

Post: data have been inserted in sequence.

Return: boolean; true if succesful, false if memory overflow.
*/
static bool _insert(ListADT* pList, Node* pPre, void* dataInPtr)
{
    Node* newNode = (Node*) malloc( sizeof(Node));

    if(!newNode)
    {
        return false;
    }
    else
    {
        newNode->data = dataInPtr;
        newNode->link = NULL;

        if(pPre == NULL)
        {
            newNode->link = pList->head;
            pList->head = newNode;

            if(pList->count == 0)
            {
                pList->rear = newNode;
            }
        }
        else
        {
            newNode->link = pPre->link;
            pPre->link = newNode;

            if(newNode->link == NULL)
            {
                pList->rear = newNode;
            }
        }
        pList->count++;

        return true;
    }
}// _insert


/*
=========== removeNode =============
removes data from list.

pPre:   pList is pointer to a valid list.
        keyPtr is pointer to key to be deleted.
        dataOutPtr is pointer to data pointer.

pPost:  Node deleted or error returned.

Return: if data isn't found, false ; if data is deleted, true.
*/

bool removeNode(ListADT* pList, void* keyPtr, void** dataOutPtr)
{
    bool found;
    Node* pPre;
    Node* pLoc;

    found = _search(pList, &pPre, &pLoc, keyPtr);

    if(!found)
    {
        return false;
    }
    else
    {
        _delete(pList, pPre, pLoc, dataOutPtr);
        return found;
    }
}// removeNode


/*
======== _delete =============
deletes data from a list and returns pointer to data to calling module.

 Pre:   pList is pointer to a valid list.
        pPre is pointer to predecessor node.
        pLoc is pointer to target node.
        dataOutPtr is pointer to data pointer.

Post:   data hve been deleted and returned.
        data memory has been freed.
*/

static void _delete(ListADT* pList, Node* pPre, Node* pLoc, void** dataOutPtr)
{
    *dataOutPtr = pLoc->data;
    if(pPre == NULL)
    {
        pList->head = pLoc->link;
    }
    else
    {
        pPre->link = pLoc->link;
    }

    if(pLoc->link == NULL)
    {
        pList->rear = pPre;
    }

    pList->count--;
    free(pLoc);
    return;
}//delete


/*
========= searchList ============
Interface to search function.

Pre:    pList pointer to initalized list.
        pArgu pointer to key being sought.

Post:   pDataOut contains pointer to found data -or- NULL if not found.

Return: if succesful, true ; if not found false.
*/

bool searchList(ListADT* pList, void* pArgu, void** pDataOut)
{
    bool found;
    Node* pPre;
    Node* pLoc;

    found = _search(pList, pPre, pLoc, pArgu);
    if(found)
    {
        *pDataOut = pLoc->data;
    }
    else
    {
        *pDataOut = NULL;
    }

    return found;
}//searchList


/*
========== _search ================
searches list and passes back address of node containing target and its logical predecessor.

Pre:    pList is pointer to initialized list.
        pPre is pointer variable to predecessor.
        pLoc is pointer variable to receive node.
        pArgu is pointer to key being sought.

Post:   pLoc points to first equal/greater key or null if target > key of last node.
        pPre points to largest node < key or null if target < key of first node

Return: if found, true or if not found, false.
*/

static bool _search(ListADT* pList, Node** pPre, Node** pLoc, void* pArgu)
{
    #define COMPARE  (((* pList->compare) (pArgu, (*pLoc)->data)))
    #define COMPARE_LAST  (((*pList->compare) (pArgu, pList->rear->data)))

    int result;

    *pPre = NULL;
    *pLoc = pList->head;

    if(pList->count == 0)
        return false;

    if( COMPARE_LAST > 0)
    {
        *pPre = pList->rear;
        *pLoc = NULL;
        return false;
    }

    while( (result = COMPARE) > 0)
    {
        *pPre = *pLoc;
        *pLoc = (*pLoc)->link;

    }

    if(result == 0)
    {
        return true;
    }
    else
    {
        return false;
    }

}// _search

/*
static bool _search(ListADT* pList, Node** pPre, Node** pLoc, void* pArgu)
{
    #define COMPARE\ (((* pList->compare) (pArgu, (*pLoc)->data)))
    #define COMPARE_LAST\ ((*pList->compare) (pArgu, pList->rear->data))

    int result;

    *pPre = NULL;
    *pLoc = pList->head;

    if(pList->count == 0)
        return false;
    else
    {
        while(pArgu > pLoc->data )
        {
            pPre = pLoc;
            pLoc = pLoc->link

            if(pArgu == pLoc)
            {
                return true;
            }
            else if(pLoc > pArgu)
            {
                return false;
            }
            else if(pLoc == NULL)
            {
                return false;
            }
        }
    }

}
*/


/*
============== retrieveNode ===============

this function retrieves data in the list without changing the list contents.

Pre:    pList is pointer to initialized list.
        pArgu is pointer to key to be retrieved.

Post:   data(pointer) passed back to caller.

Return: if succesful then true but if not succesful then false.

*/

bool retrieveNode(ListADT* pList, void* pArgu, void** dataOutPtr)
{
    bool found;

    Node* pPre;
    Node* pLoc;

    found = _search(pList, pPre, pLoc, pArgu);
    if(found)
    {
        *dataOutPtr = pLoc->data;
        return true;
    }
    else
    {
        *dataOutPtr = NULL;
        return false;
    }

}

/*
========== emptyList ===========
returns boolean indicating whether or not the list is empty

Pre:    pList is pointer to valid list.

Return: true if list is empty, false list has data.

*/

bool emptyList(ListADT* pList)
{
    return (pList->count == 0);
}//emptyList


/*
========== fullList ==============

returns boolean indicating no room for more data. This list is full if memory cannot be allocated for another node.

Pre:    pList is pointer to valid list.

Return: if list is full returns true but if memory can be allocated returns false.
*/

bool fullList(ListADT* pList)
{
    Node* temp;
    if( (temp = (Node*) malloc(sizeof(Node))) != NULL)
    {
        free(temp);
        return false;
    }

    return true;
}//fullList


/*
============= listCount ===========

returns number of nodes in list.

Pre:    pList is pointer to a valid list.

Return: returns number of nodes.
*/

int listCount(ListADT* pList)
{
    return pList->count;

}//pList


/*
============ traverse ==========

traverses a list. Each call either starts at the beginning of list or returns the location of the next element in the list.

Pre:    pList is pointer to a valid list.
        fromWhere is 0 to start at first element.
        dataPtrOut is address of pointer to data

Post:   if more data, address of next node

Return: return true node located; false if end of list.

*/

bool traverse(ListADT* pList, int fromWhere, void** dataOutPtr)
{
    if(pList->count == 0)
        return false;

    if(fromWhere == 0)
    {
        pList->pos = pList->head;
        *dataOutPtr = pList->pos->data;
        return true;
    }
    else
    {
        if(pList->pos == NULL)
        {
            return false;
        }
        else
        {
            pList->pos = pList->pos->link;
            *dataOutPtr = pList->pos->data;
            return true;
        }

    }
}// traverse


/* ============== destroyList ===============

deletes all data in list  and recycles memory.

Pre:    pList is pointer to valid list.

Post:   all data and head structure deleted.

Return: null head pointer.


*/

ListADT* destroyList(ListADT* pList)
{
    Node* deletePtr;
    if(pList)
    {
        while(pList->count >= 0)
        {
            free(pList->head->data);

            deletePtr = pList->head;
            pList->head = pList->head->link;
            pList->count-- ;
            free(deletePtr);
        }//while

        free(pList);
    }//if

    return NULL;

}// destroyList



















