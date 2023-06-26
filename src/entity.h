#pragma once

#include "defines.h"

#include "framework.h"
#include "mesh.h"
#include "texture.h"
#include "animation.h"

class Entity
{
public:
    Entity(){};
    virtual ~Entity(){};

    str name;
    Matrix44 model;

    Mesh *mesh;
    Texture *texture;

    vt<Animation *> animations;

    virtual void render(){};
    virtual void render(Matrix44 extra_model){};
    virtual void update(float dt){};

    Vector3 getPosition() { return model.getTranslation(); };
};