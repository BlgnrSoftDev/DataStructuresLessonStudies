
#include <stdbool.h>
#define LH +1
#define RH -1
#define EH 0

typedef struct node
{
    void* data;
    struct node* leftSubTree, *rightSubTree;
    int bal;
}NODE;


typedef struct vvl_tree
{
    int count;
    int (*compare) (void*, void*);
    NODE* root;
}AVL_TREE;


NODE* createNode(void* dataPtr);
AVL_TREE* create_AVL(int (*compare)(void*, void*));
AVL_TREE* destroy_AVL(AVL_TREE* tree);

bool insert_AVL(AVL_TREE* tree, void* dataPtr);
bool delete_AVL(AVL_TREE* tree, void* keyPtr);
NODE* retrieve_AVL(AVL_TREE* tree, void* keyPtr);
void traverse_AVL(AVL_TREE* tree, void (*process)(void*));

int size_AVL(AVL_TREE* tree);
bool isEmptyAVL(AVL_TREE* tree);
bool isFullAVL(AVL_TREE* tree);

static NODE* _insert(AVL_TREE* tree, NODE* root, NODE* newNode, bool* taller);
static NODE* _delete(AVL_TREE* tree, NODE* root, void* deleteKey, bool* shorter, bool* success);
static NODE* _retrieve(AVL_TREE* tree, void* keyPtr, NODE* root);
static void _traversal(NODE* root, void(*process)(void* dataPtr));
static void _destroy(NODE* root);

static NODE* rotateLeft(NODE* root);
static NODE* rotateRight(NODE* root);
static NODE* insLeftBal(NODE* root, bool* taller);
static NODE* insRightBal(NODE* root, bool* taller);
static NODE* dltLeftBal(NODE* root, bool* shorter);
static NODE* dltRightBal(NODE* root, bool* shorter);



NODE* createNode(void* dataPtr)
{
    NODE* newNode = (NODE*)malloc(sizeof(NODE));
    if(newNode)
    {
        newNode->bal = EH;
        newNode->leftSubTree = newNode->rightSubTree = NULL;
        newNode->data = dataPtr;
    }


    return newNode;
}


AVL_TREE* create_AVL(int (*compare)(void*, void*))
{
    AVL_TREE* newTree = (AVL_TREE*)malloc(sizeof(AVL_TREE));
    if(newTree)
    {
        newTree->compare = compare;
        newTree->root = NULL;
        newTree->count = 0;
    }

    return newTree;
}


bool insert_AVL(AVL_TREE* tree, void* dataPtr)
{
    bool tallerFlag = false;
    NODE* newDataNode = createNode(dataPtr);

    if(!tree || !newDataNode)
        return false;

    tree->root = _insert(tree, tree->root, newDataNode,&tallerFlag);
    tree->count += 1;

    return true;
}


static NODE* _insert(AVL_TREE* tree, NODE* root, NODE* newNode, bool* taller)
{
    if(!root)
    {
        *taller = true;
        return newNode;
    }


    if(tree->compare(newNode->data, root->data) < 0)
    {
        root->leftSubTree = _insert(tree, root->leftSubTree, newNode, taller);
        if(*taller)
        {
            switch(root->bal)
            {
                case RH:
                    root->bal = EH;
                    *taller = false;
                    break;
                case EH:
                    root->bal = LH;
                    break;
                case LH:
                    root = insLeftBal(root, taller);
                    break;
            }
        }

    }
    else
    {
        root->rightSubTree = _insert(tree, root->rightSubTree, newNode, taller);
        if(*taller)
        {

            switch(root->bal)
            {
            case RH:
                root = insRightBal(root, taller);
                break;
            case LH:
                root->bal = EH;
                *taller = false;
                break;
            case EH:
                root->bal = RH;
                break;
            }
        }

    }

    return root;
}


