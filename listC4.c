#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "listC4.h"

/*Similar/identical functions as those
for linked list for the chess problem */

Item *nodeAlloc()
{
    Item *node;

    node = (Item *)malloc(sizeof(Item));
    assert(node);

    node->board = NULL;
    node->player1 = NULL;
    node->player2 = NULL;
    node->prev = NULL;
    node->next = NULL;
    node->f = 0;

    return node;
}

void initList(List *list)
{
    list->nrEls = 0;
    list->first = NULL;
    list->last = NULL;
}

void freeItem(Item *node)
{
    if (node && node->board)
        free(node->board);
    if (node)
        free(node);
}

void cleanUpList(List *list)
{
    Item *current = list->first;
    Item *tmp;
    while (current)
    {
        tmp = current->next;
        freeItem(current);
        current = tmp;
    }
    list->first = NULL;
    list->last = NULL;
    list->nrEls = 0;
}

// Add item to queue
void addLast(List *list, Item *node)
{
    assert(list);
    assert(node);
    if (++list->nrEls == 1)
    {
        list->first = node;
        list->last = node;
    }
    else
    {
        node->prev = list->last;
        node->prev->next = node;
        list->last = node;
    }
}

// Remove node from list
void delList(List *list, Item *node)
{
    assert(list);
    assert(node);
    if (node->prev)
    {
        node->prev->next = node->next;
        if (node->next)
            node->next->prev = node->prev;
    }
    else
    {
        assert(list->first == node);
        if (node->next)
        {
            list->first = node->next;
            if (list->first)
                list->first->prev = NULL;
        }
    }
    if (node->next == NULL)
    {
        assert(list->last == node);
        list->last = node->prev;
    }
    node->next = node->prev = NULL;
    list->nrEls--;
    if (list->nrEls == 0)
    {
        list->first = NULL;
        list->last = NULL;
    }
}

// Remove first occurence of item with specific f-value
Item *popFValue(List *list, int f)
{
    assert(list->first);
    Item *item = list->first;
    while (item)
    {
        if (item->f == f)
        {
            delList(list, item);
            return item;
        }
        item = item->next;
    }
}

void printList(List list)
{
    Item *item = list.first;
    while (item)
    {
        printf(" %d ; ", item->f);
        item = item->next;
    }
    printf(" (nb_items: %d)\n", list.nrEls);
}
