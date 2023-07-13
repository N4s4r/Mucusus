#include "entityEnemy.h"
#include "entityPlayer.h"

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
    Vector3 movement = direction * 0.5f * dt;
    model.translate(movement.x, movement.y, movement.z);
}

bool EntityEnemy::checkMeshCollision(vt<sCollisionData> &collisions, Matrix44 globalMatrix, Mesh *mesh)
{
    Vector3 position = model.getTranslation();

    float sphereRadius = 0.5f;
    Vector3 colPoint, colNormal;
    if (mesh->testSphereCollision(globalMatrix, position, sphereRadius, colPoint, colNormal))
    {
        collisions.push_back({colPoint, colNormal.normalize()});
    }
    return !collisions.empty();
}

void EntityEnemy::applyInputDamage(float damage)
{
    health -= damage;
}
