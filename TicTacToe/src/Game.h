#pragma once

enum state { WINNER_FOUND, RUNNING, DRAW };

struct Game {
	static state STATE;
	Game();
	virtual void PrintVictoryMessage() = 0;
	static void PrintWelcomeMessage();
};