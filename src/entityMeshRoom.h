#pragma once

#include "defines.h"
#include "entityMesh.h"
#include "game.h"

class EntityMeshRoom
{
    EntityMesh *N_wall;
    EntityMesh *S_wall;
    EntityMesh *E_wall;
    EntityMesh *W_wall;
    EntityMesh *floor;
    EntityMesh *ceiling;

public:
    Matrix44 room_model;

    EntityMeshRoom();

    void render();
    void update(float dt);
};
