#pragma once
#include <iostream>

using namespace std;

enum CardinalDirection { North = 0, South = 1, East = 2, West = 3, Above = 4, Below = 5};

class BaseRoom
{
public:
	BaseRoom();
	BaseRoom(string name);
	BaseRoom* checkAdjacent(CardinalDirection dir);
	void setAdjacent(BaseRoom* adjRoom, CardinalDirection dir);
	void printName();
private:
	string roomName;
	BaseRoom* roomConnections[6];
};