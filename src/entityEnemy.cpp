#include "entityEnemy.h"
#include "entityPlayer.h"
#include "stageGame.h"
#include "enemyManager.h"
#include "audio.h"

EntityEnemy::EntityEnemy()
{
    // To render
    mesh = NULL;
    texture = NULL;
    shader = NULL;

    // To move
    model.setIdentity();
}

void EntityEnemy::render()
{
    if (mesh && texture && shader)
    {
        shader->enable();
        shader->setUniform("u_color", Vector4(1, 1, 1, 1));
        shader->setUniform("u_viewprojection", Camera::current->viewprojection_matrix);
        shader->setUniform("u_texture", texture);
        shader->setUniform("u_model", model);
        mesh->render(GL_TRIANGLES);
        shader->disable();
    }
}

void EntityEnemy::update(float dt)
{
    // TODO: move the enemy towards the player
    Vector3 playerPos = Game::instance->player->model.getTranslation();
    Vector3 enemyPos = model.getTranslation();
    Vector3 direction = playerPos - enemyPos;
    direction.y = 0;
    direction.normalize();
    Vector3 movement = direction * 2.0f * dt;
    model.translate(movement.x, movement.y, movement.z);
}

void EntityEnemy::applyInputDamage(float damage)
{
    health -= damage;
    if (health <= 0)
    {
        die();
    }
}

void EntityEnemy::die()
{
    Stage *stage = Game::instance->stages[(int)Game::instance->currentStage];
    StageGame *stageGame = (StageGame *)stage;
    EnemyManager *enemyManager = stageGame->enemy_manager;
    enemyManager->removeEnemy(this);

    const char *audio_filename = "data/audios/SUS_kill.wav";
    Audio::Play(audio_filename, false);
}