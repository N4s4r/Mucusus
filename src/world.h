#pragma once

#include "defines.h"

#include "entityMesh.h"
#include "entity.h"
#include "includes.h"
#include "camera.h"
#include "utils.h"
#include "shader.h"

#define MAX_BULLETS 50

class EntityMesh;
class Entity;

class World
{
public:
    World();

    vt<EntityMesh *> rooms;
};