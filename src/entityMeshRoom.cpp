#include "defines.h"
#include "entityMeshRoom.h"

EntityMeshRoom::EntityMeshRoom()
{
    // E_wall = new EntityMesh(Game::instance->X_wall_mesh, Game::instance->wall_texture, Matrix44::IDENTITY);
    // W_wall = new EntityMesh(Game::instance->X_wall_mesh, Game::instance->wall_texture, Matrix44::IDENTITY);
    N_wall = new EntityMesh(Game::instance->X_wall_mesh, Game::instance->wall_texture, Matrix44::IDENTITY);
    S_wall = new EntityMesh(Game::instance->X_wall_mesh, Game::instance->wall_texture, Matrix44::IDENTITY);
    N_wall_model.rotate(-90 * DEG2RAD, Vector3(1, 0, 0));
    N_wall_model.translate(0, 4, -2);
    S_wall_model.rotate(-90 * DEG2RAD, Vector3(1, 0, 0));
    S_wall_model.translate(0, -4, -2);
    // Set the textures
    // E_wall->texture = Game::instance->wall_texture;
    // W_wall->texture = Game::instance->wall_texture;
    N_wall->texture = Game::instance->wall_texture;
    S_wall->texture = Game::instance->wall_texture;
}

void EntityMeshRoom::render()
{
    // E_wall->render(E_wall_model);
    // W_wall->render(W_wall_model);
    N_wall->render(N_wall_model);
    S_wall->render(S_wall_model);
}

void EntityMeshRoom::update(float dt)
{
    E_wall->update(dt);
    W_wall->update(dt);
    N_wall->update(dt);
    S_wall->update(dt);
}