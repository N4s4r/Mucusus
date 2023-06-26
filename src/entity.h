#pragma once

#include "defines.h"

#include "framework.h"
#include "texture.h"
#include "animation.h"

class Entity
{
public:
    Entity(){};
    virtual ~Entity(){};

    str name;
    Matrix44 model;

    vt<Animation *> animations;

    // Pointer to parent
    Entity* parent;

    // Pointers to children
    vt<Entity*> children;

    void addChild(Entity* child);
    void removeChild(Entity* child);

    // Get transform in world coordinates
    Matrix44 getGlobalMatrix();

    virtual void render();
    virtual void render(Matrix44 extra_model){};
    virtual void update(float dt);

    Vector3 getPosition() { return model.getTranslation(); };
};