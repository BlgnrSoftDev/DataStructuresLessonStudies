#include <stdio.h>
#include <stdlib.h>

int substract(int, int);
int total(int arg1, int arg2, int (* funcPointer) (int, int));
int (* funcPtr2) (int, int);

int main()
{

    printf("5 - 3 = %d", total(5, 3, substract));
    funcPtr2 = &substract;
    printf("5 - 3 = %d", (*funcPtr2) (5, 3));

    return 0;
}


int substract(int arg1, int arg2)
{
    return arg1 - arg2;
}

int total(int arg1, int arg2, int (* funcPointer) (int, int))
{
    return (*funcPointer) (arg1, arg2);
}


