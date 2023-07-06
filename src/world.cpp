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

void World::randomizeMap()
{
	// Seed the random number generator
	std::srand(std::time(0));

	int roomType;
	for (int i = 0; i < GRIDWIDTH; i++)
	{
		vt<EntityMeshRoom*> gridrow;
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
			EntityMeshRoom* roomTemplate = roomTypes[0];
			EntityMeshRoom* room = new EntityMeshRoom(*roomTemplate);
			Vector3 roomPosition = Vector3(j * 16.0f, .0f, i * 16.0f);
			room->model.setTranslation(roomPosition.x, roomPosition.y, roomPosition.z);
			gridrow.push_back(room);
		}
		mapGrid.push_back(gridrow);
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
		gridrow.push_back(room);
	}
	mapGrid.push_back(gridrow);
}

void World::update()
{
}

void setCurrentRoom()
{
	Vector3 player_pos = Game::instance->player->model.getTranslation();

}
