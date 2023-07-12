#include "world.h"
#include "entityPlayer.h"
#include "entityBullet.h"
#include "entityDoor.h"

World::World()
{
	initializeBullets();
	bullet = new EntityBullet();
}

void World::initializeBullets(int nBullets)
{
	for (int i = 0; i < nBullets; i++)
	{
		EntityBullet* bullet = new EntityBullet();
		bulletBuffer.push_back(bullet);
	}
}

void World::shootBullet(Vector3 direction, EntityEnemy* source) 
{
	//EntityBullet* bullet = bulletBuffer[0];

	auto it = std::find_if(bulletBuffer.begin(), bulletBuffer.end(), [&](const auto& ptr) {	return ptr == bullet; });
	if (source)
	{
		bullet->enemySource = source;
		bullet->velocity = source->projectileSpeed;
	}
	else
	{
		bullet->velocity = Game::instance->player->projectileSpeed;
	}
	bullet->direction = direction;
	bullet->activate();
	Vector3 pos = Game::instance->camera->eye;
	bullet->model.setTranslation(pos.x, pos.y, pos.z);
	//bullet.model.setTranslation(position.x, position.y, position.z);
}

void World::stashBullet(EntityBullet* bullet)
{
}

void World::loadRooms()
{
	for (int i = 0; i < ROOMTYPES; i++)
	{
		EntityMeshRoom* room = new EntityMeshRoom(false);
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

void World::placeRoom(int roomID, int roomType) 
{
	EntityMeshRoom* room = new EntityMeshRoom(true);
	room->parseScene(roomTypeNames[roomType]);
	int i = roomID % GRIDHEIGHT;
	int j = roomID / GRIDHEIGHT;
	room->roomID = roomID;
	Vector3 roomPosition = Vector3(j * 16.0f, .0f, i * 16.0f);
	room->model.setTranslation(roomPosition.x, roomPosition.y, roomPosition.z);
	mapGrid[roomID] = room;
	placedRooms += 1;
}

void World::tryNeighbour(int roomID)
{
	std::srand(std::time(0));
	if (roomID < GRIDHEIGHT || roomID > GRIDHEIGHT * (GRIDHEIGHT - 1) || roomID % GRIDHEIGHT == 0 || (roomID + 1) % GRIDHEIGHT == 0) return; // edges must be empty
	if (mapGrid[roomID]) return; // already a room
	int neighbourNeighbours = 0;
	for (int i = 0; i < 4; i++) // count Neighbour Neighbours
	{
		if (mapGrid[roomID + neightbourOps[i]]) neighbourNeighbours += 1;
	}
	if (neighbourNeighbours > 2) return; // if more than two neighbours continue
	if (placedRooms == totalRooms) return; // All rooms placed
	if (std::rand() % 2 == 1) return; // 50% of filling the room
	placeRoom(roomID, std::rand() % 3); // place room
	
	for (int i = 0; i < 4; i++)
	{
		tryNeighbour(roomID + neightbourOps[i]);
	}
}

void World::randomLoad()
{
	// Seed the random number generator
	std::srand(std::time(0));
	totalRooms = 8 + std::rand() % 3;
	int roomID, roomType, neighbour, neighbourNeighbours;
	roomID = GRIDHEIGHT * GRIDHEIGHT / 2;
	// Place central Room
	placeRoom(roomID, 0);
	placedRooms += 1;

	// access Neighbours
	for (int i = 0; i < 4; i++)
	{
		tryNeighbour(roomID + neightbourOps[i]);
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

int World::countRoomNeighbours(EntityMeshRoom* room)
{
	int neighbourNeighbours = 0;
	for (int i = 0; i < 4; i++) // count Neighbour Neighbours
	{
		if (mapGrid[room->roomID + neightbourOps[i]]) neighbourNeighbours += 1;
	}
	return neighbourNeighbours;
}

void World::placeRoomsDoors()
{
 	EACH(room, mapGrid)
	{
		if (!room) continue;
		int neighbourNeighbours = 0;
		int roomID = room->roomID;
		bool isExternal = false;
		for (int direction = NORTH; direction < 4; direction++) // count Neighbour Neighbours
		{
			bool isExternal = false;
			if (mapGrid[room->roomID + neightbourOps[direction]]) isExternal = true;
			Vector3 position;
			switch (direction)
			{
			case NORTH:
				position = Vector3(16.0f, 0.0f, 6.0f);
				break;
			case EAST:
				position = Vector3(10.0f, 0.0f, 16.0f);
				break;
			case SOUTH:
				position = Vector3(0.0f, 0.0f, 6.0f);
				break;
			case WEST:
				position = Vector3(6.0f, 0.0f, 0.0f);
				break;
			}
			EntityDoor* door = new EntityDoor(position, isExternal);
			room->children.push_back(door);
			door->parent = room;
			room->roomDoors.push_back(door);
		}
	}
}

void World::render()
{

}

//void World::stashBullet(EntityBullet* bullet)
//{
//	// Find the position of the desired pointer in vectorA
//	auto it = std::find_if(activeBullets.begin(), activeBullets.end(), [&](const auto& ptr) {
//		return ptr.get() == bullet->get();
//	});
//
//	if (it != activeBullets.end()) {
//		// Use std::move to transfer ownership of the pointer from vectorA to vectorB
//		bulletBuffer.emplace_back(std::move(*it));
//		activeBullets.erase(it); // Remove the pointer from vectorA
//	}
//}
//
//void World::shootBullet(Vector3 direction, EntityEnemy* source)
//{
//	EntityBullet* bullet = bulletBuffer[0];
//	auto it = std::find_if(activeBullets.begin(), activeBullets.end(), [&](const auto& ptr) {
//		return ptr.get() == bullet->get();
//		});
//	if (source)
//	{
//		bullet->enemySource = source;
//		bullet->velocity = source->projectileSpeed;
//		bullet->direction = direction;
//		bullet->activate();
//		activeBullets.push_back(std::move(*it));
//		bulletBuffer.erase(it);
//	}
//}
