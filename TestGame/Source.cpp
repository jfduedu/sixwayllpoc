#include <iostream>
#include <map>
#include <fstream>
#include <vector>
#include "BaseRoom.h"

using namespace std;

BaseRoom* currentRoom = nullptr;

void changeRoom(CardinalDirection dir, bool& leave)
{
	BaseRoom* nextRoom = currentRoom->checkAdjacent(dir);
	if (nextRoom != nullptr)
	{
		currentRoom = nextRoom;
		currentRoom->printDescription();
		leave = false;
		return;
	}
	else
	{
		cout << "You can't go that way!";
		leave = true;
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

//BaseRoom* firstRoom = new BaseRoom("You are in a dungeon cell. There is a door to the North.");
//BaseRoom* secondRoom = new BaseRoom("You are in a damp hallway. There is a door to the South.");

struct __attribute__((__packed__)) mapFile
{
    struct mapFileHeader
    {
        char magic[4];
        uint16_t endian = 0;
        uint16_t version = 0;
        uint32_t hash = 0;
        uint32_t roomCount = 0;
    } header;
    struct roomLayout
    {
		uint32_t id = 0;
		uint32_t direction[6] = {0, 0, 0, 0, 0, 0};
        uint32_t attributes[2] = {0, 0};
    } layout[2000];
};

struct __attribute__((__packed__)) mapDescFile
{
    struct mapFileHeader
    {
        char magic[4];
        uint16_t endian = 0;
        uint16_t version = 0;
        uint32_t hash = 0;
        uint32_t roomCount = 0;
    } header;
    //static mapFileHeader header;
    struct roomDes
    {
		uint32_t id = 0;
		uint32_t stringSize = 0;
		char description[400];
    } descLayout[2000];
};



map<int, BaseRoom*> roomMap;

int main()
{
	// Read the data from the file.
	ifstream in;
	// First open the map file.
    in.open("map.mbm",ifstream::in|ifstream::binary);
	if (!in.is_open())
	{
		cout << "Could not open map.mbm." << endl;
		return 1;
	}
    mapFile map;
    mapDescFile mapDesc;

	// Load map file to bytes.
    std::vector<char> mapBytes(
         (std::istreambuf_iterator<char>(in)),
         (std::istreambuf_iterator<char>()));
	memcpy(&map, mapBytes.data(), sizeof(mapFile)); 
    in.close();

	// Open description file.
	in.open("map.mbd",ifstream::in|ifstream::binary);
	if (!in.is_open())
	{
		cout << "Could not open map.mbd." << endl;
		return 1;
	}
	
	// Load description file to bytes.
	std::vector<char> descBytes(
         (std::istreambuf_iterator<char>(in)),
         (std::istreambuf_iterator<char>()));

	memcpy(&mapDesc, descBytes.data(), sizeof(mapDescFile)); 
    in.close();

	//// Fun part, converting the data to objects

	// Set up the rooms first. Blank data.
	for (int i = 0; i < map.header.roomCount; i++)
	{
		roomMap.insert(std::pair<int, BaseRoom*>(map.layout[i].id, new BaseRoom(mapDesc.descLayout[i].description)));
	}

	// Connect said rooms.
	for (int i = 0; i < map.header.roomCount; i++)
	{
		for (int y = 0; y < sizeof(map.layout[i].direction)/sizeof(uint32_t); y++)
		{
			// There's no connection, skip.
			if (map.layout[i].direction[y] == 0)
			{
				continue;
			}
			// Simplified: roomMap[ID]->setAdjacent(OtherRoom,CardinalDirection)
			roomMap[map.layout[i].id]->setAdjacent(roomMap[map.layout[i].direction[y]],static_cast<CardinalDirection>(y));
		}
	}

	// That's it. Game time.
   
	cout << "{ North = 0, South = 1, East = 2, West = 3, Above = 4, Below = 5}" << endl;
	
	// We'll need a way to set a primary room at runtime, but this will do.
	currentRoom = roomMap[1];

	currentRoom->printDescription();

	bool leaveCheck = false;
	while (leaveCheck == false)
	{
		changeRoom(getInput(),leaveCheck);
	}
	// Once game is over, clear everything.
	for (int i = 0; i < map.header.roomCount; i++)
	{
		delete roomMap[map.layout[i].id];
		roomMap[map.layout[i].id] = nullptr;
	}

	return 0;
}