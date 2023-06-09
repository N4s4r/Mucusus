#include "enemyManager.h"
#include "game.h"
#include "entityPlayer.h"

EnemyManager::EnemyManager()
{
    normal_enemy_mesh = Mesh::Get("data/meshes/SUS.obj");
    // TODO: load the sus texture
    cout << "Loading sus texture" << endl;
    normal_enemy_texture = Texture::Get("data/textures/wall.tga");
    normal_enemy_shader = Shader::Get("data/shaders/basic.vs", "data/shaders/mtl.fs");
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
    enemy->shader = normal_enemy_shader;
    enemy->model.setTranslation(pos.x, pos.y, pos.z);
    enemy->model.scale(0.5, 0.5, 0.5);
    enemies.push_back(enemy);
}

void EnemyManager::fillRoomWithEnemies()
{
    // Add four enemies in the corners of the room where the player is, computing the position from the player position
    Vector3 playerPos = Game::instance->player->model.getTranslation();
    float distance = 2;
    addNormalEnemy(playerPos + Vector3(distance, 0, distance));
    addNormalEnemy(playerPos + Vector3(distance, 0, -distance));
    addNormalEnemy(playerPos + Vector3(-distance, 0, distance));
    addNormalEnemy(playerPos + Vector3(-distance, 0, -distance));
}