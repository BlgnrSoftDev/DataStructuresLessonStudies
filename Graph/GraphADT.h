#include "StackADT.h"
#include "QueueADT.h"
#include <stdbool.h>


typedef struct GraphMetaData
{
    int count;
    struct vertex* first;
    int (*compare) (void*, void*);
}GRAPH;

typedef struct vertex
{
    int indegree, outdegree;
    bool isProcessed;
    bool inTree;
    struct vertex* nextVertex;
    void* dataPtr;
    struct arc* pArc;
}VERTEX;

typedef struct arc
{
    struct vertex* destination;
    struct arc* nextArc;
    int weight;
}ARC;


GRAPH* createGraph(int (*compare) (void* ,void*));
void graphInsertVertex(GRAPH* graph, void* dataInPtr);
int graphDeleteVertex(GRAPH* graph, void* deleteKey);
int graphInsertArc(GRAPH* graph, void* pFromKey, void* pToKey, int weight);
int graphDeleteArc(GRAPH* graph, void* pFromKey, void* pToKey);
int graphRetrieveVertex(GRAPH* graph, void* pKey, void** dataOutPtr);

int graphFirstArc(GRAPH* graph, void*key, void** pDataOut);
int graphDFS(GRAPH* graph, void (*process) (void* dataPtr), void* keyPtr);
int graphBFS(GRAPH* graph, void (*process) (void* dataPtr), void* keyPtr);
void primSpanningTree(GRAPH* graph, void* keyPtr);


bool graphEmpty(GRAPH* graph);
bool graphFull(GRAPH* graph);
int graphCount(GRAPH* graph);



GRAPH* createGraph(int (*compare) (void* ,void*))
{
    GRAPH* newGraph = (GRAPH*)malloc(sizeof(GRAPH));
    if(newGraph)
    {
        newGraph->compare = compare;
        newGraph->count = 0;
        newGraph->first = NULL;
    }

    return newGraph;
}

VERTEX* createNewVertex(void* data)
{
    VERTEX* newVertex = (VERTEX*)malloc(sizeof(VERTEX));
    if( newVertex )
    {
        newVertex->indegree = newVertex->outdegree = 0;
        newVertex->dataPtr = data;
        newVertex->isProcessed = false;
        newVertex->nextVertex = NULL;
        newVertex->pArc = NULL;
        newVertex->inTree = false;
    }

    return newVertex;
}

ARC* createNewArc(VERTEX* dest, int weight)
{
    ARC* newArc = (ARC*)malloc(sizeof(ARC));
    if( newArc )
    {
        newArc->destination = dest;
        newArc->nextArc = NULL;
        newArc->weight = weight;
    }

    return newArc;
}

void graphInsertVertex(GRAPH* graph, void* dataInPtr)
{
    if( graph == NULL)
        return;

    VERTEX* newVertex = createNewVertex(dataInPtr);

    if(!newVertex)
        return;

    VERTEX* pLoc = graph->first, *pPre;

    if( !pLoc )
    {
        graph->first = newVertex;
    }
    else
    {
        while(pLoc && (graph->compare(dataInPtr, pLoc->dataPtr) > 0))
        {
            pPre = pLoc;
            pLoc = pLoc->nextVertex;
        }

        if(!pPre)
        {
            graph->first = newVertex;
        }
        else
        {
            pPre->nextVertex = newVertex;
        }
            newVertex->nextVertex = pLoc;
    }

    (graph->count)++;

    return;
}

int graphDeleteVertex(GRAPH* graph, void* deleteKey)
{
    // return 0 for success
    // return -1 for graph empty
    // return -2 for vertex couldnt find
    // return -3 for vertex isn't disjoint
    if( !graph )
    {
        return -1;
    }

    VERTEX* finder = (graph->first != NULL)? graph->first: NULL;
    VERTEX* pPre;

    while( finder && (graph->compare(deleteKey, finder->dataPtr)) > 0 )
    {
        pPre = finder;
        finder = finder->nextVertex;
    }

    if(!finder || graph->compare(deleteKey, finder->dataPtr) != 0)
    {
        return -2;
    }


    if(finder->indegree != 0 || finder->outdegree != 0)
        return -3;


    if(!pPre)
        graph->first = finder->nextVertex;
    else
    {
        pPre = finder->nextVertex;
    }

    graph->count -= 1;
    free(finder);
    return 0;

}

