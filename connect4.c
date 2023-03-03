#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#include "listC4.h"
#include "boardC4.h"

Item *cur, *tmp;                       // This is the object we use during the game
List nextMoves;                        // List of possible next moves
int player = 1;                        // For keeping track of which player it is
int column;                            // For keeping trach of which column was placed
int columns[] = {3, 4, 2, 5, 1, 6, 0}; // Search order

/* Player 1 (human) maximizes, player -1 (computer) minimizes.
Minimax algorithm with pruning, pseudocode taken from:
https://www.youtube.com/watch?v=l-hh51ncgDI
*/
int miniMax(Item *node, int depth, int alpha, int beta, int player)
{
    if (depth == 0 || gameOver(node))
    {
        // printf("depth == 0\n");
        // printf("evaluation: %d\n", evaluateBoard(node,player));
        // printBoard(node);
        return evaluateBoard(node, player);
    }

    int minOrMax, bestEval, eval;

    if (player == 1)
    // Maximizing
    {
        minOrMax = MAX;
        bestEval = -100000;
    }
    else
    // Minimizing
    {
        minOrMax = MIN;
        bestEval = 100000;
    }

    for (int i = 0; i < COLUMNS; i++)
    {
        column = columns[i];
        Item *child = getChildNode(node, column, player);

        if (child != NULL)
        {
            eval = miniMax(child, depth - 1, alpha, beta, (-1) * player);
            // printf("depth = %d\n", depth);
            // printf("evaluation = %d\n", eval);
            // printBoard(child);
            bestEval = getMinOrMax(bestEval, eval, minOrMax);
            if (minOrMax)
                // minOrMax = MAX == 1
                alpha = getMinOrMax(alpha, eval, minOrMax);
            else
                // minOrMax = MIN == 0
                beta = getMinOrMax(beta, eval, minOrMax);

            if (depth == DEPTH)
            // To decide which move to make
            {
                child->f = eval;
                addLast(&nextMoves, child);
            }

            if (beta <= alpha) // Pruning, disregard branches which cannot compete
                break;
        }
    }
    return bestEval;
}

void humanTurn()
{
    printf("Choose column (between 0 and %d):\n", COLUMNS - 1);
    scanf("%d", &column);
    while (column < 0 || column >= COLUMNS)
    {
        printf("Column must be between 0 and 6:\n");
        scanf("%d", &column);
    }

    tmp = getChildNode(cur, column, player);
    if (!tmp)
    {
        // If the column was not free
        printf("Invalid move. Try again\n");
        humanTurn();
    }
    else
        cur = tmp;
}

void AITurn()
{
    int bestEval = miniMax(cur, DEPTH, -100000, 100000, player);
    cur = popFValue(&nextMoves, bestEval);
    cleanUpList(&nextMoves);
    printf("\n\n\nAI played:");
    printBoard(cur);
    //printf("evaluation for (real) player 1 : %d\n", evaluateBoard(cur, 1));
}

int main()
{
    initList(&nextMoves);
    cur = initGame();

    printf("Starting board:");
    printBoard(cur);
    while (!gameOver(cur))
    {
        switch (player)
        {
        case 1:
            humanTurn();
            break;
        case -1:
            AITurn();
            break;
        }
        player *= -1;
        printBoard(cur);
    }

    
    printf("Game is over!\nSomeone won\nFinal board");

    printf("\n\n\nGame is over!\n");
    switch (evaluateBoard(cur, player))
    {
    case 1000000:
        printf("Congratulations! You won");
        break;
    case -1000000:
        printf("Too bad, the AI won :(");
        break;
    default:
        ("It is a tie!");
        break;
    }
    printBoard(cur);
}
