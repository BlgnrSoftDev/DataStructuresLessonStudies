#ifndef B_TREEADT_H_INCLUDED
#define B_TREEADT_H_INCLUDED
#endif // B_TREEADT_H_INCLUDED

#include <stdbool.h>
#include <stdlib.h>

#define ORDER 4
const int MIN_ENTRIES = 1;


struct node;

typedef struct entry
{
    void* dataPtr;
    struct node* rightPtr;

}ENTRY;

typedef struct node
{
    struct node* firstPtr;
    int numEntries;
    ENTRY entries[ORDER - 1];
}NODE;


typedef struct BTree
{
    int count;
    NODE* root;
    int (*compare) (void*, void*);

}BTREE;


BTREE* BTree_Create(int (*compare) (void* arg1, void* arg2));
void BTree_Traverse(BTREE* tree, void (*process) (void*, void*));
void BTree_Insert(BTREE* tree, void* dataInPtr);
bool BTree_Delete(BTREE* tree, void* dltKey);
void* BTree_Search(BTREE* tree, void* dataPtr);



static void* _search(BTREE* tree, void* targetPtr, NODE* root);
static int _searchNode(BTREE* tree, NODE* nodePtr, void* target);
static bool _delete(BTREE* tree, NODE* root, void* dltKeyPtr, bool* success);
static bool _insert(BTREE* tree, NODE* root, void* dataInPtr, ENTRY* upEntry);
static void _traverse(NODE* root, void (*process) (void* dataPtr));
static void _splitNode(NODE* root, int entryNdx, int compResult, ENTRY* upEntry);
static void _insertEntry(NODE* root, int entryNdx, ENTRY upEntry);
static bool _deleteEntry(NODE* node, int entryNdx);
static bool _deleteMid(NODE* root, int entryNdx, NODE* leftPtr);
static bool _reFlow(NODE* root, int entryNdx);
static void _borrowLeft(NODE* root, int entryNdx, NODE* leftTree, NODE* rightTree);
static void _borrowRight(NODE* root, int entryNdx, NODE* leftTree, NODE* rightTree);
static void _combine(NODE* root, int entryNdx, NODE* leftTree, NODE* rightTree);



BTREE* BTree_Create(int (*compare) (void* arg1, void* arg2))
{
    BTREE* newTree = (BTREE*)malloc(sizeof(BTREE));
    newTree->count = 0;
    newTree->root = NULL;
    newTree->compare = compare;

    return newTree;
}


void* BTree_Search(BTREE* tree, void* dataPtr)
{
    if(!tree)
        return NULL;

    if(tree->root)
    {
        return _search(tree, dataPtr, tree->root);
    }

    return NULL;
}


static void* _search(BTREE* tree, void* targetPtr, NODE* root)
{
    int walker = root->numEntries - 1;


    if(tree->compare(targetPtr, root->entries[0].dataPtr) < 0)
    {
        return _search(tree, targetPtr, root->firstPtr);
    }

    while(walker > 0 && tree->compare(targetPtr, root->entries[walker].dataPtr) <= 0)
    {
        if(tree->compare(targetPtr, root->entries[walker].dataPtr) == 0)
        {
            return root->entries[walker].dataPtr;
        }
        walker--;
    }

    return _search(tree, targetPtr, root->entries[walker].rightPtr);


}


void BTree_Traverse(BTREE* tree, void (*process) (void*, void*))
{
    if(!tree)
        return;

    if(tree->root)
        _traverse(tree->root, process);

    return;
}


static void _traverse(NODE* root, void (*process) (void* dataPtr))
{
    // DFS algoritmasýný kullanýyor. Aðaçlardaki tabiriyle inorder traversal.
    int walker = 0;
    NODE* pathToVisit = root->firstPtr;

    while(walker <= root->numEntries) // m tane entry varsa, m+1 tane çocuk var bu yüzden <= en sondaki pointer'ý da deðerlendirmesi için.
    {
        if(pathToVisit)
            _traverse(pathToVisit, process);

        if(walker < root->numEntries)
        {
            process(root->entries[walker].dataPtr);
            pathToVisit = root->entries[walker].rightPtr;
        }

        walker++;
    }

    return;
}


