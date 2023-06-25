#pragma once

#include "defines.h"

#include "entity.h"
#include "game.h"
#include "camera.h"

class EntityMesh : public Entity
{
public:
    vt<str> audios;

    EntityMesh();
    EntityMesh(Mesh *mesh, Texture *texture, Matrix44 model);

    virtual void render() override;
    virtual void update(float dt) override;
};