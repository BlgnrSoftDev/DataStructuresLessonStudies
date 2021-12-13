#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node
{
    void* data;
    struct node* link;
}Node;

int isPalindrome(char* str, int firstIndex, int lastIndex);
void printAllFactorsHelper(int number, int firstPrimeNumber);
int isPrimeNumber(int number, int firstPrimeNumber);
void printAllFactors(int number, int firstPrimeNumber);
int lengthOfLinkedList(struct node* traverser, int count);
void printAllFactors_v2(int number, int count);

int main()
{
    char* metin = "makam";
    printAllFactors(12345, 2);
    return 0;
}

int lengthOfLinkedList(struct node* traverser, int count)
{
    if(traverser->link == NULL)
    {
        return count;
    }
    return lengthOfLinkedList(traverser->link, count + 1);
}

int isPalindrome(char* str, int firstIndex, int lastIndex)
{
    if(firstIndex >= lastIndex)
    {
        return 1;
    }
    else
    {
        if(str[firstIndex] == str[lastIndex])
            isPalindrome(str, firstIndex + 1, lastIndex - 1);
        else
            return -1;
    }
}

int isPrimeNumber(int number, int firstPrimeNumber)
{
    if(firstPrimeNumber >= number)
    {
        return 1;
    }
    if(number % firstPrimeNumber == 0)
    {
        return 0;
    }
    else
    {
        return isPrimeNumber(number, firstPrimeNumber + 1);
    }
}

void printAllFactors(int number, int firstPrimeNumber)
{
    if(number < firstPrimeNumber)
    {
        printf("--end--");
    }
    else
    {
        if(number % firstPrimeNumber == 0)
        {
            number = dividerLoop(number, firstPrimeNumber);
        }

        printAllFactors(number, firstPrimeNumber + 1);
    }
}

int dividerLoop(int number, int divider)
{
    if(number % divider != 0)
    {
        return number;
    }
    else
    {
        printf("%d  ", divider);
        dividerLoop(number/divider, divider);
    }

}


void printAllFactors_v2(int number, int count)
{
    if(number < count)
        printf("--end--");
    else if(number % count == 0)
    {
        printf("%d  ", count);
        printAllFactors_v2(number / count, count);
    }
    else
    {
        printAllFactors_v2(number, count + 1);
    }
}
