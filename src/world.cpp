#include "world.h"
#include "entityPlayer.h"


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

//void World::randomizeMap()
//{
//	// Seed the random number generator
//	std::srand(std::time(0));
//
//	int roomType;
//	for (int i = 0; i < GRIDWIDTH; i++)
//	{
//		for (int j = 0; j < GRIDHEIGHT; j++)
//		{
//			if (i == 0 && j == 0)
//			{
//				roomType = 0;
//			} 
//			else
//			{
//				roomType = std::rand() % 3;
//			}
//			EntityMeshRoom* roomTemplate = roomTypes[0];
//			EntityMeshRoom* room = new EntityMeshRoom(*roomTemplate);
//			if ((i * GRIDHEIGHT + j) % 2 == 0) room->isCleared = true;
//			Vector3 roomPosition = Vector3(j * 16.0f, .0f, i * 16.0f);
//			room->model.setTranslation(roomPosition.x, roomPosition.y, roomPosition.z);
//			mapGrid[i * GRIDHEIGHT + j] = room;
//		}
//	}
//}

void World::randomLoad()
{
	// Seed the random number generator
	std::srand(std::time(0));

	int roomType;
	for (int i = 0; i < GRIDWIDTH; i++)
	{
		for (int j = 0; j < GRIDHEIGHT; j++)
		{
			if (i == 0 && j == 0)
			{
				roomType = 0;
			} 
			else
			{
				roomType = std::rand() % 3;
			}
			EntityMeshRoom* room = new EntityMeshRoom();
			room->parseScene(roomTypeNames[roomType]);
			Vector3 roomPosition = Vector3(j * 16.0f, .0f, i * 16.0f);
			room->model.setTranslation(roomPosition.x, roomPosition.y, roomPosition.z);
			mapGrid[i * GRIDHEIGHT + j] = room;
		}
	}
}

void World::setTestRooms()
{
	vt<EntityMeshRoom*> gridrow;
	for (int i = 0; i < ROOMTYPES; i++)
	{
		Vector3 roomPosition = Vector3(0.0f, .0f, (i + 0) * 16.0f);
		EntityMeshRoom* room = roomTypes[i];
		room->model.setTranslation(roomPosition.x, roomPosition.y, roomPosition.z);
		mapGrid[i] = room;
	}
	
}

void World::update()
{
}

void World::setCurrentRoom()
{
	Vector3 player_pos = Game::instance->player->model.getTranslation();
	int i = player_pos.x / ROOMHEIGHT;
	int j = player_pos.z / ROOMWIDTH;

	std::cout << i << j << std::endl;
	currentRoom = mapGrid[i * GRIDHEIGHT + j];
}
