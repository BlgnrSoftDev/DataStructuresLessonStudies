#ifndef UNORDEREDLINKEDLIST_H_INCLUDED
#define UNORDEREDLINKEDLIST_H_INCLUDED



#endif // UNORDEREDLINKEDLIST_H_INCLUDED

#include <stdbool.h>

typedef struct node
{
    void* data;
    struct node* next;
}NODE;

typedef struct metadata
{
    NODE* head;
    int count;
}LIST;


NODE* createNode(void* data)
{
    NODE* newNode = (NODE*)malloc(sizeof(NODE));

    if(newNode)
    {
        newNode->data = data;
        newNode->next = NULL;
    }

    return newNode;
}

LIST* createList()
{
    LIST* newList = (LIST*)malloc(sizeof(LIST));
    if(newList)
    {
        newList->count = 0;
        newList->head = NULL;
    }

    return newList;
}


void insertNode(void* data, LIST* list)
{
    NODE* newNode = createNode(data);

    if(list->head == NULL)
    {
        list->head = newNode;
        list->count = 1;
    }
    else
    {
        NODE* temp = list->head;
        while(temp->next)
        {
            temp = temp->next;
        }

        temp->next = newNode;
        list->count++;
    }
}


void removeNode(void* data, LIST* list, int (*compare) (void* arg1, void* arg2))
{
    NODE* temp = list->head;
    NODE* pre;

    if(list->head == NULL)
        return;

    while(temp)
    {
        if((compare(data, temp->data)))
        {
            if(list->head == temp)
            {
                list->head = list->head->next;
                temp->next = NULL;
            }
            else if(temp->next == NULL)
            {
                pre->next = NULL;
            }
            else
            {
                pre->next = pre->next->next;
                temp->next = NULL;
            }

            list->count--;
            break;
        }


        pre = temp;
        temp = temp->next;
    }


}
