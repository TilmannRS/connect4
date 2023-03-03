#ifndef LIST_C4_H
#define LIST_C4_H
#include "itemC4.h"

/*Essentially the same object as
linked list for the chess problem */

typedef struct List_str
{
    int nrEls;
    Item *first;
    Item *last;
} List;

Item *nodeAlloc();
void initList(List *list);
void freeItem(Item *node);
void cleanUpList(List *list);
void addLast(List *list, Item *node);
void delList(List *list, Item *node);
Item *popFValue(List *list, int f);
void printList(List list);

#endif