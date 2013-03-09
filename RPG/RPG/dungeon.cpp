#include "dungeon.h"
#include <fstream>
#include <cstdlib>
#include <cstddef>
#include <iostream>

using namespace std;

class ForwardError {};
class BackwardError {};

Dungeon::Dungeon() {
	dunStart = new Room;
	dunStart->description = "DEFAULT_ROOM";
	dunStart->isMonster = false;
	dunStart->next = NULL;
	playerLoc = dunStart;
}

// Pre: File contains correctly formatted room(s).
// Post: Dungeon has been initialized with appropriate rooms.
Dungeon::Dungeon(ifstream& inFile) {
	Room* prevLoc = NULL;
	int monsterLevel;
	string monsterName;
	dunStart = new Room;
	playerLoc = dunStart;
	string throwAway;
	getline(inFile, throwAway);

	playerLoc->previous= NULL;
	getline(inFile, playerLoc->description);
	inFile >> playerLoc->isMonster >> monsterLevel >> monsterName;
	getline(inFile, throwAway); // Read past EOL character.
	playerLoc->monster = Player(monsterName, monsterLevel);
	prevLoc = playerLoc;

	while (inFile) {
		playerLoc->next = new Room;
		playerLoc = playerLoc->next;
		playerLoc->previous=prevLoc;
		getline(inFile, playerLoc->description);
		inFile >> playerLoc->isMonster >> monsterLevel >> monsterName;
		getline(inFile, throwAway); // Read past EOL character.
		playerLoc->monster = Player(monsterName, monsterLevel);
		prevLoc = playerLoc;
	}
	playerLoc->next = NULL;
	playerLoc = dunStart;
}

string Dungeon::GetDescription() {
	return playerLoc->description;
}

void Dungeon::GoForward() {
	if (playerLoc->next == NULL)
		throw ForwardError();
	else playerLoc = playerLoc->next;
}

void Dungeon::GoBackwards() {
	if (playerLoc->previous == NULL)
		throw BackwardError();
	else playerLoc = playerLoc->previous;
}

bool Dungeon::IsMonster() {
	return playerLoc->isMonster;
}

bool Dungeon::IsBack() {
	return (playerLoc->previous != NULL);
}

bool Dungeon::IsForward() {
	return (playerLoc->next != NULL);
}

Player Dungeon::GetMonster() {
	return playerLoc->monster;
}

void Dungeon::Movement(char toMove) {
	try {
		switch (toMove) {
			case 'F':
				GoForward();
				break;
			case 'B':
				GoBackwards();
				break;
		};
	}
	catch (ForwardError()) {
		cout << "Warning!  NULL dereference attempted!" << endl;
	}
	catch (BackwardError()) {
		cout << "Warning! NULL dereference attempted!" << endl;
	}
}
