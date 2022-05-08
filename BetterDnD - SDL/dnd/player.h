#pragma once

#include <string>
#include <vector>

#include "../ECS/TextureManager.h"

typedef unsigned int uint32;

enum Classes
{
	Barbarian,
	Bard,
	Cleric,
	Druid,
	Fighter,
	Monk,
	Paladin,
	Ranger,
	Rogue,
	Sorcerer,
	Warlock,
	Wizard
};
enum Races
{
	Dwarf,
	Elf,
	Halfling,
	Human,
	Dragonborn,
	Gnome,
	Half_Elf,
	Half_Orc,
	Tiefling
};
enum Background
{
	Acolyte,
	Criminal,
	FolkHero,
	Noble,
	Sage,
	Soldier
};

namespace Player
{
	class Player
	{
	public:
		Player() = default;
		Player(uint32 Strength, uint32 Dexterity, uint32 Constitution, uint32 Intelligence, uint32 Wisdom, uint32 Charisma, int playersClass, int playersRace, int backround, const char* alignment);
		bool checkIfProficient(std::string searchFor);
		~Player();

		int mapX;
		int mapY;

		int m_PlayerClass;
		int m_PlayerRace;
		int m_Background;
		int m_PassivePerception;

		const char* m_CharPlayerClass;
		const char* m_CharPlayerRace;
		const char* m_CharPlayerBackground;
		const char* m_CharAlignment;
		const char* m_Size;
		const char* m_SubClass;
		const char* m_SubRace;

		int m_Strength;
		int m_Dexterity;
		int m_Constitution;
		int m_Intelligence;
		int m_Wisdom;
		int m_Charisma;

		int m_StrengthBonus = 0;
		int m_DexterityBonus = 0;
		int m_ConstitutionBonus = 0;
		int m_IntelligenceBonus = 0;
		int m_WisdomBonus = 0;
		int m_CharismaBonus = 0;

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

		std::vector<std::string> m_Traits;
		std::vector<std::string> m_Weapons;
		std::vector<std::string> m_Armor;
		std::vector<std::string> m_SavingThrows;
		std::vector<std::string> m_Skill;
		std::vector<std::string> m_Feature;
		std::vector<std::string> m_Tools;
		std::vector<std::string> m_Resistances;
		std::vector<std::string> m_Immunities;
		std::vector<std::string> m_Vulnerabilities;

		uint32 m_Speed;
		uint32 m_Level = 1;
		uint32 m_ExperiencePoints = 0;
		uint32 m_ProficiencyBonus = 2;
		uint32 m_HitDice;
		uint32 m_ArmorClass;
		uint32 m_HitPoints;
		uint32 m_HitPointsCurrent;
		uint32 Successes = 0;
		uint32 Failures = 0;

		bool advantageAttacking = false;
		bool advantageAttacked = false;
		bool advantageAbilityCheck = false;

		bool disadvantageAttacking = false;
		bool disadvantageAttacked = false;
		bool disadvantageAbilityCheck = false;

		SDL_Texture *m_Representation;
		SDL_Texture *m_MapIcon;
	public:
		void update();
	};
}
