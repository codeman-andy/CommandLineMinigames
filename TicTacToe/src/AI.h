#pragma once

#include "Player.h"
#include "TicTacToe.h"

class AI : public Player {
	 move* m_valid_moves;
	 int m_nr_of_valid_moves;
	 int FindMoveIndex(move move) const;
	 void DecrementValidMoves(int index);
	 void CopyBoard(int board[3][3], int new_board[3][3]);
public:
	AI(const char* name);
	void SetValidMoves(move* valid_moves);
	void RemoveFromValidMoves(move move);
	move MakeRandomMove() const;
	static int FindWinningMoveInRows(move& winning_move, ttt_board board, int my_letter);
	static int FindWinningMoveInCols(move& winning_move, ttt_board board, int my_letter);
	static int FindWinningMoveInDiagonals(move& winning_move, ttt_board board, int my_letter);
	static int FindWinningMove(move& winning_move, ttt_board board, int my_letter);
	move FindWinOrMakeRandomMove(ttt_board board) const;
	move FindWinOrPreventLossOrMakeRandomMove(ttt_board board) const;
	int MinMaxScore(move& last_move, ttt_board board, int last_letter);
	int MinMaxMove(ttt_board board, int my_letter);
	static AI* CreatePlayer(const char* name);
};