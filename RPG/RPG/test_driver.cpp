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

	// CAL, 8-mar-2013:  I have added this line, ha!
	Derpola = Dungeon(inFile);
	cout << Derpola.GetDescription() << endl;
	while (cin >> moveChar) {
		Derpola.Movement(moveChar);
		cout << Derpola.GetDescription() << endl;
	}
}