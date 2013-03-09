#include "player_character.h"
#include "fighter_character.h"
#include <iostream>
#include <fstream>
#include "dungeon.h"

using namespace std;

int main() {
	ifstream inFile;
	Dungeon Derpola;
	inFile.open("dungeon.dat");
	char moveChar;

	Derpola = Dungeon(inFile);
	cout << Derpola.GetDescription() << endl;
	while (cin >> moveChar) {
		Derpola.Movement(moveChar);
		cout << Derpola.GetDescription() << endl;
	}
}