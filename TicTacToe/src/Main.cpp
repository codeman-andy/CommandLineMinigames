#include <iostream>
//#include <string>

#define RUNNING 1
#define WINNER_FOUND 0

#define EMPTY 0
#define FULL 3

#define CheckForRow 0
#define CheckForCol 1
#define CheckForDiagLeft 2
#define CheckForDiagRight 3


char board[3][3] = { {'-', '-', '-'},
					 {'-', '-', '-'},
					 {'-', '-', '-'} };

struct line {
	unsigned char count = EMPTY;
	char elements[3] = { '-' };
} row_0, row_1, row_2, col_0, col_1, col_2, diag_left, diag_right;

unsigned char rows[3] = { EMPTY, EMPTY, EMPTY };
unsigned char cols[3] = { EMPTY, EMPTY, EMPTY };
unsigned char diagonals[2] = { EMPTY, EMPTY };

char current_letter = 'X';

unsigned char GAME_STATE = RUNNING;

static void Log(const char* message) {
	std::cout << message << std::endl;
}

static int CheckForWinner(int index, unsigned char CheckFor) {
	if (CheckFor == CheckForRow) {
		if (board[index][0] == board[index][1] && board[index][0] == board[index][2]) return WINNER_FOUND;
		return RUNNING;
	}
	if (CheckFor == CheckForCol) {
		if (board[0][index] == board[1][index] && board[0][index] == board[2][index]) return WINNER_FOUND;
		return RUNNING;
	}
	if (CheckFor == CheckForDiagLeft) {
		if (board[0][0] == board[1][1] && board[0][0] == board[2][2]) return WINNER_FOUND;
		return RUNNING;
	}
	if (CheckFor == CheckForDiagRight) {
		if (board[0][2] == board[1][1] && board[0][2] == board[2][0]) return WINNER_FOUND;
		return RUNNING;
	}
	/*
	unsigned char row = 0;
	while (row < 3) {
		if (board[row][0] == board[row][1] && board[row][0] == board[row][2]) {
			return WINNER_FOUND;
		}
		row++;
	}
	unsigned char column = 0;
	while (column < 3) {
		if (board[0][column] == board[1][column] && board[0][column] == board[2][column]) {
			return WINNER_FOUND;
		}
		column++;
	}
	if (board[0][0] == board[1][1] && board[0][0] == board[2][2]) {
		return WINNER_FOUND;
	}
	if (board[0][2] == board[1][1] && board[0][2] == board[2][0]) {
		return WINNER_FOUND;
	}*/
}

static void UpdateLetter() {
	if (current_letter == 'X') {
		current_letter = 'O';
		return; // Perguntar ao devm se o compiler optimiza isto
	}
	else {
		current_letter = 'X';
	}
}

static void MarkOnBoard(int x, int y) {
	board[y][x] = current_letter;
}

static void PrintBoard() {
	Log("  0 1 2");
	Log("  -----");
	for (unsigned char i = 0; i < 3; i++) {
		std::cout << +i << "|" << board[i][0] << " " << board[i][1] << " " << board[i][2] << "|" << std::endl;
		//Log("|- - -|");
	}
	Log("  -----");
}

static int UpdateBoard(int x, int y) {
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

static void TakeTurn() {

	std::cout << "Where do you wish to place? (vertical)\n";
	int Y;
	std::cin >> Y;

	std::cout << "Where do you wish to place? (horizontal)\n";
	int X;
	std::cin >> X;

	MarkOnBoard(X, Y);

	if (UpdateBoard(X, Y) == WINNER_FOUND) GAME_STATE = WINNER_FOUND;
	else UpdateLetter();
}

int main() {
	while (GAME_STATE == RUNNING) {
		PrintBoard();
		TakeTurn();
	}
	std::cout << "Congratulations! You won!" << std::endl;
	std::cin.get();
	std::cin.get();
}