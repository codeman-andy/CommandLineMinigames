#pragma once

#include "Player.h"
#include "TicTacToe.h"

class AI : public Player {
	 move* m_valid_moves;
	 int m_nr_of_valid_moves;
	 int FindMoveIndex(move move) const;
	 void DecrementValidMoves(int index);
public:
	AI(const char* name);
	void SetValidMoves(int dimensions_lengths[]);
	void RemoveFromValidMoves(move move);
	move MakeRandomMove() const;
	static int FindWinningMoveInRows(move& winning_move, int board[3][3], int row_count[3], int my_letter);
	static int FindWinningMoveInCols(move& winning_move, int board[3][3], int col_count[3], int my_letter);
	static int FindWinningMoveInDiagonals(move& winning_move, int board[3][3], int diagonal_count[2], int my_letter);
	static int FindWinningMove(move& winning_move, int board[3][3], int row_count[3], int col_count[3], int diagonal_count[2], int my_letter);
	move FindWinOrMakeRandomMove(int board[3][3], int row_count[3], int col_count[3], int diagonal_count[2]) const;
	move FindWinOrPreventLossOrMakeRandomMove(int board[3][3], int row_count[3], int col_count[3], int diagonal_count[2]) const;
	//int MinMaxMove(move& winning_move, int board[3][3], int row_count[3], int col_count[3], int diagonal_count[2], int my_letter);
	static AI* CreatePlayer(const char* name);
};