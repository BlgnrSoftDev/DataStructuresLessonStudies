#include <stdio.h>
#include <stdlib.h>
#include "DoubleLinkedList.h"

void towerOfHanoi(int, char*, char*, char*);
int factorial(int);
int fibonacci(int);
float squareRootRecursive(int num, float ans, float tol);

int main()
{
    return 0;
}


void towerOfHanoi(int n, char* base, char* target, char* helper)
{
    if(n == 1)
    {
        printf("disk-%d moved from %s to %s\n", n, base, target);
    }
    else
    {
        towerOfHanoi(n-1, base, helper, target);
        printf("disk-%d moved from %s to %s\n", n, base, target);
        towerOfHanoi(n-1, helper, target, base);
    }

}

// function to find middle element of linkedlist using recursion.
void ortancayiBul(Node* head, Node* total, int* count)
{
    if(head->link == NULL)
    {
        *count = (*count) -  ((*count / 2) + 1) ;
    }
    else
    {
        (*count) = (*count) + 1;

        ortancayiBul(head->link, total, count);
    }

    if(head->link != NULL)
    {
        if( (*count) == 0)
        {
            printf("\n\nthe mid element is %d\n", *((int*)head->data));
            total = head;
        }

        (*count) = (*count) - 1;
    }

}

int factorial(int n)
{
    if(n == 1 || n == 0)
        return 1;
    else
        return n * factorial(n-1);
}

int fibonacci(int n)
{
    if(n == 1)
        return 1;
    else if(n == 0)
        return 0;
    else
        return fibonacci(n-1) + fibonacci(n-2);
}

void printUserInputReverseOrder()
{
    int temp;
    printf("Enter number : \n ==>");
    scanf("%d",&temp);

    if(temp == -1)
    {
        printf("\n\n Total: %d ", temp);
    }
    else
    {
        printUserInputReverseOrder();
        printf("%d ", temp);
    }


}

int recursiveGcd(int a, int b)
{
    if(a == 0)
        return b;
    else if(b == 0)
        return a;
    else
    {
        if(a > b)
            recursiveGcd(a - b, b);
        else
            recursiveGcd(a, b - a);
    }
}
int recursiveGcd_v2(int a, int b)
{
    if(a == 0)
        return b;
    else if(b == 0)
        return a;
    else
    {
        recursiveGcd_v2(b, a % b);
    }
}

float squareRootRecursive(int num, float ans, float tol)
{
    if(abs(ans * ans - num) <= tol)
    {
        return ans;
    }
    else
    {
        return squareRootRecursive(num, (ans*ans + num)/(2 * ans), tol);
    }
}

int recursiveCombination(int n, int k)
{
    if(k == 0 || n == k)
    {
        return 1;
    }
    else if(n > k && k > 0)
    {
        return recursiveCombination(n-1, k) + recursiveCombination(n-1, k-1);
    }
}

int ackermanFunction(int m, int n)
{
    if(m == 0)
        return n+1;
    else if(n == 0 && m > 0)
        return ackermanFunction(m-1, 1);
    else
        return ackermanFunction(m-1, ackermanFunction(m, n-1));
}

