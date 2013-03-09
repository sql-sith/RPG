#include <iostream>
#include <string>
#include <cstdlib>
#include "player_character.h"
#include "fighter_character.h"
#include <windows.h>
#include <time.h>
#include <fstream>

using namespace std;

void GetPlayer(Player& initplayer);
void GetPlayerFromFile(ifstream& inFile, Player& gabe);
void RollAttack(Player& attacker, Player& defender);
void LoadCharacter(ifstream& inFile, Fighter& gabe, int& levelCounter);
void SaveCharacter(ofstream& outFile, Fighter gabe);
void SavePrompt(ofstream& outFile, Player gabe);
void PrintWinner(Player gabe, Player bob);
void ResolveEnding(Fighter& gabe, char& keepGoing, ofstream& outFile, int& levelCounter);
void PlayerPrompt(Player& gabe);
void EnemyPrompt();
void PromptLevelUp(Player& gabe);
void GetDetails(Player gabe);
void CreateEnemy(Player& bob, int levelCounter);
bool GoodInput(int hitDie,	int attack,	int AC,	int attackBonus);
void RunCombat(Fighter& gabe, Player& bob);
void PlayerPrompt2(Fighter& gabe);
void GetPlayer2(Player& initPlayer);
void GetPlayerFromFile2(ifstream& inFile, Fighter& initPlayer);
bool IsLetterOK(char classLetter);
void HandlePreCombat(Fighter gabe, Player& bob);

int main() {
	ifstream inFile;
	ofstream outFile;
	Player bob;
	Fighter gabe;
	char keepGoing = 'Y';
	int levelCounter = 0;
	string fightResult;

	LoadCharacter(inFile, gabe, levelCounter);
	while (keepGoing == 'Y') {
		srand (time(NULL));

		CreateEnemy(bob, levelCounter);
		cout << "A wild " << bob.GetName() << " approaches!" << endl;
		Sleep(500);
		RunCombat(gabe, bob);
		levelCounter++;
		PrintWinner(gabe, bob);
		ResolveEnding(gabe, keepGoing, outFile, levelCounter);
	}
	cout << "End of simulation.  Goodbye!" << endl;
	return 0;
}

void GetPlayer(Player& initPlayer) {
	string name;
	int hitDie;
	int attack;
	int AC;
	int attackBonus;
	string throwAway;
	//cout << "Enter name, hit die, attack die, attack bonus and AC for the character." << endl;
	cin >> name >> hitDie >> attack >> attackBonus >> AC;
	Player tempPlayer(name, hitDie, attack, attackBonus, AC);
	initPlayer = tempPlayer;
	getline(cin, throwAway);
	cin.clear();
}

void GetPlayerFromFile(ifstream& inFile, Player& initPlayer) {
	string name;
	int hitPoints;
	int hitDie;
	int attack;
	int AC;
	int attackBonus;
	int level;
	inFile >> name >> hitPoints >> hitDie >> attack >> attackBonus >> AC >> level;
	Player tempPlayer(name, hitPoints, hitDie, attack, attackBonus, AC, level);
	initPlayer = tempPlayer;
}

void RollAttack(Player& attacker, Player& defender) {
	int AttackRoll = attacker.D20Role();
	int DamageRoll = attacker.AttackDmg();
	
	if (AttackRoll == 20) {
		DamageRoll = DamageRoll*2;
		defender.RemoveHealth(DamageRoll);
		cout << "Critical hit!" << attacker.GetName() << " deals " << DamageRoll << " damage! " << defender.GetName() << " has " << defender.GetHealth() << " health left." << endl;
	}
	else {
	if ((AttackRoll + attacker.GetAttackBonus())> defender.GetAC()) {
		defender.RemoveHealth(DamageRoll);
		cout << attacker.GetName() << " deals " << DamageRoll << " damage.  " << defender.GetName() << " has " << defender.GetHealth() << " health left." << endl;
	}
	else cout << attacker.GetName() << " misses!" << endl;
	}
	
}

void SavePrompt(ofstream& outFile, Fighter gabe) {
	char YN;
	cout << "Save winner? (Y/N)" << endl;
	cin >> YN;
	if (YN == 'Y') {
			SaveCharacter(outFile, gabe);
	}
	else cout << "Proceeding unsaved!" << endl;
}

void LoadCharacter(ifstream& inFile, Fighter& gabe, int& levelCounter) {
	char YN;
	inFile.open("save.dat");
	if (inFile) {
		cout << "Load last surviving character? (Y/N)" << endl;
		cin >> YN;
		if (YN == 'Y') {
			GetPlayerFromFile2(inFile, gabe);
			levelCounter = gabe.GetLevel();
			levelCounter--;
		}
		else {
			PlayerPrompt2(gabe);
		}
	}
	else {
		cout << "Can't find save file. Proceeding with manual input." << endl;
		PlayerPrompt2(gabe);
	}
	inFile.close();
}

void SaveCharacter(ofstream& outFile, Fighter gabe) {
	outFile.open("save.dat");
	outFile << gabe.GetName() << " " << gabe.GetHealth() << " " << gabe.GetHitDie() << " " << gabe.GetAttackDie() << " " << gabe.GetAttackBonus() << " " << gabe.GetAC() << " " << gabe.GetLevel() << " " << gabe.GetClassChar() << endl;
			}

void PrintWinner(Player gabe, Player bob) {
	if (bob.IsAlive()) {
		cout << bob.GetName() << " is the winner!" << endl;
	}
	else {
		cout << gabe.GetName() << " is the winner!" << endl;
	}
}

