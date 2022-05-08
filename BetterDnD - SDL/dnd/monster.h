#pragma once

#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

typedef unsigned int uint32;

#include "playerFuncs.h"

bool replace(std::string& str, const std::string& from, const std::string& to) {
	size_t start_pos = str.find(from);
	if (start_pos == std::string::npos)
		return false;
	str.replace(start_pos, from.length(), to);
	return true;
}
std::vector<std::string> split(std::string str, std::string token) {
	std::vector<std::string>result;
	while (str.size()) {
		int index = str.find(token);
		if (index != std::string::npos) {
			result.push_back(str.substr(0, index));
			str = str.substr(index + token.size());
			if (str.size() == 0)result.push_back(str);
		}
		else {
			result.push_back(str);
			str = "";
		}
	}
	return result;
}

namespace Monsters
{

	class Monster
	{
	private:
		std::vector<int> m_PlayersXp;
	public:
		Monster(bool autoGenHP);
		Monster(std::string name, int AC, std::string HP, int speed, int strength,
			int dexterity,
			int constitution,
			int intelligence,
			int wisdom,
			int charisma,
			std::string vulnerabilities,
			std::string resistances,
			std::string immunities,
			std::string feats,
			std::string actions,
			std::string lactions,
			std::string reactions,
			float cr)
			: m_MonsterName(name), m_ArmorClass(AC), m_HPstring(HP), m_Speed(speed), m_Strength(strength), m_Dexterity(dexterity), m_Constitution(constitution), m_Intelligence(intelligence), m_Wisdom(wisdom), m_Charisma(charisma), m_CR(cr)
		{
			if (vulnerabilities != "none") { m_Vulnerabilities = split(vulnerabilities, ","); }
			if (immunities != "none") { m_Immunities = split(immunities, ","); }
			if (feats != "none") { m_Feats = split(feats, ","); }
			if (actions != "none") { m_Actions = split(actions, ","); }
			if (lactions != "none") { m_Lactions = split(lactions, ","); }
			if (resistances != "none") { m_Resistance = split(resistances, ","); }
			if (reactions != "none") { m_Reactions = split(reactions, ","); }

			m_HitPoints = monsterDieTransfromer(m_HPstring, true);

			m_StrengthBonus = StatsTransform(m_Strength);
			m_DexterityBonus = StatsTransform(m_Dexterity);
			m_ConstitutionBonus = StatsTransform(m_Constitution);
			m_IntelligenceBonus = StatsTransform(m_Intelligence);
			m_WisdomBonus = StatsTransform(m_Wisdom);
			m_CharismaBonus = StatsTransform(m_Charisma);

			xMap = yMap = 575;
			invisible = false;
			m_PassivePerception = 10 + m_Perception;
		}

		std::string m_MonsterName;
		int m_PassivePerception;
		//misc
		bool invisible;
		int m_ArmorClass;
		float m_CR;
		int m_HitPoints;
		std::string m_HPstring;
		int m_Speed;

		//stats
		int m_Strength;
		int m_Dexterity;
		int m_Constitution;
		int m_Intelligence;
		int m_Wisdom;
		int m_Charisma;

		//modifiers
		int m_StrengthBonus;
		int m_DexterityBonus;
		int m_ConstitutionBonus;
		int m_IntelligenceBonus;
		int m_WisdomBonus;
		int m_CharismaBonus;

		//skills
		uint32 m_Acrobatics;
		uint32 m_AnimalHandling;
		uint32 m_Arcana;
		uint32 m_Athletics;
		uint32 m_Deception;
		uint32 m_History;
		uint32 m_Insight;
		uint32 m_Intimidation;
		uint32 m_Investigation;
		uint32 m_Medicine;
		uint32 m_Nature;
		uint32 m_Perception;
		uint32 m_Performance;
		uint32 m_Persuasion;
		uint32 m_Religion;
		uint32 m_SleightOfHand;
		uint32 m_Stealth;
		uint32 m_Survival;

		std::vector<std::string> m_Vulnerabilities;
		std::vector<std::string> m_Immunities;
		std::vector<std::string> m_Feats;
		std::vector<std::string> m_Actions;
		std::vector<std::string> m_Lactions;
		std::vector<std::string> m_Resistance;
		std::vector<std::string> m_Reactions;

		bool advantageAttacking;
		bool advantageAttacked;//advantage on attacker
		bool advantageAbilityCheck;

		bool disadvantageAttacking;
		bool disadvantageAttacked;//disadvantage on attacker
		bool disadvantageAbilityCheck;

		float xMap, yMap;

		//todo reactions
	};

