#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include "boardC4.h"

/* To test, passed */
// int main()
// {
//     Item *cur = initGame();

//     Item *child1 = getChildNode(cur, 2, 1);
//     Item *child2 = getChildNode(child1, 3, -1);
//     Item *child3 = getChildNode(child2, 3, 1);
//     Item *child4 = getChildNode(child3, 4, -1);
//     Item *child5 = getChildNode(child4, 4, -1);
//     Item *child6 = getChildNode(child5, 4, 1);
//     Item *child7 = getChildNode(child6,4, -1);

//     printBoard(cur);
//     printf("value = %d\n", evaluateBoard(cur, -1));
//     printBoard(child1);
//     printf("value = %d\n", evaluateBoard(child1, -1));
//     printBoard(child2);
//     printf("value = %d\n", evaluateBoard(child2, -1));
//     printBoard(child3);
//     printf("value = %d\n", evaluateBoard(child3, -1));
//     printBoard(child4);
//     printf("value = %d\n", evaluateBoard(child4, -1));
//     printBoard(child5);
//     printf("value = %d\n", evaluateBoard(child5, -1));
//     printBoard(child6);
//     printf("value = %d\n", evaluateBoard(child6, -1));
//     printBoard(child7);
//     printf("value = %d\n", evaluateBoard(child7, -1));

//     return 0;
// }

int evaluateBoard(Item *node, int player)
{
    int value = 0;
    int pos;

    if (gameOver(node))
    {
        return value = -1 * player * 1000000;
    }
    switch (player)
    {
    case 1:
        for (int i = 0; i < node->movesMade1; i++)
        {
            pos = node->player1[i];
            value += valorisationPosition(node, pos, 1);
        }
        for (int i = 0; i < node->movesMade2; i++)
        {
            pos = node->player2[i];
            value -= valorisationPosition(node, pos, -1);
        }
        break;

    case -1:
        for (int i = 0; i < node->movesMade2; i++)
        {
            pos = node->player2[i];
            value += valorisationPosition(node, pos, -1);
        }
        for (int i = 0; i < node->movesMade1; i++)
        {
            pos = node->player1[i];
            value -= valorisationPosition(node, pos, 1);
        }
        break;
    }
    return value;
}

/* Returns an heuristic value for a board and a given position for a player.
1 point for a section only the player is in
help functions sect 1 to 4 for the different types of sets */
int valorisationPosition(Item *node, int pos, int player)
{
    int value = 0;
    int iPos = pos / COLUMNS; //  row of the position
    int jPos = pos % COLUMNS; // column of the position

    /* HORIZONTICAL */
    if (jPos == 0)
    {
        value += sectType1(node, pos, player, HORIZON);
    }
    if (jPos == 1)
    {
        value += sectType1(node, pos, player, HORIZON);
        value += sectType2(node, pos, player, HORIZON);
    }
    if (jPos == 2)
    {
        value += sectType1(node, pos, player, HORIZON);
        value += sectType2(node, pos, player, HORIZON);
        value += sectType3(node, pos, player, HORIZON);
    }
    if (jPos == 3)
    {
        value += sectType1(node, pos, player, HORIZON);
        value += sectType2(node, pos, player, HORIZON);
        value += sectType3(node, pos, player, HORIZON);
        value += sectType4(node, pos, player, HORIZON);
    }
    if (jPos == 4)
    {
        value += sectType2(node, pos, player, HORIZON);
        value += sectType3(node, pos, player, HORIZON);
        value += sectType4(node, pos, player, HORIZON);
    }
    if (jPos == 5)
    {
        value += sectType3(node, pos, player, HORIZON);
        value += sectType4(node, pos, player, HORIZON);
    }
    if (jPos == 6)
    {
        value += sectType4(node, pos, player, HORIZON);
    }

    /* VERTICAL */
    if (iPos == 3 | iPos == 2 | iPos == 1)
    {
        value += sectType1(node, pos, player, VERTICAL);
        value += sectType2(node, pos, player, VERTICAL);
        value += sectType3(node, pos, player, VERTICAL);
    }
    if (iPos == 4)
    {
        value += sectType1(node, pos, player, VERTICAL);
        value += sectType2(node, pos, player, VERTICAL);
    }

    if (iPos == 5)
    {
        value += sectType1(node, pos, player, VERTICAL);
    }

    /* DIAGONAL LEFT */
    if (iPos > 2 && jPos > 2)
    {
        value += sectType1(node, pos, player, DIAGLEFT);
    }

    if (iPos > 1 && iPos < 5 && jPos > 1 && jPos < 6)
    {
        value += sectType2(node, pos, player, DIAGLEFT);
    }

    if (iPos > 0 && iPos < 4 && jPos > 0 && jPos < 5)
    {
        value += sectType3(node, pos, player, DIAGLEFT);
    }

    /* DIAGONAL RIGHT */
    if (iPos > 2 && jPos < 4)
    {
        value += sectType1(node, pos, player, DIAGRIGHT);
    }

    if (iPos > 1 && iPos < 5 && jPos < 5 && jPos > 0)
    {
        value += sectType2(node, pos, player, DIAGRIGHT);
    }

    if (iPos > 0 && iPos < 4 && jPos < 6 && jPos > 1)
    {
        value += sectType3(node, pos, player, DIAGRIGHT);
    }

    return value;
}

