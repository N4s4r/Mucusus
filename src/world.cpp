#include "world.h"
#include "entityPlayer.h"
#include "entityBullet.h"


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
			if (room->ceiling) ceiling.push_back(room->ceiling);
			if (room->floor) floor.push_back(room->floor);
			if (room->pilarEast) pilarEast.push_back(room->pilarEast);
			if (room->pilarWest) pilarWest.push_back(room->pilarWest);
			if (room->pilarSouth) pilarSouth.push_back(room->pilarSouth);
			if (room->pilarNorth) pilarNorth.push_back(room->pilarNorth);
			if (room->bigaEast) bigaEast.push_back(room->bigaEast);
			if (room->bigaWest) bigaWest.push_back(room->bigaWest);
			if (room->bigaSouth) bigaSouth.push_back(room->bigaSouth);
			if (room->bigaNorth) bigaNorth.push_back(room->bigaNorth);
			if (room->wallEast) wallEast.push_back(room->wallEast);
			if (room->wallWest) wallWest.push_back(room->wallWest);
			if (room->wallSouth) wallSouth.push_back(room->wallSouth);
			if (room->wallNorth) wallNorth.push_back(room->wallNorth);
			if (room->midCube) midCube.push_back(room->midCube);
			if (room->diagonalNW) diagonalNW.push_back(room->diagonalNW);
			if (room->diagonalSW) diagonalSW.push_back(room->diagonalSW);
			if (room->diagonalNE) diagonalNE.push_back(room->diagonalNE);
			if (room->diagonalSE) diagonalSE.push_back(room->diagonalSE);
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
