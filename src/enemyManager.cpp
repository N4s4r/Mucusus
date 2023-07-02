#include "enemyManager.h"

EnemyManager::EnemyManager()
{
    normal_enemy_mesh = Mesh::Get("data/meshes/SUS.obj");
    // TODO: load the sus texture
    normal_enemy_texture = Texture::Get("data/textures/box.tga");
    normal_enemy_shader = Shader::Get("data/shaders/basic.vs", "data/shaders/texture.fs");
}

EnemyManager::~EnemyManager()
{
    EACH(it, enemies)
    {
        delete it;
    }

    enemies.clear();
}

void EnemyManager::render()
{
    EACH(it, enemies)
    {
        it->render();
    }
}

void EnemyManager::update(float dt)
{
    EACH(it, enemies)
    {
        it->update(dt);
    }
}

void EnemyManager::addNormalEnemy(Vector3 pos)
{
    EntityEnemy *enemy = new EntityEnemy();
    enemy->mesh = normal_enemy_mesh;
    enemy->texture = normal_enemy_texture;
    enemy->shader = Shader::Get("data/shaders/basic.vs", "data/shaders/texture.fs");
    enemy->model.setTranslation(pos.x, pos.y, pos.z);
    enemies.push_back(enemy);
}