static NODE* insLeftBal(NODE* root, bool* taller)
{
    NODE* leftsubTree = root->leftSubTree;
    NODE* rightOfLeftSubtree;
    if(leftsubTree->bal == LH)
    {
        root->bal= leftsubTree->bal = EH;
        root = rotateRight(root);
        *taller = false;
    }
    else if(leftsubTree->bal == EH)
    {
        printf("that's impossible situation... it must be devil's job 0_0"), exit(666);
    }
    else if(leftsubTree->bal == RH)
    {
        rightOfLeftSubtree = leftsubTree->rightSubTree;
        switch(rightOfLeftSubtree->bal)
        {
            case LH:
                     root->bal = RH;
                     leftsubTree->bal = EH;
                     break;
            case EH:
                     root->bal= EH;
                     leftsubTree->bal = EH;
                     break;
            case RH:
                     root->bal = EH;
                     leftsubTree->bal = LH;
                     break;
        }


        rightOfLeftSubtree->bal = EH;
        root->leftSubTree = rotateLeft(leftsubTree);

        root = rotateRight(root);
        *taller = false;
    }

    return root;
}


static NODE* insRightBal(NODE* root, bool* taller)
{
    NODE* rightSubTree = root->rightSubTree;
    NODE* leftOfRightSubTree;

    if(rightSubTree->bal == RH)
    {
        root->bal = rightSubTree->bal = EH;
        root = rotateLeft(root);
        *taller = false;
    }
    else if(rightSubTree->bal == EH)
    {
        printf("that's impossible situation... it must be devil's job 0_0"), exit(666);
    }
    else if(rightSubTree->bal == LH)
    {
        leftOfRightSubTree = rightSubTree->leftSubTree;
        switch(leftOfRightSubTree->bal)
        {
        case LH:
                 root->bal = EH;
                 rightSubTree->bal = RH;
                 break;

        case EH:
                 root->bal = EH;
                 rightSubTree->bal = EH;
                 break;
        case RH:
                 root->bal = LH;
                 rightSubTree->bal = EH;
                 break;
        }

        leftOfRightSubTree->bal = EH;
        root->rightSubTree = rotateRight(rightSubTree);
        root = rotateLeft(root);
        *taller = false;
    }

    return root;
}


static NODE* rotateLeft(NODE* root)
{
    NODE* temp = root->rightSubTree;
    root->rightSubTree = temp->leftSubTree;
    temp->leftSubTree = root;
    return temp;
}

static NODE* rotateRight(NODE* root)
{
    NODE* temp = root->leftSubTree;
    root->leftSubTree = temp->rightSubTree;
    temp->rightSubTree = root;
    return temp;
}

bool delete_AVL(AVL_TREE* tree, void* keyPtr)
{
    bool shorter = false;
    bool success = false;
    NODE* newRoot;

    newRoot = _delete(tree, tree->root, keyPtr, &shorter, &success);

    if(success)
    {
        tree->root= newRoot;
        (tree->count)--;
        return true;
    }
    else
    {
        return false;
    }
}

static NODE* _delete(AVL_TREE* tree, NODE* root, void* deleteKey, bool* shorter, bool* success)
{
    if(!root)
    {
        *success = false;
        *shorter = false;
        return root;
    }

    if(tree->compare(deleteKey, root->data) < 0)
    {
        root->leftSubTree = _delete(tree, root->leftSubTree, deleteKey, shorter, success);
        if(*shorter)
            root = dltRightBal(root, shorter);
    }
    else if(tree->compare(deleteKey, root->data) > 0)
    {
        root->rightSubTree = _delete(tree, root->rightSubTree, deleteKey, shorter, success);
        if(*shorter)
            root = dltLeftBal(root, shorter);
    }
    else
    {
        NODE* temp;
        if(!(root->rightSubTree))
        {
            *success = true;
            *shorter = true;
            temp =  root->leftSubTree;
            free(root);
            return temp;
        }
        else if(!(root->leftSubTree))
        {
            *shorter = true;
            *success = true;
            temp = root->rightSubTree;
            free(root);
            return temp;
        }
        else
        {
            void* dataHolder;
            temp = root->rightSubTree;
            while(temp->leftSubTree)
            {
                temp = temp->leftSubTree;
            }
            dataHolder = root->data;
            root->data = temp->data;
            temp->data = dataHolder;
            root->rightSubTree = _delete(tree, root->rightSubTree, dataHolder, shorter, success);

            if(*shorter)
                root = dltLeftBal(root, shorter);


        }
    }

    return root;
}

