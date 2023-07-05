#include "world.h"



World::World()
{
}

void World::loadRooms()
{
	for (int i = 0; i < ROOMTYPES; i++)
	{
		EntityMeshRoom* room = new EntityMeshRoom();
		room->parseScene(this->roomTypeNames[i]);
		this->roomTypes.push_back(room);
	}
}

void World::randomizeMap()
{
	// Seed the random number generator
	std::srand(std::time(0));
	// Generate a random number between 1 and 100
	int randomNumber = std::rand() % 100 + 1;

	
}