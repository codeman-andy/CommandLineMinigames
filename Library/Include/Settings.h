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

enum State { RUNNING, FINISHED, DRAW };

/*
 * Flag for when the Active and Opponent Game-struct-members are uninitialized.
 */

#define UNASSIGNED 3



/*
 * The possible numerical values for each position on the TicTacToe and Battleship boards.
 */

enum Letter { UNOCCUPIED, X, O };



/*
 * AI-Difficulty levels.
 * 
 * EASY :
 *   TicTacToe : The AI will make a winning Move, otherwise a random Move
 * MEDIUM :
 *   TicTacToe : The AI will make a winning Move, otherwise prevent the opponent to win, otherwise a random Move
 * EXPERT :
 *   TicTacToe : The AI applies a minmax-algorithm to choose its next Move
 *               (if there are no good moves left, it will prevent the opponent to win or otherwise make a random Move)
 * 
 */

enum Difficulty { EASY = 1, MEDIUM, EXPERT };



/*
 * Parameter for the game mode.
 * 
 * PvP   : Player vs. Player
 * Other : Player vs. AI
 * 
 */

#define PvP 1



/*
 * Flags for an user-input Move.
 * 
 * INVALID_COORDINATE : The user typed-in a value outside of the of the possible range of coordinates
 * INVALID_MOVE       : The user tried to make a Move to a position that is currently unavailable
 * VALIDATED		  : The provided input passed all checks
 * TURN_END			  : The turn ended successfully
 * 
 */

#define INVALID_COORDINATE 0
#define INVALID_MOVE 0
#define INVALID_PLACEMENT 0
#define VALID 1
#define TURN_END 1



/*
 * Flag for when the game has reached a terminal State.
 */

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
 * TicTacToe-parameters for which lane to check in for a possible recent winning Move.
 */

#define InRow 0
#define InCol 1
#define InDiagLeft 2
#define InDiagRight 3



/*
 * AI-flag for when it has found a winning Move.
 */

#define WINNER_FOUND 1
#define NOT_FOUND 0





 /*
  * * * * * * * * * * * * * * * * * *
   * * * * * Battleship * * * * * * *
  * * * * * * * * * * * * * * * * * *
  */


/*
 * The five different vessels in a Battleship game board.
 */

enum VesselType { CARRIER, BATTLESHIP, DESTROYER, SUBMARINE, PATROL_BOAT };



/*
 * Flags for the outcome of a Move.
 */

#define MISS 0
#define HIT 1
#define VESSEL_SURVIVED 0
#define VESSEL_DESTROYED 1