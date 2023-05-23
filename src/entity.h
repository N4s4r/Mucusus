#pragma once

#include "defines.h"
#include "framework.h"
#include "mesh.h"
#include "texture.h"
#include "shader.h"
#include "camera.h"

class Entity
{
public:
    // Constructor and destructor
    Entity();
    virtual ~Entity();

    // Some attributes
    str name;
    Matrix44 model;

    // Methods hat should be overwritten
    virtual void render();
    virtual void update(float dt);

    Matrix44 getGlobalMatrix();

    Entity *parent = nullptr;

    // Children
    vt<Entity *> children;
    void addChild(Entity *entity);
    void removeChild(Entity *entity);
};

class EntityMesh : public Entity
{
public:
    Mesh *mesh = nullptr;
    Texture *texture = nullptr;
    Shader *shader = nullptr;
    Vector4 color;

    // Overwritten methods
    void render();
    void update(float dt);
};