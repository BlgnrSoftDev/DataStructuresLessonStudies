#ifndef DOUBLELINKEDLIST_H_INCLUDED
#define DOUBLELINKEDLIST_H_INCLUDED

#include <stdbool.h>

#endif // DOUBLELINKEDLIST_H_INCLUDED

typedef struct node
{
    struct node* before;
    void* data;
    struct node* next;

}NODE;


typedef struct listt
{
    NODE* pHead;
    int count;
    NODE* rear;
    NODE* pos;
    int (*compare) (void* param1, void* param2);
}LIST;

// prototype declarations for double linked list.

LIST* createList(int (* compare) (void*, void*));

LIST* destroyList(LIST* pList);

int addNode(LIST* pList, void* dataInPtr);

bool removeNode(LIST* pList, void* keyPtr);

bool searchList(LIST* pList, void* pArgu);

NODE* retrieveNode(LIST* pList, void* pArgu);

bool traverse(LIST* pList, int fromWhere, void** dataOutPtr);

int listCount(LIST* pList);

bool emptyList(LIST* pList);

bool fullList(LIST* pList);

static bool _insert(LIST* pList, NODE* pPre, NODE* pLoc, void* dataInPtr);

static bool _search(LIST*, NODE** pPre, NODE** pLoc, void* pArgu);

static bool _delete(LIST* pList, NODE* pPre, NODE* pLoc);

// end of prototype declarations





/* ======= createList ===========

Pre : compare is pointer to function which is used to compare two nodes.

post : new list is created.

return : if successful it returns list's address .
*/

LIST* createList(int (* compare) (void* param1, void* param2))
{
    LIST* newList = (LIST*) malloc(sizeof(LIST));

    newList->compare = compare;
    newList->count = 0;
    newList->pHead = NULL;
    newList->pos = NULL;
    newList->rear = NULL;

    return newList;
}

/* ============ destroyList ==========

Pre: pList is pointer to valid list.

Post: list is destroyed.

Return: if succesfull func returns null.

*/

LIST* destroyList(LIST* pList)
{
    NODE* temp = pList->pHead;
    NODE* temp2 = temp;

    while(temp != NULL)
    {
        temp = temp->next;
        free(temp2);
        temp2 = temp;
    }

}


/*========== addNode ===============

Pre: pList is pointer to a valid list,
     dataInPtr is data to insert a new node.

Post: this function adds node in ordered double linked list.


Return: if succesful returns 0, if overflow returns 1, if data already present returns -1;
*/


int addNode(LIST* pList, void* dataInPtr)
{
    bool found, success;
    NODE* pPre;
    NODE* pLoc;

    if( (found = _search(pList, &pPre, &pLoc, dataInPtr)) )
    {
        return -1;
    }
    else
    {
        if( (success = _insert(pList, pPre, pLoc, dataInPtr)) )
            return 0;
        else
            return 1;
    }

}

/*======== _search ============

Pre: pList is pointer to valid list.
     pPre is pointer to predecessor node.
     pLoc is pointer to successor node.
     pArgu is data to be searched.

Post: searches list for a spesicific node.

Return: if data is found, returns true but if data isn't found returns false.

*/

static bool _search(LIST* pList, NODE** pPre, NODE** pLoc, void* pArgu)
{
    #define COMPARE ((* (pList->compare)) (pArgu, (*pLoc)->data))
    #define COMPARE_LAST ((* (pList->compare)) (pArgu, pList->rear->data))

    *pLoc = pList->pHead;
    *pPre = NULL;

    if( pList->count == 0 || pList == NULL)
    {
        *pLoc = NULL;
        return false;
    }


    if( (COMPARE_LAST) > 0)
    {
        *pLoc = NULL;
        *pPre = pList->rear;
        return false;
    }


    while( (COMPARE) > 0)
    {
        (*pPre) = (*pLoc);
        (*pLoc) = (*pLoc)->next;
    }

    if( (COMPARE) == 0)
    {
        return true;
    }

    return false;

}

/* ========= _insert =============

Pre: pList is pointer to valid list,
     pPre is pointer to predecessor node,
     pLoc is pointer to successor node,
     dataInPtr is data to be inserted.

Post: inserts data to list.

Return: if data is successfully inserted returns true, else returns false.

*/