int graphInsertArc(GRAPH* graph, void* pFromKey, void* pToKey, int weight)
{
    VERTEX* fromVertex;
    VERTEX* toVertex;

    if(!graph)
        return -1;

    fromVertex = (graph->first != NULL)? graph->first: NULL;

    // graph is empty so there are no vertex which has same key given.
    if(!fromVertex)
        return -1;

    while(fromVertex && graph->compare(pFromKey, fromVertex->dataPtr) > 0)
    {
        fromVertex = fromVertex->nextVertex;
    }


    // vertex couldnt be found
    if(!fromVertex || graph->compare(fromVertex->dataPtr, pFromKey) != 0)
    {
        return -2;
    }

    toVertex = graph->first;

    while(toVertex && graph->compare(pToKey, toVertex->dataPtr) > 0)
    {
        toVertex = toVertex->nextVertex;
    }

    if(!toVertex || graph->compare(toVertex->dataPtr, pToKey) != 0)
    {
        return -3;
    }

    // from_vertex and to_vertex found.
    // then update their degrees
    (toVertex->indegree)++;
    (fromVertex->outdegree)++;


    ARC* newArc = createNewArc(toVertex, weight);
    ARC* pLocArc, *pPreArc;

    pLocArc = fromVertex->pArc;

    if(!pLocArc)
    {
        fromVertex->pArc = newArc;
        return 1;
    }

    while(pLocArc && graph->compare(pToKey, pLocArc->destination->dataPtr) > 0)
    {
        pPreArc = pLocArc;
        pLocArc = pLocArc->nextArc;
    }


    if(pLocArc && graph->compare(pLocArc->destination->dataPtr, pToKey) == 0)
    {
        return -4;
    }

    if(!pPreArc)
    {
        fromVertex->pArc = newArc;
    }
    else
    {
        pPreArc->nextArc = newArc;
    }
    newArc->nextArc = pLocArc;

    return 0;
}

int graphDeleteArc(GRAPH* graph, void* pFromKey, void* pToKey)
{
    VERTEX* fromVertex, *toVertex;
    ARC* pPreArc, *pLocArc;

    if(!graph->first)
        return -2;

    fromVertex = graph->first;

    while(fromVertex && graph->compare(pFromKey, fromVertex->dataPtr) > 0)
    {
        fromVertex = fromVertex->nextVertex;
    }

    if(!fromVertex || graph->compare(pFromKey, fromVertex->dataPtr) != 0)
    {
        return -2;
    }

    pLocArc = fromVertex->pArc;

    if( !pLocArc )
            return -3;

    while(pLocArc && ( graph->compare(pToKey, pLocArc->destination->dataPtr) > 0))
    {
        pPreArc = pLocArc;
        pLocArc = pLocArc->nextArc;
    }

    if( !pLocArc || graph->compare(pLocArc->destination->dataPtr, pToKey) != 0)
    {
        return -3;
    }


    toVertex = pLocArc->destination;
    --(toVertex->indegree);
    --(fromVertex->outdegree);

    if(!pPreArc)
    {
        fromVertex->pArc = pLocArc->nextArc;
    }
    else
    {
        pPreArc->nextArc = pLocArc->nextArc;
    }

    return 0;
}


int graphDFS(GRAPH* graph, void (*process) (void* dataPtr), void* keyPtr)
{
    VERTEX* findStartingPoint;
    VERTEX* temp;
    VERTEX* currVertex;

    if( !graph )
        return -1;

    STACK* newStack = createStack();

    if(!newStack)
        return -1;

    findStartingPoint = graph->first;

    while(findStartingPoint && graph->compare(keyPtr, findStartingPoint->dataPtr) > 0)
    {
        findStartingPoint = findStartingPoint->nextVertex;
    }

    if(!findStartingPoint || graph->compare(keyPtr, findStartingPoint->dataPtr) != 0)
        return -2;


    temp = graph->first;
    while( temp )
    {
        temp->isProcessed = false;
        temp = temp->nextVertex;
    }

    findStartingPoint->isProcessed = true;
    pushStack(newStack, findStartingPoint);

    while( !isEmptyStack(newStack) )
    {
        currVertex = popStack(newStack);
        process(currVertex->dataPtr);

        ARC* temp_ = currVertex->pArc;
        while(temp_)
        {
            if( !temp_->destination->isProcessed )
            {
                pushStack(newStack, temp_->destination);
                temp_->destination->isProcessed = true;
            }

            temp_ = temp_->nextArc;
        }
    }

    destroyStack(newStack);
}

