#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>

#include "../headers/functions.h"

int main()
{
	char grid[9];
	clearGrid(grid);

	// Value of X represents player 1's turn, value of O represents player 2's turn
	char playerTurn = 'X';
	char human = 'X';

	int emptySpaces = 9;

	// Coordinates for grid placement in the form '1A' to '3C'
	char coordinate[3];

	int error;

	int gameOver = 0;
	char replay;

	// Mode variable. 0 for 2 player, 1 for normal AI, and 2 for impossible AI mode
	char mode = '0';
	char option;

	printf("X & O ~ C EDITION\n");
	printf("=================");

	MENU:
	printf("\nSelect a mode:\n");
	printf("  1. Two player,\n  2. Single player (vs AI)\n  3. Exit\n");

	printf("Enter 1, 2, or 3: ");
	inputc(option);
	if (option == '2') {
		printf("\nSelect a difficulty:\n");
		printf("  1. Normal,\n  2. Impossible\n");
		printf("Enter 1 or 2: ");
		DIFFICULTY:
		inputc(option);
		if (option != '1' && option != '2') {
			printf("Select between option 1 or 2: ");
			goto DIFFICULTY;
		}
		mode = option;
		time_t t;
		srand((unsigned)time(&t));
		printf("\nDo you want to play 1st or 2nd:\n");
		printf("  1. X,\n  2. O,\n  3. Random\n");
		printf("Enter 1, 2, or 3: ");
		PLAYERSELECT:
		inputc(option);
		switch (option) {
			case '1':
				human = 'X';
				break;
			case '2':
				human = 'O';
				break;
			case '3':
				human = (char [2]){'X', 'O'}[random(2)];
				break;
			default:
				printf("Select between option 1, 2 or 3: ");
				goto PLAYERSELECT;
				break;
		}

	} else if (option == '3') {
		printf("Exiting...");
		return 0;
	} else if (option != '1') {
		goto MENU;
	}

	printf("\n");

	// Main gameplay loop
	while(1)
	{

		if (mode == '0' || human == playerTurn) {
			gridOut(grid);
			printf("Player %c's turn\n", playerTurn);
			printf("Enter a coordinate: ");
			input(coordinate, 3);
			error = placeToken(playerTurn, grid, coordinate);
		} else {
			printf("AI's turn...\n");
			if (mode == '1') {
				error = normalAI(grid, playerTurn, emptySpaces);
			} else {
				error = impossibleAI(grid, playerTurn, emptySpaces);
			}
		}

		if (error != -1) {
			playerTurn = switchPlayer(playerTurn);
			emptySpaces--;
			printf("\n");
		}

		if (checkWinner('X', grid) == 1) {
			gridOut(grid);
			printf("Player X has won!\n");
			gameOver = 1;
		} else if (checkWinner('O', grid) == 1) {
			gridOut(grid);
			printf("Player O has won!\n");
			gameOver = 1;
		} else if (emptySpaces == 0) {
			gridOut(grid);
			printf("There has been a draw!\n");
			gameOver = 1;
		}
		
		if (gameOver) {
			RETRY:
			printf("Would you like to play again? [Y/N]: ");
			inputc(replay);
			if (toupper(replay) == 'N') {
				printf("Exiting...");
				break;
			} else if (toupper(replay) == 'Y') {
				clearGrid(grid);
				gameOver = 0;
				playerTurn = 'X';
				emptySpaces = 9;
				goto MENU;
			} else {
				printf("\n");
				goto RETRY;
			}
		}
	}

	return 0;
}