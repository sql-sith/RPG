#ifndef FIGHTER_FLAG
#define FIGHTER_FLAG
#include "player_character.h"

using namespace std;

class Fighter : public Player {
public: Fighter();
		Fighter(string inName, char inType);
		Fighter(string inName, int inHitDie, int inAttackDie, int inAttackBonus, int inAC);
		Fighter(string inName, int inHP, int inHitDie, int inAttackDie, int inAttackBonus, int inArmorClass, int inLevel, char charClass);
		void RollAttack(Player& defender, string& writeOut);
		void RollAttack(Player& defender);
		string GetClass();
		char GetClassChar();
		int FirstStrikes();
private: 
	string charType;
	char classChar;
	static int FindHitDie(char inChar) {
			switch (inChar) {
				case 'B': return 10;
					break;
				case 'N': return 8;
					break;
				case 'F': return 10;
					break;
				case 'T': return 14;
					break;
				case 'A': return 10;
					break;
				default: return 4;
			}
}
	static int FindAttackDie(char inChar) {
			switch (inChar) {
				case 'B': return 14;
					break;
				case 'N': return 10;
					break;
				case 'F': return 10;
					break;
				case 'T': return 8;
					break;
				case 'A': return 10;
					break;
				default: return 4;
			}
		 }
	static int FindAttackBonus(char inChar) {
			switch (inChar) {
				case 'B': return 0;
					break;
				case 'N': return 10;
					break;
				case 'F': return 2;
					break;
				case 'T': return 2;
					break;
				case 'A': return 5;
					break;
				default: return 4;
			}
		 }
	static int FindAC(char inChar) {
			switch (inChar) {
				case 'B': return 10;
					break;
				case 'N': return 10;
					break;
				case 'F': return 16;
					break;
				case 'T': return 12;
					break;
				case 'A': return 10;
					break;
				default: return 4;
			}
		 }
	static string CharToString(char inChar) {
		switch (inChar) {
			case 'B': return "barbarian";
				break;
			case 'N': return "ninja";
				break;
			case 'F': return "fighter";
				break;
			case 'T': return "tank";
				break;
			case 'A': return "archer";
				break;
			default: return "DEFAULT";
		}
	}
};

#endif