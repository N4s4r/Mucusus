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

class World
{
public:
    World();

    char* roomTypeNames[ROOMTYPES] = { "room0", "roomDiamond", "roomSquare" };

    vt<EntityMeshRoom *> roomTypes;
    vt<EntityMeshRoom *> mapGrid;

    void loadRooms();
    void randomizeMap();
    void setTestRooms();
};