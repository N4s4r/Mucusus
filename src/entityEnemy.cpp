#include "entityEnemy.h"

EntityEnemy::EntityEnemy()
{
    // To render
    mesh = NULL;
    texture = NULL;
    shader = NULL;

    // To move
    model.setIdentity();
    max_speed = 1.0f;
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
    // TODO: move the enemy
}