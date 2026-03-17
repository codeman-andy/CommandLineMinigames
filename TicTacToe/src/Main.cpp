#include <iostream>

#define RUNNING 1
#define WINNER_FOUND 0

#define INVALID_COORDINATE 0

#define EMPTY 0
#define FULL 3

#define CheckForRow 0
#define CheckForCol 1
#define CheckForDiagLeft 2
#define CheckForDiagRight 3



unsigned char board[3][3] = { 0 };

unsigned char rows[3] = { EMPTY, EMPTY, EMPTY };
unsigned char cols[3] = { EMPTY, EMPTY, EMPTY };
unsigned char diagonals[2] = { EMPTY, EMPTY };

char CharTranslation[3] = { '-', 'X', 'O' };

enum letter : unsigned char { UNOCCUPIED, X, O };
letter current_letter = X;

unsigned char GAME_STATE = RUNNING;

static void Log(const char* message) {
	std::cout << message << std::endl;
}

static int CheckForWinner(short int index, unsigned char CheckFor) {
	if (CheckFor == CheckForRow) {
		if (board[index][0] == board[index][1] && board[index][0] == board[index][2]) return WINNER_FOUND;
	}
	if (CheckFor == CheckForCol) {
		if (board[0][index] == board[1][index] && board[0][index] == board[2][index]) return WINNER_FOUND;
	}
	if (CheckFor == CheckForDiagLeft) {
		if (board[0][0] == board[1][1] && board[0][0] == board[2][2]) return WINNER_FOUND;
	}
	if (CheckFor == CheckForDiagRight) {
		if (board[0][2] == board[1][1] && board[0][2] == board[2][0]) return WINNER_FOUND;
	}
	return RUNNING;
}

static void PrintBoard() {
	Log("  0 1 2");
	Log("  -----");
	for (unsigned char i = 0; i < 3; i++) {
		std::cout << +i << "|" << CharTranslation[board[i][0]] << " " << CharTranslation[board[i][1]] << " " << CharTranslation[board[i][2]] << "|" << std::endl;
	}
	Log("  -----");
}

static void UpdateLetter() {
	if (current_letter == X) {
		current_letter = O;
	}
	else {
		current_letter = X;
	}
}

static int UpdateBoard(short int x, short int y) {
	rows[y] += 1;
	cols[x] += 1;
	if (rows[y] == FULL && !CheckForWinner(y, CheckForRow)) return WINNER_FOUND;
	if (cols[x] == FULL && !CheckForWinner(x, CheckForCol)) return WINNER_FOUND;

	if (x == y) diagonals[0]++;
	if (x + y == 2) diagonals[1]++;
	if (diagonals[0] == FULL && !CheckForWinner(0, CheckForDiagLeft)) return WINNER_FOUND;
	if (diagonals[1] == FULL && !CheckForWinner(1, CheckForDiagRight)) return WINNER_FOUND;

	return RUNNING;
}

static int MarkOnBoard(short int x, short int y) {
	if (board[y][x] != UNOCCUPIED) return INVALID_COORDINATE;
	board[y][x] = current_letter;
	return RUNNING;
}

static int MakeMove(short int X, short int Y) {

	if (!MarkOnBoard(X, Y)) return INVALID_COORDINATE;

	if (UpdateBoard(X, Y) == WINNER_FOUND) GAME_STATE = WINNER_FOUND;

	else UpdateLetter();

	return RUNNING;
}

static int GetMove(short int& X, short int& Y) {
	Log("Where do you wish to place? (vertical)");
	std::cin >> Y;
	if (Y < 0 || Y > 2 || Y % 1 != 0) return INVALID_COORDINATE;

	Log("Where do you wish to place? (horizontal)");
	std::cin >> X;
	if (X < 0 || X > 2 || X % 1 != 0) return INVALID_COORDINATE;

	return RUNNING;
}

static void TakeTurn() {
	short int X = 0;
	short int Y = 0;

	if (!GetMove(X, Y)) {
		Log("Your last coordinate was invalid. Please, type your coordinates again.");
		return;
	}

	if (!MakeMove(X, Y)) Log("The coordinate you tried to mark is already occupied. Please, choose another.");
}

int main() {
	Log("Let's play a game of Tic-Tac-Toe!");
	std::cin.get();
	while (GAME_STATE == RUNNING) {
		PrintBoard();
		TakeTurn();
	}
	PrintBoard();
	std::cout << "Congratulations! You won!" << std::endl;
	std::cin.get();
	std::cin.get();
}