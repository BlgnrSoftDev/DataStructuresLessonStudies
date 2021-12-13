#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define OPERATORS  "/+-*"


void preToPostFix(char*, char*);
int findExprLen(char*);

int main()
{
    char string[256] = "-+*ABC/E*FG";
    char string2[256] = "";
    printf("%d", findExprLen(string));
    preToPostFix(string, string2);
    printf("%s", string2);
    return 0;
}

void preToPostFix(char* preFixIn, char* postFix)
{
    char operatora[2];
    char postFix1[256];
    char postFix2[256];
    char temp[256];
    int lenPreFix;

    if(strlen(preFixIn) == 1)
    {
        *postFix = *preFixIn;
        *(postFix + 1) = '\0';
        return;
    }

    *operatora = *preFixIn;
    *(operatora + 1) = '\0';

    lenPreFix = findExprLen(preFixIn+1);
    strncpy(temp, preFixIn + 1, lenPreFix);
    *(temp + lenPreFix) = '\0';
    preToPostFix(temp, postFix1);

    strcpy(temp, preFixIn + 1 + lenPreFix);
    preToPostFix(temp, postFix2);

    strcpy(postFix, postFix1);
    strcat(postFix, postFix2);
    strcat(postFix, operatora);

    return;
}

int findExprLen(char* exprIn)
{
    int len1, len2;
    if(strcspn(exprIn, OPERATORS) == 0)
    {
        len1 = findExprLen(exprIn + 1);

        len2 = findExprLen(exprIn + 1 + len1);
    }
    else
    {
        len1 = len2 = 0;
    }

    return len1 + len2 + 1;
}


