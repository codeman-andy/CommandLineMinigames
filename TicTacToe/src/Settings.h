#pragma once

enum state { WINNER_FOUND, RUNNING, DRAW };

enum difficulty { EASY = 1, MEDIUM, EXPERT };

#define EMPTY 0
#define FULL 3

#define INVALID_COORDINATE 0
#define INVALID_MOVE 0

#define CheckForRow 0
#define CheckForCol 1
#define CheckForDiagLeft 2
#define CheckForDiagRight 3

enum letter { UNOCCUPIED, X, O };