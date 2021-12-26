#include <stdio.h>
#include <stdlib.h>
#include "QueueADT.h"
#include <stdbool.h>
#include <time.h>

/*
Queue yapisi kullanilarak yapilmis bir simulasyon programidir.
Burger king baz alarak verdigim bilgilerin istatistiklerini gorebilirsiniz.
musteri gelis sikligi ortalama : 10dk
servis hazirlanma suresi : 5-15dk
calısma suresi: 12 saat.

bu bilgileri istediginiz gibi degistirerek kendi simulasyonunuzu olusturabilirsiniz.
*/

typedef struct cust
{
    int custNumber, arriveTime, startTime, svcTime;

}CUSTOMER;

typedef struct status
{
    int totalCustomer;
    int totalSvcTime;
    int totalWaitTime;
    int maxQueueSize;

}SIMU_STATUS;

bool serviceDone(QUEUE* line, CUSTOMER** currCustomer, int clock, SIMU_STATUS* simulator);
bool newCustomer(QUEUE* line, int clock);
bool serverFree(QUEUE* line, CUSTOMER** currCustomer, int clock);

int main()
{
    srand(time(0));
    int clock = 1;
    QUEUE* line = createQueue();
    CUSTOMER* currCustomer = NULL;
    SIMU_STATUS* simulator = (SIMU_STATUS*)malloc(sizeof(SIMU_STATUS));
    simulator->maxQueueSize = simulator->totalCustomer = simulator->totalSvcTime = simulator->totalWaitTime = 0;

    while( clock < 720 || line->count != 0) // clock kapanma saatine ulastiginda daha fazla musteri almaz sadece siradakilere hizmet verir.
    {
        if( clock < 720 )
            newCustomer(line, clock);
//        to see queue status uncomment line 41.
        printQueue(line);
        serverFree(line, &currCustomer, clock);
        serviceDone(line, &currCustomer, clock, simulator);
        simulator->maxQueueSize = (line->count > simulator->maxQueueSize)? line->count: simulator->maxQueueSize;
        clock++;

    }

    printf("\n\n------- SIMULATION STATISTIC -------------\n");
    printf("Toplam gelen Musteri : %d\n", simulator->totalCustomer);
    printf("Toplam servis suresi : %d\n", simulator->totalSvcTime);
    printf("Toplam bekletme Musteri : %d\n", simulator->totalWaitTime);
    printf("En uzun Kuyruk sayisi : %d\n", simulator->maxQueueSize);
    return 0;
}

bool serviceDone(QUEUE* line, CUSTOMER** currCustomer, int clock, SIMU_STATUS* simulator)
{
    if(*currCustomer == NULL)
        return false;


    if(clock >= ((*currCustomer)->startTime + (*currCustomer)->svcTime))
    {
        void* data;
        printf("\n(zaman : %d) musteri teslim aldi. no : %d\n",clock, (*currCustomer)->custNumber);
        deQueue(line, &data);
        (simulator->totalCustomer)++;
        simulator->totalSvcTime += (*currCustomer)->svcTime;
        simulator->totalWaitTime += (*currCustomer)->startTime - (*currCustomer)->arriveTime;

        (*currCustomer) = NULL;
        return true;

    }

    return false;
}

bool serverFree(QUEUE* line, CUSTOMER** currCustomer, int clock)
{
    if(*currCustomer == NULL)
    {
        void* data;
        if(!queueFront(line, &data))
        {
            return false;
        }

        *currCustomer = (CUSTOMER*) data;
        (*currCustomer)->startTime = clock;
        printf("\n(zaman : %d) musteri siparisi hazirlaniyor. no: %d\n", clock, (*currCustomer)->custNumber);
    }
    else
        return false;
}
bool newCustomer(QUEUE* line, int clock)
{
    int r = rand() % 10 + 1;

    if( r == 10)
    {
        CUSTOMER* newCust = (CUSTOMER*)malloc(sizeof(CUSTOMER));
        newCust->custNumber = rand() % 4000 + 1000;
        newCust->arriveTime = clock;
        newCust->startTime = -1;
        newCust->svcTime = rand() % 10 + 5;
        enQueue(newCust, line);
        printf("\n(zaman : %d)yeni musteri geldi. no : %d\n", clock, newCust->custNumber);

        return true;
    }

    return false;
}


void printQueue(QUEUE* line)
{
    NODE* temp = line->front;
    printf("\n------- QUEUE UP -------------\n");
    while(temp != NULL)
    {
        printf(" %d ", ((CUSTOMER*)temp->data)->custNumber);
        temp = temp->link;
    }
    printf("\n------- QUEUE DOWN -------------\n");

}