static NODE* dltLeftBal(NODE* root, bool* shorter)
{
    NODE* leftSubTree;
    NODE* rightOfLeftSubTree;
    switch(root->bal)
    {
    case RH:
             root->bal = EH;
             break;
    case EH:
             root->bal = LH;
             *shorter = false;
             break;
    case LH:
             leftSubTree = root->leftSubTree;
             if(leftSubTree->bal == RH)
             {
                 rightOfLeftSubTree = leftSubTree->rightSubTree;
                 switch(rightOfLeftSubTree->bal)
                 {
                 case LH:
                         root->bal = RH;
                         leftSubTree->bal = EH;
                         break;
                 case RH:
                         root->bal= EH;
                         leftSubTree->bal = LH;
                         break;
                 case EH:
                         root->bal = EH;
                         leftSubTree->bal = EH;
                         break;
                 }

                 rightOfLeftSubTree = EH;

                 root->leftSubTree = rotateLeft(leftSubTree);
                 root = rotateRight(root);
             }
             else
             {
                 switch(leftSubTree->bal)
                 {
                 case RH:
                 case EH:
                         root->bal = LH;
                         leftSubTree->bal = RH;
                         *shorter = false;
                         break;
                 case LH:
                         root->bal = EH;
                         leftSubTree->bal = EH;
                         break;
                 }

                 root = rotateRight(root);
             }
    }
    return root;
}


static NODE* dltRightBal(NODE* root, bool* shorter)
{
    NODE* rightTree;
    NODE* leftOfRightTree;


    switch(root->bal)
    {
    case LH:
            root->bal = EH;
            break;
    case EH:
            root->bal = RH;
            *shorter = false;
            break;
    case RH:
            rightTree = root->rightSubTree;

            if(rightTree->bal == LH)
            {
                leftOfRightTree = rightTree->leftSubTree;

                switch(leftOfRightTree->bal)
                {
                case LH:
                        root->bal  = EH;
                        rightTree->bal = RH;
                        break;
                case RH:
                        root->bal = LH;
                        rightTree->bal = EH;
                        break;
                case EH:
                        root->bal = EH;
                        rightTree->bal = EH;
                        break;
                }


                leftOfRightTree = EH;
                root->rightSubTree = rotateRight(rightTree);
                root = rotateLeft(root);
            }
            else
            {

                switch(rightTree->bal)
                {
                case LH:
                case RH:
                        root->bal= EH;
                        rightTree->bal = EH;
                        break;
                case EH:
                        root->bal = RH;
                        rightTree->bal = LH;
                        *shorter = false;
                        break;
                }

                root = rotateLeft(root);
            }

    }
    return root;
}

void traverse_AVL(AVL_TREE* tree, void (*process)(void*))
{
    _traversal(tree->root, process);
    return;
}

static void _traversal(NODE* root, void(*process)(void* dataPtr))
{
    if(root)
    {
        _traversal(root->leftSubTree, process);
        process(root->data);
        _traversal(root->rightSubTree, process);
    }
    return;
}



NODE* retrieve_AVL(AVL_TREE* tree, void* keyPtr)
{
    if(!tree)
        return NULL;


    return _retrieve(tree, keyPtr, tree->root);
}


static NODE* _retrieve(AVL_TREE* tree, void* keyPtr, NODE* root)
{
    if(!root)
    {
        return NULL;
    }


    if(tree->compare(keyPtr, root->data) > 0)
    {
        root->rightSubTree = _retrieve(tree, keyPtr, root->rightSubTree);
    }
    else if( tree->compare(keyPtr, root->data))
    {
        root->leftSubTree = _retrieve(tree, keyPtr, root->leftSubTree);
    }
    else
    {
        return root;
    }

}


int size_AVL(AVL_TREE* tree)
{
    if(!tree)
        return 0;

    return tree->count;
}
bool isEmptyAVL(AVL_TREE* tree)
{
    if(!tree)
        return true;

    return tree->count == 0;
}

bool isFullAVL(AVL_TREE* tree)
{
    void* m = NULL;
    NODE* temp = createNode(m);

    if(!temp)
        return true;

    free(temp);
    return false;
}

AVL_TREE* destroy_AVL(AVL_TREE* tree)
{
    if(!tree)
        return NULL;

    _destroy(tree->root);

    free(tree);

    return NULL;
}

static void _destroy(NODE* root)
{
    if(root)
    {

    _destroy(root->leftSubTree);
    free(root->data);
    _destroy(root->rightSubTree);
    free(root);

    }
}



