#pragma once

/*
 * The Player-superclass that all player-variants will inherit
 * Every Player-instance must possess a name
 */
class Player {
public:
	const char* m_name;
	Player();
	Player(const char* const& name);

	const char* GetName() const;

	static Player* CreatePlayer(const char* name);
};