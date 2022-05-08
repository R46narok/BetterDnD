#pragma once
#include <vector>
#include <string>

#include "../dnd/player.h"

class LoggingSystem
{
public:
	std::vector<std::string> m_Log;

	void logRoll(Player::Player *player, std::string roll, int rolled)
	{
		std::string log;
		log = player->m_CharPlayerClass;
		log += "rolled " + roll + ": " + std::to_string(rolled);
		m_Log.push_back(log);
	}

private:
};