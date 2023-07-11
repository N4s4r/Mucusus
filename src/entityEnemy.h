#pragma once

#include "entity.h"
#include "mesh.h"
#include "texture.h"
#include "shader.h"
#include "camera.h"
#include "utils.h"
#include "game.h"

class EntityPlayer;

class EntityEnemy : public Entity
{
public:
    // To render
    Mesh *mesh;
    Texture *texture;
    Shader *shader;

    float health = 100.0f;

    // To move
    Matrix44 model;
    float enemy_speed = 100.0f;
    float projectileSpeed = 1.0f;

    float damage = 10.0f;

    // Methods
    EntityEnemy();

    void render();
    void update(float dt);

    bool checkMeshCollision(vt<sCollisionData>& collisions, Matrix44 globalMatrix, Mesh* mesh);
    void applyInputDamage(float damage);
};
