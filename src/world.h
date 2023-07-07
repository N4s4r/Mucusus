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

class World
{
public:
    World();

    char* roomTypeNames[ROOMTYPES] = { "roomBasic", "roomDiamond", "roomSquare" };

    vt<EntityMeshRoom *> roomTypes;
    vt<EntityMeshRoom*> mapGrid{ GRIDWIDTH * GRIDHEIGHT };

    EntityMeshRoom* currentRoom;

    void loadRooms();
    void randomizeMap();
    void randomLoad();
    void setTestRooms();

    void update();
    void setCurrentRoom();
};