#pragma once

class Player {
	const char* m_name;
public:
	Player(const char* name);

	const char* GetName() const;
};