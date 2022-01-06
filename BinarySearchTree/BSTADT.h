#ifndef BSTADT_H_INCLUDED
#define BSTADT_H_INCLUDED

#include <stdbool.h>
#endif // BSTADT_H_INCLUDED


typedef struct node
{
    struct node* leftSubTree, *rightSubTree;
    void* data;
    int level;
}NODE;


typedef struct binarySearchTree
{
    int (*compare) (void* param1, void* param2);
    int count;
    NODE* root;
}BST_TREE;


BST_TREE* create_BST(int (*compare) (void* param1, void* param2));
BST_TREE* destroy_BST(BST_TREE* tree);

bool insert_BST(BST_TREE* tree, void* dataPtr);
bool delete_BST(BST_TREE* tree, void* keyPtr);
void* retrieve_BST(BST_TREE* tree, void* deletePtr);
void traverse_BST(BST_TREE* tree, void (*process) (void* param1));

bool isEmpty_BST(BST_TREE* tree);
bool isFull_BST(BST_TREE* tree);
int size_BST(BST_TREE* tree);

static NODE* _insert(BST_TREE* tree, NODE* root, NODE* newNodePtr);
static NODE* _delete(BST_TREE* tree, NODE* root, void* dataPtr, bool* success);
static void* _retrieve(BST_TREE* tree, void* dataPtr, NODE* root);
static void _traverse(NODE* root, void (*process) (void* dataPtr));
static void _destroy(NODE* root);


NODE* createNode()
{
    NODE* newNode = (NODE*)malloc(sizeof(NODE));
    if(newNode)
    {
        newNode->data = newNode->leftSubTree = newNode->rightSubTree = NULL;
    }

    return newNode;
}


BST_TREE* create_BST(int (*compare) (void* param1, void* param2))
{
    BST_TREE* newTree = (BST_TREE*) malloc(sizeof(BST_TREE));
    if(newTree)
    {
        newTree->compare = compare;
        newTree->count = 0;
        newTree->root = NULL;
    }

    return newTree;
}


bool insert_BST(BST_TREE* tree, void* dataPtr)
{

    bool success;

    if(!tree)
    {
        return false;
    }


    NODE* newNode = createNode();
    if(!newNode)
    {
        return false;
    }
    newNode->data = dataPtr;


    if(tree->count == 0)
    {
        tree->root = newNode;
    }
    else
    {
        _insert(tree, tree->root, newNode);
    }

    tree->count++;
    return true;
}


static NODE* _insert(BST_TREE* tree, NODE* root, NODE* newNodePtr)
{
    if(!root)
    {
        return newNodePtr;
    }


    if(tree->compare(newNodePtr->data, root->data) >= 0)
    {
        root->rightSubTree = _insert(tree, root->rightSubTree, newNodePtr);
    }
    else
    {
        root->leftSubTree = _insert(tree, root->leftSubTree, newNodePtr);
    }

    return root;
}


bool delete_BST(BST_TREE* tree, void* keyPtr)
{

    bool success;

    if(!tree || !keyPtr)
        return false;

    NODE* newRoot = _delete(tree, tree->root, keyPtr, &success);

    if(success)
    {
        tree->root = newRoot;
        tree->count -= 1;
    }

    return success;
}

static NODE* _delete(BST_TREE* tree, NODE* root, void* dataPtr, bool* success)
{
    if(!root)
    {
        *success = false;
        return NULL;
    }

    if(tree->compare(dataPtr, root->data) > 0)
    {
        root->rightSubTree = _delete(tree, root->rightSubTree, dataPtr, success);
        return root;
    }
    else if(tree->compare(dataPtr, root->data) < 0)
    {
        root->leftSubTree = _delete(tree, root->leftSubTree, dataPtr, success);
        return root;
    }
    else
    {
        NODE* temp;

        if(!(root->leftSubTree))
        {
            temp = root->rightSubTree;
            free(root->data);
            free(root);
            *success = true;
            return temp;
        }
        else if( !(root->rightSubTree))
        {
            temp = root->leftSubTree;
            free(root->data);
            free(root);
            *success = true;
            return temp;
        }
        else
        {
            void* holdData;
            temp = root->rightSubTree;
            while(temp->leftSubTree != NULL)
            {
                temp = temp->leftSubTree;
            }

            holdData = root->data;
            root->data = temp->data;
            temp->data = holdData;
            root->rightSubTree = _delete(tree, root->rightSubTree, dataPtr, success);
            return root;
        }
    }

}


void* retrieve_BST(BST_TREE* tree, void* deletePtr)
{
    if(!tree)
        return NULL;

    return _retrieve(tree, deletePtr, tree->root);
}


static void* _retrieve(BST_TREE* tree, void* dataPtr, NODE* root)
{
    if(!root)
    {
        return NULL;
    }

    if(tree->compare(dataPtr, root->data) < 0)
    {
        _retrieve(tree, dataPtr, root->leftSubTree);
    }
    else if(tree->compare(dataPtr, root->data) > 0)
    {
        _retrieve(tree, dataPtr, root->rightSubTree);
    }
    else
    {
        return root;
    }
}

void traverse_BST(BST_TREE* tree, void (*process) (void* param1))
{
    _traverse(tree->root, process);
}


static void _traverse(NODE* root, void (*process) (void* dataPtr))
{
    if(!root)
    {
        return;
    }

    _traverse(root->leftSubTree, process);
    process(root->data);
    _traverse(root->rightSubTree, process);
}


bool isEmpty_BST(BST_TREE* tree)
{
    return tree->count == 0;
}

bool isFull_BST(BST_TREE* tree)
{
    NODE* nn = createNode();
    if(nn)
    {
        free(nn);
        return true;
    }
    return false;
}

int size_BST(BST_TREE* tree)
{
    return tree->count;
}



BST_TREE* destroy_BST(BST_TREE* tree)
{
    if(tree)
    {
        _destroy(tree->root);
    }

    free(tree);
    return NULL;
}


static void _destroy(NODE* root)
{
    if(!root)
        return NULL;

    _destroy(root->leftSubTree);
    free(root->data);
    _destroy(root->rightSubTree);
    free(root);
}




