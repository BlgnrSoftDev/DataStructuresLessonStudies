#ifndef TREEADT_H_INCLUDED
#define TREEADT_H_INCLUDED



#endif // TREEADT_H_INCLUDED


typedef struct node
{
    void* data;
    struct node* leftSubTree;
    struct node* rightSubTree;

}NODE;


typedef struct tree
{
    NODE* root;
    int count;
}TREE;



TREE* createTree();
NODE* createNode();
bool addAtPosition(TREE* tree, char* instr, void* data);
bool deleteAtPosition(TREE* tree, char* instr, void* data);
static bool _search(NODE** pPre, NODE** pLoc, TREE* tree, int* index, char* instr);


bool deleteAtPosition(TREE* tree, char* instr, void* data)
{
    bool found;
    NODE**  pLoc, **pPre;
    int* index;

    if( instr == NULLL || tree == NULL)
    {
        return false;
    }

    if(tree->count == 0)
    {
        return false;
    }

    index = (int*)malloc(sizeof(int));
    if( (found = _search(pPre, pLoc, tree, index, instr)))
    {
        if(instr[*index - 1] == 'r')
        {
            NODE* temp = pLoc->rightSubTree;
            pPre->rightSubTree = pLoc->leftSubTree;
            pLoc->leftSubTree->rightSubTree = temp;
        }
        else id(instr[*index - 1] == 'l')
        {
            pLoc->leftSubTree = pLoc->leftSubTree->
        }
    }
    else




}

bool addAtPosition(TREE* tree, char* instr, void* data)
{
    bool found;
    NODE** pLoc, **pPre;
    int* index;

    if( instr == NULL || tree == NULL)
        return false;

    if(tree->count == 0)
    {
        NODE* newNode = createNode();
        newNode->data = data;
        tree->root = newNode;
        (tree->count)++;

        return true;
    }


    index = (int*)malloc(sizeof(int));
    if( (found = _search(pPre, pLoc, tree, index, instr)))
    {
        NODE* newNode = (NODE*)malloc(sizeof(NODE));
        newNode->data = data;

        if(instr[*index] == 'r')
        {
            newNode->rightSubTree = (*pLoc)->rightSubTree;
            (*pLoc)->rightSubTree = newNode;
        }
        else if( instr[*index] == 'l')
        {
            newNode->leftSubTree = (*pLoc)->leftSubTree;
            (*pLoc)->leftSubTree = newNode;
        }


        tree->count++;
    }
    else
    {
        return false;
    }


    return true;
}


static bool _search(NODE** pPre, NODE** pLoc, TREE* tree, int* index, char* instr)
{
    NODE* temp = tree->root;
    *pPre = *pLoc = tree->root;

    int i = 0;
    while(i < strlen(instr)-1 && temp != NULL)
    {
        *pPre = *pLoc;
        *pLoc = temp;
        if(instr[i] == 'l')
        temp = temp->leftSubTree;
        else if(instr[i] == 'r')
        temp = temp->rightSubTree;

        ++i;
    }


    *index = i;


    return true;
}

NODE* createNode()
{
    NODE* newNode = (NODE*)malloc(sizeof(NODE));

    if(newNode == NULL)
        return NULL;

    newNode->data = NULL;
    newNode->leftSubTree = NULL;
    newNode->rightSubTree = NULL;

    return newNode;
}

TREE* createTree()
{

    TREE* newTree = (TREE*)malloc(sizeof(TREE));

    if(newTree == NULL)
        return NULL;

    newTree->count = 0;
    newTree->root = createNode();

    return newTree;
}


