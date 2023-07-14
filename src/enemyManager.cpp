#include "enemyManager.h"
#include "game.h"
#include "entityPlayer.h"
#include "entityMeshRoom.h"

EnemyManager::EnemyManager()
{
    normal_enemy_mesh = Mesh::Get("data/meshes/SUS.obj");
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

    // If K is pressed, kill one enemy
    if (Input::wasKeyPressed(SDL_SCANCODE_K))
    {
        if (enemies.size() > 0)
        {
            enemies[0]->die();
        }
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
    EntityMeshRoom *current_room = Game::instance->player->currentRoom;
    // Add four enemies in the corners of the room where the player is
    Vector3 room_center = current_room->model.getTranslation();
    addNormalEnemy(room_center + Vector3(1, 0, 1));
    addNormalEnemy(room_center + Vector3(1, 0, 15));
    addNormalEnemy(room_center + Vector3(15, 0, 1));
    addNormalEnemy(room_center + Vector3(15, 0, 15));
}

void EnemyManager::removeEnemy(EntityEnemy *enemy)
{
    FOR(i, 0, enemies.size())
    {
        if (enemies[i] == enemy)
        {
            enemies.erase(enemies.begin() + i);
            return;
        }
    }
}