#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

// Generate random numbers between 0 to n-1 inclusive
#define random(n) (rand()%(n))

char *input(char *buffer, size_t n);
char inputc();

// Clear the grid for a new game
#define clearGrid(grid) memset(grid, ' ', 9)

void gridOut(char grid[9]);
char switchPlayer(char player);
void getEmptySpaces(char grid[9], int indexes[9]);
int placeToken(char player, char grid[9], char *coordinate);
int checkWinner(char player, char grid[9]);

// Used for determining when to minimise/maximise the scores
typedef enum _compare{
    max = 1,
    min = -1,
} compare;

int normalAI(char grid[9], char player, int emptySpaces);
int minimax(char grid[9], int emptySpaces, char player, compare cmp);
int impossibleAI(char grid[9], char player, int emptySpaces);

#endif // FUNCTIONS_H