void BTree_Insert(BTREE* tree, void* dataInPtr)
{
    NODE* newPtr;
    bool taller;
    ENTRY upEntry;

    if(!tree)
        return;

    if(!(tree->root))
    {
        if( (newPtr = (NODE*)malloc(sizeof(NODE))) )
        {
            newPtr->firstPtr = NULL;
            newPtr->numEntries = 1;
            newPtr->entries[0].dataPtr = dataInPtr;
            newPtr->entries[0].rightPtr = NULL;
            tree->root = newPtr;
            tree->count++;

            for(int i = 1; i < ORDER-1; ++i)
            {
                newPtr->entries[i].dataPtr = NULL;
                newPtr->entries[i].rightPtr = NULL;
            }

            return;
        }
        else
        {
            printf("Error in BTree_Insert, memory couldn't be allocated... \\n"), exit(100);
        }
    }


    taller = _insert(tree, tree->root, dataInPtr, &upEntry);
    if(taller)
    {

        if( (newPtr = (NODE*)malloc(sizeof(NODE))) )
        {
            newPtr->firstPtr = tree->root;
            newPtr->numEntries = 1;
            newPtr->entries[0] = upEntry;
            tree->root = newPtr;
        }
        else
        {
            printf("Error in Btree_Insert, memory cannot be allocated for upEntry\a\n"), exit(101);
        }
    }

    tree->count++;
    return;
}


static bool _insert(BTREE* tree, NODE* root, void* dataInPtr, ENTRY* upEntry)
{

    int compResult;
    int entryNdx;
    bool taller;

    NODE* subtreePtr;

    if(root == NULL)
    {
        upEntry->dataPtr = dataInPtr;
        upEntry->rightPtr = NULL;
        return true;
    }

    entryNdx = _searchNode(tree, root, dataInPtr);
    compResult = tree->compare(dataInPtr, root->entries[entryNdx].dataPtr);

    if(entryNdx <= 0 && compResult < 0 )
    {
        subtreePtr = root->firstPtr;
    }
    else
        subtreePtr = root->entries[entryNdx].rightPtr;

    taller = _insert(tree, subtreePtr, dataInPtr, upEntry);

    // bu kýsýma kadar eklenecek node bulmak için.
    if(taller)
    {

//        printf("here");
        if(root->numEntries >= ORDER - 1)
        {
            _splitNode(root, entryNdx, compResult, upEntry);
            taller = true;
        }
        else
        {
            if(compResult >= 0)
            {
                _insertEntry(root, entryNdx + 1, *upEntry);
            }
            else
            {
                _insertEntry(root, entryNdx, *upEntry);
            }

            (root->numEntries)++;
            taller = false;
        }

    }

    return taller;
}


static void _splitNode(NODE* node, int entryNdx, int compResult, ENTRY* upEntry)
{
    int fromNdx, toNdx;
    NODE* rightPtr;

    rightPtr = (NODE*)malloc(sizeof(NODE));
    if(!rightPtr)
        printf("Overflow error 101 in _splitNode\a\n"), exit(100);

    if(entryNdx < MIN_ENTRIES)
    {
        fromNdx = MIN_ENTRIES;
    }
    else
    {
        fromNdx = MIN_ENTRIES + 1;
    }

    toNdx = 0;

    rightPtr->numEntries = 0;
    while(fromNdx < node->numEntries)
    {
        rightPtr->entries[toNdx++] = node->entries[fromNdx++];
        (rightPtr->numEntries)++;
    }

    node->numEntries = node->numEntries - rightPtr->numEntries;

    if(entryNdx < MIN_ENTRIES)
    {
        if(compResult < 0)
            _insertEntry(node, entryNdx, *upEntry);
        else
            _insertEntry(node, entryNdx + 1, *upEntry);
    }
    else
    {
        _insertEntry(rightPtr, entryNdx - MIN_ENTRIES, *upEntry);
        (rightPtr->numEntries)++;
        (node->numEntries)--;
    }

    upEntry->dataPtr = node->entries[MIN_ENTRIES].dataPtr;
    upEntry->rightPtr = rightPtr;
    rightPtr->firstPtr = node->entries[MIN_ENTRIES].rightPtr;


    return;
}

