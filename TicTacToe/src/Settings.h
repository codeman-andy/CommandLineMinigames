#pragma once

/*   
   + + + + + + + + + + + + + +
   + + + GAME PARAMETERS + + +
   + + + + + + + + + + + + + +
*/


/*
 * Game states for the currently running game.
 * 
 * RUNNING : The game still has not finished
 * WINNER_FOUND : The game ended with a victor
 * DRAW : The game ended and there was no victor
 * 
 */

enum state { WINNER_FOUND, RUNNING, DRAW };



/*
 * AI-difficulty levels.
 * 
 * EASY :
 *   TicTacToe : The AI will make a winning move, otherwise a random move
 * MEDIUM :
 *   TicTacToe : The AI will make a winning move, otherwise prevent the opponent to win, otherwise a random move
 * EXPERT :
 *   TicTacToe : The AI applies a minmax-algorithm to choose its next move
 *               (if there are no good moves left, it will prevent the opponent to win or otherwise make a random move)
 * 
 */

enum difficulty { EASY = 1, MEDIUM, EXPERT };



/*
 * Parameters for the lanes on the board.
 * 
 * EMPTY : There are currently no elements in the lane
 * FULL  : There are no more available spaces in the lane
 * 
 */

#define EMPTY 0
#define FULL 3



/*
 * Parameter for the game mode.
 * 
 * PvP   : Player vs. Player
 * Other : Player vs. AI
 * 
 */

#define PvP 1



/*
 * Flags for an invalid user-input move.
 * 
 * INVALID_COORDINATE : The user typed-in a value outside of the of the possible range of coordinates
 * INVALID_MOVE       : The user tried to make a move to a position that is currently unavailable
 * 
 */

#define INVALID_COORDINATE 0
#define INVALID_MOVE 0



/*
 * TicTacToe-parameters for which lane to check for a possible recent winning move.
 */

#define CheckForRow 0
#define CheckForCol 1
#define CheckForDiagLeft 2
#define CheckForDiagRight 3



/*
 * The possible numerical values for each position on the TicTacToe board.
 */

enum letter { UNOCCUPIED, X, O };