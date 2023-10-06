#include <iostream>
#include "BaseRoom.h"

using namespace std;

BaseRoom* currentRoom = new BaseRoom();

void changeRoom(CardinalDirection dir)
{
	BaseRoom* nextRoom = currentRoom->checkAdjacent(dir);
	if (nextRoom != nullptr)
	{
		currentRoom = nextRoom;
		currentRoom->printName();
		return;
	}
	else
	{
		cout << "You can't go that way!";
	}
}

bool validate(int userInput)
{
	if (userInput >= 0 && userInput <= 5)
	{
		return true;
	}
	return false;
}

CardinalDirection getInput()
{
	int userInput = -1;
	while (validate(userInput) != true)
	{
		cout << endl << endl << "Where would you like to go? " << endl;
		cin >> userInput;
	}
	CardinalDirection dir = static_cast<CardinalDirection>(userInput);
	return dir;
}

BaseRoom* firstRoom = new BaseRoom("You are in a dungeon cell. There is a door to the North.");
BaseRoom* secondRoom = new BaseRoom("You are in a damp hallway. There is a door to the South.");

int main()
{
	cout << "Literally just type 0 - It's not going to do much but like that's just the way it is. Refining comes later";
	currentRoom = firstRoom;

	firstRoom->setAdjacent(secondRoom, CardinalDirection::North);
	secondRoom->setAdjacent(firstRoom, CardinalDirection::South);

	firstRoom->printName();

	changeRoom(getInput());

	return 0;
}