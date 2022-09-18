#include "../headers/functions.h"

/**
 * @brief Reusable input function for strings
 * 
 * @param buffer 
 * @param n size of buffer
 */
void input(char *buffer, size_t n)
{
    fgets(buffer, n, stdin);
    size_t nl = strlen(buffer)-1;
    if (buffer[nl] == '\n') {
        buffer[nl] = '\0';
    } else {
        char c;
        while (1)
        {
            c = getchar();
            if (c == '\n')
            {
                break;
            }
        }
    }
    return;
}

// Output the current state of the grid
void gridOut(char grid[9])
{
	printf(" |A|B|C|\n");
	printf("-+-----+\n");
	printf("1|%c|%c|%c|\n", grid[0], grid[1], grid[2]);
	printf("-|-----|\n");
	printf("2|%c|%c|%c|\n", grid[3], grid[4], grid[5]);
	printf("-|-----|\n");
	printf("3|%c|%c|%c|\n", grid[6], grid[7], grid[8]);
	printf("-+-----+\n\n");
}

char switchPlayer(char player)
{
	if (player == 'X') {
		return 'O';
	} else {
		return 'X';
	}
}

/**
 * @brief Get the indexes of all empty spaces
 * 
 * @param grid 
 * @param indexes Array containing indexes
 */
void getEmptySpaces(char grid[9], int indexes[9])
{
	int count = 0;
	for (int i = 0; i < 9; i++)
	{
		if (grid[i] == ' ') {
			indexes[count] = i;
			count++;
		}
	}
}

/**
 * @brief Place the specified token in the grid
 * 
 * @param player Either 'X' or 'O'
 * @param grid 
 * @param coordinate In the form "1A" to "3C"
 * @return 0 on sucess and -1 if the coordinate is invalid
 */
int placeToken(char player, char grid[9], char *coordinate)
{
	int y;
    char x;
    sscanf(coordinate, "%1d%1c", &y, &x);
	y--;
	x = toupper(x) - 65;
	if ((x < 0 || x > 2) || (y < 0 || y > 2)) {
		printf("Please enter a coordinate between 1A and 3C\n\n");
		return -1;
	};

	// Check if a token has already been placed in the grid
	if (grid[y*3 + x] != ' ') {
		printf("A token has already been placed here!\n\n");
		return -1;
	}

	grid[y*3 + x] = player;
	return 0;
}

// Checks if a certain player has won
int checkWinner(char player, char grid[9])
{
	if (
		(grid[0] == player && grid[4] == player && grid[8] == player) || 
		(grid[2] == player && grid[4] == player && grid[6] == player) ||
		(grid[0] == player && grid[1] == player && grid[2] == player) ||
		(grid[3] == player && grid[4] == player && grid[5] == player) ||
		(grid[6] == player && grid[7] == player && grid[8] == player) ||
		(grid[0] == player && grid[3] == player && grid[6] == player) ||
		(grid[1] == player && grid[4] == player && grid[7] == player) ||
		(grid[2] == player && grid[5] == player && grid[8] == player)
		) {
			return 1;
	}

	return 0;
}

/**
 * @brief Randomly place a token in any empty space
 * 
 * @param grid 
 * @param player 
 * @param emptySpaces
 * @returns 0
 */
int normalAI(char grid[9], char player, int emptySpaces)
{
	int indexes[9];
	getEmptySpaces(grid, indexes);
	grid[indexes[random(emptySpaces)]] = player;

    return 0;
}

/**
 * @brief Main minimax function
 * 
 * @param grid 
 * @param emptySpaces
 * @param player 
 * @param cmp Determines whether to maximise or minimise
 * @return int 
 */
int minimax(char grid[9], int emptySpaces, char player, compare cmp)
{

    int indexes[9];
	getEmptySpaces(grid, indexes);  // Stores a list of empty spaces in the grid in the array 'indexes'

    if (cmp == min) {
        int score = 1000;
        int thisScore;
        for (int i = 0; i < emptySpaces; i++)  // Go through each free index
        {
            grid[indexes[i]] = player;
            if (checkWinner(player, grid) == 1) {
                thisScore = emptySpaces*cmp;
            } else if (emptySpaces-1 == 0) {
                thisScore = 0;
            } else {
                thisScore = minimax(grid, emptySpaces-1, switchPlayer(player), -cmp);
            }
            //printf("%d -> ", thisScore);
            if (thisScore < score) {
                score = thisScore;
            }
            grid[indexes[i]] = ' ';
        }

        return score;
    } else {
        int score = -1000;
        int thisScore;
        for (int i = 0; i < emptySpaces; i++)
        {
            grid[indexes[i]] = player;
            if (checkWinner(player, grid) == 1) {
                thisScore = emptySpaces*cmp;
            } else if (emptySpaces-1 == 0) {
                thisScore = 0;
            } else {
                thisScore = minimax(grid, emptySpaces-1, switchPlayer(player), -cmp);
            }
            //printf("%d -> ", thisScore);
            if (thisScore > score) {
                score = thisScore;
            }
            grid[indexes[i]] = ' ';
        }

        return score;
    }
}

/**
 * @brief Entry point for the minimax algorithm
 * 
 * @param grid 
 * @param player 
 * @param emptySpaces 
 * @return int 
 */
int impossibleAI(char grid[9], char player, int emptySpaces)
{
    int score = -1000;
    int thisScore;

    int move = -1;

    int indexes[9];
	getEmptySpaces(grid, indexes);

    for (int i = 0; i < emptySpaces; i++)
    {
        grid[indexes[i]] = player;
        if (checkWinner(player, grid) == 1) {
            thisScore = emptySpaces;
        } else if (emptySpaces-1 == 0) {
                thisScore = 0;
        } else {
            thisScore = minimax(grid, emptySpaces-1, switchPlayer(player), min);
        }
        if (thisScore > score) {
            score = thisScore;
            move = i;
        }
        grid[indexes[i]] = ' ';
    }

    grid[indexes[move]] = player;
    return 0;
}