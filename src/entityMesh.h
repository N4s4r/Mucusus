#pragma once

#include "defines.h"
#include "mesh.h"
#include "entity.h"
#include "game.h"
#include "camera.h"

class EntityMesh : public Entity
{
public:
    vt<str> audios;
    Shader* shader;
    Mesh* mesh;
    Texture* texture;

    EntityMesh();
    EntityMesh(Mesh *mesh, Shader *shader, Texture *texture);

    virtual void render() override;
    virtual void render(Matrix44 extra_model) override;
    virtual void update(float dt) override;
};