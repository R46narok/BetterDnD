#pragma once

#include "monster.h"
#include "player.h"
#include "weapons.h"
#include "spells.h"

std::vector<Spell> spellsVec = loadSpells();

class CombatSystem { //t0d0r monster.h
public:
	static void attack(Player::Player *player1, Player::Player *player2, Weapon::Weapon *weapon) {
		int attackRoll = 0;
		int bonus = 0;
		if (weapon->Finesse) {
			attackRoll += player1->m_DexterityBonus; // roll += dex or str
			bonus = player1->m_DexterityBonus;
		}
		else {
			attackRoll += player1->m_StrengthBonus;
			bonus = player1->m_StrengthBonus;
		}

		//attRol + d20(adv and disadv)
		if (((player1->advantageAttacking || player2->advantageAttacked) && !(player1->disadvantageAttacking || player2->disadvantageAttacked)) || (player1->advantageAbilityCheck && !player1->disadvantageAbilityCheck)) {
			int roll1 = random_numberHardware(20), roll2 = random_numberHardware(20);
			if (roll1 > roll2)
				attackRoll += roll1;
			else
				attackRoll += roll2;
		}
		else if (((player1->disadvantageAttacking || player2->disadvantageAttacked) && !(player1->advantageAttacking || player2->advantageAttacked)) || (!player1->advantageAbilityCheck && player1->disadvantageAbilityCheck)) {
			int roll1 = random_numberHardware(20), roll2 = random_numberHardware(20);
			if (roll1 < roll2)
				attackRoll += roll1;
			else
				attackRoll += roll2;
		}
		else
			attackRoll += random_numberHardware(20);

		//proficient
		if (player1->checkIfProficient(weapon->m_Name) || player1->checkIfProficient("simple weapons"))
			attackRoll += player1->m_ProficiencyBonus;

		//cycles with dmg
		int a = 0;
		if (attackRoll >= player2->m_ArmorClass) {
			for (int i = 0; i < player2->m_Immunities.size(); i++) {
				if (weapon->m_DamageType == player2->m_Immunities[i]) {
					a++;
					break;
				}
			}
			if (a == 0) {
				for (int i = 0; i < player2->m_Resistances.size(); i++) {
					if (weapon->m_DamageType == player2->m_Resistances[i]) {
						player2->m_HitPointsCurrent -= (dieTransformer(weapon->m_Damage) + bonus) / 2;
						a++;
						break;
					}
				}
			}
			if (a == 0) {
				for (int i = 0; i < player2->m_Vulnerabilities.size(); i++) {
					if (weapon->m_DamageType == player2->m_Vulnerabilities[i]) {
						player2->m_HitPointsCurrent -= (dieTransformer(weapon->m_Damage) + bonus) * 2;
						a++;
						break;
					}
				}
			}
			if (a == 0) {
				player2->m_HitPointsCurrent -= (dieTransformer(weapon->m_Damage) + bonus);
				a++;
			}
		}
	}
	static void attack(Player::Player *player, Monsters::Monster *monster, Weapon::Weapon *weapon) {
		int attackRoll = 0;
		int bonus = 0;
		if (weapon->Finesse) {
			attackRoll += player->m_DexterityBonus; // roll += dex or str
			bonus = player->m_DexterityBonus;
		}
		else {
			attackRoll += player->m_StrengthBonus;
			bonus = player->m_StrengthBonus;
		}

		//attRol + d20(adv and disadv)
		if (((player->advantageAttacking || monster->advantageAttacked) && !(player->disadvantageAttacking || monster->disadvantageAttacked)) || (player->advantageAbilityCheck && !player->disadvantageAbilityCheck)) {
			int roll1 = random_numberHardware(20), roll2 = random_numberHardware(20);
			if (roll1 > roll2)
				attackRoll += roll1;
			else
				attackRoll += roll2;
		}
		else if (((player->disadvantageAttacking || monster->disadvantageAttacked) && !(player->advantageAttacking || monster->advantageAttacked)) || (!player->advantageAbilityCheck && player->disadvantageAbilityCheck)) {
			int roll1 = random_numberHardware(20), roll2 = random_numberHardware(20);
			if (roll1 < roll2)
				attackRoll += roll1;
			else
				attackRoll += roll2;
		}
		else
			attackRoll += random_numberHardware(20);

		//proficient
		if (player->checkIfProficient(weapon->m_Name) || player->checkIfProficient("simple weapons"))
			attackRoll += player->m_ProficiencyBonus;

		//cycles with dmg
		int a = 0;
		if (attackRoll >= monster->m_ArmorClass) {
			for (int i = 0; i < monster->m_Immunities.size(); i++) {
				if (weapon->m_DamageType == monster->m_Immunities[i]) {
					a++;
					break;
				}
			}
			if (a == 0) {
				for (int i = 0; i < monster->m_Resistance.size(); i++) {
					if (weapon->m_DamageType == monster->m_Resistance[i]) {
						monster->m_HitPoints -= (dieTransformer(weapon->m_Damage) + bonus) / 2;
						a++;
						break;
					}
				}
			}
			if (a == 0) {
				for (int i = 0; i < monster->m_Vulnerabilities.size(); i++) {
					if (weapon->m_DamageType == monster->m_Vulnerabilities[i]) {
						monster->m_HitPoints -= (dieTransformer(weapon->m_Damage) + bonus) * 2;
						a++;
						break;
					}
				}
			}
			if (a == 0) {
				monster->m_HitPoints -= (dieTransformer(weapon->m_Damage) + bonus);
				a++;
			}
		}
	}
	static void attack(Monsters::Monster *monster, Player::Player *player, Weapon::Weapon *weapon) {
		int attackRoll = 0;
		attackRoll += monster->m_StrengthBonus;
		//get bonuses form monster
		//attRoll + d20(adv and disadv)
		if (((monster->advantageAttacking || player->advantageAttacked) && !(monster->disadvantageAttacking || player->disadvantageAttacked)) || (monster->advantageAbilityCheck && !monster->disadvantageAbilityCheck)) {
			int roll1 = random_numberHardware(20), roll2 = random_numberHardware(20);
			if (roll1 > roll2)
				attackRoll += roll1;
			else
				attackRoll += roll2;
		}
		else if (((monster->disadvantageAttacking || player->disadvantageAttacked) && !(monster->advantageAttacking || player->advantageAttacked)) || (!monster->advantageAbilityCheck && monster->disadvantageAbilityCheck)) {
			int roll1 = random_numberHardware(20), roll2 = random_numberHardware(20);
			if (roll1 < roll2)
				attackRoll += roll1;
			else
				attackRoll += roll2;
		}
		else
			attackRoll += random_numberHardware(20);

		//cycles with dmg
		int a = 0;
		if (attackRoll >= player->m_ArmorClass) {
			for (int i = 0; i < player->m_Immunities.size(); i++)
			{
				if (weapon->m_DamageType == player->m_Immunities[i]) {
					a++;
					break;
				}
			}
			if (a == 0) {
				for (int i = 0; i < player->m_Resistances.size(); i++) {
					if (weapon->m_DamageType == player->m_Resistances[i]) {
						player->m_HitPointsCurrent -= (dieTransformer(weapon->m_Damage) + monster->m_Strength) / 2;
						a++;
						break;
					}
				}
			}
			if (a == 0) {
				for (int i = 0; i < player->m_Vulnerabilities.size(); i++) {
					if (weapon->m_DamageType == player->m_Vulnerabilities[i]) {
						player->m_HitPointsCurrent -= (dieTransformer(weapon->m_Damage) + monster->m_Strength) * 2;
						a++;
						break;
					}
				}
			}
			if (a == 0)
				player->m_HitPointsCurrent -= (dieTransformer(weapon->m_Damage) + monster->m_Strength);
		}
	}
	static void attack(Monsters::Monster *monster1, Monsters::Monster *monster2, Weapon::Weapon *weapon) {
		int attackRoll = 0;

		attackRoll += monster1->m_StrengthBonus;
		//attRol + d20(adv and disadv)
		if (((monster1->advantageAttacking || monster2->advantageAttacked) && !(monster1->disadvantageAttacking || monster2->disadvantageAttacked)) || (monster1->advantageAbilityCheck && !monster1->disadvantageAbilityCheck)) {
			int roll1 = random_numberHardware(20), roll2 = random_numberHardware(20);
			if (roll1 > roll2)
				attackRoll += roll1;
			else
				attackRoll += roll2;
		}
		else if (((monster1->disadvantageAttacking || monster2->disadvantageAttacked) && !(monster1->advantageAttacking || monster2->advantageAttacked)) || (!monster1->advantageAbilityCheck && monster1->disadvantageAbilityCheck)) {
			int roll1 = random_numberHardware(20), roll2 = random_numberHardware(20);
			if (roll1 < roll2)
				attackRoll += roll1;
			else
				attackRoll += roll2;
		}
		else
			attackRoll += random_numberHardware(20);

		//cycles with dmg
		int a = 0;
		if (attackRoll >= monster2->m_ArmorClass) {
			for (int i = 0; i < monster2->m_Immunities.size(); i++)
			{
				if (weapon->m_DamageType == monster2->m_Immunities[i]) {
					a++;
					break;
				}
			}
			if (a == 0) {
				for (int i = 0; i < monster2->m_Resistance.size(); i++) {
					if (weapon->m_DamageType == monster2->m_Resistance[i]) {
						monster2->m_HitPoints -= (dieTransformer(weapon->m_Damage) + monster1->m_Strength) / 2;
						a++;
						break;
					}
				}
			}
			if (a == 0) {
				for (int i = 0; i < monster2->m_Vulnerabilities.size(); i++) {
					if (weapon->m_DamageType == monster2->m_Vulnerabilities[i]) {
						monster2->m_HitPoints -= (dieTransformer(weapon->m_Damage) + monster1->m_Strength) * 2;
						a++;
						break;
					}
				}
			}
			if (a == 0)
				monster2->m_HitPoints -= (dieTransformer(weapon->m_Damage) + monster1->m_Strength);
		}
	}
	static void help(Player::Player *player1, Player::Player *player2) {
		player2->advantageAbilityCheck = true;
	}
	static void help(Player::Player *player, Monsters::Monster *monster) {
		monster->advantageAbilityCheck = true;
	}
	static void help(Monsters::Monster *monster, Player::Player *player) {
		player->advantageAbilityCheck = true;
	}
	static void help(Monsters::Monster *monster1, Monsters::Monster *monster2) {
		monster2->advantageAbilityCheck = true;
	}
	static void dash(Player::Player *player) {
		player->m_Speed *= 2;
	}
	static void dash(Monsters::Monster *monster) {
		monster->m_Speed *= 2;
	}
	static void hide(Player::Player *player, Monsters::Monster *monster) {
		int stealthRoll = 0;
		if (player->advantageAbilityCheck && !player->disadvantageAbilityCheck) {
			int roll1 = random_numberHardware(20), roll2 = random_numberHardware(20);
			if (roll1 > roll2)
				stealthRoll += roll1;
			else
				stealthRoll += roll2;
		}
		else if (!player->advantageAbilityCheck && player->disadvantageAbilityCheck) {
			int roll1 = random_numberHardware(20), roll2 = random_numberHardware(20);
			if (roll1 < roll2)
				stealthRoll += roll1;
			else
				stealthRoll += roll2;
		}
		else
			stealthRoll += random_numberHardware(20);

		if (player->checkIfProficient("Stealth"))
			stealthRoll += player->m_ProficiencyBonus;

		stealthRoll += player->m_Stealth;

		if (stealthRoll <= monster->m_PassivePerception)
			player->advantageAttacking = true;
	}
	static void hide(Player::Player *player1, Player::Player *player2) {
		int stealthRoll = 0;
		if (player1->advantageAbilityCheck && !player1->disadvantageAbilityCheck) {
			int roll1 = random_numberHardware(20), roll2 = random_numberHardware(20);
			if (roll1 > roll2)
				stealthRoll += roll1;
			else
				stealthRoll += roll2;
		}
		else if (!player1->advantageAbilityCheck && player1->disadvantageAbilityCheck) {
			int roll1 = random_numberHardware(20), roll2 = random_numberHardware(20);
			if (roll1 < roll2)
				stealthRoll += roll1;
			else
				stealthRoll += roll2;
		}
		else
			stealthRoll += random_numberHardware(20);

		if (player1->checkIfProficient("Stealth"))
			stealthRoll += player1->m_ProficiencyBonus;

		stealthRoll += player1->m_Stealth;
		if (stealthRoll <= player2->m_PassivePerception)
			player1->advantageAttacking = true;
	}
	static void hide(Monsters::Monster *monster, Player::Player *player) {
		int stealthRoll = 0;
		stealthRoll += monster->m_DexterityBonus;
		if (monster->advantageAbilityCheck && !monster->disadvantageAbilityCheck) {
			int roll1 = random_numberHardware(20), roll2 = random_numberHardware(20);
			if (roll1 > roll2)
				stealthRoll += roll1;
			else
				stealthRoll += roll2;
		}
		else if (!monster->advantageAbilityCheck && monster->disadvantageAbilityCheck) {
			int roll1 = random_numberHardware(20), roll2 = random_numberHardware(20);
			if (roll1 < roll2)
				stealthRoll += roll1;
			else
				stealthRoll += roll2;
		}
		else
			stealthRoll += random_numberHardware(20);

		if (stealthRoll <= player->m_PassivePerception)
			monster->advantageAttacking = true;
	}
	static void hide(Monsters::Monster *monster1, Monsters::Monster *monster2) {
		int stealthRoll = 0;
		stealthRoll += monster1->m_DexterityBonus;
		if (monster1->advantageAbilityCheck && !monster1->disadvantageAbilityCheck) {
			int roll1 = random_numberHardware(20), roll2 = random_numberHardware(20);
			if (roll1 > roll2)
				stealthRoll += roll1;
			else
				stealthRoll += roll2;
		}
		else if (!monster1->advantageAbilityCheck && monster1->disadvantageAbilityCheck) {
			int roll1 = random_numberHardware(20), roll2 = random_numberHardware(20);
			if (roll1 < roll2)
				stealthRoll += roll1;
			else
				stealthRoll += roll2;
		}
		else
			stealthRoll += random_numberHardware(20);

		if (stealthRoll <= monster2->m_PassivePerception)
			monster1->advantageAttacking = true;
	}
	//static void disengage(){ //t0d0r }
	static void dodge(Player::Player *player) {
		player->disadvantageAttacked = true;
	}
	static void dodge(Monsters::Monster *monster) {
		monster->disadvantageAttacked = true;
	}
};
