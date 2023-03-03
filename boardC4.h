#include "listC4.h"

#define MAX 1
#define MIN 0
#define DEPTH 5

#define HORIZON 1
#define DIAGLEFT (COLUMNS - 1)
#define DIAGRIGHT (COLUMNS + 1)
#define VERTICAL (-COLUMNS)

Item *initGame();
void printBoard(Item *node);
int gameOver(Item *node);
int evaluateBoard(Item *node, int player);
int getMinOrMax(int x, int y, int minOrMax);
void createChild(Item *child, Item *parent);
int getFreeRow(Item *node, int column);
Item *getChildNode(Item *node, int column, int player);
int valorisationPosition(Item *node, int pos, int player);
int sectType4(Item *node, int pos, int player, int direction);
int sectType3(Item *node, int pos, int player, int direction);
int sectType2(Item *node, int pos, int player, int direction);
int sectType1(Item *node, int pos, int player, int direction);