#include "player.h"
#include "DM.h"

#include <iostream>

namespace Player
{

Player::Player(uint32 Strength, uint32 Dexterity, uint32 Constitution, uint32 Intelligence, uint32 Wisdom, uint32 Charisma, int playersClass, int playersRace, int backround, const char* alignment)
	: m_Strength(Strength), m_Dexterity(Dexterity), m_Constitution(Constitution), m_Intelligence(Intelligence), m_Wisdom(Wisdom), m_Charisma(Charisma), m_PlayerClass(playersClass), m_PlayerRace(playersRace), m_Background(backround), m_CharAlignment(alignment)
{
	switch (m_PlayerRace)
	{

	case Races::Dwarf:
		m_Speed = 25;
		m_ConstitutionBonus++;
		m_WisdomBonus++;
		m_Traits.push_back("dwarven resilience");
		m_Traits.push_back("tool proficiency");
		m_Traits.push_back("stonecutting");
		m_Traits.push_back("dwarven toughness");
		m_CharPlayerRace = "Hill Dwarf";
		break;

	case Races::Elf:
		m_Speed = 30;
		m_DexterityBonus++;
		m_IntelligenceBonus++;
		m_Traits.push_back("keen senses");
		m_Traits.push_back("fey ancestry");
		m_Traits.push_back("trance");
		m_CharPlayerRace = "High Elf";
		break;
	case Races::Halfling:
		m_Speed = 25;
		m_DexterityBonus++;
		m_CharismaBonus++;
		m_Traits.push_back("lucky");
		m_Traits.push_back("brave");
		m_Traits.push_back("halfling nimbleness");
		m_Traits.push_back("naturally stealthy");
		m_CharPlayerRace = "Lightfoot Halfling";
		break;
	case Races::Human:
		m_Speed = 30;
		m_StrengthBonus++;
		m_DexterityBonus++;
		m_ConstitutionBonus++;
		m_IntelligenceBonus++;
		m_WisdomBonus++;
		m_CharismaBonus++;
		m_CharPlayerRace = "Human";
		break;
	case Races::Dragonborn:
		m_Speed = 30;
		m_StrengthBonus += 2;
		m_CharismaBonus++;
		m_Traits.push_back("draconic ancestry");
		m_CharPlayerRace = "Dragonborn";
		break;
	case Races::Gnome:
		m_Speed = 25;
		m_CharismaBonus++;
		m_IntelligenceBonus += 2;
		m_Traits.push_back("gnome cunning");
		m_Traits.push_back("artificer");
		m_Traits.push_back("tinker");
		m_CharPlayerRace = "Rock Gnome";
		break;
	case Races::Half_Elf:
		m_Speed = 30;
		m_Traits.push_back("fey ancestry");
		m_Traits.push_back("skill versatility");
		m_CharPlayerRace = "Half Elf";
		break;
	case Races::Half_Orc:
		m_Speed = 30;
		m_StrengthBonus += 2;
		m_ConstitutionBonus++;
		m_Traits.push_back("menacing");
		m_Traits.push_back("relentless endurance");
		m_Traits.push_back("savage attacks");
		m_CharPlayerRace = "Half Orc";
		break;
	case Races::Tiefling:
		m_Speed = 30;
		m_IntelligenceBonus++;
		m_CharismaBonus += 2;
		m_Traits.push_back("hellish resistance");
		m_CharPlayerRace = "Tiefling";
		//TO DO SPELLS
		//Spell thaumaturgy (at will)
		break;
	default:
		break;
	}
	switch (m_PlayerClass) {
	case Classes::Barbarian:
		m_Weapons.push_back("simple weapons");
		m_Weapons.push_back("martial weapons");
		m_Armor.push_back("light armor");
		m_Armor.push_back("medium armor");
		m_SavingThrows.push_back("Strength");
		m_SavingThrows.push_back("Constitution");
		m_CharPlayerClass = "Barbarian";
		m_HitDice = 12;
		m_ArmorClass = 10 + m_DexterityBonus + m_ConstitutionBonus;
		//tOdO skills
		break;
	case Classes::Bard:
		m_Weapons.push_back("simple weapons");
		m_Weapons.push_back("hand crossbow");
		m_Weapons.push_back("longsword");
		m_Weapons.push_back("shortsword");
		m_Weapons.push_back("rapier");
		m_Armor.push_back("light armor");
		m_SavingThrows.push_back("dexterity");
		m_SavingThrows.push_back("charisma");
		m_Tools.push_back("musical instrument");
		m_CharPlayerClass = "Bard";
		m_HitDice = 8;
		m_ArmorClass = 11 + m_DexterityBonus;
		//tOdO tool
		//tOdO skills
		break;
	case Classes::Cleric:
		m_Weapons.push_back("simple weapons");
		m_Armor.push_back("light armor");
		m_Armor.push_back("medium armor");
		m_Armor.push_back("shields");
		m_SavingThrows.push_back("Wisdom");
		m_SavingThrows.push_back("Charisma");
		m_CharPlayerClass = "Cleric";
		m_HitDice = 8;
		//tOdO skills
		break;
	case Classes::Druid:
		m_Weapons.push_back("club");
		m_Weapons.push_back("dagger");
		m_Weapons.push_back("dart");
		m_Weapons.push_back("javelin");
		m_Weapons.push_back("mace");
		m_Weapons.push_back("quarterstaff");
		m_Weapons.push_back("scimitar");
		m_Weapons.push_back("sickle");
		m_Weapons.push_back("sling");
		m_Weapons.push_back("spear");
		m_Armor.push_back("light armor");
		m_Armor.push_back("medium armor");
		m_Armor.push_back("shields");
		m_SavingThrows.push_back("intelligence");
		m_SavingThrows.push_back("wisdom");
		m_Tools.push_back("herbalism kit");
		m_CharPlayerClass = "Druid";
		m_HitDice = 8;
		m_ArmorClass = 11 + m_DexterityBonus;
		//tOdO skills
		break;
	case Classes::Fighter:
		m_Weapons.push_back("simple weapons");
		m_Weapons.push_back("martial weapons");
		m_Armor.push_back("all armors");
		m_Armor.push_back("shields");
		m_SavingThrows.push_back("strength");
		m_SavingThrows.push_back("constitution");
		m_CharPlayerClass = "Fighter";
		m_HitDice = 10;
		m_ArmorClass = 11 + m_DexterityBonus;
		//toododo
		//tOdO skills
		break;
	case Classes::Monk:
		m_Weapons.push_back("simple weapons");
		m_Weapons.push_back("shortsword");
		m_SavingThrows.push_back("strength");
		m_SavingThrows.push_back("dexterity");
		m_Tools.push_back("artisans tools");
		m_CharPlayerClass = "Monk";
		m_HitDice = 8;
		m_ArmorClass = 10 + m_DexterityBonus + m_WisdomBonus;
		//tOdO skills
		break;
	case Classes::Paladin:
		m_Weapons.push_back("simple weapons");
		m_Weapons.push_back("martial weapons");
		m_Armor.push_back("all armor");
		m_Armor.push_back("shields");
		m_SavingThrows.push_back("wisdom");
		m_SavingThrows.push_back("charisma");
		m_CharPlayerClass = "Paladin";
		m_HitDice = 10;
		if (m_Strength < 13) {
			m_ArmorClass = 16;
			m_Speed -= 10;
		}
		else {
			m_ArmorClass = 16;
		}
		//tOdO skills
		break;
	case Classes::Ranger:
		m_Weapons.push_back("simple weapons");
		m_Weapons.push_back("martial weapons");
		m_Armor.push_back("light armor");
		m_Armor.push_back("medium armor");
		m_Armor.push_back("shields");
		m_SavingThrows.push_back("strength");
		m_SavingThrows.push_back("dexterity");
		m_CharPlayerClass = "Ranger";
		m_HitDice = 10;
		//tOdO skills
		break;
	case Classes::Rogue:
		m_Weapons.push_back("simple weapons");
		m_Weapons.push_back("hand crossbow");
		m_Weapons.push_back("shortsword");
		m_Weapons.push_back("longsword");
		m_Weapons.push_back("rapier");
		m_Weapons.push_back("shortbow");
		m_Armor.push_back("light armor");
		m_SavingThrows.push_back("dexterity");
		m_SavingThrows.push_back("intelligence");
		m_Tools.push_back("thieves tools");
		m_CharPlayerClass = "Rouge";
		m_HitDice = 8;
		m_ArmorClass = 11 + m_DexterityBonus;
		//tOdO skills
		break;
	case Classes::Sorcerer:
		m_Weapons.push_back("dagger");
		m_Weapons.push_back("dart");
		m_Weapons.push_back("sling");
		m_Weapons.push_back("quarterstaff");
		m_Weapons.push_back("light crossbow");
		m_Weapons.push_back("light crossbow");
		m_SavingThrows.push_back("constitution");
		m_SavingThrows.push_back("charisma");
		m_CharPlayerClass = "Sorcerer";
		m_HitDice = 6;
		m_ArmorClass = 10 + m_DexterityBonus;
		//tOdO skills
		break;
	case Classes::Warlock:
		m_Weapons.push_back("simple weapons");
		m_Armor.push_back("light armor");
		m_SavingThrows.push_back("wisdom");
		m_SavingThrows.push_back("charisma");
		m_CharPlayerClass = "Warlock";
		m_HitDice = 8;
		m_ArmorClass = 11 + m_DexterityBonus;
		//tOdO skills
		break;
	case Classes::Wizard:
		m_Weapons.push_back("dagger");
		m_Weapons.push_back("dart");
		m_Weapons.push_back("sling");
		m_Weapons.push_back("quarterstaff");
		m_Weapons.push_back("light crossbow");
		m_SavingThrows.push_back("intelligence");
		m_SavingThrows.push_back("wisdom");//tOdO skills
		m_CharPlayerClass = "Wizard";
		m_HitDice = 6;
		m_ArmorClass = 10 + m_DexterityBonus;
		break;
	}
	switch (m_Background)
	{
		//TODO more backgrounds
	case Background::Acolyte:
		m_Skill.push_back("insight");
		m_Skill.push_back("religion");
		m_Feature.push_back("shelter of the faithful");
		m_CharPlayerBackground = "Acolyte";
		break;
	case Background::Criminal:
		m_Skill.push_back("deception");
		m_Skill.push_back("stealth");
		m_Tools.push_back("gaming set");
		m_Tools.push_back("thieves tools");
		m_Feature.push_back("criminal contact");
		m_CharPlayerBackground = "Criminal";
		break;
	case Background::FolkHero:
		m_Skill.push_back("animal handling");
		m_Skill.push_back("survival");
		m_Tools.push_back("artisans tools");
		m_Tools.push_back("vehicles-land");
		m_Feature.push_back("rustic hospitality");
		m_CharPlayerBackground = "Folk Hero";
		break;
	case Background::Noble:
		m_Skill.push_back("history");
		m_Skill.push_back("persuasion");
		m_Tools.push_back("gaming set");
		m_Feature.push_back("position of privilege");
		m_CharPlayerBackground = "Noble";
		break;
	case Background::Sage:
		m_Skill.push_back("arcana");
		m_Skill.push_back("history");
		m_Feature.push_back("researcher");
		m_CharPlayerBackground = "Sage";
		break;
	case Background::Soldier:
		m_Skill.push_back("athletics");
		m_Skill.push_back("intimidation");
		m_Tools.push_back("gaming set");
		m_Tools.push_back("vehicles-land");
		m_Feature.push_back("miltary rank");
		m_CharPlayerBackground = "Soldier";
		break;
	default:
		break;
	}

	//skills
	for (int i = 0; i < m_Skill.size(); i++)
	{
		if (m_Skill[i] == "acrobatics")
		{
			m_Acrobatics += m_ProficiencyBonus;
		}
		if (m_Skill[i] == "animal handling")
		{
			m_AnimalHandling += m_ProficiencyBonus;
		}
		if (m_Skill[i] == "arcana")
		{
			m_Arcana += m_ProficiencyBonus;
		}
		if (m_Skill[i] == "athletics")
		{
			m_Athletics += m_ProficiencyBonus;
		}
		if (m_Skill[i] == "deception")
		{
			m_Deception += m_ProficiencyBonus;
		}
		if (m_Skill[i] == "history")
		{
			m_History += m_ProficiencyBonus;
		}
		if (m_Skill[i] == "insight")
		{
			m_Insight += m_ProficiencyBonus;
		}
		if (m_Skill[i] == "intimidation")
		{
			m_Intimidation += m_ProficiencyBonus;
		}
		if (m_Skill[i] == "investigation")
		{
			m_Investigation += m_ProficiencyBonus;
		}
		if (m_Skill[i] == "medicine")
		{
			m_Medicine += m_ProficiencyBonus;
		}
		if (m_Skill[i] == "nature")
		{
			m_Nature += m_ProficiencyBonus;
		}
		if (m_Skill[i] == "perception")
		{
			m_Perception += m_ProficiencyBonus;
		}
		if (m_Skill[i] == "performance")
		{
			m_Performance += m_ProficiencyBonus;
		}
		if (m_Skill[i] == "persuasion")
		{
			m_Persuasion += m_ProficiencyBonus;
		}
		if (m_Skill[i] == "religion")
		{
			m_Religion += m_ProficiencyBonus;
		}
		if (m_Skill[i] == "sleight of hand")
		{
			m_SleightOfHand += m_ProficiencyBonus;
		}
		if (m_Skill[i] == "stealth")
		{
			m_Stealth += m_ProficiencyBonus;
		}
		if (m_Skill[i] == "survival")
		{
			m_Survival += m_ProficiencyBonus;
		}
	}

	m_Acrobatics = m_DexterityBonus;
	m_AnimalHandling = m_WisdomBonus;
	m_Arcana = m_IntelligenceBonus;
	m_Athletics = m_StrengthBonus;
	m_Deception = m_CharismaBonus;
	m_History = m_IntelligenceBonus;
	m_Insight = m_WisdomBonus;
	m_Intimidation = m_CharismaBonus;
	m_Investigation = m_IntelligenceBonus;
	m_Medicine = m_WisdomBonus;
	m_Nature = m_IntelligenceBonus;
	m_Perception = m_WisdomBonus;
	m_Performance = m_CharismaBonus;
	m_Persuasion = m_CharismaBonus;
	m_Religion = m_IntelligenceBonus;
	m_SleightOfHand = m_DexterityBonus;
	m_Stealth = m_DexterityBonus;
	m_Survival = m_WisdomBonus;


	//ability scores
	m_Strength += m_StrengthBonus;
	m_Dexterity += m_DexterityBonus;
	m_Constitution += m_ConstitutionBonus;
	m_Intelligence += m_IntelligenceBonus;
	m_Wisdom += m_WisdomBonus;
	m_Charisma += m_CharismaBonus;

	m_PassivePerception = 10 + m_Perception;
	m_HitPoints = m_HitDice + m_ConstitutionBonus;

	std::string str = "database/Players/";
	std::string str_ = "database/Players/";
	std::string str2(m_CharPlayerRace);
	std::string str3(m_CharPlayerClass);

	m_HitPointsCurrent = m_HitPoints;

	m_Representation = TextureManager::LoadTexture((str.append(str2) + ".jpg").c_str());
	m_MapIcon = TextureManager::LoadTexture((str_.append(str3) + ".png").c_str());
}

bool Player::checkIfProficient(std::string searchFor)
{
	for (auto& a : m_Armor)
	{
		if (a == searchFor){return true;}
	}

	for (auto& w : m_Weapons)
	{
		if (w == searchFor) { return true; }
	}

	for (auto& t : m_Tools)
	{
		if (t == searchFor) { return true; }
	}

	return false;
}

void Player::update()
{
	//tOdO check if ded
	{
		if (m_ExperiencePoints >= 300 && m_ExperiencePoints < 900 && m_Level != 2)
		{
			m_Level = 2;
			m_ProficiencyBonus = 2;
		}
		if (m_ExperiencePoints >= 900 && m_ExperiencePoints < 2700 && m_Level != 3)
		{
			m_Level = 3;
			m_ProficiencyBonus = 2;
		}
		if (m_ExperiencePoints >= 2700 && m_ExperiencePoints < 6500 && m_Level != 4)
		{
			m_Level = 4;
			m_ProficiencyBonus = 2;
		}
		if (m_ExperiencePoints >= 6500 && m_ExperiencePoints < 14000 && m_Level != 5)
		{
			m_Level = 5;
			m_ProficiencyBonus = 3;
			for (int i = 0; i < m_Skill.size(); i++)
			{
				if (m_Skill[i] == "acrobatics")
				{
					m_Acrobatics += 1;
				}
				if (m_Skill[i] == "animal handling")
				{
					m_AnimalHandling += 1;
				}
				if (m_Skill[i] == "arcana")
				{
					m_Arcana += 1;
				}
				if (m_Skill[i] == "athletics")
				{
					m_Athletics += 1;
				}
				if (m_Skill[i] == "deception")
				{
					m_Deception += 1;
				}
				if (m_Skill[i] == "history")
				{
					m_History += 1;
				}
				if (m_Skill[i] == "insight")
				{
					m_Insight += 1;
				}
				if (m_Skill[i] == "intimidation")
				{
					m_Intimidation += 1;
				}
				if (m_Skill[i] == "investigation")
				{
					m_Investigation += 1;
				}
				if (m_Skill[i] == "medicine")
				{
					m_Medicine += 1;
				}
				if (m_Skill[i] == "nature")
				{
					m_Nature += 1;
				}
				if (m_Skill[i] == "perception")
				{
					m_Perception += 1;
				}
				if (m_Skill[i] == "performance")
				{
					m_Performance += 1;
				}
				if (m_Skill[i] == "persuasion")
				{
					m_Persuasion += 1;
				}
				if (m_Skill[i] == "religion")
				{
					m_Religion += 1;
				}
				if (m_Skill[i] == "sleight of hand")
				{
					m_SleightOfHand += 1;
				}
				if (m_Skill[i] == "stealth")
				{
					m_Stealth += 1;
				}
				if (m_Skill[i] == "survival")
				{
					m_Survival += 1;
				}
			}
		}
		if (m_ExperiencePoints >= 14000 && m_ExperiencePoints < 23000 && m_Level != 6)
		{
			m_Level = 6;
			m_ProficiencyBonus = 3;
		}
		if (m_ExperiencePoints >= 23000 && m_ExperiencePoints < 34000 && m_Level != 7)
		{
			m_Level = 7;
			m_ProficiencyBonus = 3;
		}
		if (m_ExperiencePoints >= 34000 && m_ExperiencePoints < 48000 && m_Level != 8)
		{
			m_Level = 8;
			m_ProficiencyBonus = 3;
		}
		if (m_ExperiencePoints >= 48000 && m_ExperiencePoints < 64000 && m_Level != 9)
		{
			m_Level = 9;
			m_ProficiencyBonus = 4;
			for (int i = 0; i < m_Skill.size(); i++)
			{
				if (m_Skill[i] == "acrobatics")
				{
					m_Acrobatics += 1;
				}
				if (m_Skill[i] == "animal handling")
				{
					m_AnimalHandling += 1;
				}
				if (m_Skill[i] == "arcana")
				{
					m_Arcana += 1;
				}
				if (m_Skill[i] == "athletics")
				{
					m_Athletics += 1;
				}
				if (m_Skill[i] == "deception")
				{
					m_Deception += 1;
				}
				if (m_Skill[i] == "history")
				{
					m_History += 1;
				}
				if (m_Skill[i] == "insight")
				{
					m_Insight += 1;
				}
				if (m_Skill[i] == "intimidation")
				{
					m_Intimidation += 1;
				}
				if (m_Skill[i] == "investigation")
				{
					m_Investigation += 1;
				}
				if (m_Skill[i] == "medicine")
				{
					m_Medicine += 1;
				}
				if (m_Skill[i] == "nature")
				{
					m_Nature += 1;
				}
				if (m_Skill[i] == "perception")
				{
					m_Perception += 1;
				}
				if (m_Skill[i] == "performance")
				{
					m_Performance += 1;
				}
				if (m_Skill[i] == "persuasion")
				{
					m_Persuasion += 1;
				}
				if (m_Skill[i] == "religion")
				{
					m_Religion += 1;
				}
				if (m_Skill[i] == "sleight of hand")
				{
					m_SleightOfHand += 1;
				}
				if (m_Skill[i] == "stealth")
				{
					m_Stealth += 1;
				}
				if (m_Skill[i] == "survival")
				{
					m_Survival += 1;
				}
			}
		}
		if (m_ExperiencePoints >= 64000 && m_ExperiencePoints < 85000 && m_Level != 10)
		{
			m_Level = 10;
			m_ProficiencyBonus = 4;
		}
		if (m_ExperiencePoints >= 85000 && m_ExperiencePoints < 100000 && m_Level != 11)
		{
			m_Level = 11;
			m_ProficiencyBonus = 4;
		}
		if (m_ExperiencePoints >= 100000 && m_ExperiencePoints < 120000 && m_Level != 12)
		{
			m_Level = 12;
			m_ProficiencyBonus = 4;
		}
		if (m_ExperiencePoints >= 120000 && m_ExperiencePoints < 140000 && m_Level != 13)
		{
			m_Level = 13;
			m_ProficiencyBonus = 5;
			for (int i = 0; i < m_Skill.size(); i++)
			{
				if (m_Skill[i] == "acrobatics")
				{
					m_Acrobatics += 1;
				}
				if (m_Skill[i] == "animal handling")
				{
					m_AnimalHandling += 1;
				}
				if (m_Skill[i] == "arcana")
				{
					m_Arcana += 1;
				}
				if (m_Skill[i] == "athletics")
				{
					m_Athletics += 1;
				}
				if (m_Skill[i] == "deception")
				{
					m_Deception += 1;
				}
				if (m_Skill[i] == "history")
				{
					m_History += 1;
				}
				if (m_Skill[i] == "insight")
				{
					m_Insight += 1;
				}
				if (m_Skill[i] == "intimidation")
				{
					m_Intimidation += 1;
				}
				if (m_Skill[i] == "investigation")
				{
					m_Investigation += 1;
				}
				if (m_Skill[i] == "medicine")
				{
					m_Medicine += 1;
				}
				if (m_Skill[i] == "nature")
				{
					m_Nature += 1;
				}
				if (m_Skill[i] == "perception")
				{
					m_Perception += 1;
				}
				if (m_Skill[i] == "performance")
				{
					m_Performance += 1;
				}
				if (m_Skill[i] == "persuasion")
				{
					m_Persuasion += 1;
				}
				if (m_Skill[i] == "religion")
				{
					m_Religion += 1;
				}
				if (m_Skill[i] == "sleight of hand")
				{
					m_SleightOfHand += 1;
				}
				if (m_Skill[i] == "stealth")
				{
					m_Stealth += 1;
				}
				if (m_Skill[i] == "survival")
				{
					m_Survival += 1;
				}
			}
		}
		if (m_ExperiencePoints >= 140000 && m_ExperiencePoints < 165000 && m_Level != 14)
		{
			m_Level = 14;
			m_ProficiencyBonus = 5;
		}
		if (m_ExperiencePoints >= 165000 && m_ExperiencePoints < 195000 && m_Level != 15)
		{
			m_Level = 15;
			m_ProficiencyBonus = 5;
		}
		if (m_ExperiencePoints >= 195000 && m_ExperiencePoints < 225000 && m_Level != 16)
		{
			m_Level = 16;
			m_ProficiencyBonus = 5;
		}
		if (m_ExperiencePoints >= 225000 && m_ExperiencePoints < 265000 && m_Level != 17)
		{
			m_Level = 17;
			m_ProficiencyBonus = 6;
			for (int i = 0; i < m_Skill.size(); i++)
			{
				if (m_Skill[i] == "acrobatics")
				{
					m_Acrobatics += 1;
				}
				if (m_Skill[i] == "animal handling")
				{
					m_AnimalHandling += 1;
				}
				if (m_Skill[i] == "arcana")
				{
					m_Arcana += 1;
				}
				if (m_Skill[i] == "athletics")
				{
					m_Athletics += 1;
				}
				if (m_Skill[i] == "deception")
				{
					m_Deception += 1;
				}
				if (m_Skill[i] == "history")
				{
					m_History += 1;
				}
				if (m_Skill[i] == "insight")
				{
					m_Insight += 1;
				}
				if (m_Skill[i] == "intimidation")
				{
					m_Intimidation += 1;
				}
				if (m_Skill[i] == "investigation")
				{
					m_Investigation += 1;
				}
				if (m_Skill[i] == "medicine")
				{
					m_Medicine += 1;
				}
				if (m_Skill[i] == "nature")
				{
					m_Nature += 1;
				}
				if (m_Skill[i] == "perception")
				{
					m_Perception += 1;
				}
				if (m_Skill[i] == "performance")
				{
					m_Performance += 1;
				}
				if (m_Skill[i] == "persuasion")
				{
					m_Persuasion += 1;
				}
				if (m_Skill[i] == "religion")
				{
					m_Religion += 1;
				}
				if (m_Skill[i] == "sleight of hand")
				{
					m_SleightOfHand += 1;
				}
				if (m_Skill[i] == "stealth")
				{
					m_Stealth += 1;
				}
				if (m_Skill[i] == "survival")
				{
					m_Survival += 1;
				}
			}

		}
		if (m_ExperiencePoints >= 265000 && m_ExperiencePoints < 305000 && m_Level != 18)
		{
			m_Level = 18;
			m_ProficiencyBonus = 6;
		}
		if (m_ExperiencePoints >= 305000 && m_ExperiencePoints < 355000 && m_Level != 19)
		{
			m_Level = 19;
			m_ProficiencyBonus = 6;
		}
		if (m_ExperiencePoints >= 355000 && m_Level != 20)
		{
			m_Level = 20;
			m_ProficiencyBonus = 6;
		}
	}

}

Player::~Player()
{

}

}
