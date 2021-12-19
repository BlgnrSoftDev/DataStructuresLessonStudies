#include <stdio.h>
#include <stdlib.h>
#include "stackADT.h"
#include <stdbool.h>

typedef struct
{
    int row, col;
}POSITION;


int getSize(void);
void fillBoard(STACK* stack, int boardSize);
void printBoard(STACK*, int boardSize);
bool isGuarded(int board[][9], int row, int col, int boardSize);

int main()
{
   int boardSize;
   STACK* stack;
   boardSize = getSize();
   stack = createStack();


   fillBoard(stack, boardSize);
   printBoard(stack, boardSize);
   destroyStack(stack);


   printf("\nWe hoped you liked eight Queens.\n");


    return 0;
}


void printBoard(STACK* stack, int boardSize)
{
    POSITION* pos;
    STACK* reverseStack = (STACK*) malloc(sizeof(STACK));

    if( isEmptyStack(stack))
    {
        printf("\nthere are no positions on this board!!\n");
    }

    int i = 0;
    int m = stack->count;
    while(i < m)
    {
        pushStack(reverseStack, popStack(stack));
        ++i;
    }

    printf("elements total: %d", i);
    printf("\nPlace queens in following positions:\n");


    while( !isEmptyStack(reverseStack))
    {
        pos = (POSITION*) popStack(reverseStack);
        printf("Row-%d-Col-%d :  ", pos->row, pos->col);
        for(int i = 1; i <= boardSize; ++i)
        {
            if( pos->col == i)
            {
                printf(" Q |");
            }
            else
            {
                printf("   |");
            }

        }
            printf("\n");
    }

    printf("burada");
    destroyStack(reverseStack);
}

bool isGuarded(int board[][9], int row, int col, int boardSize)
{

    // checking all the elements in current column.
    for(int i = 1; i <= row; ++i)
    {
        if( board[i][col] == 1)
            return true;
    }


    //upper-left diagonal control
    for(int i = row-1, j = col-1; i >= 1 && j >= 1; --i, --j)
    {
        if( board[i][j] == 1)
            return true;

    }


    //upper-right diagonal control
    for(int i = row-1, j = col+1; i >= 1 && j < boardSize; i--, j++)
    {
        if(board[i][j] == 1)
            return true;


    }


    return false;

}

void fillBoard(STACK* stack, int boardSize)
{
    int row = 1;
    int col = 0;

    int board[9][9] = {0};


    while( row <= boardSize )
    {
        while(row <= boardSize && col <= boardSize)
        {
            ++col;


            if( !isGuarded(board, row, col, boardSize))
            {
                board[row][col] = 1;
                POSITION* newPos = (POSITION*) malloc(sizeof(POSITION));
                newPos->row = row;
                newPos->col = col;
                pushStack(stack, newPos);

                col = 0;
                row++;
            }//if

            while(col >= boardSize)
            {
                POSITION* pos = (POSITION*) popStack(stack);
                row = pos->row;
                col = pos->col;

                board[row][col] = 0;
                free(pos);
            }//while
        }//while
    }//while

    return;
}



int getSize()
{
    int temp;
    printf("Welcome to Program \n \
           \ryou may select a board size 4x4 from 8x8.\n\
           \r(Note: there aren't any solution for less than 4x4 boardsize\n");
    printf("Please, Enter the board size : \n==> ");
    scanf("%d", &temp);
    while(temp > 8 || temp < 4)
    {
        printf("\nBoard size must be bigger than 8 and less than 4, Please retry.\n");
        printf("Please Enter board size again: \n==> ");
        scanf("%d", &temp);
    }// while
    return temp;
}
