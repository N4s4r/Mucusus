#pragma once

#include "defines.h"
#include "entityMesh.h"
#include "game.h"

class EntityMeshRoom
{

public:
    Matrix44 N_wall_model;
    Matrix44 S_wall_model;
    Matrix44 E_wall_model;
    Matrix44 W_wall_model;
    EntityMesh *N_wall;
    EntityMesh *S_wall;
    EntityMesh *E_wall;
    EntityMesh *W_wall;

    EntityMeshRoom();

    void render();
    void update(float dt);
};
