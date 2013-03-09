#ifndef PLAYER_FLAG
#define PLAYER_FLAG
#include <string>

using namespace std;

class Player {
public: Player(string inName, int inHP, int inHitDie, int inAttackDie, int inAttackBonus, int inArmorClass, int inLevel);
		Player(string inName, int inHitDie, int inAttackDie, int inAttackBonus, int inArmorClass);
		Player(string inName, int level);
		Player();

		void AddHealth(int amount);
		void RemoveHealth(int amount);
		int GetHealth();
		int AttackDmg(int bonus);
		int AttackDmg();
		string GetName();
		int GetAC();
		int D20Role();
		int GetAttackBonus();
		bool IsAlive();
		int GetAttackDie();
		int GetHitDie();
		void LevelUp(char toLevel);
		void FullHeal();
		int GetLevel();
		int GetMaxHealth();
		void RollAttack(Player& defender);
		void RollAttack(Player& defender, string& writeOut);
		int GetTotalPoints();
		bool ValidValues();

private:
	string name;
	int HP;
	int hitDie;
	int attackBonus;
	int attackDie;
	int AC;
	string inventory[25];
	int level;
	int maxHealth;
		};

#endif