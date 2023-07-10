#include "defines.h"

#include "entityMesh.h"
#include "shader.h"

EntityMesh::EntityMesh()
{
}

EntityMesh::EntityMesh(Mesh *mesh, Shader *shader, Texture *texture)
{
    this->name = "MyEntityMesh";
    this->mesh = mesh;
    this->texture = texture;
    this->shader = shader;
}

void EntityMesh::render()
{
    Camera* cam = Game::instance->camera;

    float time = Game::instance->time;

    if (!shader)
        return;

    shader->enable();

    shader->setUniform("u_color", Vector4(1, 1, 1, 1));
    shader->setUniform("u_viewprojection", cam->viewprojection_matrix);
    if (texture)
        shader->setUniform("u_texture", texture, 0);
    else glBindTexture(GL_TEXTURE_2D, 0);

    shader->setUniform("u_time", time);
    shader->setUniform("u_tiles", 10.0f);
    Matrix44 mmatrix = getGlobalMatrix();
    shader->setUniform("u_model", mmatrix);

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