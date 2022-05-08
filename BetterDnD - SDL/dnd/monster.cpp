

/*
Monster::Monster(std::vector<Player*> players)
	:m_Players(players)
{
	for (auto& p : m_Players)
	{
		temp += p->m_ExperiencePoints;
	}

	temp = temp / m_Players.size();
	if (temp <= 10)
	{
		m_CR = 0;
		m_Monster = rand() % 1 + 1; // number of monster with CR 0
		std::ifstream file;
		file.open("database/Monsters/cr0-"+std::to_string(m_Monster)+".database");

		std::string line;
		//first line name
		std::getline(file, line);
	}
}


namespace Monsters
{

	Monster::Monster(bool autoGenHP)
	{

	}

	Monster::Monster(std::string name, int AC, std::string HP, int speed, int strength,
		int dexterity,
		int constitution,
		int intelligence,
		int wisdom,
		int charisma,
		std::string resistances,
		std::string immunities,
		std::string feats,
		std::string actions,
		std::string lactions)
		: m_MonsterName(name), m_ArmorClass(AC), m_HPstring(HP), m_Speed(speed), m_Strength(strength), m_Dexterity(dexterity), m_Constitution(constitution), m_Intelligence(intelligence), m_Wisdom(wisdom), m_Charisma(charisma)
	{
		if (immunities != "none") { m_Immunities = split(immunities, ","); }
		if (immunities != "none") { m_Feats = split(feats, ","); }
		if (immunities != "none") { m_Actions = split(actions, ","); }
		if (immunities != "none") { m_Lactions = split(lactions, ","); }
		if (immunities != "none") { m_Resistance = split(resistances, ","); }

	}

}*/