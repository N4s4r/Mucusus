#pragma once

#include "defines.h"

#include "entityMesh.h"
#include "entityMeshRoom.h"
#include "entity.h"
#include "includes.h"
#include "camera.h"
#include "utils.h"
#include "shader.h"

#include <cstdlib>
#include <ctime>

#define MAX_BULLETS 50
#define ROOMTYPES 3

class EntityMesh;
class Entity;

class World
{
public:
    World();

    char* roomTypeNames[ROOMTYPES] = { "room0", "roomDiamond", "roomSquare" };

    vt<EntityMeshRoom *> roomTypes;
    vt<EntityMesh *> mapGrid;

    void loadRooms();
    void randomizeMap();
};