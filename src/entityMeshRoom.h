#pragma once
#include "defines.h"
#include "entity.h"

class EntityMesh;
class EntityDoor;

class EntityMeshRoom : public Entity
{
	struct sRenderData
	{
		Texture *texture = nullptr;
		Shader *shader = nullptr;
		std::vector<Matrix44> models;
	};

	std::map<std::string, sRenderData> meshes_to_load;

public:
	EntityMeshRoom(bool isRoom);
	int roomID = -1;
	bool isRoom;
	bool isEdge;

	Matrix44 room_model;
	vt<EntityMesh *> staticEntities;
	vt<EntityDoor *> roomDoors;

	EntityMesh *ceiling = NULL;
	EntityMesh *floor = NULL;
	EntityMesh *pilarEast = NULL;
	EntityMesh *pilarWest = NULL;
	EntityMesh *pilarSouth = NULL;
	EntityMesh *pilarNorth = NULL;
	EntityMesh *bigaEast = NULL;
	EntityMesh *bigaWest = NULL;
	EntityMesh *bigaSouth = NULL;
	EntityMesh *bigaNorth = NULL;
	EntityMesh *wallEast = NULL;
	EntityMesh *wallWest = NULL;
	EntityMesh *wallSouth = NULL;
	EntityMesh *wallNorth = NULL;
	EntityMesh *midCube = NULL;
	EntityMesh *diagonalNW = NULL;
	EntityMesh *diagonalSW = NULL;
	EntityMesh *diagonalNE = NULL;
	EntityMesh *diagonalSE = NULL;

	EntityMeshRoom();

	bool parseScene(const char *filename);
	void addStaticEntity(EntityMesh *entity);

	void loadDoors();

	bool isCleared = false;
};
