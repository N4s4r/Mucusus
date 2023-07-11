#pragma once

#include "defines.h"

#include "entityMeshRoom.h"
#include "includes.h"
#include "camera.h"
#include "utils.h"
#include "shader.h"

#include <cstdlib>
#include <ctime>

#define MAX_BULLETS 50
#define ROOMTYPES 3
#define ROOMWIDTH 16
#define ROOMHEIGHT 16
#define GRIDWIDTH 4
#define GRIDHEIGHT 4

class EntityEnemy;
class EntityBullet;

class World
{
public:
    World();

    char* roomTypeNames[ROOMTYPES] = { "roomBasic", "roomDiamond", "roomSquare" };

    vt<EntityMeshRoom *> roomTypes;
    vt<EntityMeshRoom*> mapGrid{ GRIDWIDTH * GRIDHEIGHT };

	vt<EntityEnemy*> activeEnemies;

	vt<EntityBullet*> bulletBuffer;
	EntityBullet* bullet;
	//vt<EntityBullet*> activeBullets;

    EntityMeshRoom* currentRoom;

	vt<EntityMesh*> ceiling;
	vt<EntityMesh*> floor;
	vt<EntityMesh*> pilarEast;
	vt<EntityMesh*> pilarWest;
	vt<EntityMesh*> pilarSouth;
	vt<EntityMesh*> pilarNorth;
	vt<EntityMesh*> bigaEast;
	vt<EntityMesh*> bigaWest;
	vt<EntityMesh*> bigaSouth;
	vt<EntityMesh*> bigaNorth;
	vt<EntityMesh*> wallEast;
	vt<EntityMesh*> wallWest;
	vt<EntityMesh*> wallSouth;
	vt<EntityMesh*> wallNorth;
	vt<EntityMesh*> midCube;
	vt<EntityMesh*> diagonalNW;
	vt<EntityMesh*> diagonalSW;
	vt<EntityMesh*> diagonalNE;
	vt<EntityMesh*> diagonalSE;

    void loadRooms();
    void randomizeMap();
    void randomLoad();
    void setTestRooms();

    void update();
    void setCurrentRoom();
	void render();

	void initializeBullets(int nBullets = MAX_BULLETS);
	void shootBullet(Vector3 direction, EntityEnemy* source = NULL);
	void stashBullet(EntityBullet* bullet);
};