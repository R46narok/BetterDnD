#pragma once

#include <vector>
#include <fstream>
#include <string>
#include <iostream>

namespace Weapon
{


	struct Weapon
	{
		Weapon(std::string Name, std::string DamageType, std::string Damage, std::string AdditionalInfo)
			:m_Name(Name), m_DamageType(DamageType), m_Damage(Damage), m_AdditionalInfo(AdditionalInfo)
		{
			if (m_AdditionalInfo == "finesse")
				Finesse = true;
		}
		Weapon(std::string Name, std::string DamageType, std::string Damage)
			:m_Name(Name), m_DamageType(DamageType), m_Damage(Damage), m_AdditionalInfo("none")
		{

		}
		std::string m_Name;
		std::string m_DamageType;
		std::string m_Damage;
		std::string m_AdditionalInfo;

		bool Finesse;
	};

	std::vector<Weapon> loadWeapons()
	{
		std::vector<Weapon> weapons;
		std::string line1;
		std::string line2;
		std::string line3;
		std::string line4;
		//load simple
		for (int i = 1; i <= 16; i++)
		{
			std::ifstream infile;
			infile.open("database/Weapons/simp-" + std::to_string(i) + ".database");
			std::getline(infile, line1);
			std::getline(infile, line2);
			std::getline(infile, line3);
			if (std::getline(infile, line4))
			{
				weapons.push_back(Weapon(line1, line2, line3, line4));
			}
			else
			{
				weapons.push_back(Weapon(line1, line2, line3));
			}

			infile.close();
		}
		return weapons;
	}

}
