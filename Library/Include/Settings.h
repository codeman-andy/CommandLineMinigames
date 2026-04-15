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
 * FINISHED : The game ended with a victor
 * DRAW : The game ended and there was no victor
 * 
 */

enum state { RUNNING, FINISHED, DRAW };



/*
 * The possible numerical values for each position on the TicTacToe and Battleship boards.
 */

enum letter { UNOCCUPIED, X, O };



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
 * Parameter for the game mode.
 * 
 * PvP   : Player vs. Player
 * Other : Player vs. AI
 * 
 */

#define PvP 1



/*
 * Flags for an user-input move.
 * 
 * INVALID_COORDINATE : The user typed-in a value outside of the of the possible range of coordinates
 * INVALID_MOVE       : The user tried to make a move to a position that is currently unavailable
 * VALIDATED		  : The provided input passed all checks
 * 
 */

#define INVALID_COORDINATE 1
#define INVALID_MOVE 1
#define VALID 0



/*
 * Flags for the outcome of a turn.
 * 
 * TURN_END	: The turn ended with no victor
 * GAME_END : A victor was crowned during the turn
 * 
 */

#define TURN_END 0
#define GAME_END 1





/*
 * * * * * * * * * * * * * * * * *
 * * * * * * TicTacToe * * * * * *
 * * * * * * * * * * * * * * * * *
 */


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
 * TicTacToe-parameters for which lane to check in for a possible recent winning move.
 */

#define InRow 0
#define InCol 1
#define InDiagLeft 2
#define InDiagRight 3





 /*
  * * * * * * * * * * * * * * * * * *
   * * * * * Battleship * * * * * * *
  * * * * * * * * * * * * * * * * * *
  */


/*
 * The five different vessels in a Battleship game board.
 */

enum vessel_type { CARRIER, BATTLESHIP, DESTROYER, SUBMARINE, PATROL_BOAT };



/*
 * Flags for the outcome of a move.
 */

#define MISS 0
#define HIT 1