static bool _insert(LIST* pList, NODE* pPre, NODE* pLoc, void* dataInPtr)
{

    NODE* newNode;

    if( !(newNode = (NODE*) malloc(sizeof(NODE))) )
        return false;

    newNode->before = NULL;
    newNode->next = NULL;
    newNode->data = dataInPtr;

    if( pPre == NULL && pLoc != NULL)
    {
        pList->pHead = newNode;
        newNode->next = pLoc;
        pLoc->before = newNode;
    }
    else if(pPre == NULL && pLoc == NULL)
    {
        pList->pHead = newNode;
        pList->rear = newNode;
    }
    else if(pPre != NULL && pLoc == NULL)
    {
        pPre->next = newNode;
        newNode->before = pPre;
        pList->rear = newNode;
    }
    else if(pPre != NULL && pLoc != NULL)
    {
        newNode->next = pLoc;
        newNode->before = pPre;
        pLoc->before = newNode;
        pPre->next = newNode;

    }

    pList->count++;
    return true;
}

/* ========== removeNode ==========

Pre: pList is pointer to valid list,
     keyPtr is pointer to data to be deleted.

Post: removes node from list.

Return: returns true if successful, else returns false.
*/
bool removeNode(LIST* pList, void* keyPtr)
{
    bool found, success;
    NODE* pPre;
    NODE *pLoc;

    if( pList->count == 0 || pList == NULL)
    {
        return false;
    }

    if( !(found = _search(pList, &pPre, &pLoc, keyPtr)) )
    {
        return false;
    }

    if( !(success = _delete(pList, pPre, pLoc)) )
    {
        return false;
    }

    return true;

}


/* ========= _delete ==============

Pre: pList is pointer to valid list,
     pPre is pointer to predecessor node,
     pLoc is pointer to successor node.

Post: deletes successor(current) node.

Return if successful returns true, else returns false.

*/

static bool _delete(LIST* pList, NODE* pPre, NODE* pLoc)
{

    if(pPre == NULL)// baþtan sil.
    {
        pList->pHead = pLoc->next;

        if(pList->count == 1)
            pList->rear =  pPre;
        else
            pLoc->next->before = pPre;
    }
    else if( pPre != NULL)// ortadan sil.
    {
        pPre->next = pLoc->next;

        if(pList->rear == pLoc)
            pList->rear = pPre;
        else
            pLoc->next->before = pPre;
    }
    pList->count--;
    free(pLoc);
    return true;
}

/*======== searchList ================

Pre: pList is pointer to valid list

Post: it searches given key in the list.

Return: if found return true, else returns false;
*/

bool searchList(LIST* pList, void* pArgu)
{
    NODE* pPre;
    NODE* pLoc;
    bool found = _search(pList, &pPre, &pLoc, pArgu);

    return found;
}


/*============= retrieveNode ================

Pre: pList is pointer to a valid list,
     pArgu is pointer to data whose node will be retrieved.

Post: retrieves node whose data is given key.

Return: if data is found returns node else returns false.

*/
NODE* retrieveNode(LIST* pList, void* pArgu)
{
    NODE* pPre;
    NODE* pLoc;
    bool found = _search(pList, &pPre, &pLoc, pArgu);

    if( found )
        return pLoc;
    else
        return NULL;
}


/*======= traverse ==========

Pre: pList is pointer to valid list,
     fromWhere specifies where to start traverse
     if 1 , from beginning to end
     if 0 , current position to forward
     if 2, end to beginning
     if 3, current position to back.

Post: traverse all through list.

Return: returns true if successful, else returns false.
*/

bool traverse(LIST* pList, int fromWhere, void** dataOutPtr)
{
    if(pList->count == 0 || pList == NULL)
        return false;

    if(pList->pos == NULL)
    {
        pList->pos = pList->pHead;
    }

    if(fromWhere == 0)
    {
        pList->pos = pList->pos->next;
    }
    else if(fromWhere == 1)
    {
        pList->pos = pList->pHead;
    }
    else if(fromWhere == 2)
    {
        pList->pos = pList->rear;
    }
    else if(fromWhere == 3)
    {
        pList->pos = pList->pos->before;
    }

    if(pList->pos == NULL)
        return false;

    dataOutPtr = &(pList->pos->data);
    return true;
}

/*========== listCount =============

Pre: pList is pointer to valid list.

Return: it returns number of node.

*/
int listCount(LIST* pList)
{
    if( pList != NULL)
        return pList->count;

    return 0;
}




/*========== fullList ==============

Pre: pList is pointer to valid list.

Return: true if full, false if not.
*/


bool fullList(LIST* pList)
{
    NODE* newNode = (NODE*) malloc(sizeof(NODE));
    if(!newNode)
        return false;

    return true;
}


/*============ emptyList ================

Pre: pList is pointer to valid list.

Return true if empty, false if not.

*/
bool emptyList(LIST* pList)
{
    bool total = (pList->count == 0)? true: false;

    return total;
}

void printAllNodes(LIST* pList)
{
    NODE* iterate = pList->pHead;

    while(iterate != NULL)
    {
        printf(" %d ---> ", *((int*)iterate->data));
        iterate = iterate->next;
    }
    printf(" --END-- \n\n");
}