int graphBFS(GRAPH* graph, void (*process) (void* dataPtr), void* keyPtr)
{
    VERTEX* findStartingPoint;
    VERTEX* temp;
    VERTEX* currVertex;

    if( !graph )
        return -1;

    QUEUE* newQueue = createQueue();

    if(!newQueue)
        return -1;

    findStartingPoint = graph->first;

    while(findStartingPoint && graph->compare(keyPtr, findStartingPoint->dataPtr) > 0)
    {
        findStartingPoint = findStartingPoint->nextVertex;
    }

    if(!findStartingPoint || graph->compare(keyPtr, findStartingPoint->dataPtr) != 0)
        return -2;


    temp = graph->first;
    while( temp )
    {
        temp->isProcessed = false;
        temp = temp->nextVertex;
    }

    findStartingPoint->isProcessed = true;
    enQueue(findStartingPoint, newQueue);

    while( newQueue->count != 0 )
    {
        deQueue(newQueue, &currVertex);
        process(currVertex->dataPtr);

        ARC* temp_ = currVertex->pArc;
        while(temp_)
        {
            if( !temp_->destination->isProcessed )
            {
                enQueue(temp_->destination, newQueue);
                temp_->destination->isProcessed = true;
            }

            temp_ = temp_->nextArc;
        }
    }

    destroyQueue(newQueue);


}

int graphFirstArc(GRAPH* graph, void*key, void** pDataOut)
{
    if( !graph )
    {
        return -1;
    }


    VERTEX* walker  = graph->first;

    if(!walker)
    {
        *pDataOut = NULL;
        return 0;
    }

    while( walker )
    {
        if( graph->compare(walker->dataPtr, key) == 0)
        {
            *pDataOut  = (void*)walker->pArc;
            break;
        }

        walker = walker->nextVertex;
    }



    return 1;
}

bool graphEmpty(GRAPH* graph)
{
    return (graph == NULL) || (graph->count == 0);
}
bool graphFull(GRAPH* graph)
{
    VERTEX* vertex = createNewVertex(NULL);
    if(vertex)
        return true;

    return false;
}
int graphCount(GRAPH* graph)
{
    return graph->count;
}

void primSpanningTree(GRAPH* graph, void* keyPtr)
{
    if(!graph || !graph->first)
        return -1;


    VERTEX* startVertex = graph->first;
    while(startVertex && graph->compare(startVertex->dataPtr, keyPtr) < 0)
    {
        startVertex = startVertex->nextVertex;
    }

    if(!startVertex || graph->compare(startVertex->dataPtr, keyPtr) != 0)
    {
        return -2;
    }


    VERTEX* walker = graph->first;
    while( walker)
    {
        walker->inTree = false;
        walker = walker->nextVertex;
    }


    VERTEX** path = (VERTEX**)malloc(sizeof(VERTEX)* graph->count);
    path[0] = startVertex;
    startVertex->inTree = true;
    int len = 1, x = 0;
    ARC* MAX = createNewArc(NULL, 99999);
    ARC* minArcRef = MAX;
    VERTEX* minArcFrom = NULL;
    int i;
    for(i = 0; i <  len; ++i)
    {
        if(path[i]->inTree)
        {
            ARC* temp = path[i]->pArc;
            while( temp )
            {

                if(!temp->destination->inTree)
                {

                    if(minArcRef->weight > temp->weight)
                    {
                        minArcRef = temp;
                        minArcFrom = path[i];

                    }
                }
                temp = temp->nextArc;
            }

            if(x == i)
            {
                if(minArcRef == MAX)
                {
                    break;
                }
                x++;
                len++;
                i = -1;
                minArcRef->destination->inTree = true;
                path[x] = minArcRef->destination;
                printf("%d ---> %d\n", *((int*)minArcFrom->dataPtr), *((int*)minArcRef->destination->dataPtr)) ;
                minArcRef = MAX;
                if(x == graph->count)
                    break;
            }

        }
    }





}