void ResolveEnding(Fighter& gabe, char& keepGoing, ofstream& outFile, int& levelCounter) {

	if (gabe.IsAlive()) {
			PromptLevelUp(gabe);
			do {
			cout << "Continue? (Y/N)" << endl;
			cin >> keepGoing;
			} while (keepGoing != 'N' && keepGoing != 'Y');
			if (keepGoing == 'N')
				SavePrompt(outFile, gabe);
		}
		else {
			cout << gabe.GetName() << " loses! Tough luck!" << endl;
			cout << "When he died, " << gabe.GetName() << " had ";
			GetDetails(gabe);
			cout << "He was a level " << gabe.GetLevel() << " " << gabe.GetClass() << "." << endl;
			do {
				cout << "Play again? (Y/N) " << endl;
				cin >> keepGoing;
			} while (keepGoing != 'N' && keepGoing != 'Y');
			if (keepGoing == 'Y') {
				PlayerPrompt2(gabe);
				levelCounter = 0;
			}
		}
}

void PlayerPrompt(Player& gabe) {
	do {
	cout << "Enter name, hit die, attack die, attack bonus and AC for the player." << endl;
	cout << "Total combined value all attributes may not exceed 34." << endl;
	GetPlayer(gabe);
	if (gabe.GetTotalPoints() > 34)
		cout << endl << "Whoops! You assigned too many points." << endl;
	if (!gabe.ValidValues())
		cout << endl << "Uh-oh! Some of your stats are not within the acceptable range(s)!" << endl;
	cout << endl;
	} while ((gabe.GetTotalPoints() > 34) || !gabe.ValidValues());
}

void EnemyPrompt() {
	cout << "Enter name, hit die, attack die, attack bonus and AC for the opponent." << endl;
}

void PromptLevelUp(Player& gabe) {
	char levelChar;

	cout << gabe.GetName() << " levels up!" << endl;
	cout << gabe.GetName() << " has ";
	GetDetails(gabe);
	do {
	cout << "What should " << gabe.GetName() << " level? (H for HP, A for AC, D for damage, or K for Attack.)" << endl;
	cin >> levelChar;
	if (levelChar != 'H' && levelChar != 'A' && levelChar != 'D' && levelChar != 'K')
		cout << endl << "Invalid letter!" << endl;
	} while (levelChar != 'H' && levelChar != 'A' && levelChar != 'D' && levelChar != 'K');
	gabe.LevelUp(levelChar);
	gabe.FullHeal();
}

void GetDetails(Player gabe) {
	cout << gabe.GetMaxHealth() << " HP, " << gabe.GetAC() << " AC, " << gabe.GetAttackDie() << " damage, and a bonus of " << gabe.GetAttackBonus() << " to attack." << endl;
}

void CreateEnemy(Player& bob, int levelCounter) {
	string name[10] = {"Bob", "Goblin king", "Troll", "Orc", "Goblin", "Skeleton", "Zombie", "Congress", "Creeper", "Jello Pudding"};
	string useName = name[(rand()%10)];
	int hitDie = (8+(2*levelCounter));
	int attack = (8+(2*levelCounter));
	int AC = (8+(2*levelCounter));
	int attackBonus(2*levelCounter);
	//cout << "Enter name, hit die, attack die, attack bonus and AC for the character." << endl;
	Player tempPlayer(useName, hitDie, attack, attackBonus, AC);
	bob = tempPlayer;
}

void RunCombat(Fighter& gabe, Player& bob) {
	string fightResult;

	HandlePreCombat(gabe, bob);
	while (bob.IsAlive() && gabe.IsAlive()) {
		Sleep(rand()%700 + 400);
		gabe.RollAttack(bob, fightResult);
		cout << fightResult << endl;
		Sleep(rand()%700 + 400);
		if (bob.IsAlive()) {
			bob.RollAttack(gabe, fightResult);
			cout << fightResult << endl;
			}
		}
}

void PlayerPrompt2(Fighter& gabe) {
	string inName;
	char classLetter;
	do {
	cout << "Enter name and class letter. (N for ninja, B for barbarian, F for fighter, T for tank, or A for archer.)" << endl;
	cin >> inName >> classLetter;
	} while (!IsLetterOK(classLetter));
	Fighter tempFighter(inName, classLetter);
	gabe = tempFighter;
}

void GetPlayerFromFile2(ifstream& inFile, Fighter& initPlayer) {
	string name;
	int hitPoints;
	int hitDie;
	int attack;
	int AC;
	int attackBonus;
	int level;
	char charClass;
	inFile >> name >> hitPoints >> hitDie >> attack >> attackBonus >> AC >> level >> charClass;
	Fighter tempPlayer(name, hitPoints, hitDie, attack, attackBonus, AC, level, charClass);
	initPlayer = tempPlayer;
}

bool IsLetterOK(char classLetter) {
	if (classLetter == 'N' || classLetter == 'B' || classLetter == 'F' || classLetter == 'T' || classLetter == 'A')
		return true;
	else return false;
}

void HandlePreCombat(Fighter gabe, Player& bob) {
	int numFirstStrikes;
	string toWriteOut;
	
	numFirstStrikes = gabe.FirstStrikes();
	for (int i = 0; i < numFirstStrikes; i++) {
		cout << "Pre-emptive strike! ";
		gabe.RollAttack(bob, toWriteOut);
		cout << toWriteOut << endl;
		Sleep(rand()%500 + 200);
	}
}