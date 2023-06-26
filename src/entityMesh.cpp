#include "defines.h"

#include "entityMesh.h"
#include "shader.h"

EntityMesh::EntityMesh()
{
}

EntityMesh::EntityMesh(Mesh *mesh, Texture *texture, Matrix44 model)
{
    this->name = "MyEntityMesh";
    this->mesh = mesh;
    this->texture = texture;
    this->model = model;
}

void EntityMesh::render()
{
    float time = Game::instance->time;

    // Select chader
    Shader *shader;
    shader = Game::instance->shader;

    if (!shader)
        return;

    shader->enable();

    Camera *cam = Game::instance->camera;
    shader->setUniform("u_color", Vector4(1, 1, 1, 1));
    shader->setUniform("u_viewprojection", cam->viewprojection_matrix);
    shader->setUniform("u_texture", texture, 0);
    shader->setUniform("u_time", time);

    shader->setUniform("u_model", model);

    mesh->render(GL_TRIANGLES);

    shader->disable();
}

void EntityMesh::render(Matrix44 extra_model)
{
    float time = Game::instance->time;

    // Select chader
    Shader *shader;
    shader = Game::instance->shader;

    if (!shader)
        return;

    shader->enable();

    Camera *cam = Game::instance->camera;
    shader->setUniform("u_color", Vector4(1, 1, 1, 1));
    shader->setUniform("u_viewprojection", cam->viewprojection_matrix);
    shader->setUniform("u_texture", texture, 0);
    shader->setUniform("u_time", time);

    Matrix44 new_model = model * extra_model;

    shader->setUniform("u_model", new_model);

    mesh->render(GL_TRIANGLES);

    shader->disable();
}

void EntityMesh::update(float dt)
{
}