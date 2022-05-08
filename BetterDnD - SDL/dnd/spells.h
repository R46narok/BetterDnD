#pragma once

#include <sstream>
#include <string>
#include <vector>
#include <fstream>

bool replaceStr(std::string& str, const std::string& from, const std::string& to) {
	size_t start_pos = str.find(from);
	if (start_pos == std::string::npos)
		return false;
	str.replace(start_pos, from.length(), to);
	return true;
}
std::vector<std::string> splitStr(std::string str, std::string token) {
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

class Spell
{
public:
	Spell(std::string spellName,
	int level,
	std::string castingTime,
	std::string range,
	std::string school,
	std::string attackSave,
	std::string damage,
	std::string additionalInfo)
		: m_SpellName(spellName), m_CastingTime(castingTime), m_Range(range), m_School(school), m_AttackSave(attackSave), m_Damage(damage), m_AdditionalInfo(additionalInfo), m_Level(level)
	{

	}
	std::string m_SpellName;
	std::string m_CastingTime;
	std::string m_Range;
	std::string m_School;
	std::string m_AttackSave;
	std::string m_Damage;
	std::string m_AdditionalInfo;

	int m_Level;
private:
};

std::vector<Spell> loadSpells()
{
	std::vector<Spell> spells;
	
	std::string line1;
	std::string line2;
	std::string line3;
	std::string line4;
	std::string line5;
	std::string line6;
	std::string line7;
	std::string line8;

	for (int i = 1; i <= 19; i++)
	{
		std::fstream infile;
		infile.open("database/Spells/page1/spell-"+std::to_string(i)+".database");
		std::getline(infile, line1);

		std::getline(infile, line2);
		replaceStr(line2, "Level-", "");
		int i2;
		std::istringstream ss2(line2);
		ss2 >> i2;


		std::getline(infile, line3);
		replaceStr(line3, "CastingTime-", "");

		std::getline(infile, line4);
		replaceStr(line4, "Range/Area-", "");

		std::getline(infile, line5);
		replaceStr(line5, "School-", "");

		std::getline(infile, line6);
		replaceStr(line6, "Attack/Save-", "");

		std::getline(infile, line7);
		replaceStr(line7, "Damage-", "");

		std::getline(infile, line8);
		std::vector<std::string> vec = splitStr(line8, " ");
		line8 = "";
		for (auto& v : vec)
		{
			line8 += v + " ";
		}

		spells.push_back(Spell(line1, i2, line3, line4, line5, line6, line7, line8));
	}
	for (int i = 1; i <= 12; i++)
	{
		std::fstream infile;
		infile.open("database/Spells/page2/spell-" + std::to_string(i) + ".database");
		std::getline(infile, line1);

		std::getline(infile, line2);
		replaceStr(line2, "Level-", "");
		int i2;
		std::istringstream ss2(line2);
		ss2 >> i2;


		std::getline(infile, line3);
		replaceStr(line3, "CastingTime-", "");

		std::getline(infile, line4);
		replaceStr(line4, "Range/Area-", "");

		std::getline(infile, line5);
		replaceStr(line5, "School-", "");

		std::getline(infile, line6);
		replaceStr(line6, "Attack/Save-", "");

		std::getline(infile, line7);
		replaceStr(line7, "Damage-", "");

		std::getline(infile, line8);
		std::vector<std::string> vec = splitStr(line8, " ");
		line8 = "";
		for (auto& v : vec)
		{
			line8 += v + " ";
		}

		spells.push_back(Spell(line1, i2, line3, line4, line5, line6, line7, line8));
	}
	for (int i = 1; i <= 13; i++)
	{
		std::fstream infile;
		infile.open("database/Spells/page3/spell-" + std::to_string(i) + ".database");
		std::getline(infile, line1);

		std::getline(infile, line2);
		replaceStr(line2, "Level-", "");
		int i2;
		std::istringstream ss2(line2);
		ss2 >> i2;


		std::getline(infile, line3);
		replaceStr(line3, "CastingTime-", "");

		std::getline(infile, line4);
		replaceStr(line4, "Range/Area-", "");

		std::getline(infile, line5);
		replaceStr(line5, "School-", "");

		std::getline(infile, line6);
		replaceStr(line6, "Attack/Save-", "");

		std::getline(infile, line7);
		replaceStr(line7, "Damage-", "");

		std::getline(infile, line8);
		std::vector<std::string> vec = splitStr(line8, " ");
		line8 = "";
		for (auto& v : vec)
		{
			line8 += v + " ";
		}

		spells.push_back(Spell(line1, i2, line3, line4, line5, line6, line7, line8));
	}
	for (int i = 1; i <= 15; i++)
	{
		std::fstream infile;
		infile.open("database/Spells/page4/spell-" + std::to_string(i) + ".database");
		std::getline(infile, line1);

		std::getline(infile, line2);
		replaceStr(line2, "Level-", "");
		int i2;
		std::istringstream ss2(line2);
		ss2 >> i2;


		std::getline(infile, line3);
		replaceStr(line3, "CastingTime-", "");

		std::getline(infile, line4);
		replaceStr(line4, "Range/Area-", "");

		std::getline(infile, line5);
		replaceStr(line5, "School-", "");

		std::getline(infile, line6);
		replaceStr(line6, "Attack/Save-", "");

		std::getline(infile, line7);
		replaceStr(line7, "Damage-", "");

		std::getline(infile, line8);
		std::vector<std::string> vec = splitStr(line8, " ");
		line8 = "";
		for (auto& v : vec)
		{
			line8 += v + " ";
		}

		spells.push_back(Spell(line1, i2, line3, line4, line5, line6, line7, line8));
	}
	for (int i = 1; i <= 16; i++)
	{
		std::fstream infile;
		infile.open("database/Spells/page5/spell-" + std::to_string(i) + ".database");
		std::getline(infile, line1);

		std::getline(infile, line2);
		replaceStr(line2, "Level-", "");
		int i2;
		std::istringstream ss2(line2);
		ss2 >> i2;


		std::getline(infile, line3);
		replaceStr(line3, "CastingTime-", "");

		std::getline(infile, line4);
		replaceStr(line4, "Range/Area-", "");

		std::getline(infile, line5);
		replaceStr(line5, "School-", "");

		std::getline(infile, line6);
		replaceStr(line6, "Attack/Save-", "");

		std::getline(infile, line7);
		replaceStr(line7, "Damage-", "");

		std::getline(infile, line8);
		std::vector<std::string> vec = splitStr(line8, " ");
		line8 = "";
		for (auto& v : vec)
		{
			line8 += v + " ";
		}

		spells.push_back(Spell(line1, i2, line3, line4, line5, line6, line7, line8));
	}
	for (int i = 1; i <= 14; i++)
	{
		std::fstream infile;
		infile.open("database/Spells/page6/spell-" + std::to_string(i) + ".database");
		std::getline(infile, line1);

		std::getline(infile, line2);
		replaceStr(line2, "Level-", "");
		int i2;
		std::istringstream ss2(line2);
		ss2 >> i2;


		std::getline(infile, line3);
		replaceStr(line3, "CastingTime-", "");

		std::getline(infile, line4);
		replaceStr(line4, "Range/Area-", "");

		std::getline(infile, line5);
		replaceStr(line5, "School-", "");

		std::getline(infile, line6);
		replaceStr(line6, "Attack/Save-", "");

		std::getline(infile, line7);
		replaceStr(line7, "Damage-", "");

		std::getline(infile, line8);
		std::vector<std::string> vec = splitStr(line8, " ");
		line8 = "";
		for (auto& v : vec)
		{
			line8 += v + " ";
		}

		spells.push_back(Spell(line1, i2, line3, line4, line5, line6, line7, line8));
	}
	for (int i = 1; i <= 16; i++)
	{
		std::fstream infile;
		infile.open("database/Spells/page7/spell-" + std::to_string(i) + ".database");
		std::getline(infile, line1);

		std::getline(infile, line2);
		replaceStr(line2, "Level-", "");
		int i2;
		std::istringstream ss2(line2);
		ss2 >> i2;


		std::getline(infile, line3);
		replaceStr(line3, "CastingTime-", "");

		std::getline(infile, line4);
		replaceStr(line4, "Range/Area-", "");

		std::getline(infile, line5);
		replaceStr(line5, "School-", "");

		std::getline(infile, line6);
		replaceStr(line6, "Attack/Save-", "");

		std::getline(infile, line7);
		replaceStr(line7, "Damage-", "");

		std::getline(infile, line8);
		std::vector<std::string> vec = splitStr(line8, " ");
		line8 = "";
		for (auto& v : vec)
		{
			line8 += v + " ";
		}

		spells.push_back(Spell(line1, i2, line3, line4, line5, line6, line7, line8));
	}
	for (int i = 1; i <= 14; i++)
	{
		std::fstream infile;
		infile.open("database/Spells/page8/spell-" + std::to_string(i) + ".database");
		std::getline(infile, line1);

		std::getline(infile, line2);
		replaceStr(line2, "Level-", "");
		int i2;
		std::istringstream ss2(line2);
		ss2 >> i2;


		std::getline(infile, line3);
		replaceStr(line3, "CastingTime-", "");

		std::getline(infile, line4);
		replaceStr(line4, "Range/Area-", "");

		std::getline(infile, line5);
		replaceStr(line5, "School-", "");

		std::getline(infile, line6);
		replaceStr(line6, "Attack/Save-", "");

		std::getline(infile, line7);
		replaceStr(line7, "Damage-", "");

		std::getline(infile, line8);
		std::vector<std::string> vec = splitStr(line8, " ");
		line8 = "";
		for (auto& v : vec)
		{
			line8 += v + " ";
		}

		spells.push_back(Spell(line1, i2, line3, line4, line5, line6, line7, line8));
	}
	for (int i = 1; i <= 17; i++)
	{
		std::fstream infile;
		infile.open("database/Spells/page9/spell-" + std::to_string(i) + ".database");
		std::getline(infile, line1);

		std::getline(infile, line2);
		replaceStr(line2, "Level-", "");
		int i2;
		std::istringstream ss2(line2);
		ss2 >> i2;


		std::getline(infile, line3);
		replaceStr(line3, "CastingTime-", "");

		std::getline(infile, line4);
		replaceStr(line4, "Range/Area-", "");

		std::getline(infile, line5);
		replaceStr(line5, "School-", "");

		std::getline(infile, line6);
		replaceStr(line6, "Attack/Save-", "");

		std::getline(infile, line7);
		replaceStr(line7, "Damage-", "");

		std::getline(infile, line8);
		std::vector<std::string> vec = splitStr(line8, " ");
		line8 = "";
		for (auto& v : vec)
		{
			line8 += v + " ";
		}

		spells.push_back(Spell(line1, i2, line3, line4, line5, line6, line7, line8));
	}
	for (int i = 1; i <= 16; i++)
	{
		std::fstream infile;
		infile.open("database/Spells/page10/spell-" + std::to_string(i) + ".database");
		std::getline(infile, line1);

		std::getline(infile, line2);
		replaceStr(line2, "Level-", "");
		int i2;
		std::istringstream ss2(line2);
		ss2 >> i2;


		std::getline(infile, line3);
		replaceStr(line3, "CastingTime-", "");

		std::getline(infile, line4);
		replaceStr(line4, "Range/Area-", "");

		std::getline(infile, line5);
		replaceStr(line5, "School-", "");

		std::getline(infile, line6);
		replaceStr(line6, "Attack/Save-", "");

		std::getline(infile, line7);
		replaceStr(line7, "Damage-", "");

		std::getline(infile, line8);
		std::vector<std::string> vec = splitStr(line8, " ");
		line8 = "";
		for (auto& v : vec)
		{
			line8 += v + " ";
		}

		spells.push_back(Spell(line1, i2, line3, line4, line5, line6, line7, line8));
	}
	for (int i = 1; i <= 16; i++)
	{
		std::fstream infile;
		infile.open("database/Spells/page11/spell-" + std::to_string(i) + ".database");
		std::getline(infile, line1);

		std::getline(infile, line2);
		replaceStr(line2, "Level-", "");
		int i2;
		std::istringstream ss2(line2);
		ss2 >> i2;


		std::getline(infile, line3);
		replaceStr(line3, "CastingTime-", "");

		std::getline(infile, line4);
		replaceStr(line4, "Range/Area-", "");

		std::getline(infile, line5);
		replaceStr(line5, "School-", "");

		std::getline(infile, line6);
		replaceStr(line6, "Attack/Save-", "");

		std::getline(infile, line7);
		replaceStr(line7, "Damage-", "");

		std::getline(infile, line8);
		std::vector<std::string> vec = splitStr(line8, " ");
		line8 = "";
		for (auto& v : vec)
		{
			line8 += v + " ";
		}

		spells.push_back(Spell(line1, i2, line3, line4, line5, line6, line7, line8));
	}
	for (int i = 1; i <= 16; i++)
	{
		std::fstream infile;
		infile.open("database/Spells/page12/spell-" + std::to_string(i) + ".database");
		std::getline(infile, line1);

		std::getline(infile, line2);
		replaceStr(line2, "Level-", "");
		int i2;
		std::istringstream ss2(line2);
		ss2 >> i2;


		std::getline(infile, line3);
		replaceStr(line3, "CastingTime-", "");

		std::getline(infile, line4);
		replaceStr(line4, "Range/Area-", "");

		std::getline(infile, line5);
		replaceStr(line5, "School-", "");

		std::getline(infile, line6);
		replaceStr(line6, "Attack/Save-", "");

		std::getline(infile, line7);
		replaceStr(line7, "Damage-", "");

		std::getline(infile, line8);
		std::vector<std::string> vec = splitStr(line8, " ");
		line8 = "";
		for (auto& v : vec)
		{
			line8 += v + " ";
		}

		spells.push_back(Spell(line1, i2, line3, line4, line5, line6, line7, line8));
	}
	for (int i = 1; i <= 15; i++)
	{
		std::fstream infile;
		infile.open("database/Spells/page13/spell-" + std::to_string(i) + ".database");
		std::getline(infile, line1);

		std::getline(infile, line2);
		replaceStr(line2, "Level-", "");
		int i2;
		std::istringstream ss2(line2);
		ss2 >> i2;


		std::getline(infile, line3);
		replaceStr(line3, "CastingTime-", "");

		std::getline(infile, line4);
		replaceStr(line4, "Range/Area-", "");

		std::getline(infile, line5);
		replaceStr(line5, "School-", "");

		std::getline(infile, line6);
		replaceStr(line6, "Attack/Save-", "");

		std::getline(infile, line7);
		replaceStr(line7, "Damage-", "");

		std::getline(infile, line8);
		std::vector<std::string> vec = splitStr(line8, " ");
		line8 = "";
		for (auto& v : vec)
		{
			line8 += v + " ";
		}

		spells.push_back(Spell(line1, i2, line3, line4, line5, line6, line7, line8));
	}
	for (int i = 1; i <= 15; i++)
	{
		std::fstream infile;
		infile.open("database/Spells/page14/spell-" + std::to_string(i) + ".database");
		std::getline(infile, line1);

		std::getline(infile, line2);
		replaceStr(line2, "Level-", "");
		int i2;
		std::istringstream ss2(line2);
		ss2 >> i2;


		std::getline(infile, line3);
		replaceStr(line3, "CastingTime-", "");

		std::getline(infile, line4);
		replaceStr(line4, "Range/Area-", "");

		std::getline(infile, line5);
		replaceStr(line5, "School-", "");

		std::getline(infile, line6);
		replaceStr(line6, "Attack/Save-", "");

		std::getline(infile, line7);
		replaceStr(line7, "Damage-", "");

		std::getline(infile, line8);
		std::vector<std::string> vec = splitStr(line8, " ");
		line8 = "";
		for (auto& v : vec)
		{
			line8 += v + " ";
		}

		spells.push_back(Spell(line1, i2, line3, line4, line5, line6, line7, line8));
	}
	for (int i = 1; i <= 16; i++)
	{
		std::fstream infile;
		infile.open("database/Spells/page15/spell-" + std::to_string(i) + ".database");
		std::getline(infile, line1);

		std::getline(infile, line2);
		replaceStr(line2, "Level-", "");
		int i2;
		std::istringstream ss2(line2);
		ss2 >> i2;


		std::getline(infile, line3);
		replaceStr(line3, "CastingTime-", "");

		std::getline(infile, line4);
		replaceStr(line4, "Range/Area-", "");

		std::getline(infile, line5);
		replaceStr(line5, "School-", "");

		std::getline(infile, line6);
		replaceStr(line6, "Attack/Save-", "");

		std::getline(infile, line7);
		replaceStr(line7, "Damage-", "");

		std::getline(infile, line8);
		std::vector<std::string> vec = splitStr(line8, " ");
		line8 = "";
		for (auto& v : vec)
		{
			line8 += v + " ";
		}

		spells.push_back(Spell(line1, i2, line3, line4, line5, line6, line7, line8));
	}
	for (int i = 1; i <= 12; i++)
	{
		std::fstream infile;
		infile.open("database/Spells/page16/spell-" + std::to_string(i) + ".database");
		std::getline(infile, line1);

		std::getline(infile, line2);
		replaceStr(line2, "Level-", "");
		int i2;
		std::istringstream ss2(line2);
		ss2 >> i2;


		std::getline(infile, line3);
		replaceStr(line3, "CastingTime-", "");

		std::getline(infile, line4);
		replaceStr(line4, "Range/Area-", "");

		std::getline(infile, line5);
		replaceStr(line5, "School-", "");

		std::getline(infile, line6);
		replaceStr(line6, "Attack/Save-", "");

		std::getline(infile, line7);
		replaceStr(line7, "Damage-", "");

		std::getline(infile, line8);
		std::vector<std::string> vec = splitStr(line8, " ");
		line8 = "";
		for (auto& v : vec)
		{
			line8 += v + " ";
		}

		spells.push_back(Spell(line1, i2, line3, line4, line5, line6, line7, line8));
	}
	for (int i = 1; i <= 16; i++)
	{
		std::fstream infile;
		infile.open("database/Spells/page17/spell-" + std::to_string(i) + ".database");
		std::getline(infile, line1);

		std::getline(infile, line2);
		replaceStr(line2, "Level-", "");
		int i2;
		std::istringstream ss2(line2);
		ss2 >> i2;


		std::getline(infile, line3);
		replaceStr(line3, "CastingTime-", "");

		std::getline(infile, line4);
		replaceStr(line4, "Range/Area-", "");

		std::getline(infile, line5);
		replaceStr(line5, "School-", "");

		std::getline(infile, line6);
		replaceStr(line6, "Attack/Save-", "");

		std::getline(infile, line7);
		replaceStr(line7, "Damage-", "");

		std::getline(infile, line8);
		std::vector<std::string> vec = splitStr(line8, " ");
		line8 = "";
		for (auto& v : vec)
		{
			line8 += v + " ";
		}

		spells.push_back(Spell(line1, i2, line3, line4, line5, line6, line7, line8));
	}
	for (int i = 1; i <= 17; i++)
	{
		std::fstream infile;
		infile.open("database/Spells/page18/spell-" + std::to_string(i) + ".database");
		std::getline(infile, line1);

		std::getline(infile, line2);
		replaceStr(line2, "Level-", "");
		int i2;
		std::istringstream ss2(line2);
		ss2 >> i2;


		std::getline(infile, line3);
		replaceStr(line3, "CastingTime-", "");

		std::getline(infile, line4);
		replaceStr(line4, "Range/Area-", "");

		std::getline(infile, line5);
		replaceStr(line5, "School-", "");

		std::getline(infile, line6);
		replaceStr(line6, "Attack/Save-", "");

		std::getline(infile, line7);
		replaceStr(line7, "Damage-", "");

		std::getline(infile, line8);
		std::vector<std::string> vec = splitStr(line8, " ");
		line8 = "";
		for (auto& v : vec)
		{
			line8 += v + " ";
		}

		spells.push_back(Spell(line1, i2, line3, line4, line5, line6, line7, line8));
	}
	for (int i = 1; i <= 16; i++)
	{
		std::fstream infile;
		infile.open("database/Spells/page19/spell-" + std::to_string(i) + ".database");
		std::getline(infile, line1);

		std::getline(infile, line2);
		replaceStr(line2, "Level-", "");
		int i2;
		std::istringstream ss2(line2);
		ss2 >> i2;


		std::getline(infile, line3);
		replaceStr(line3, "CastingTime-", "");

		std::getline(infile, line4);
		replaceStr(line4, "Range/Area-", "");

		std::getline(infile, line5);
		replaceStr(line5, "School-", "");

		std::getline(infile, line6);
		replaceStr(line6, "Attack/Save-", "");

		std::getline(infile, line7);
		replaceStr(line7, "Damage-", "");

		std::getline(infile, line8);
		std::vector<std::string> vec = splitStr(line8, " ");
		line8 = "";
		for (auto& v : vec)
		{
			line8 += v + " ";
		}

		spells.push_back(Spell(line1, i2, line3, line4, line5, line6, line7, line8));
	}
	for (int i = 1; i <= 16; i++)
	{
		std::fstream infile;
		infile.open("database/Spells/page20/spell-" + std::to_string(i) + ".database");
		std::getline(infile, line1);

		std::getline(infile, line2);
		replaceStr(line2, "Level-", "");
		int i2;
		std::istringstream ss2(line2);
		ss2 >> i2;


		std::getline(infile, line3);
		replaceStr(line3, "CastingTime-", "");

		std::getline(infile, line4);
		replaceStr(line4, "Range/Area-", "");

		std::getline(infile, line5);
		replaceStr(line5, "School-", "");

		std::getline(infile, line6);
		replaceStr(line6, "Attack/Save-", "");

		std::getline(infile, line7);
		replaceStr(line7, "Damage-", "");

		std::getline(infile, line8);
		std::vector<std::string> vec = splitStr(line8, " ");
		line8 = "";
		for (auto& v : vec)
		{
			line8 += v + " ";
		}

		spells.push_back(Spell(line1, i2, line3, line4, line5, line6, line7, line8));
	}
	for (int i = 1; i <= 14; i++)
	{
		std::fstream infile;
		infile.open("database/Spells/page21/spell-" + std::to_string(i) + ".database");
		std::getline(infile, line1);

		std::getline(infile, line2);
		replaceStr(line2, "Level-", "");
		int i2;
		std::istringstream ss2(line2);
		ss2 >> i2;


		std::getline(infile, line3);
		replaceStr(line3, "CastingTime-", "");

		std::getline(infile, line4);
		replaceStr(line4, "Range/Area-", "");

		std::getline(infile, line5);
		replaceStr(line5, "School-", "");

		std::getline(infile, line6);
		replaceStr(line6, "Attack/Save-", "");

		std::getline(infile, line7);
		replaceStr(line7, "Damage-", "");

		std::getline(infile, line8);
		std::vector<std::string> vec = splitStr(line8, " ");
		line8 = "";
		for (auto& v : vec)
		{
			line8 += v + " ";
		}

		spells.push_back(Spell(line1, i2, line3, line4, line5, line6, line7, line8));
	}
	for (int i = 1; i <= 10; i++)
	{
		std::fstream infile;
		infile.open("database/Spells/page22/spell-" + std::to_string(i) + ".database");
		std::getline(infile, line1);

		std::getline(infile, line2);
		replaceStr(line2, "Level-", "");
		int i2;
		std::istringstream ss2(line2);
		ss2 >> i2;


		std::getline(infile, line3);
		replaceStr(line3, "CastingTime-", "");

		std::getline(infile, line4);
		replaceStr(line4, "Range/Area-", "");

		std::getline(infile, line5);
		replaceStr(line5, "School-", "");

		std::getline(infile, line6);
		replaceStr(line6, "Attack/Save-", "");

		std::getline(infile, line7);
		replaceStr(line7, "Damage-", "");

		std::getline(infile, line8);
		std::vector<std::string> vec = splitStr(line8, " ");
		line8 = "";
		for (auto& v : vec)
		{
			line8 += v + " ";
		}

		spells.push_back(Spell(line1, i2, line3, line4, line5, line6, line7, line8));
	}
	for (int i = 1; i <= 17; i++)
	{
		std::fstream infile;
		infile.open("database/Spells/page23/spell-" + std::to_string(i) + ".database");
		std::getline(infile, line1);

		std::getline(infile, line2);
		replaceStr(line2, "Level-", "");
		int i2;
		std::istringstream ss2(line2);
		ss2 >> i2;


		std::getline(infile, line3);
		replaceStr(line3, "CastingTime-", "");

		std::getline(infile, line4);
		replaceStr(line4, "Range/Area-", "");

		std::getline(infile, line5);
		replaceStr(line5, "School-", "");

		std::getline(infile, line6);
		replaceStr(line6, "Attack/Save-", "");

		std::getline(infile, line7);
		replaceStr(line7, "Damage-", "");

		std::getline(infile, line8);
		std::vector<std::string> vec = splitStr(line8, " ");
		line8 = "";
		for (auto& v : vec)
		{
			line8 += v + " ";
		}

		spells.push_back(Spell(line1, i2, line3, line4, line5, line6, line7, line8));
	}
	for (int i = 1; i <= 15; i++)
	{
		std::fstream infile;
		infile.open("database/Spells/page24/spell-" + std::to_string(i) + ".database");
		std::getline(infile, line1);

		std::getline(infile, line2);
		replaceStr(line2, "Level-", "");
		int i2;
		std::istringstream ss2(line2);
		ss2 >> i2;


		std::getline(infile, line3);
		replaceStr(line3, "CastingTime-", "");

		std::getline(infile, line4);
		replaceStr(line4, "Range/Area-", "");

		std::getline(infile, line5);
		replaceStr(line5, "School-", "");

		std::getline(infile, line6);
		replaceStr(line6, "Attack/Save-", "");

		std::getline(infile, line7);
		replaceStr(line7, "Damage-", "");

		std::getline(infile, line8);
		std::vector<std::string> vec = splitStr(line8, " ");
		line8 = "";
		for (auto& v : vec)
		{
			line8 += v + " ";
		}

		spells.push_back(Spell(line1, i2, line3, line4, line5, line6, line7, line8));
	}

	return spells;
}