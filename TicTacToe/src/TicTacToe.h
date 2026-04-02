#pragma once

#define EMPTY 0
#define FULL 3

#define INVALID_COORDINATE 0
#define INVALID_MOVE 0

#define CheckForRow 0
#define CheckForCol 1
#define CheckForDiagLeft 2
#define CheckForDiagRight 3

enum letter { UNOCCUPIED, X, O };

enum difficulty { EASY = 1, MEDIUM, EXPERT };

#include "Move.h"

/*
struct ttt_board {
	int coordinates[3][3];
	int row_counter[3];
	int col_counter[3];
	int diagonal_counter[2];
	int nr_of_available_moves;

	ttt_board() : coordinates({ UNOCCUPIED }), row_counter({ EMPTY }), col_counter({ EMPTY }), diagonal_counter({ EMPTY }), nr_of_available_moves(9) {};

	ttt_board(int coordinates[3][3], int rows_counters[3], int cols_counters[3], int diagonals_counters[2], int nr_of_available_moves) {
		for (int row = 0; row < 3; row++) {
			for (int col = 0; col < 3; col++) {
				this->coordinates[col][row] = coordinates[col][row];
			}
		}

		for (int counter_index = 0; counter_index < 2; counter_index++) {
			this->row_counter[counter_index] = rows_counters[counter_index];
			this->col_counter[counter_index] = cols_counters[counter_index];
			this->diagonal_counter[counter_index] = diagonals_counters[counter_index];
		}
		this->row_counter[2] = rows_counters[2];
		this->col_counter[2] = cols_counters[2];

		this->nr_of_available_moves = nr_of_available_moves;
	}

	
	ttt_board(const ttt_board& other) : nr_of_available_moves(other.nr_of_available_moves) {
		memcpy(this->coordinates, other.coordinates, 9);
		memcpy(this->row_counter, other.row_counter, 3);
		memcpy(this->col_counter, other.col_counter, 3);
		memcpy(this->diagonal_counter, other.diagonal_counter, 2);
	}

	void CopyBoard(ttt_board other) {
		for (int row = 0; row < 3; row++) {
			for (int col = 0; col < 3; col++) {
				this->coordinates[col][row] = other.coordinates[col][row];
			}
		}

		for (int counter_index = 0; counter_index < 2; counter_index++) {
			this->row_counter[counter_index] = other.row_counter[counter_index];
			this->col_counter[counter_index] = other.col_counter[counter_index];
			this->diagonal_counter[counter_index] = other.diagonal_counter[counter_index];
		}
		this->row_counter[2] = other.row_counter[2];
		this->col_counter[2] = other.col_counter[2];

		this->nr_of_available_moves = other.nr_of_available_moves;
	}
};
*/

#include "Game.h"
#include "Player.h"
#include "Human_Player.h"
#include "AI.h"

struct TicTacToe : public Game {
	struct ttt_board {
		int coordinates[3][3];
		int row_counter[3];
		int col_counter[3];
		int diagonal_counter[2];
		int nr_of_available_moves;

		ttt_board();

		ttt_board(int coordinates[3][3], int rows_counters[3], int cols_counters[3], int diagonals_counters[2], int nr_of_available_moves);

		/*
		ttt_board(const ttt_board& other) : nr_of_available_moves(other.nr_of_available_moves) {
			memcpy(this->coordinates, other.coordinates, 9);
			memcpy(this->row_counter, other.row_counter, 3);
			memcpy(this->col_counter, other.col_counter, 3);
			memcpy(this->diagonal_counter, other.diagonal_counter, 2);
		}
		*/

		void CopyBoard(ttt_board other);
	};
	TicTacToe();
	static move* GetValidMoves(const ttt_board& board);
	static letter GetCurrentLetter();
	static int CheckForDraw(const ttt_board& board);
	static int CheckForWinner(const ttt_board& board, const int& index, const int& CheckFor);
	static int CheckBoard(const ttt_board& board, const int& x, const int& y);
	static void MarkOnBoard(ttt_board& board, const int& x, const int& y, const int& letter);
	static int MakeMove(const int& x, const int& y);
	static int GetPlayerMove(move& move);
	static int TakeTurn();
	static void SetUpTurn();
	void SetUpGame();
	static void PrintBoard();
	void PrintVictoryMessage();
	static void PrintWelcomeMessage();
private:
	static TicTacToe::ttt_board board;
	static int rows[3];
	static int cols[3];
	static int diagonals[2];
	static char CharTranslation[3];
	static int (*game_loop)();
	static Player* current_player;
	static letter current_letter;
	static Player* Players[2];
	static int isPossible(const int& X, const int& Y);
	static int isValid(const int& Coord);
	//static int TakePlayerTurn();
	//static int TakeAITurn();
	static int PvERound();
	static int PvPRound();
	static void ToggleLetter();
	static void TogglePlayer();
	//static void ToggleTurn();
	void SetUpPvE();
	void SetUpPvP();
};