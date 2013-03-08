#include <string>
#include "player_character.h"
#include <cstdlib>
#include <sstream>

using namespace std;


// Constructs a Player from the provided arguments.
// Pre: inAttackDie must be > 0, and all values must be positive.
	Player::Player(string inName, int inHP, int inHitDie, int inAttackDie, int inAttackBonus, int inArmorClass, int inLevel) {
		name = inName;
		HP = inHP;
		hitDie = inHitDie;
		attackDie = inAttackDie;
		attackBonus = inAttackBonus;
		AC = inArmorClass;
		maxHealth = inHP;
		level = inLevel;
	}

	Player::Player(string inName, int inHitDie, int inAttackDie, int inAttackBonus, int inArmorClass) {
		name = inName;
		HP = inHitDie;
		hitDie = inHitDie;
		attackDie = inAttackDie;
		attackBonus = inAttackBonus;
		AC = inArmorClass;
		maxHealth = inHitDie;
		level = 1;
		}

	Player::Player(string inName, int inLevel) {
		name = inName;
		hitDie = (8+rand()%(2*level+1));
		HP = hitDie;
		attackDie = (8+rand()%(2*level+1));
		attackBonus = (rand()%(2*level+1));
		AC = (8+rand()%(2*level+1));
		maxHealth = hitDie;
		level = inLevel;
	}

	Player::Player() {
		name = "DEFAULT";
		HP = 4;
		hitDie = 4;
		attackDie = 1;
		attackBonus = 0;
		AC = 10;
		maxHealth = 4;
		level = 1;
	}

	int Player::GetHealth() {
		if (HP > 0)
		return HP;
		else {
			HP = 0;
			return HP;
		}
	}

	int Player::AttackDmg(int bonus) {
		if (attackDie != 0)
		return ((rand()%attackDie+1) + bonus + attackBonus);
		else return (rand());
	}

	int Player::AttackDmg() {
		if (attackDie != 0)
		return ((rand()%attackDie+1));
		else return (rand());
	}

	string Player::GetName() {
		return name;
	}

	void Player::AddHealth(int amount) {
		HP = HP + amount;
	}

	void Player::RemoveHealth(int amount) {
		HP = HP - amount;
	}

	int Player::GetAC() {
		return AC;
	}

	int Player::D20Role() {
		int roll;
		roll = (rand()%20+1);
		return (roll);
	}

	int Player::GetAttackBonus() {
		return attackBonus;
	}

	bool Player::IsAlive() {
		if (HP > 0)
			return true;
		else return false;
	}

	int Player::GetAttackDie() {
		return attackDie;
	}

	int Player::GetHitDie() {
		return hitDie;
	}

	void Player::LevelUp(char toLevel) {
		level++;
		switch (toLevel) {
		case 'H':
			maxHealth += (rand()%hitDie + 1);
			break;
		case 'K':
			attackBonus += (rand()%6 + 1);
			break;
		case 'A':
			AC += (rand()%6 + 1);
			break;
		case 'D':
			attackDie += (rand()%6 + 1);
			break;
		}
	}

	void Player::FullHeal() {
		HP = maxHealth;
	}

	int Player::GetLevel() {
		return level;
	}

	int Player::GetMaxHealth() {
		return maxHealth;
	}

	void Player::RollAttack(Player& defender) {	
		int AttackRoll = D20Role();
		int DamageRoll = AttackDmg();
	
		if (AttackRoll == 20) {
			DamageRoll = DamageRoll*2;
			defender.RemoveHealth(DamageRoll);
		}
		else {
			if ((AttackRoll + attackBonus) > defender.GetAC()) {
				defender.RemoveHealth(DamageRoll);
			}
		}
	}

	void Player::RollAttack(Player& defender, string& writeOut) {
		int AttackRoll = D20Role();
		int DamageRoll = AttackDmg();
		stringstream toStrHlth;
		stringstream toStrDmg;
		string strDmg;
		
		if (AttackRoll == 20) {

			DamageRoll = DamageRoll*2;
			toStrDmg << DamageRoll;
			strDmg = toStrDmg.str();

			defender.RemoveHealth(DamageRoll);

			toStrHlth << defender.GetHealth();
			string strHlth = toStrHlth.str();

			writeOut = ("Critical hit! " + name + " deals " + strDmg + " damage! " + defender.GetName() + " has " + strHlth + " health left.");
		}
		else {

			toStrDmg << DamageRoll;
			strDmg = toStrDmg.str();

			if ((AttackRoll + attackBonus) > defender.GetAC()) {
				defender.RemoveHealth(DamageRoll);

				toStrHlth << defender.GetHealth();
				string strHlth = toStrHlth.str();

				writeOut = ( GetName() + " deals " + strDmg + " damage.  " + defender.GetName() + " has " + strHlth + " health left.");
			}
			else writeOut = ( GetName() + " misses!");
		}
	}

	int Player::GetTotalPoints() {
		return (AC+hitDie+attackBonus+attackDie);
	}

	bool Player::ValidValues() {
		if (HP <= 0 || hitDie <= 0 || AC < 0 || attackBonus < 0 || attackDie <= 0)
			return false;
		else return true;
	}