	std::vector<Monster> loadMonsters()
	{
		std::vector<Monster> monsters;

		int i2;
		int i4;
		int i5;
		int i6;
		int i7;
		int i8;
		int i9;
		int i10;
		std::string line1;
		std::string line2;
		std::string line3;
		std::string line4;
		std::string line5;
		std::string line6;
		std::string line7;
		std::string line8;
		std::string line9;
		std::string line10;
		std::string line11 = "none";
		std::string line12 = "none";
		std::string line13 = "none";
		std::string line14 = "none";
		std::string line15 = "none";
		std::string line16 = "none";
		std::string line17 = "none";

		//cr 0
		for (int i = 1; i <= 30; i++)
		{
			std::ifstream infile;
			infile.open("database/Monsters/cr0-" + std::to_string(i) + ".database");
			std::getline(infile, line1);
			std::getline(infile, line2);
			replace(line2, "AC-", "");

			std::getline(infile, line3);
			replace(line3, "HP-", "");

			std::getline(infile, line4);
			replace(line4, "SPEED-", "");
			std::getline(infile, line5);
			std::getline(infile, line6);
			std::getline(infile, line7);
			std::getline(infile, line8);
			std::getline(infile, line9);
			std::getline(infile, line10);

			if (std::getline(infile, line11))
			{
				replace(line11, "vulnerabilities-", "");
			}
			if (std::getline(infile, line12))
			{
				replace(line12, "resistences-", "");
			}
			if (std::getline(infile, line13))
			{
				replace(line13, "immunities-", "");
			}
			if (std::getline(infile, line14))
			{
				replace(line14, "feats-", "");
			}
			if (std::getline(infile, line15))
			{
				replace(line15, "actions-", "");
			}
			if (std::getline(infile, line16))
			{
				replace(line16, "lactions-", "");
			}
			if (std::getline(infile, line17))
			{
				replace(line17, "reactions-", "");
			}
			std::istringstream ss2(line2);
			ss2 >> i2;
			std::istringstream ss4(line4);
			ss4 >> i4;
			std::istringstream ss5(line5);
			ss5 >> i5;
			std::istringstream ss6(line6);
			ss6 >> i6;
			std::istringstream ss7(line7);
			ss7 >> i7;
			std::istringstream ss8(line8);
			ss8 >> i8;
			std::istringstream ss9(line9);
			ss9 >> i9;
			std::istringstream ss10(line10);
			ss10 >> i10;

			monsters.push_back(Monster(line1, i2, line3, i4, i5, i6, i7, i8, i9, i10, line11, line12, line13, line14, line15, line16, line17, 0));

			infile.close();
			line11 = "none";
			line12 = "none";
			line13 = "none";
			line14 = "none";
			line15 = "none";
			line16 = "none";
			line17 = "none";
		}
		//cr 1.2
		for (int i = 1; i <= 28; i++)
		{
			std::ifstream infile;
			infile.open("database/Monsters/cr1.2-" + std::to_string(i) + ".database");
			std::getline(infile, line1);
			std::getline(infile, line2);
			replace(line2, "AC-", "");

			std::getline(infile, line3);
			replace(line3, "HP-", "");

			std::getline(infile, line4);
			replace(line4, "SPEED-", "");
			std::getline(infile, line5);
			std::getline(infile, line6);
			std::getline(infile, line7);
			std::getline(infile, line8);
			std::getline(infile, line9);
			std::getline(infile, line10);

			if (std::getline(infile, line11))
			{
				replace(line11, "vulnerabilities-", "");
			}
			if (std::getline(infile, line12))
			{
				replace(line12, "resistences-", "");
			}
			if (std::getline(infile, line13))
			{
				replace(line13, "immunities-", "");
			}
			if (std::getline(infile, line14))
			{
				replace(line14, "feats-", "");
			}
			if (std::getline(infile, line15))
			{
				replace(line15, "actions-", "");
			}
			if (std::getline(infile, line16))
			{
				replace(line16, "lactions-", "");
			}
			if (std::getline(infile, line17))
			{
				replace(line17, "reactions-", "");
			}
			std::istringstream ss2(line2);
			ss2 >> i2;
			std::istringstream ss4(line4);
			ss4 >> i4;
			std::istringstream ss5(line5);
			ss5 >> i5;
			std::istringstream ss6(line6);
			ss6 >> i6;
			std::istringstream ss7(line7);
			ss7 >> i7;
			std::istringstream ss8(line8);
			ss8 >> i8;
			std::istringstream ss9(line9);
			ss9 >> i9;
			std::istringstream ss10(line10);
			ss10 >> i10;

			monsters.push_back(Monster(line1, i2, line3, i4, i5, i6, i7, i8, i9, i10, line11, line12, line13, line14, line15, line16, line17, 1.2));

			infile.close();
			line11 = "none";
			line12 = "none";
			line13 = "none";
			line14 = "none";
			line15 = "none";
			line16 = "none";
			line17 = "none";
		}
		//cr 1.4
		for (int i = 1; i <= 33; i++)
		{
			std::ifstream infile;
			infile.open("database/Monsters/cr1.4-" + std::to_string(i) + ".database");
			std::getline(infile, line1);
			std::getline(infile, line2);
			replace(line2, "AC-", "");

			std::getline(infile, line3);
			replace(line3, "HP-", "");

			std::getline(infile, line4);
			replace(line4, "SPEED-", "");
			std::getline(infile, line5);
			std::getline(infile, line6);
			std::getline(infile, line7);
			std::getline(infile, line8);
			std::getline(infile, line9);
			std::getline(infile, line10);

			if (std::getline(infile, line11))
			{
				replace(line11, "vulnerabilities-", "");
			}
			if (std::getline(infile, line12))
			{
				replace(line12, "resistences-", "");
			}
			if (std::getline(infile, line13))
			{
				replace(line13, "immunities-", "");
			}
			if (std::getline(infile, line14))
			{
				replace(line14, "feats-", "");
			}
			if (std::getline(infile, line15))
			{
				replace(line15, "actions-", "");
			}
			if (std::getline(infile, line16))
			{
				replace(line16, "lactions-", "");
			}
			if (std::getline(infile, line17))
			{
				replace(line17, "reactions-", "");
			}
			std::istringstream ss2(line2);
			ss2 >> i2;
			std::istringstream ss4(line4);
			ss4 >> i4;
			std::istringstream ss5(line5);
			ss5 >> i5;
			std::istringstream ss6(line6);
			ss6 >> i6;
			std::istringstream ss7(line7);
			ss7 >> i7;
			std::istringstream ss8(line8);
			ss8 >> i8;
			std::istringstream ss9(line9);
			ss9 >> i9;
			std::istringstream ss10(line10);
			ss10 >> i10;

			monsters.push_back(Monster(line1, i2, line3, i4, i5, i6, i7, i8, i9, i10, line11, line12, line13, line14, line15, line16, line17, 1.4));

			infile.close();
			line11 = "none";
			line12 = "none";
			line13 = "none";
			line14 = "none";
			line15 = "none";
			line16 = "none";
			line17 = "none";
		}
		//cr 1.8
		for (int i = 1; i <= 19; i++)
		{
			std::ifstream infile;
			infile.open("database/Monsters/cr1.8-" + std::to_string(i) + ".database");
			std::getline(infile, line1);
			std::getline(infile, line2);
			replace(line2, "AC-", "");

			std::getline(infile, line3);
			replace(line3, "HP-", "");

			std::getline(infile, line4);
			replace(line4, "SPEED-", "");
			std::getline(infile, line5);
			std::getline(infile, line6);
			std::getline(infile, line7);
			std::getline(infile, line8);
			std::getline(infile, line9);
			std::getline(infile, line10);

			if (std::getline(infile, line11))
			{
				replace(line11, "vulnerabilities-", "");
			}
			if (std::getline(infile, line12))
			{
				replace(line12, "resistences-", "");
			}
			if (std::getline(infile, line13))
			{
				replace(line13, "immunities-", "");
			}
			if (std::getline(infile, line14))
			{
				replace(line14, "feats-", "");
			}
			if (std::getline(infile, line15))
			{
				replace(line15, "actions-", "");
			}
			if (std::getline(infile, line16))
			{
				replace(line16, "lactions-", "");
			}
			if (std::getline(infile, line17))
			{
				replace(line17, "reactions-", "");
			}
			std::istringstream ss2(line2);
			ss2 >> i2;
			std::istringstream ss4(line4);
			ss4 >> i4;
			std::istringstream ss5(line5);
			ss5 >> i5;
			std::istringstream ss6(line6);
			ss6 >> i6;
			std::istringstream ss7(line7);
			ss7 >> i7;
			std::istringstream ss8(line8);
			ss8 >> i8;
			std::istringstream ss9(line9);
			ss9 >> i9;
			std::istringstream ss10(line10);
			ss10 >> i10;

			monsters.push_back(Monster(line1, i2, line3, i4, i5, i6, i7, i8, i9, i10, line11, line12, line13, line14, line15, line16, line17, 1.8));

			infile.close();
			line11 = "none";
			line12 = "none";
			line13 = "none";
			line14 = "none";
			line15 = "none";
			line16 = "none";
			line17 = "none";
		}
		//cr 1
		for (int i = 1; i <= 25; i++)
		{
			std::ifstream infile;
			infile.open("database/Monsters/cr1-" + std::to_string(i) + ".database");
			std::getline(infile, line1);
			std::getline(infile, line2);
			replace(line2, "AC-", "");

			std::getline(infile, line3);
			replace(line3, "HP-", "");

			std::getline(infile, line4);
			replace(line4, "SPEED-", "");
			std::getline(infile, line5);
			std::getline(infile, line6);
			std::getline(infile, line7);
			std::getline(infile, line8);
			std::getline(infile, line9);
			std::getline(infile, line10);

			if (std::getline(infile, line11))
			{
				replace(line11, "vulnerabilities-", "");
			}
			if (std::getline(infile, line12))
			{
				replace(line12, "resistences-", "");
			}
			if (std::getline(infile, line13))
			{
				replace(line13, "immunities-", "");
			}
			if (std::getline(infile, line14))
			{
				replace(line14, "feats-", "");
			}
			if (std::getline(infile, line15))
			{
				replace(line15, "actions-", "");
			}
			if (std::getline(infile, line16))
			{
				replace(line16, "lactions-", "");
			}
			if (std::getline(infile, line17))
			{
				replace(line17, "reactions-", "");
			}
			std::istringstream ss2(line2);
			ss2 >> i2;
			std::istringstream ss4(line4);
			ss4 >> i4;
			std::istringstream ss5(line5);
			ss5 >> i5;
			std::istringstream ss6(line6);
			ss6 >> i6;
			std::istringstream ss7(line7);
			ss7 >> i7;
			std::istringstream ss8(line8);
			ss8 >> i8;
			std::istringstream ss9(line9);
			ss9 >> i9;
			std::istringstream ss10(line10);
			ss10 >> i10;

			monsters.push_back(Monster(line1, i2, line3, i4, i5, i6, i7, i8, i9, i10, line11, line12, line13, line14, line15, line16, line17, 1));

			infile.close();
			line11 = "none";
			line12 = "none";
			line13 = "none";
			line14 = "none";
			line15 = "none";
			line16 = "none";
			line17 = "none";
		}
		//cr 2
		for (int i = 1; i <= 43; i++)
		{
			std::ifstream infile;
			infile.open("database/Monsters/cr2-" + std::to_string(i) + ".database");
			std::getline(infile, line1);
			std::getline(infile, line2);
			replace(line2, "AC-", "");

			std::getline(infile, line3);
			replace(line3, "HP-", "");

			std::getline(infile, line4);
			replace(line4, "SPEED-", "");
			std::getline(infile, line5);
			std::getline(infile, line6);
			std::getline(infile, line7);
			std::getline(infile, line8);
			std::getline(infile, line9);
			std::getline(infile, line10);

			if (std::getline(infile, line11))
			{
				replace(line11, "vulnerabilities-", "");
			}
			if (std::getline(infile, line12))
			{
				replace(line12, "resistences-", "");
			}
			if (std::getline(infile, line13))
			{
				replace(line13, "immunities-", "");
			}
			if (std::getline(infile, line14))
			{
				replace(line14, "feats-", "");
			}
			if (std::getline(infile, line15))
			{
				replace(line15, "actions-", "");
			}
			if (std::getline(infile, line16))
			{
				replace(line16, "lactions-", "");
			}
			if (std::getline(infile, line17))
			{
				replace(line17, "reactions-", "");
			}
			std::istringstream ss2(line2);
			ss2 >> i2;
			std::istringstream ss4(line4);
			ss4 >> i4;
			std::istringstream ss5(line5);
			ss5 >> i5;
			std::istringstream ss6(line6);
			ss6 >> i6;
			std::istringstream ss7(line7);
			ss7 >> i7;
			std::istringstream ss8(line8);
			ss8 >> i8;
			std::istringstream ss9(line9);
			ss9 >> i9;
			std::istringstream ss10(line10);
			ss10 >> i10;

			monsters.push_back(Monster(line1, i2, line3, i4, i5, i6, i7, i8, i9, i10, line11, line12, line13, line14, line15, line16, line17, 2));

			infile.close();
			line11 = "none";
			line12 = "none";
			line13 = "none";
			line14 = "none";
			line15 = "none";
			line16 = "none";
			line17 = "none";
		}
		//cr 3
		for (int i = 1; i <= 23; i++)
		{
			std::ifstream infile;
			infile.open("database/Monsters/cr3-" + std::to_string(i) + ".database");
			std::getline(infile, line1);
			std::getline(infile, line2);
			replace(line2, "AC-", "");

			std::getline(infile, line3);
			replace(line3, "HP-", "");

			std::getline(infile, line4);
			replace(line4, "SPEED-", "");
			std::getline(infile, line5);
			std::getline(infile, line6);
			std::getline(infile, line7);
			std::getline(infile, line8);
			std::getline(infile, line9);
			std::getline(infile, line10);

			if (std::getline(infile, line11))
			{
				replace(line11, "vulnerabilities-", "");
			}
			if (std::getline(infile, line12))
			{
				replace(line12, "resistences-", "");
			}
			if (std::getline(infile, line13))
			{
				replace(line13, "immunities-", "");
			}
			if (std::getline(infile, line14))
			{
				replace(line14, "feats-", "");
			}
			if (std::getline(infile, line15))
			{
				replace(line15, "actions-", "");
			}
			if (std::getline(infile, line16))
			{
				replace(line16, "lactions-", "");
			}
			if (std::getline(infile, line17))
			{
				replace(line17, "reactions-", "");
			}
			std::istringstream ss2(line2);
			ss2 >> i2;
			std::istringstream ss4(line4);
			ss4 >> i4;
			std::istringstream ss5(line5);
			ss5 >> i5;
			std::istringstream ss6(line6);
			ss6 >> i6;
			std::istringstream ss7(line7);
			ss7 >> i7;
			std::istringstream ss8(line8);
			ss8 >> i8;
			std::istringstream ss9(line9);
			ss9 >> i9;
			std::istringstream ss10(line10);
			ss10 >> i10;

			monsters.push_back(Monster(line1, i2, line3, i4, i5, i6, i7, i8, i9, i10, line11, line12, line13, line14, line15, line16, line17, 3));

			infile.close();
			line11 = "none";
			line12 = "none";
			line13 = "none";
			line14 = "none";
			line15 = "none";
			line16 = "none";
			line17 = "none";
		}
		//cr 4
		for (int i = 1; i <= 13; i++)
		{
			std::ifstream infile;
			infile.open("database/Monsters/cr4-" + std::to_string(i) + ".database");
			std::getline(infile, line1);
			std::getline(infile, line2);
			replace(line2, "AC-", "");

			std::getline(infile, line3);
			replace(line3, "HP-", "");

			std::getline(infile, line4);
			replace(line4, "SPEED-", "");
			std::getline(infile, line5);
			std::getline(infile, line6);
			std::getline(infile, line7);
			std::getline(infile, line8);
			std::getline(infile, line9);
			std::getline(infile, line10);

			if (std::getline(infile, line11))
			{
				replace(line11, "vulnerabilities-", "");
			}
			if (std::getline(infile, line12))
			{
				replace(line12, "resistences-", "");
			}
			if (std::getline(infile, line13))
			{
				replace(line13, "immunities-", "");
			}
			if (std::getline(infile, line14))
			{
				replace(line14, "feats-", "");
			}
			if (std::getline(infile, line15))
			{
				replace(line15, "actions-", "");
			}
			if (std::getline(infile, line16))
			{
				replace(line16, "lactions-", "");
			}
			if (std::getline(infile, line17))
			{
				replace(line17, "reactions-", "");
			}
			std::istringstream ss2(line2);
			ss2 >> i2;
			std::istringstream ss4(line4);
			ss4 >> i4;
			std::istringstream ss5(line5);
			ss5 >> i5;
			std::istringstream ss6(line6);
			ss6 >> i6;
			std::istringstream ss7(line7);
			ss7 >> i7;
			std::istringstream ss8(line8);
			ss8 >> i8;
			std::istringstream ss9(line9);
			ss9 >> i9;
			std::istringstream ss10(line10);
			ss10 >> i10;

			monsters.push_back(Monster(line1, i2, line3, i4, i5, i6, i7, i8, i9, i10, line11, line12, line13, line14, line15, line16, line17, 4));

			infile.close();
			line11 = "none";
			line12 = "none";
			line13 = "none";
			line14 = "none";
			line15 = "none";
			line16 = "none";
			line17 = "none";
		}
		//cr 5
		for (int i = 1; i <= 25; i++)
		{
			std::ifstream infile;
			infile.open("database/Monsters/cr5-" + std::to_string(i) + ".database");
			std::getline(infile, line1);
			std::getline(infile, line2);
			replace(line2, "AC-", "");

			std::getline(infile, line3);
			replace(line3, "HP-", "");

			std::getline(infile, line4);
			replace(line4, "SPEED-", "");
			std::getline(infile, line5);
			std::getline(infile, line6);
			std::getline(infile, line7);
			std::getline(infile, line8);
			std::getline(infile, line9);
			std::getline(infile, line10);

			if (std::getline(infile, line11))
			{
				replace(line11, "vulnerabilities-", "");
			}
			if (std::getline(infile, line12))
			{
				replace(line12, "resistences-", "");
			}
			if (std::getline(infile, line13))
			{
				replace(line13, "immunities-", "");
			}
			if (std::getline(infile, line14))
			{
				replace(line14, "feats-", "");
			}
			if (std::getline(infile, line15))
			{
				replace(line15, "actions-", "");
			}
			if (std::getline(infile, line16))
			{
				replace(line16, "lactions-", "");
			}
			if (std::getline(infile, line17))
			{
				replace(line17, "reactions-", "");
			}
			std::istringstream ss2(line2);
			ss2 >> i2;
			std::istringstream ss4(line4);
			ss4 >> i4;
			std::istringstream ss5(line5);
			ss5 >> i5;
			std::istringstream ss6(line6);
			ss6 >> i6;
			std::istringstream ss7(line7);
			ss7 >> i7;
			std::istringstream ss8(line8);
			ss8 >> i8;
			std::istringstream ss9(line9);
			ss9 >> i9;
			std::istringstream ss10(line10);
			ss10 >> i10;

			monsters.push_back(Monster(line1, i2, line3, i4, i5, i6, i7, i8, i9, i10, line11, line12, line13, line14, line15, line16, line17, 5));

			infile.close();
			line11 = "none";
			line12 = "none";
			line13 = "none";
			line14 = "none";
			line15 = "none";
			line16 = "none";
			line17 = "none";
		}
		//cr 6
		for (int i = 1; i <= 10; i++)
		{
			std::ifstream infile;
			infile.open("database/Monsters/cr6-" + std::to_string(i) + ".database");
			std::getline(infile, line1);
			std::getline(infile, line2);
			replace(line2, "AC-", "");

			std::getline(infile, line3);
			replace(line3, "HP-", "");

			std::getline(infile, line4);
			replace(line4, "SPEED-", "");
			std::getline(infile, line5);
			std::getline(infile, line6);
			std::getline(infile, line7);
			std::getline(infile, line8);
			std::getline(infile, line9);
			std::getline(infile, line10);

			if (std::getline(infile, line11))
			{
				replace(line11, "vulnerabilities-", "");
			}
			if (std::getline(infile, line12))
			{
				replace(line12, "resistences-", "");
			}
			if (std::getline(infile, line13))
			{
				replace(line13, "immunities-", "");
			}
			if (std::getline(infile, line14))
			{
				replace(line14, "feats-", "");
			}
			if (std::getline(infile, line15))
			{
				replace(line15, "actions-", "");
			}
			if (std::getline(infile, line16))
			{
				replace(line16, "lactions-", "");
			}
			if (std::getline(infile, line17))
			{
				replace(line17, "reactions-", "");
			}
			std::istringstream ss2(line2);
			ss2 >> i2;
			std::istringstream ss4(line4);
			ss4 >> i4;
			std::istringstream ss5(line5);
			ss5 >> i5;
			std::istringstream ss6(line6);
			ss6 >> i6;
			std::istringstream ss7(line7);
			ss7 >> i7;
			std::istringstream ss8(line8);
			ss8 >> i8;
			std::istringstream ss9(line9);
			ss9 >> i9;
			std::istringstream ss10(line10);
			ss10 >> i10;

			monsters.push_back(Monster(line1, i2, line3, i4, i5, i6, i7, i8, i9, i10, line11, line12, line13, line14, line15, line16, line17, 6));

			infile.close();
			line11 = "none";
			line12 = "none";
			line13 = "none";
			line14 = "none";
			line15 = "none";
			line16 = "none";
			line17 = "none";
		}
		//cr 7
		for (int i = 1; i <= 6; i++)
		{
			std::ifstream infile;
			infile.open("database/Monsters/cr7-" + std::to_string(i) + ".database");
			std::getline(infile, line1);
			std::getline(infile, line2);
			replace(line2, "AC-", "");

			std::getline(infile, line3);
			replace(line3, "HP-", "");

			std::getline(infile, line4);
			replace(line4, "SPEED-", "");
			std::getline(infile, line5);
			std::getline(infile, line6);
			std::getline(infile, line7);
			std::getline(infile, line8);
			std::getline(infile, line9);
			std::getline(infile, line10);

			if (std::getline(infile, line11))
			{
				replace(line11, "vulnerabilities-", "");
			}
			if (std::getline(infile, line12))
			{
				replace(line12, "resistences-", "");
			}
			if (std::getline(infile, line13))
			{
				replace(line13, "immunities-", "");
			}
			if (std::getline(infile, line14))
			{
				replace(line14, "feats-", "");
			}
			if (std::getline(infile, line15))
			{
				replace(line15, "actions-", "");
			}
			if (std::getline(infile, line16))
			{
				replace(line16, "lactions-", "");
			}
			if (std::getline(infile, line17))
			{
				replace(line17, "reactions-", "");
			}
			std::istringstream ss2(line2);
			ss2 >> i2;
			std::istringstream ss4(line4);
			ss4 >> i4;
			std::istringstream ss5(line5);
			ss5 >> i5;
			std::istringstream ss6(line6);
			ss6 >> i6;
			std::istringstream ss7(line7);
			ss7 >> i7;
			std::istringstream ss8(line8);
			ss8 >> i8;
			std::istringstream ss9(line9);
			ss9 >> i9;
			std::istringstream ss10(line10);
			ss10 >> i10;

			monsters.push_back(Monster(line1, i2, line3, i4, i5, i6, i7, i8, i9, i10, line11, line12, line13, line14, line15, line16, line17, 7));

			infile.close();
			line11 = "none";
			line12 = "none";
			line13 = "none";
			line14 = "none";
			line15 = "none";
			line16 = "none";
			line17 = "none";
		}
		//cr 8
		for (int i = 1; i <= 10; i++)
		{
			std::ifstream infile;
			infile.open("database/Monsters/cr8-" + std::to_string(i) + ".database");
			std::getline(infile, line1);
			std::getline(infile, line2);
			replace(line2, "AC-", "");

			std::getline(infile, line3);
			replace(line3, "HP-", "");

			std::getline(infile, line4);
			replace(line4, "SPEED-", "");
			std::getline(infile, line5);
			std::getline(infile, line6);
			std::getline(infile, line7);
			std::getline(infile, line8);
			std::getline(infile, line9);
			std::getline(infile, line10);

			if (std::getline(infile, line11))
			{
				replace(line11, "vulnerabilities-", "");
			}
			if (std::getline(infile, line12))
			{
				replace(line12, "resistences-", "");
			}
			if (std::getline(infile, line13))
			{
				replace(line13, "immunities-", "");
			}
			if (std::getline(infile, line14))
			{
				replace(line14, "feats-", "");
			}
			if (std::getline(infile, line15))
			{
				replace(line15, "actions-", "");
			}
			if (std::getline(infile, line16))
			{
				replace(line16, "lactions-", "");
			}
			if (std::getline(infile, line17))
			{
				replace(line17, "reactions-", "");
			}
			std::istringstream ss2(line2);
			ss2 >> i2;
			std::istringstream ss4(line4);
			ss4 >> i4;
			std::istringstream ss5(line5);
			ss5 >> i5;
			std::istringstream ss6(line6);
			ss6 >> i6;
			std::istringstream ss7(line7);
			ss7 >> i7;
			std::istringstream ss8(line8);
			ss8 >> i8;
			std::istringstream ss9(line9);
			ss9 >> i9;
			std::istringstream ss10(line10);
			ss10 >> i10;

			monsters.push_back(Monster(line1, i2, line3, i4, i5, i6, i7, i8, i9, i10, line11, line12, line13, line14, line15, line16, line17, 8));

			infile.close();
			line11 = "none";
			line12 = "none";
			line13 = "none";
			line14 = "none";
			line15 = "none";
			line16 = "none";
			line17 = "none";
		}
		//cr 9
		for (int i = 1; i <= 8; i++)
		{
			std::ifstream infile;
			infile.open("database/Monsters/cr9-" + std::to_string(i) + ".database");
			std::getline(infile, line1);
			std::getline(infile, line2);
			replace(line2, "AC-", "");

			std::getline(infile, line3);
			replace(line3, "HP-", "");

			std::getline(infile, line4);
			replace(line4, "SPEED-", "");
			std::getline(infile, line5);
			std::getline(infile, line6);
			std::getline(infile, line7);
			std::getline(infile, line8);
			std::getline(infile, line9);
			std::getline(infile, line10);

			if (std::getline(infile, line11))
			{
				replace(line11, "vulnerabilities-", "");
			}
			if (std::getline(infile, line12))
			{
				replace(line12, "resistences-", "");
			}
			if (std::getline(infile, line13))
			{
				replace(line13, "immunities-", "");
			}
			if (std::getline(infile, line14))
			{
				replace(line14, "feats-", "");
			}
			if (std::getline(infile, line15))
			{
				replace(line15, "actions-", "");
			}
			if (std::getline(infile, line16))
			{
				replace(line16, "lactions-", "");
			}
			if (std::getline(infile, line17))
			{
				replace(line17, "reactions-", "");
			}
			std::istringstream ss2(line2);
			ss2 >> i2;
			std::istringstream ss4(line4);
			ss4 >> i4;
			std::istringstream ss5(line5);
			ss5 >> i5;
			std::istringstream ss6(line6);
			ss6 >> i6;
			std::istringstream ss7(line7);
			ss7 >> i7;
			std::istringstream ss8(line8);
			ss8 >> i8;
			std::istringstream ss9(line9);
			ss9 >> i9;
			std::istringstream ss10(line10);
			ss10 >> i10;

			monsters.push_back(Monster(line1, i2, line3, i4, i5, i6, i7, i8, i9, i10, line11, line12, line13, line14, line15, line16, line17, 9));

			infile.close();
			line11 = "none";
			line12 = "none";
			line13 = "none";
			line14 = "none";
			line15 = "none";
			line16 = "none";
			line17 = "none";
		}
		//cr 10
		for (int i = 1; i <= 6; i++)
		{
			std::ifstream infile;
			infile.open("database/Monsters/cr10-" + std::to_string(i) + ".database");
			std::getline(infile, line1);
			std::getline(infile, line2);
			replace(line2, "AC-", "");

			std::getline(infile, line3);
			replace(line3, "HP-", "");

			std::getline(infile, line4);
			replace(line4, "SPEED-", "");
			std::getline(infile, line5);
			std::getline(infile, line6);
			std::getline(infile, line7);
			std::getline(infile, line8);
			std::getline(infile, line9);
			std::getline(infile, line10);

			if (std::getline(infile, line11))
			{
				replace(line11, "vulnerabilities-", "");
			}
			if (std::getline(infile, line12))
			{
				replace(line12, "resistences-", "");
			}
			if (std::getline(infile, line13))
			{
				replace(line13, "immunities-", "");
			}
			if (std::getline(infile, line14))
			{
				replace(line14, "feats-", "");
			}
			if (std::getline(infile, line15))
			{
				replace(line15, "actions-", "");
			}
			if (std::getline(infile, line16))
			{
				replace(line16, "lactions-", "");
			}
			if (std::getline(infile, line17))
			{
				replace(line17, "reactions-", "");
			}
			std::istringstream ss2(line2);
			ss2 >> i2;
			std::istringstream ss4(line4);
			ss4 >> i4;
			std::istringstream ss5(line5);
			ss5 >> i5;
			std::istringstream ss6(line6);
			ss6 >> i6;
			std::istringstream ss7(line7);
			ss7 >> i7;
			std::istringstream ss8(line8);
			ss8 >> i8;
			std::istringstream ss9(line9);
			ss9 >> i9;
			std::istringstream ss10(line10);
			ss10 >> i10;

			monsters.push_back(Monster(line1, i2, line3, i4, i5, i6, i7, i8, i9, i10, line11, line12, line13, line14, line15, line16, line17, 10));

			infile.close();
			line11 = "none";
			line12 = "none";
			line13 = "none";
			line14 = "none";
			line15 = "none";
			line16 = "none";
			line17 = "none";
		}
		//cr 11
		for (int i = 1; i <= 7; i++)
		{
			std::ifstream infile;
			infile.open("database/Monsters/c11-" + std::to_string(i) + ".database");
			std::getline(infile, line1);
			std::getline(infile, line2);
			replace(line2, "AC-", "");

			std::getline(infile, line3);
			replace(line3, "HP-", "");

			std::getline(infile, line4);
			replace(line4, "SPEED-", "");
			std::getline(infile, line5);
			std::getline(infile, line6);
			std::getline(infile, line7);
			std::getline(infile, line8);
			std::getline(infile, line9);
			std::getline(infile, line10);

			if (std::getline(infile, line11))
			{
				replace(line11, "vulnerabilities-", "");
			}
			if (std::getline(infile, line12))
			{
				replace(line12, "resistences-", "");
			}
			if (std::getline(infile, line13))
			{
				replace(line13, "immunities-", "");
			}
			if (std::getline(infile, line14))
			{
				replace(line14, "feats-", "");
			}
			if (std::getline(infile, line15))
			{
				replace(line15, "actions-", "");
			}
			if (std::getline(infile, line16))
			{
				replace(line16, "lactions-", "");
			}
			if (std::getline(infile, line17))
			{
				replace(line17, "reactions-", "");
			}
			std::istringstream ss2(line2);
			ss2 >> i2;
			std::istringstream ss4(line4);
			ss4 >> i4;
			std::istringstream ss5(line5);
			ss5 >> i5;
			std::istringstream ss6(line6);
			ss6 >> i6;
			std::istringstream ss7(line7);
			ss7 >> i7;
			std::istringstream ss8(line8);
			ss8 >> i8;
			std::istringstream ss9(line9);
			ss9 >> i9;
			std::istringstream ss10(line10);
			ss10 >> i10;

			monsters.push_back(Monster(line1, i2, line3, i4, i5, i6, i7, i8, i9, i10, line11, line12, line13, line14, line15, line16, line17, 11));

			infile.close();
			line11 = "none";
			line12 = "none";
			line13 = "none";
			line14 = "none";
			line15 = "none";
			line16 = "none";
			line17 = "none";
		}
		//cr 12
		for (int i = 1; i <= 2; i++)
		{
			std::ifstream infile;
			infile.open("database/Monsters/cr12-" + std::to_string(i) + ".database");
			std::getline(infile, line1);
			std::getline(infile, line2);
			replace(line2, "AC-", "");

			std::getline(infile, line3);
			replace(line3, "HP-", "");

			std::getline(infile, line4);
			replace(line4, "SPEED-", "");
			std::getline(infile, line5);
			std::getline(infile, line6);
			std::getline(infile, line7);
			std::getline(infile, line8);
			std::getline(infile, line9);
			std::getline(infile, line10);

			if (std::getline(infile, line11))
			{
				replace(line11, "vulnerabilities-", "");
			}
			if (std::getline(infile, line12))
			{
				replace(line12, "resistences-", "");
			}
			if (std::getline(infile, line13))
			{
				replace(line13, "immunities-", "");
			}
			if (std::getline(infile, line14))
			{
				replace(line14, "feats-", "");
			}
			if (std::getline(infile, line15))
			{
				replace(line15, "actions-", "");
			}
			if (std::getline(infile, line16))
			{
				replace(line16, "lactions-", "");
			}
			if (std::getline(infile, line17))
			{
				replace(line17, "reactions-", "");
			}
			std::istringstream ss2(line2);
			ss2 >> i2;
			std::istringstream ss4(line4);
			ss4 >> i4;
			std::istringstream ss5(line5);
			ss5 >> i5;
			std::istringstream ss6(line6);
			ss6 >> i6;
			std::istringstream ss7(line7);
			ss7 >> i7;
			std::istringstream ss8(line8);
			ss8 >> i8;
			std::istringstream ss9(line9);
			ss9 >> i9;
			std::istringstream ss10(line10);
			ss10 >> i10;

			monsters.push_back(Monster(line1, i2, line3, i4, i5, i6, i7, i8, i9, i10, line11, line12, line13, line14, line15, line16, line17, 12));

			infile.close();
			line11 = "none";
			line12 = "none";
			line13 = "none";
			line14 = "none";
			line15 = "none";
			line16 = "none";
			line17 = "none";
		}
		//cr 13
		for (int i = 1; i <= 6; i++)
		{
			std::ifstream infile;
			infile.open("database/Monsters/cr13-" + std::to_string(i) + ".database");
			std::getline(infile, line1);
			std::getline(infile, line2);
			replace(line2, "AC-", "");

			std::getline(infile, line3);
			replace(line3, "HP-", "");

			std::getline(infile, line4);
			replace(line4, "SPEED-", "");
			std::getline(infile, line5);
			std::getline(infile, line6);
			std::getline(infile, line7);
			std::getline(infile, line8);
			std::getline(infile, line9);
			std::getline(infile, line10);

			if (std::getline(infile, line11))
			{
				replace(line11, "vulnerabilities-", "");
			}
			if (std::getline(infile, line12))
			{
				replace(line12, "resistences-", "");
			}
			if (std::getline(infile, line13))
			{
				replace(line13, "immunities-", "");
			}
			if (std::getline(infile, line14))
			{
				replace(line14, "feats-", "");
			}
			if (std::getline(infile, line15))
			{
				replace(line15, "actions-", "");
			}
			if (std::getline(infile, line16))
			{
				replace(line16, "lactions-", "");
			}
			if (std::getline(infile, line17))
			{
				replace(line17, "reactions-", "");
			}
			std::istringstream ss2(line2);
			ss2 >> i2;
			std::istringstream ss4(line4);
			ss4 >> i4;
			std::istringstream ss5(line5);
			ss5 >> i5;
			std::istringstream ss6(line6);
			ss6 >> i6;
			std::istringstream ss7(line7);
			ss7 >> i7;
			std::istringstream ss8(line8);
			ss8 >> i8;
			std::istringstream ss9(line9);
			ss9 >> i9;
			std::istringstream ss10(line10);
			ss10 >> i10;

			monsters.push_back(Monster(line1, i2, line3, i4, i5, i6, i7, i8, i9, i10, line11, line12, line13, line14, line15, line16, line17, 13));

			infile.close();
			line11 = "none";
			line12 = "none";
			line13 = "none";
			line14 = "none";
			line15 = "none";
			line16 = "none";
			line17 = "none";
		}
		//cr 14
		for (int i = 1; i <= 3; i++)
		{
			std::ifstream infile;
			infile.open("database/Monsters/cr14-" + std::to_string(i) + ".database");
			std::getline(infile, line1);
			std::getline(infile, line2);
			replace(line2, "AC-", "");

			std::getline(infile, line3);
			replace(line3, "HP-", "");

			std::getline(infile, line4);
			replace(line4, "SPEED-", "");
			std::getline(infile, line5);
			std::getline(infile, line6);
			std::getline(infile, line7);
			std::getline(infile, line8);
			std::getline(infile, line9);
			std::getline(infile, line10);

			if (std::getline(infile, line11))
			{
				replace(line11, "vulnerabilities-", "");
			}
			if (std::getline(infile, line12))
			{
				replace(line12, "resistences-", "");
			}
			if (std::getline(infile, line13))
			{
				replace(line13, "immunities-", "");
			}
			if (std::getline(infile, line14))
			{
				replace(line14, "feats-", "");
			}
			if (std::getline(infile, line15))
			{
				replace(line15, "actions-", "");
			}
			if (std::getline(infile, line16))
			{
				replace(line16, "lactions-", "");
			}
			if (std::getline(infile, line17))
			{
				replace(line17, "reactions-", "");
			}
			std::istringstream ss2(line2);
			ss2 >> i2;
			std::istringstream ss4(line4);
			ss4 >> i4;
			std::istringstream ss5(line5);
			ss5 >> i5;
			std::istringstream ss6(line6);
			ss6 >> i6;
			std::istringstream ss7(line7);
			ss7 >> i7;
			std::istringstream ss8(line8);
			ss8 >> i8;
			std::istringstream ss9(line9);
			ss9 >> i9;
			std::istringstream ss10(line10);
			ss10 >> i10;

			monsters.push_back(Monster(line1, i2, line3, i4, i5, i6, i7, i8, i9, i10, line11, line12, line13, line14, line15, line16, line17, 14));

			infile.close();
			line11 = "none";
			line12 = "none";
			line13 = "none";
			line14 = "none";
			line15 = "none";
			line16 = "none";
			line17 = "none";
		}
		//cr 15
		for (int i = 1; i <= 4; i++)
		{
			std::ifstream infile;
			infile.open("database/Monsters/cr15-" + std::to_string(i) + ".database");
			std::getline(infile, line1);
			std::getline(infile, line2);
			replace(line2, "AC-", "");

			std::getline(infile, line3);
			replace(line3, "HP-", "");

			std::getline(infile, line4);
			replace(line4, "SPEED-", "");
			std::getline(infile, line5);
			std::getline(infile, line6);
			std::getline(infile, line7);
			std::getline(infile, line8);
			std::getline(infile, line9);
			std::getline(infile, line10);

			if (std::getline(infile, line11))
			{
				replace(line11, "vulnerabilities-", "");
			}
			if (std::getline(infile, line12))
			{
				replace(line12, "resistences-", "");
			}
			if (std::getline(infile, line13))
			{
				replace(line13, "immunities-", "");
			}
			if (std::getline(infile, line14))
			{
				replace(line14, "feats-", "");
			}
			if (std::getline(infile, line15))
			{
				replace(line15, "actions-", "");
			}
			if (std::getline(infile, line16))
			{
				replace(line16, "lactions-", "");
			}
			if (std::getline(infile, line17))
			{
				replace(line17, "reactions-", "");
			}
			std::istringstream ss2(line2);
			ss2 >> i2;
			std::istringstream ss4(line4);
			ss4 >> i4;
			std::istringstream ss5(line5);
			ss5 >> i5;
			std::istringstream ss6(line6);
			ss6 >> i6;
			std::istringstream ss7(line7);
			ss7 >> i7;
			std::istringstream ss8(line8);
			ss8 >> i8;
			std::istringstream ss9(line9);
			ss9 >> i9;
			std::istringstream ss10(line10);
			ss10 >> i10;

			monsters.push_back(Monster(line1, i2, line3, i4, i5, i6, i7, i8, i9, i10, line11, line12, line13, line14, line15, line16, line17, 15));

			infile.close();
			line11 = "none";
			line12 = "none";
			line13 = "none";
			line14 = "none";
			line15 = "none";
			line16 = "none";
			line17 = "none";
		}
		//cr 16
		for (int i = 1; i <= 5; i++)
		{
			std::ifstream infile;
			infile.open("database/Monsters/cr16-" + std::to_string(i) + ".database");
			std::getline(infile, line1);
			std::getline(infile, line2);
			replace(line2, "AC-", "");

			std::getline(infile, line3);
			replace(line3, "HP-", "");

			std::getline(infile, line4);
			replace(line4, "SPEED-", "");
			std::getline(infile, line5);
			std::getline(infile, line6);
			std::getline(infile, line7);
			std::getline(infile, line8);
			std::getline(infile, line9);
			std::getline(infile, line10);

			if (std::getline(infile, line11))
			{
				replace(line11, "vulnerabilities-", "");
			}
			if (std::getline(infile, line12))
			{
				replace(line12, "resistences-", "");
			}
			if (std::getline(infile, line13))
			{
				replace(line13, "immunities-", "");
			}
			if (std::getline(infile, line14))
			{
				replace(line14, "feats-", "");
			}
			if (std::getline(infile, line15))
			{
				replace(line15, "actions-", "");
			}
			if (std::getline(infile, line16))
			{
				replace(line16, "lactions-", "");
			}
			if (std::getline(infile, line17))
			{
				replace(line17, "reactions-", "");
			}
			std::istringstream ss2(line2);
			ss2 >> i2;
			std::istringstream ss4(line4);
			ss4 >> i4;
			std::istringstream ss5(line5);
			ss5 >> i5;
			std::istringstream ss6(line6);
			ss6 >> i6;
			std::istringstream ss7(line7);
			ss7 >> i7;
			std::istringstream ss8(line8);
			ss8 >> i8;
			std::istringstream ss9(line9);
			ss9 >> i9;
			std::istringstream ss10(line10);
			ss10 >> i10;

			monsters.push_back(Monster(line1, i2, line3, i4, i5, i6, i7, i8, i9, i10, line11, line12, line13, line14, line15, line16, line17, 16));

			infile.close();
			line11 = "none";
			line12 = "none";
			line13 = "none";
			line14 = "none";
			line15 = "none";
			line16 = "none";
			line17 = "none";
		}
		//cr 17
		for (int i = 1; i <= 4; i++)
		{
			std::ifstream infile;
			infile.open("database/Monsters/cr17-" + std::to_string(i) + ".database");
			std::getline(infile, line1);
			std::getline(infile, line2);
			replace(line2, "AC-", "");

			std::getline(infile, line3);
			replace(line3, "HP-", "");

			std::getline(infile, line4);
			replace(line4, "SPEED-", "");
			std::getline(infile, line5);
			std::getline(infile, line6);
			std::getline(infile, line7);
			std::getline(infile, line8);
			std::getline(infile, line9);
			std::getline(infile, line10);

			if (std::getline(infile, line11))
			{
				replace(line11, "vulnerabilities-", "");
			}
			if (std::getline(infile, line12))
			{
				replace(line12, "resistences-", "");
			}
			if (std::getline(infile, line13))
			{
				replace(line13, "immunities-", "");
			}
			if (std::getline(infile, line14))
			{
				replace(line14, "feats-", "");
			}
			if (std::getline(infile, line15))
			{
				replace(line15, "actions-", "");
			}
			if (std::getline(infile, line16))
			{
				replace(line16, "lactions-", "");
			}
			if (std::getline(infile, line17))
			{
				replace(line17, "reactions-", "");
			}
			std::istringstream ss2(line2);
			ss2 >> i2;
			std::istringstream ss4(line4);
			ss4 >> i4;
			std::istringstream ss5(line5);
			ss5 >> i5;
			std::istringstream ss6(line6);
			ss6 >> i6;
			std::istringstream ss7(line7);
			ss7 >> i7;
			std::istringstream ss8(line8);
			ss8 >> i8;
			std::istringstream ss9(line9);
			ss9 >> i9;
			std::istringstream ss10(line10);
			ss10 >> i10;

			monsters.push_back(Monster(line1, i2, line3, i4, i5, i6, i7, i8, i9, i10, line11, line12, line13, line14, line15, line16, line17, 17));

			infile.close();
			line11 = "none";
			line12 = "none";
			line13 = "none";
			line14 = "none";
			line15 = "none";
			line16 = "none";
			line17 = "none";
		}
		//cr 19
		for (int i = 1; i <= 1; i++)
		{
			std::ifstream infile;
			infile.open("database/Monsters/cr19-" + std::to_string(i) + ".database");
			std::getline(infile, line1);
			std::getline(infile, line2);
			replace(line2, "AC-", "");

			std::getline(infile, line3);
			replace(line3, "HP-", "");

			std::getline(infile, line4);
			replace(line4, "SPEED-", "");
			std::getline(infile, line5);
			std::getline(infile, line6);
			std::getline(infile, line7);
			std::getline(infile, line8);
			std::getline(infile, line9);
			std::getline(infile, line10);

			if (std::getline(infile, line11))
			{
				replace(line11, "vulnerabilities-", "");
			}
			if (std::getline(infile, line12))
			{
				replace(line12, "resistences-", "");
			}
			if (std::getline(infile, line13))
			{
				replace(line13, "immunities-", "");
			}
			if (std::getline(infile, line14))
			{
				replace(line14, "feats-", "");
			}
			if (std::getline(infile, line15))
			{
				replace(line15, "actions-", "");
			}
			if (std::getline(infile, line16))
			{
				replace(line16, "lactions-", "");
			}
			if (std::getline(infile, line17))
			{
				replace(line17, "reactions-", "");
			}
			std::istringstream ss2(line2);
			ss2 >> i2;
			std::istringstream ss4(line4);
			ss4 >> i4;
			std::istringstream ss5(line5);
			ss5 >> i5;
			std::istringstream ss6(line6);
			ss6 >> i6;
			std::istringstream ss7(line7);
			ss7 >> i7;
			std::istringstream ss8(line8);
			ss8 >> i8;
			std::istringstream ss9(line9);
			ss9 >> i9;
			std::istringstream ss10(line10);
			ss10 >> i10;

			monsters.push_back(Monster(line1, i2, line3, i4, i5, i6, i7, i8, i9, i10, line11, line12, line13, line14, line15, line16, line17, 19));

			infile.close();
			line11 = "none";
			line12 = "none";
			line13 = "none";
			line14 = "none";
			line15 = "none";
			line16 = "none";
			line17 = "none";
		}
		//cr 20
		for (int i = 1; i <= 3; i++)
		{
			std::ifstream infile;
			infile.open("database/Monsters/cr20-" + std::to_string(i) + ".database");
			std::getline(infile, line1);
			std::getline(infile, line2);
			replace(line2, "AC-", "");

			std::getline(infile, line3);
			replace(line3, "HP-", "");

			std::getline(infile, line4);
			replace(line4, "SPEED-", "");
			std::getline(infile, line5);
			std::getline(infile, line6);
			std::getline(infile, line7);
			std::getline(infile, line8);
			std::getline(infile, line9);
			std::getline(infile, line10);

			if (std::getline(infile, line11))
			{
				replace(line11, "vulnerabilities-", "");
			}
			if (std::getline(infile, line12))
			{
				replace(line12, "resistences-", "");
			}
			if (std::getline(infile, line13))
			{
				replace(line13, "immunities-", "");
			}
			if (std::getline(infile, line14))
			{
				replace(line14, "feats-", "");
			}
			if (std::getline(infile, line15))
			{
				replace(line15, "actions-", "");
			}
			if (std::getline(infile, line16))
			{
				replace(line16, "lactions-", "");
			}
			if (std::getline(infile, line17))
			{
				replace(line17, "reactions-", "");
			}
			std::istringstream ss2(line2);
			ss2 >> i2;
			std::istringstream ss4(line4);
			ss4 >> i4;
			std::istringstream ss5(line5);
			ss5 >> i5;
			std::istringstream ss6(line6);
			ss6 >> i6;
			std::istringstream ss7(line7);
			ss7 >> i7;
			std::istringstream ss8(line8);
			ss8 >> i8;
			std::istringstream ss9(line9);
			ss9 >> i9;
			std::istringstream ss10(line10);
			ss10 >> i10;

			monsters.push_back(Monster(line1, i2, line3, i4, i5, i6, i7, i8, i9, i10, line11, line12, line13, line14, line15, line16, line17, 20));

			infile.close();
			line11 = "none";
			line12 = "none";
			line13 = "none";
			line14 = "none";
			line15 = "none";
			line16 = "none";
			line17 = "none";
		}
		//cr 21
		for (int i = 1; i <= 4; i++)
		{
			std::ifstream infile;
			infile.open("database/Monsters/cr21-" + std::to_string(i) + ".database");
			std::getline(infile, line1);
			std::getline(infile, line2);
			replace(line2, "AC-", "");

			std::getline(infile, line3);
			replace(line3, "HP-", "");

			std::getline(infile, line4);
			replace(line4, "SPEED-", "");
			std::getline(infile, line5);
			std::getline(infile, line6);
			std::getline(infile, line7);
			std::getline(infile, line8);
			std::getline(infile, line9);
			std::getline(infile, line10);

			if (std::getline(infile, line11))
			{
				replace(line11, "vulnerabilities-", "");
			}
			if (std::getline(infile, line12))
			{
				replace(line12, "resistences-", "");
			}
			if (std::getline(infile, line13))
			{
				replace(line13, "immunities-", "");
			}
			if (std::getline(infile, line14))
			{
				replace(line14, "feats-", "");
			}
			if (std::getline(infile, line15))
			{
				replace(line15, "actions-", "");
			}
			if (std::getline(infile, line16))
			{
				replace(line16, "lactions-", "");
			}
			if (std::getline(infile, line17))
			{
				replace(line17, "reactions-", "");
			}
			std::istringstream ss2(line2);
			ss2 >> i2;
			std::istringstream ss4(line4);
			ss4 >> i4;
			std::istringstream ss5(line5);
			ss5 >> i5;
			std::istringstream ss6(line6);
			ss6 >> i6;
			std::istringstream ss7(line7);
			ss7 >> i7;
			std::istringstream ss8(line8);
			ss8 >> i8;
			std::istringstream ss9(line9);
			ss9 >> i9;
			std::istringstream ss10(line10);
			ss10 >> i10;

			monsters.push_back(Monster(line1, i2, line3, i4, i5, i6, i7, i8, i9, i10, line11, line12, line13, line14, line15, line16, line17, 21));

			infile.close();
			line11 = "none";
			line12 = "none";
			line13 = "none";
			line14 = "none";
			line15 = "none";
			line16 = "none";
			line17 = "none";
		}
		//cr 22
		for (int i = 1; i <= 4; i++)
		{
			std::ifstream infile;
			infile.open("database/Monsters/cr22-" + std::to_string(i) + ".database");
			std::getline(infile, line1);
			std::getline(infile, line2);
			replace(line2, "AC-", "");

			std::getline(infile, line3);
			replace(line3, "HP-", "");

			std::getline(infile, line4);
			replace(line4, "SPEED-", "");
			std::getline(infile, line5);
			std::getline(infile, line6);
			std::getline(infile, line7);
			std::getline(infile, line8);
			std::getline(infile, line9);
			std::getline(infile, line10);

			if (std::getline(infile, line11))
			{
				replace(line11, "vulnerabilities-", "");
			}
			if (std::getline(infile, line12))
			{
				replace(line12, "resistences-", "");
			}
			if (std::getline(infile, line13))
			{
				replace(line13, "immunities-", "");
			}
			if (std::getline(infile, line14))
			{
				replace(line14, "feats-", "");
			}
			if (std::getline(infile, line15))
			{
				replace(line15, "actions-", "");
			}
			if (std::getline(infile, line16))
			{
				replace(line16, "lactions-", "");
			}
			if (std::getline(infile, line17))
			{
				replace(line17, "reactions-", "");
			}
			std::istringstream ss2(line2);
			ss2 >> i2;
			std::istringstream ss4(line4);
			ss4 >> i4;
			std::istringstream ss5(line5);
			ss5 >> i5;
			std::istringstream ss6(line6);
			ss6 >> i6;
			std::istringstream ss7(line7);
			ss7 >> i7;
			std::istringstream ss8(line8);
			ss8 >> i8;
			std::istringstream ss9(line9);
			ss9 >> i9;
			std::istringstream ss10(line10);
			ss10 >> i10;

			monsters.push_back(Monster(line1, i2, line3, i4, i5, i6, i7, i8, i9, i10, line11, line12, line13, line14, line15, line16, line17, 22));

			infile.close();
			line11 = "none";
			line12 = "none";
			line13 = "none";
			line14 = "none";
			line15 = "none";
			line16 = "none";
			line17 = "none";
		}
		//cr 23
		for (int i = 1; i <= 3; i++)
		{
			std::ifstream infile;
			infile.open("database/Monsters/cr23-" + std::to_string(i) + ".database");
			std::getline(infile, line1);
			std::getline(infile, line2);
			replace(line2, "AC-", "");

			std::getline(infile, line3);
			replace(line3, "HP-", "");

			std::getline(infile, line4);
			replace(line4, "SPEED-", "");
			std::getline(infile, line5);
			std::getline(infile, line6);
			std::getline(infile, line7);
			std::getline(infile, line8);
			std::getline(infile, line9);
			std::getline(infile, line10);

			if (std::getline(infile, line11))
			{
				replace(line11, "vulnerabilities-", "");
			}
			if (std::getline(infile, line12))
			{
				replace(line12, "resistences-", "");
			}
			if (std::getline(infile, line13))
			{
				replace(line13, "immunities-", "");
			}
			if (std::getline(infile, line14))
			{
				replace(line14, "feats-", "");
			}
			if (std::getline(infile, line15))
			{
				replace(line15, "actions-", "");
			}
			if (std::getline(infile, line16))
			{
				replace(line16, "lactions-", "");
			}
			if (std::getline(infile, line17))
			{
				replace(line17, "reactions-", "");
			}
			std::istringstream ss2(line2);
			ss2 >> i2;
			std::istringstream ss4(line4);
			ss4 >> i4;
			std::istringstream ss5(line5);
			ss5 >> i5;
			std::istringstream ss6(line6);
			ss6 >> i6;
			std::istringstream ss7(line7);
			ss7 >> i7;
			std::istringstream ss8(line8);
			ss8 >> i8;
			std::istringstream ss9(line9);
			ss9 >> i9;
			std::istringstream ss10(line10);
			ss10 >> i10;

			monsters.push_back(Monster(line1, i2, line3, i4, i5, i6, i7, i8, i9, i10, line11, line12, line13, line14, line15, line16, line17, 23));

			infile.close();
			line11 = "none";
			line12 = "none";
			line13 = "none";
			line14 = "none";
			line15 = "none";
			line16 = "none";
			line17 = "none";
		}
		//cr 30
		for (int i = 1; i <= 1; i++)
		{
			std::ifstream infile;
			infile.open("database/Monsters/cr30-" + std::to_string(i) + ".database");
			std::getline(infile, line1);
			std::getline(infile, line2);
			replace(line2, "AC-", "");

			std::getline(infile, line3);
			replace(line3, "HP-", "");

			std::getline(infile, line4);
			replace(line4, "SPEED-", "");
			std::getline(infile, line5);
			std::getline(infile, line6);
			std::getline(infile, line7);
			std::getline(infile, line8);
			std::getline(infile, line9);
			std::getline(infile, line10);

			if (std::getline(infile, line11))
			{
				replace(line11, "vulnerabilities-", "");
			}
			if (std::getline(infile, line12))
			{
				replace(line12, "resistences-", "");
			}
			if (std::getline(infile, line13))
			{
				replace(line13, "immunities-", "");
			}
			if (std::getline(infile, line14))
			{
				replace(line14, "feats-", "");
			}
			if (std::getline(infile, line15))
			{
				replace(line15, "actions-", "");
			}
			if (std::getline(infile, line16))
			{
				replace(line16, "lactions-", "");
			}
			if (std::getline(infile, line17))
			{
				replace(line17, "reactions-", "");
			}
			std::istringstream ss2(line2);
			ss2 >> i2;
			std::istringstream ss4(line4);
			ss4 >> i4;
			std::istringstream ss5(line5);
			ss5 >> i5;
			std::istringstream ss6(line6);
			ss6 >> i6;
			std::istringstream ss7(line7);
			ss7 >> i7;
			std::istringstream ss8(line8);
			ss8 >> i8;
			std::istringstream ss9(line9);
			ss9 >> i9;
			std::istringstream ss10(line10);
			ss10 >> i10;

			monsters.push_back(Monster(line1, i2, line3, i4, i5, i6, i7, i8, i9, i10, line11, line12, line13, line14, line15, line16, line17, 30));

			infile.close();
			line11 = "none";
			line12 = "none";
			line13 = "none";
			line14 = "none";
			line15 = "none";
			line16 = "none";
			line17 = "none";
		}

		return monsters;
	}
	

}