/* Three elements ahead */
int sectType1(Item *node, int pos, int player, int direction)
{
    if (node->board[pos + direction] != player * -1 && node->board[pos + 2 * direction] != player * -1 && node->board[pos + 3 * direction] != player * -1)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/* Two elements ahead, one behind */
int sectType2(Item *node, int pos, int player, int direction)
{
    if (node->board[pos + direction] != player * -1 && node->board[pos + 2 * direction] != player * -1 && node->board[pos - direction] != player * -1)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/* One element ahead, two behind */
int sectType3(Item *node, int pos, int player, int direction)
{
    if (node->board[pos + direction] != player * -1 && node->board[pos - direction] != player * -1 && node->board[pos - 2 * direction] != player * -1)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/* Three elements on the left (only for row) */
int sectType4(Item *node, int pos, int player, int direction)
{
    if (node->board[pos - direction] != player * -1 && node->board[pos - 2 * direction] != player * -1 && node->board[pos - 3 * direction] != player * -1)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

Item *initGame()
{
    Item *node;

    node = nodeAlloc();
    // Calloc initializes with zeroes everywhere
    node->board = calloc(SIZE, sizeof(char));
    node->player1 = calloc(SIZE / 2, sizeof(int));
    node->movesMade1 = 0;
    node->player2 = calloc(SIZE / 2, sizeof(int));
    node->movesMade2 = 0;
    node->f = 0;

    return node;
}

void printBoard(Item *node)
{
    assert(node);
    printf("\n************************************\n");
    printf("\n  0   1   2   3   4   5   6 \n");
    for (int i = 0; i < COLUMNS; i++)
        if (i == 0)
            printf(" ___");
        else
            printf("____");
    printf("\n");
    for (int j = 0; j < SIZE; j++)
    {
        if (j % COLUMNS == 0)
            printf("|");
        if (node->board[j] == 1)
            printf(" O |");
        else if (node->board[j] == -1)
            printf(" X |");
        else
            printf("   |");
        if ((j + 1) % COLUMNS == 0)
        {
            printf("\n");
            for (int i = 0; i < COLUMNS; i++)
                if (i == 0)
                    printf(" ___");
                else
                    printf("____");
            printf("\n");
        }
    }
    printf("\n************************************\n");
    printf("************************************\n");
}

// Only need to check if the last move was a winning move
int gameOver(Item *node)
{
    if (node->movesMade1 + node->movesMade2 == SIZE)
        // Board is full
        return 1;
    else if (node->movesMade1 + node->movesMade2 == 0)
        // Board is empty
        return 0;

    int move;                                   // Last move
    int vIndex, hIndex, dDIndex, dUIndex;       // Keeps track of board traversing
    int vert = 0, hori = 0, dDown = 0, dUp = 0; // Chain counts

    if (node->movesMade1 > node->movesMade2)
        // Player 1, human, always starts
        move = node->player1[node->movesMade1 - 1];
    else
        move = node->player2[node->movesMade2 - 1];

    int player = node->board[move]; // Player who made the last move
    int i = -3;                     // Three places before, will loop until 3 places after

    while (i <= 3 &&
           vert < 4 &&
           hori < 4 &&
           dDown < 4 &&
           dUp < 4)
    {
        if (i == 0)
        // This is the latest piece, it always contributes to a chain
        {
            vert++;
            hori++;
            dDown++;
            dUp++;
            i++;
            continue;
        }

        // Index calculations
        vIndex = move + i;
        hIndex = move + i * COLUMNS;
        dDIndex = move + i * (COLUMNS + 1);
        dUIndex = move + i * (COLUMNS - 1);

        // Vertical check
        if ((vIndex >= 0) && (vIndex < SIZE) &&
            ((vIndex % COLUMNS - move % COLUMNS) == i) &&
            (node->board[vIndex] == player))
            vert++;
        else
            vert = 0;

        // Horizontal check
        if ((hIndex >= 0) && (hIndex < SIZE) &&
            ((hIndex / COLUMNS - move / COLUMNS) == i) &&
            (node->board[hIndex] == player))
            hori++;
        else
            hori = 0;

        // Diagonal down check
        if ((dDIndex >= 0) && (dDIndex < SIZE) &&
            ((dDIndex % COLUMNS - move % COLUMNS) == i) &&
            (node->board[dDIndex] == player))
            dDown++;
        else
            dDown = 0;

        // Diagonal up check
        if ((dUIndex >= 0) && (dUIndex < SIZE) &&
            ((move % COLUMNS - dUIndex % COLUMNS) == i) &&
            (node->board[dUIndex] == player))
            dUp++;
        else
            dUp = 0;

        i++;
    }

    if (vert != 4 && hori != 4 && dDown != 4 && dUp != 4)
        return 0;
    return 1;
}

int getMinOrMax(int x, int y, int minOrMax)
{
    assert((minOrMax == MIN) || (minOrMax == MAX));
    switch (minOrMax)
    {
    case MIN:
        if (x < y)
            return x;
        return y;
    case MAX:
        if (x > y)
            return x;
        return y;
    }
}

/* creates child from parent and asigns an identical board */
void createChild(Item *child, Item *parent)
{
    assert(parent);
    child->board = calloc(SIZE, sizeof(char));
    child->player1 = calloc(SIZE / 2, sizeof(int));
    child->player2 = calloc(SIZE / 2, sizeof(int));
    child->movesMade1 = parent->movesMade1;
    child->movesMade2 = parent->movesMade2;

    assert(child->board);
    /* Copy board */
    for (int i = 0; i < SIZE; i++)
        child->board[i] = parent->board[i];

    assert(child->player1);
    /* Copy player1 */
    for (int i = 0; i < SIZE / 2; i++)
        child->player1[i] = parent->player1[i];

    assert(child->player2);
    /* Copy player2 */
    for (int i = 0; i < SIZE / 2; i++)
        child->player2[i] = parent->player2[i];
}

/* Gets the first free row out of a column */
int getFreeRow(Item *node, int column)
{
    int row = 0;
    /* For every row that is empty, row++*/
    for (int i = 0; i < 6; i++)
    {
        if (node->board[column] == 0)
        {
            row++;
            column = column + COLUMNS;
        }
    }
    /* If first row not empty, column is full return -1,
    first row that is free: row = 0 etc.*/
    row = row - 1;
    return row;
}

/* Return a new item where player places a piece at position pos if possible,
NULL if not valid. player = {-1,1}
 */
Item *getChildNode(Item *node, int column, int player)
{

    /* allocate and init child node */
    Item *child_p = nodeAlloc();
    createChild(child_p, node);
    int row = getFreeRow(node, column);

    /*Column not full*/
    if (row != -1)
    {
        int pos = row * COLUMNS + column;
        child_p->board[pos] = player; // new move
        if (player == 1)
        {
            child_p->player1[child_p->movesMade1] = pos;
            child_p->movesMade1++;
        }
        else
        {
            child_p->player2[child_p->movesMade2] = pos;
            child_p->movesMade2++;
        }
        return child_p;
    }
    else
        return NULL;
}
