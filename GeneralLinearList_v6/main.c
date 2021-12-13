#include <stdio.h>
#include <stdlib.h>
#include <C:\Users\BlgnrCENG\Desktop\Dosyalarim\C_lang\DataStructuresSeries\GeneralLinearList_v6\ListHeader.h>
#include <stdbool.h>
int compare(void* param1, void* param2);

int main()
{
    int a = 9, b = 8, c = 7, d = 3, e = 1, f = 10, g = 11;
    ListADT* pList = createList(&compare);

    addNode(pList,&b);
    addNode(pList,&c);
    addNode(pList,&a);
    addNode(pList,&d);
    addNode(pList,&e);
    addNode(pList,&f);
    addNode(pList,&g);
    printAllList(pList);
    Node* total;
    int* count = (int*) malloc(sizeof(int));
    *count = 0;
    ortancayiBul(pList->head, total, count);


}



int compare(void* param1, void* param2)
{
    if( *((int*)param1) > *((int*)param2))
    {
        return 1;
    }
    else if( *((int*)param1) == *((int*)param2))
    {
        return 0;
    }
    else
    {
        return -1;
    }

}

void printAllList(ListADT* pList)
{
    Node* temp = pList->head;

    while(temp != NULL)
    {
        printf(" %d --> ", *((int*)temp->data));
        temp = temp->link;
    }

    if(temp == NULL)
    {
        printf(" -END-");
        return ;
    }
}







