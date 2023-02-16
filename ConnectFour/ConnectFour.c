#include<stdio.h>
#include<stdlib.h>

const int HEIGHT = 8, WIDITH = 9;
char board[8][9];
const char PLAYER1 = 'X', PLAYER2 = 'O';
char currentPlayer = 'X';

void resetBoard();
void printBoard();
void makePlay(char, int);
char checkWin();
void changePlayer();

int main(){
	printf("\033[2J\033[1;1H");
	resetBoard();
	printBoard();
	int move;
	while(checkWin() == ' '){
		printf("Make a move: ");
		scanf("%d", &move);
		if (move > 9){
			printBoard();
			printf("Invalid move\n");
			continue;
		}
		makePlay(currentPlayer, move);
		printf("\033[2J\033[1;1H");
		changePlayer();
		printBoard();
		}
	printf("Winner: %c", checkWin());




	return 0;
}

void resetBoard(){
	for (int i = 0; i < HEIGHT; i++){
		for (int j = 0; j < WIDITH; j++){
			board[i][j] = ' ';
		}
	}
}

void printBoard(){
	for (int i = 0; i < HEIGHT + 1; i++){
		printf("|");
		for (int j = 0; j < WIDITH; j++){
			if (i < HEIGHT) printf("%c|", board[i][j]);
			else 			printf("%d|", j + 1);
		}
		printf("\n");
	}
	printf("\n\n\n");
}

void makePlay(char player, int place){
	place--;
	for (int i = HEIGHT; i > 0; i--){
		if (board[i][place] == ' '){
			board[i][place] = player;
			return;
		}
	}
}

char checkWin(){
	//Check for win conditions in the shape of  -
	for (int i = 0; i < HEIGHT; i++){
		for (int j = 0; j < WIDITH - 3; j++){
			if (
				(board[i][j] != ' ') &&
				(board[i][j] == board[i][j+1]) &&
				(board[i][j+1] == board[i][j+2]) &&
				(board[i][j+2] == board[i][j+3]))
			{
				return board[i][j];
			}
		}
	}
	//Check for win condition in the shape of |
	for (int i = 0; i < HEIGHT - 3; i++){
		for (int j = 0; j < WIDITH; j++){
			if (
				(board[i][j] != ' ') &&
				(board[i][j] == board[i+1][j]) &&
				(board[i+1][j] == board[i+2][j]) &&
				(board[i+2][j] == board[i+3][j]))
			{
				return board[i][j];
			}
		}
	}
	//Check for win condition in the shape of /
	for (int i = 0; i < HEIGHT - 3; i++){
		for (int j = 0; j < WIDITH - 3; j++){
			if (
				(board[i][j] != ' ') &&
				(board[i][j] == board[i+1][j+1]) &&
				(board[i+1][j+1] == board[i+2][j+2]) &&
				(board[i+2][j+2] == board[i+3][j+3]))
			{
				return board[i][j];
			}
		}
	}
	for (int i = 0; i < HEIGHT - 3; i++){
			for (int j = 0; j < WIDITH - 3; j++){
				if (
					(board[i+3][j] != ' ') &&
					(board[i+3][j] == board[i+2][j+1]) &&
					(board[i+2][j+1] == board[i+1][j+2]) &&
					(board[i+1][j+2] == board[i][j+3]))
				{
					return board[i+3][j];
				}
			}
		}


	return ' ';
}

void changePlayer(){
	if (currentPlayer == PLAYER1) currentPlayer = PLAYER2;
	else currentPlayer = PLAYER1;
}
