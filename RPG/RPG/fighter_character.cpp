#include "fighter_character.h"
#include <sstream>
#include <iostream>
#include <windows.h>

using namespace std;

Fighter::Fighter() : Player() { 
	charType = "DEFAULTCLASS";
	classChar = '~';
}

Fighter::Fighter(string inName, char inType) : Player(inName, FindHitDie(inType), FindAttackDie(inType), FindAttackBonus(inType), FindAC(inType))   {
	charType = CharToString(inType);
	classChar = inType;
}

Fighter::Fighter(string inName, int inHitDie, int inAttackDie, int inAttackBonus, int inAC) : Player(inName, inHitDie, inAttackDie, inAttackBonus, inAC) { }

Fighter::Fighter(string inName, int inHP, int inHitDie, int inAttackDie, int inAttackBonus, int inArmorClass, int inLevel, char charClass) : Player(inName, inHP, inHitDie, inAttackDie, inAttackBonus, inArmorClass, inLevel) {
	charType = CharToString(charClass);
	classChar = charClass;
}

void Fighter::RollAttack(Player& defender) {	
		int AttackRoll = D20Role();
		int DamageRoll = AttackDmg();
	
		if (AttackRoll == 20) {
			DamageRoll = DamageRoll*2;
			defender.RemoveHealth(DamageRoll);
		}
		else {
			if ((AttackRoll + GetAttackBonus()) > defender.GetAC()) {
				defender.RemoveHealth(DamageRoll);
			}
		}
	}

void Fighter::RollAttack(Player& defender, string& writeOut) {
		int AttackRoll = D20Role();
		int DamageRoll = AttackDmg();
		stringstream toStrHlth;
		stringstream toStrDmg;
		string strDmg;
		
		if (AttackRoll < 1) {

			DamageRoll = DamageRoll*2;
			toStrDmg << DamageRoll;
			strDmg = toStrDmg.str();

			defender.RemoveHealth(DamageRoll);

			toStrHlth << defender.GetHealth();
			string strHlth = toStrHlth.str();

			writeOut = ("Critical hit! " + GetName() + " deals " + strDmg + " damage! " + defender.GetName() + " has " + strHlth + " health left.");
		}
		else {

			toStrDmg << DamageRoll;
			strDmg = toStrDmg.str();

			if ((AttackRoll + GetAttackBonus()) > defender.GetAC()) {
				defender.RemoveHealth(DamageRoll);

				toStrHlth << defender.GetHealth();
				string strHlth = toStrHlth.str();

				writeOut = ( GetName() + " deals " + strDmg + " damage.  " + defender.GetName() + " has " + strHlth + " health left.");
			}
			else writeOut = ( GetName() + " misses!");
		}
	}

string Fighter::GetClass() {
	return charType;
}

char Fighter::GetClassChar() {
	return classChar;
}

int Fighter::FirstStrikes() {
	switch (classChar) {
	case 'A': return (rand()%GetLevel());
			break;
	case 'N': return 1;
			break;
	default: return 0;
		break;
	}
}