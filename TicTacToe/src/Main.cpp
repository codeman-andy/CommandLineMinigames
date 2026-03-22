#include "Log.h"
#include "Player.h"

#define RUNNING 1
#define WINNER_FOUND 0

#define INVALID_COORDINATE 0
#define INVALID_MOVE 0

#define EMPTY 0
#define FULL 3

#define CheckForRow 0
#define CheckForCol 1
#define CheckForDiagLeft 2
#define CheckForDiagRight 3

struct TicTacToeBoard {
	size_t board[3][3];
	size_t rows[3];
	size_t cols[3];
	size_t diagonals[2];

	TicTacToeBoard() {
		size_t board[3][3] = { 0 };
		size_t rows[3] = { EMPTY, EMPTY, EMPTY };
		size_t cols[3] = { EMPTY, EMPTY, EMPTY };
		size_t diagonals[2] = { EMPTY, EMPTY };
	};
};

TicTacToeBoard GAME = TicTacToeBoard();

char CharTranslation[3] = { '-', 'X', 'O' };

enum letter : size_t { UNOCCUPIED, X, O };

Player* PLAYERS[2];

Player* CURRENT_PLAYER;

letter CURRENT_LETTER = UNOCCUPIED;

size_t GAME_STATE = RUNNING;

static void PrintVictoryMessage() {
	const char* winner = CURRENT_PLAYER->GetName();
	std::cout << "Congratulations, " << winner << "! You won!" << std::endl;
}

static void PrintBoard() {
	Log("  0 1 2\n");
	Log("  -----\n");
	for (size_t i = 0; i < 3; i++) {
		std::cout << +i << "|" << CharTranslation[GAME.board[i][0]] << " " << CharTranslation[GAME.board[i][1]] << " " << CharTranslation[GAME.board[i][2]] << "|" << std::endl;
	}
	Log("  -----\n");
}

static int CheckForWinner(size_t index, size_t CheckFor) {
	if (CheckFor == CheckForRow) {
		if (GAME.board[index][0] == GAME.board[index][1] && GAME.board[index][0] == GAME.board[index][2]) return WINNER_FOUND;
	}
	if (CheckFor == CheckForCol) {
		if (GAME.board[0][index] == GAME.board[1][index] && GAME.board[0][index] == GAME.board[2][index]) return WINNER_FOUND;
	}
	if (CheckFor == CheckForDiagLeft) {
		if (GAME.board[0][0] == GAME.board[1][1] && GAME.board[0][0] == GAME.board[2][2]) return WINNER_FOUND;
	}
	if (CheckFor == CheckForDiagRight) {
		if (GAME.board[0][2] == GAME.board[1][1] && GAME.board[0][2] == GAME.board[2][0]) return WINNER_FOUND;
	}
	return RUNNING;
}

static int UpdateBoard(size_t x, size_t y) {
	GAME.rows[y] += 1;
	GAME.cols[x] += 1;
	if (GAME.rows[y] == FULL && !CheckForWinner(y, CheckForRow)) return WINNER_FOUND;
	if (GAME.cols[x] == FULL && !CheckForWinner(x, CheckForCol)) return WINNER_FOUND;

	if (x == y) GAME.diagonals[0]++;
	if (x + y == 2) GAME.diagonals[1]++;
	if (GAME.diagonals[0] == FULL && !CheckForWinner(0, CheckForDiagLeft)) return WINNER_FOUND;
	if (GAME.diagonals[1] == FULL && !CheckForWinner(1, CheckForDiagRight)) return WINNER_FOUND;

	return RUNNING;
}

static void MarkOnBoard(size_t x, size_t y) {
	GAME.board[y][x] = CURRENT_LETTER;
}

static int MakeMove(size_t X, size_t Y) {
	MarkOnBoard(X, Y);

	if (UpdateBoard(X, Y) == WINNER_FOUND) {
		GAME_STATE = WINNER_FOUND;
		return WINNER_FOUND;
	}

	return RUNNING;
}

static int isPossible(size_t X, size_t Y) {
	if (GAME.board[Y][X] == UNOCCUPIED) return RUNNING;

	else Log("The coordinate you tried to mark is already occupied. Please, choose another.\n");
	return INVALID_MOVE;
}

static int isValid(size_t coord) {
	if (coord % 1 == 0 && coord >= 0 && coord <= 2) return RUNNING;

	else Log("Your last coordinate was invalid. Please, type your coordinates again.\n");
	return INVALID_COORDINATE;
}

static int GetMove(size_t& X, size_t& Y) {
	Log("Where do you wish to place? (vertically)\n");
	std::cin >> Y;
	if (!isValid(Y)) return INVALID_COORDINATE;

	Log("Where do you wish to place? (horizontally)\n");
	std::cin >> X;
	if (!isValid(X)) return INVALID_COORDINATE;

	return RUNNING;
}

static int TakeTurn() {
	size_t X = 0;
	size_t Y = 0;

	if (!GetMove(X, Y)) return INVALID_COORDINATE;

	if (!isPossible(X, Y)) return INVALID_MOVE;

	if (!MakeMove(X, Y)) return WINNER_FOUND;

	return RUNNING;
}

static void SetLetter() {
	if (CURRENT_LETTER == X) CURRENT_LETTER = O;
	else CURRENT_LETTER = X;
}

static void SetPlayer() {
	if (CURRENT_PLAYER == PLAYERS[0]) CURRENT_PLAYER = PLAYERS[1];
	else CURRENT_PLAYER = PLAYERS[0];
}

static void SetUpTurn() {
	SetPlayer();
	SetLetter();
}

static char* GetPlayerName() {
	clear_buffer();
	Log("What do you want to be called? (max. 32-characters)\n");
	char input[32];
	std::cin >> input;
	size_t name_length = strlen(input);
	char* name = (char*) malloc(name_length + 1);
	for (size_t i = 0; i <= name_length; i++) {
		name[i] = input[i];
	}
	return name;
}

static Player* CreatePlayer() {
	char* name = GetPlayerName();

	Player* ptr = new Player(name);

	return ptr;
}

static void SetUpPlayers() {
	PLAYERS[0] = CreatePlayer();
	PLAYERS[1] = CreatePlayer();
}

static void PrintWelcomeMessage() {
	Log("Let's play a game of Tic-Tac-Toe!");
}

int main() {
	PrintWelcomeMessage();

	SetUpPlayers();

	SetUpTurn();

	PrintBoard();
	while (GAME_STATE == RUNNING) {
		if (TakeTurn() != WINNER_FOUND) SetUpTurn();
		PrintBoard();
	}
	PrintVictoryMessage();

	clear_buffer();
	std::cin.get();
}