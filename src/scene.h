#pragma once

#include "defines.h"
#include "entity.h"

// TODO Use singleton pattern
class Scene
{
public:
    vt<Entity *> entities;
};