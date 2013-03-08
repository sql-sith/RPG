#include <string>
#include <fstream>
#include "player_character.h"

using namespace std;

struct Room {
	bool isMonster;
	Player monster;
	Room* previous;
	Room* next;
	string description;
};

class Dungeon {
public:
	Dungeon();
	Dungeon (ifstream& InFile);
	string GetDescription();
	void GoForward();
	void GoBackwards();
	bool IsMonster();
	Player GetMonster();
	bool IsBack();
	bool IsForward();
	void Movement(char toMove);
private:
	Room* playerLoc;
	Room* dunStart;
};