static void _insertEntry(NODE* root, int entryNdx, ENTRY upEntry)
{
    for( int i = root->numEntries; i > entryNdx; --i)
    {
        root->entries[i] = root->entries[i - 1];
    }

    root->entries[entryNdx] = upEntry;
}


static int _searchNode(BTREE* tree, NODE* nodePtr, void* target)
{
    int walker = nodePtr->numEntries - 1;
    while(walker > 0)
    {
       if(tree->compare(target, nodePtr->entries[walker].dataPtr) > 0)
       {
           return walker;
       }

       walker--;
    }


    return walker;

}

static int _searchNodeForDelete(BTREE* tree, NODE* nodePtr, void* target)
{
    int walker = 0;
    while(walker < nodePtr->numEntries)
    {
        if(tree->compare(target, nodePtr->entries[walker].dataPtr) == 0)
            return walker;

        if(tree->compare(target, nodePtr->entries[walker].dataPtr) < 0)
        {
            if(walker == 0)
                return 0;
            else if(walker > 0)
            {
                return walker - 1;
            }

        }

        walker++;
    }


    return walker - 1;
}

bool BTree_Delete(BTREE* tree, void* dltKey)
{
    bool success;
    NODE* dltPtr;

    if(!tree)
        return false;

    if(!tree->root)
        return false;

    _delete(tree, tree->root, dltKey, &success);

    if(success)
    {
        (tree->count)--;
        if(tree->root->numEntries == 0)
        {
                dltPtr = tree->root;
                tree->root = tree->root->firstPtr;
                free(dltPtr);
        }
    }
    return success;
}


static bool _delete(BTREE* tree, NODE* root, void* dltKeyPtr, bool* success)
{
    NODE* leftPtr;
    NODE* subTreePtr;
    int entryNdx;
    bool underflow;


    if(!root)
    {
        *success = false;
        return false;
    }


    entryNdx = _searchNodeForDelete(tree, root, dltKeyPtr);
    if(tree->compare(dltKeyPtr, root->entries[entryNdx].dataPtr) == 0)
    {

        *success = true;
        if(root->entries[entryNdx].rightPtr == NULL)
        {
            underflow = _deleteEntry(root, entryNdx);
        }
        else
        {
            if(entryNdx > 0)
                leftPtr = root->entries[entryNdx - 1].rightPtr;
            else
                leftPtr = root->firstPtr;

            underflow = _deleteMid(root, entryNdx, leftPtr);
            if(underflow)
            {
                underflow = _reFlow(root, entryNdx);
            }
        }
    }
    else
    {

        if(tree->compare(dltKeyPtr, root->entries[0].dataPtr) < 0)
        {
//            printf("buradaa");
            subTreePtr = root->firstPtr;
        }
        else
        {
            subTreePtr = root->entries[entryNdx].rightPtr;
        }

        underflow = _delete(tree, subTreePtr, dltKeyPtr, success);
        if(underflow)
            _reFlow(root, entryNdx);
    }

    return underflow;
}


static bool _deleteEntry(NODE* node, int entryNdx)
{
   int walker = node->numEntries;
   int i = entryNdx;
   while(i < walker)
   {
       node->entries[i] = node->entries[i + 1];
       ++i;
   }
   (node->numEntries)--;

   return (node->numEntries < MIN_ENTRIES);
}


