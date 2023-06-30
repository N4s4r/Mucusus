#pragma once

#include "defines.h"
#include "entity.h"
#include "mesh.h"
#include "texture.h"
#include "shader.h"
#include "camera.h"

class EntityEnemy : public Entity
{
public:
    // To render
    Mesh *mesh;
    Texture *texture;
    Shader *shader;

    // To move
    Matrix44 model;
    float max_speed;

    // Methods
    EntityEnemy();

    void render();
    void update(float dt);
};
