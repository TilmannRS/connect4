#ifndef ITEM_C4_H
#define ITEM_C4_H

#define SIZE 42

#define COLUMNS 7
#define ROWS 6

typedef struct Item_str
{
    char *board; // 0=empty, 1=human, -1=AI
    int f;       // costs
    struct Item_str *prev, *next;

    int *player1;
    int *player2;
    int movesMade1;
    int movesMade2;

} Item;

#endif