static bool _deleteMid(NODE* root, int entryNdx, NODE* subTreePtr)
{
    int dltNdx;
    int rightNdx;
    bool underflow;

    if(subTreePtr->entries[subTreePtr->numEntries - 1].rightPtr == NULL)
    {
        dltNdx = subTreePtr->numEntries - 1;
        root->entries[entryNdx].dataPtr = subTreePtr->entries[dltNdx].dataPtr;
        (subTreePtr->numEntries)--;
        underflow = (subTreePtr->numEntries < MIN_ENTRIES);
    }
    else
    {
        rightNdx = subTreePtr->numEntries - 1;
        underflow = _deleteMid(root, entryNdx, subTreePtr->entries[rightNdx].rightPtr);
        if(underflow)
            _reFlow(subTreePtr, rightNdx);
    }

    return underflow;
}

static bool _reFlow(NODE* root, int entryNdx)
{
    NODE* rightTree;
    NODE* leftTree;
    bool underflow;

    if(entryNdx == 0)
        leftTree = root->firstPtr;
    else
        leftTree = root->entries[entryNdx - 1].rightPtr;

    rightTree = root->entries[entryNdx].rightPtr;

    if(rightTree->numEntries > MIN_ENTRIES)
    {
        _borrowRight(root, entryNdx, leftTree, rightTree);
        underflow = false;
    }
    else
    {
        if(leftTree->numEntries > MIN_ENTRIES)
        {
            _borrowLeft(root, entryNdx, leftTree, rightTree);
            underflow = false;
        }
        else
        {
            _combine(root, entryNdx, leftTree, rightTree);
            underflow = (root->numEntries < MIN_ENTRIES);
        }
    }
    return underflow;
}


static void _borrowRight(NODE* root, int entryNdx, NODE* leftTree, NODE* rightTree)
{
    int toNdx;
    int shifter;


    toNdx = leftTree->numEntries;
    leftTree->entries[toNdx].dataPtr = root->entries[entryNdx].dataPtr;
    leftTree->entries[toNdx].rightPtr = rightTree->firstPtr;
    (leftTree->numEntries)++;

    root->entries[entryNdx].dataPtr = rightTree->entries[0].dataPtr;
    rightTree->firstPtr = rightTree->entries[0].rightPtr;

    shifter = 0;
    while(shifter < rightTree->numEntries-1)
    {
        rightTree->entries[shifter] = rightTree->entries[shifter + 1];
        shifter++;
    }

    rightTree->numEntries -= 1;
    return;
}

static void _borrowLeft(NODE* root, int entryNdx, NODE* leftTree, NODE* rightTree)
{
    int shifter;


    //first prepare a location to insert root data to right-beginning.
    shifter = rightTree->numEntries - 1;
    while(shifter >= 0)
    {
        rightTree->entries[shifter + 1] = rightTree->entries[shifter];

        --shifter;
    }

    //and we now ready to insert root element to rightTree's first location
    rightTree->entries[0].dataPtr = root->entries[entryNdx].dataPtr;

    // let's update right first location's children
    rightTree->entries[0].rightPtr = rightTree->firstPtr;
    rightTree->firstPtr = leftTree->entries[leftTree->numEntries - 1].rightPtr;

    //move left's last element to root.
    root->entries[entryNdx].dataPtr = leftTree->entries[leftTree->numEntries - 1].dataPtr;

    //update rightTree's and leftTree's total element number.
    (leftTree->numEntries)--;
    (rightTree->numEntries)++;

    return;
}


static void _combine(NODE* root, int entryNdx, NODE* leftTree, NODE* rightTree)
{
    int toNdx;
    int fromNdx;
    int shifter;

    toNdx = leftTree->numEntries;
    leftTree->entries[toNdx].dataPtr = root->entries[entryNdx].dataPtr;
    leftTree->entries[toNdx].rightPtr = rightTree->firstPtr;
    (leftTree->numEntries)++;
    (root->numEntries)--;
    toNdx++;
    fromNdx = 0;
    while(fromNdx < rightTree->numEntries)
    {
        leftTree->entries[toNdx++] = rightTree->entries[fromNdx++];
        (leftTree->numEntries)++;
    }
    free(rightTree);


    shifter = entryNdx;
    while(shifter < root->numEntries)
    {
        root->entries[shifter] = root->entries[shifter + 1];
        shifter++;
    }

    return;
}
















