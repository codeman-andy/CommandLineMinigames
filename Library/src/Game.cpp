#include "Game.h"

state Game::STATE = RUNNING;
void (*Game::Gamemode)();
Player* Game::Players[2];
int Game::Active = UNASSIGNED;
int Game::Opponent = UNASSIGNED;

Game::Game() {};