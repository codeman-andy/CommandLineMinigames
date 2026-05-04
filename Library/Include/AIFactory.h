#pragma once

#include "PlayerFactory.h"

#include "AI.h"


class AIFactory : PlayerFactory {
public:
	Player* CreatePlayer() override
	{
		Log("Choose Difficulty:\n1. Easy  2. Medium  3. Expert\n");
		int input;
		std::cin >> input;

		Difficulty chosen_difficulty = static_cast<Difficulty>(input);
		return new AI(chosen_difficulty);
	}

	/* Destructor */
	~AIFactory() {}
};