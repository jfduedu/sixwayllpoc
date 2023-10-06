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
	if (dir >= 0 && dir<= 0 && roomConnections[dir] != nullptr)
	{
		return roomConnections[dir];
	}
	return nullptr;
}

void BaseRoom::setAdjacent(BaseRoom* adjRoom, CardinalDirection dir)
{
	if (dir >= 0 && dir <= 5)
	{
		roomConnections[dir] = adjRoom;
	}
}

void BaseRoom::printName()
{
	cout << endl << roomName << endl;
}