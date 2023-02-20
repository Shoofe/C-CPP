/*
 * mine.c
 *
 *  Created on: Feb 17, 2023
 *      Author: boz
 */
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

const int MINE = 11, FLAG = 10, UNSEEN = 9, SEEN = 8;

const char FLAG_SPRITE = 'F', UNSEEN_SPRITE = '_', MINE_SPRITE = 'X', EMPTY_SPRITE = '#';




int** generate2dArray(int, int);
void  placeMines(int**, int, int, int);
int   minesNearby(int**, int, int, int, int );
int   printBoard(int**, int**, int, int);
void  drawMines(int**, int, int);
int   openField(int**, int**, int, int, int, int);

int main(){
	int W, H, am;
	printf("Choose the size of the board: (5 - 99 recommended)\nWidth:");
	scanf("%d", &W);
	printf("\nHeight:\n");
	scanf("%d", &H);
	printf("Number of mines:");
	scanf("%d", &am);

	//Setup
	int** board = generate2dArray(W, H);
	int** mines = generate2dArray(W, H);
	placeMines(mines, W, H, am);


	//Main game loop input vars
	int x, y, func;
	int condition = 0;
	while(condition != 11){
		//First, take input
		while(x < 0 || x > W || y < 0 || y > H || (func != 0 && func != 1 && func != 99)){

			x = -1;
			y = -1;
			func = -1;

			printf("X coords of the field:");
			scanf("%d", &x);
			printf("Y coords of the field:");
			scanf("%d", &y);
			printf("Function (Open(0) or Flag(1):");
			scanf("%d", &func);


			if (func == 99) {
				free(mines);
				free(board);
				return 0;

		}
		}
		if (func){
			if (board[x][y] == FLAG) board[x][y] = UNSEEN;
			else if (board[x][y] == UNSEEN) board[x][y] = FLAG;
		}
		else{
			if (openField(mines, board, x, y, W, H) == 11){
				free(mines);
				free(board);
				printBoard(mines, board, W, H);
				printf("BOOM!");
				return 0;
			}
		}
		condition = printBoard(mines, board, W, H);
		x = -1;
		y = -1;
		func = -1;
	}


	//end
	free(mines);
	free(board);

	return 0;

}


int  openField(int** mines, int** arr, int x, int y, int W, int H){
	//returns 11 if you try to open a mine
	if (mines[x][y] == MINE) return 11;
	arr[x][y] = SEEN;

	//Check all the surrounding fields if any are not next to a mine and opens those too
	for (int i = 0; i < 3; i++){
			for (int j = 0; j < 3; j++){
				int X = x + i - 1, Y = y + j - 1;
				if((X < W) && (Y >= 0) &&
				   (X < H) && (X >= 0)){
					if (!minesNearby(mines, X, Y, W, H)){
						arr[X][Y] = SEEN;
					}
				}
			}
		}

	return 0;
}


void  drawMines(int** arr, int W, int H){
}

int   minesNearby(int** arr, int x, int y, int W, int H){
	int numberOfMines = 0;
	for (int i = 0; i < 3; i++){
		for (int j = 0; j < 3; j++){
			int X = x + i - 1, Y = y + j - 1;
			if((X < W) && (Y >= 0) &&
			   (X < H) && (X >= 0)){
				if (arr[X][Y] == MINE){
					numberOfMines++;
				}
			}
		}
	}
	return numberOfMines;
}

int** generate2dArray(int W, int H){
	int** arr = malloc(W * sizeof(int*));
	for(int i = 0; i < W; i++){
		arr[i] = malloc(H * sizeof(int));
		for (int j = 0; j < H; j++){
			arr[i][j] = 0;
		}
	}
	return arr;
}

void placeMines(int** arr, int W, int H, int amount){
	srand((long) &arr);
	for(int i = 0; i < amount; i++){
		int condition = 1;
		int x, y;
		while(condition != 0){
			x = rand() % W;
			y = rand() % H;
			if (arr[x][y] != MINE){
				arr[x][y] = MINE;
				condition = 0;
			}
		}
	}
}

int printBoard(int** mines, int** arr, int W, int H){
	printf("\033[2J"); // clear screen
	for (int i = 0; i < W; i++){
		printf("X:%2d  ", i);
		for (int j = 0; j < H; j++){
			if (arr[i][j] == SEEN){
				if (mines[i][j] == MINE){
					printf("BOOM!");
					return 11;
				}
				int n = minesNearby(mines, i, j, W, H);
				if (!n){
					printf("%3c", EMPTY_SPRITE);
				}
				else{
					printf("%3d", n);
				}
			}
			else if (arr[i][j] == FLAG){
				printf("%3c", FLAG_SPRITE);
			}
			else{
				printf("%3c", UNSEEN_SPRITE);
			}
		}
		printf("\n");
	}
	printf("  Y:  ");
	for (int j = 0; j < H; j++){
		printf("%3d", j);
	}
	printf("\n\n");
	return 0;
}
