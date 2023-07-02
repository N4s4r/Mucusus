#pragma once

#include "defines.h"
#include "entityEnemy.h"
#include "mesh.h"
#include "texture.h"
#include "shader.h"

class EnemyManager
{
public:
    Mesh *normal_enemy_mesh;
    Texture *normal_enemy_texture;
    Shader *normal_enemy_shader;
    vt<EntityEnemy *> enemies;

    EnemyManager();
    ~EnemyManager();

    void render();
    void update(float dt);

    void addNormalEnemy(Vector3 pos);

    void removeEnemy(EntityEnemy *enemy);
};