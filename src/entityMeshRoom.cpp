#include "defines.h"
#include "entityMeshRoom.h"

EntityMeshRoom::EntityMeshRoom()
{
    E_wall = new EntityMesh(Game::instance->Z_wall_mesh, Game::instance->wall_texture, Matrix44::IDENTITY);
    W_wall = new EntityMesh(Game::instance->Z_wall_mesh, Game::instance->wall_texture, Matrix44::IDENTITY);
    N_wall = new EntityMesh(Game::instance->X_wall_mesh, Game::instance->wall_texture, Matrix44::IDENTITY);
    S_wall = new EntityMesh(Game::instance->X_wall_mesh, Game::instance->wall_texture, Matrix44::IDENTITY);
    N_wall->model.rotate(-90 * DEG2RAD, Vector3(1, 0, 0));
    N_wall->model.translate(0, 4, -2);
    S_wall->model.rotate(-90 * DEG2RAD, Vector3(1, 0, 0));
    S_wall->model.translate(0, -4, -2);
    E_wall->model.rotate(-90 * DEG2RAD, Vector3(0, 1, 0));
    E_wall->model.rotate(-90 * DEG2RAD, Vector3(1, 0, 0));
    E_wall->model.translate(0, -6, -2);
    W_wall->model.rotate(-90 * DEG2RAD, Vector3(0, 1, 0));
    W_wall->model.rotate(-90 * DEG2RAD, Vector3(1, 0, 0));
    W_wall->model.translate(0, 6, -2);
}

void EntityMeshRoom::render()
{
    E_wall->render(E_wall_model);
    W_wall->render(W_wall_model);
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