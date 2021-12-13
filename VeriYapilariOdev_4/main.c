#include <stdio.h>
#include <stdlib.h>
#include "StackADT.h"

/*
Veri yapilari Odevi. verilen metnin parantez açýsýndan dengeli veya dengesiz oldugunu bulan algoritma.
fonksiyonun prototype'ý odev'de verildigi gibidir.
her iterasyonda guncel stack durumunu ekrana bastýrýr.
*/
bool isBalanced(const char p[], int n);
int main()
{
    const char p[6] = "{({})}";
    const char p2[4] = "({)}";

    if(isBalanced(p, 6))
        printf("ilk ifade dengelidir...\n\n");
    if( !isBalanced(p2, 4))
        printf("ikinci ifade dengeli degildir...");
    return 0;
}


bool isBalanced(const char p[], int n)
{
    STACK* stack = createStack();
    char* chPtr;
    if(!stack)
        printf("\nMemory cannot be allocated for stack... \n"),exit(100);

    int i = 0;
    while(i < n)
    {
        if(p[i] == '{' || p[i] == '(')
        {
            chPtr = (char*)malloc(sizeof(char));
            *chPtr = p[i];
            pushStack(stack, chPtr);
        }//if
        else if( p[i] == '}' || p[i] == ')')
        {
            if( p[i] == '}')
            {
                chPtr = (char*)popStack(stack);
                if(*chPtr != '{')
                    return false;
            }//if
            else if(p[i] == ')')
            {
                chPtr = (char*)popStack(stack);
                if(*chPtr != '(')
                    return false;
            }//else if
        }//else

        printStack(stack);
        ++i;
    }//while

    if(!isEmptyStack(stack))
        return false;

    return true;

}

void printStack(STACK* stack)
{
    NODE* g = stack->top;
    printf("--> ");
    while(g != NULL)
    {
        printf("%c, ", *((char*)g->data));
        g = g->link;
    }
    printf("\n\n");
}
