#pragma once

enum state : size_t { WINNER_FOUND, RUNNING };

struct Game {
	static state STATE;
	Game();
	virtual void PrintVictoryMessage() = 0;
	static void PrintWelcomeMessage();
};