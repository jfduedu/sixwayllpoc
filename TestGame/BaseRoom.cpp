#include "BaseRoom.h"

BaseRoom::BaseRoom()
{
	for (int i = 0; i < 6; i++)
	{
		roomConnections[i] = nullptr;
	}
}

BaseRoom::BaseRoom(string name)
{
	roomName = name;
	
	for (int i = 0; i < 6; i++)
	{
		roomConnections[i] = nullptr;
	}
}

BaseRoom* BaseRoom::checkAdjacent(CardinalDirection dir)
{
	if (dir >= 0 && dir <= 5 && roomConnections[dir] != nullptr)
	{
		return roomConnections[dir];
	}
	return nullptr;
}

void BaseRoom::setAdjacent(BaseRoom* adjRoom, CardinalDirection dir, bool twoWay = false)
{
	if (dir >= 0 && dir <= 5)
	{
		roomConnections[dir] = adjRoom;
	}
	if  (twoWay == true)
	{
		CardinalDirection oppositeDirection;
		if (dir%2)
		{
			oppositeDirection = static_cast<CardinalDirection>(dir - 1);
		}
		else
		{
			oppositeDirection = static_cast<CardinalDirection>(dir + 1);
		}
		adjRoom->setAdjacent(this, oppositeDirection, false);
	}
}

void BaseRoom::printName()
{
	cout << endl << roomName << endl;
}