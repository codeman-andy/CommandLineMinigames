#pragma once

class Player {
public:
	const char* m_name;
	Player();
	Player(const char* const& name);

	const char* GetName() const;

	static Player* CreatePlayer(const char* name);
};