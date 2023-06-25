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
    Entity();
    virtual ~Entity();

    str name;
    Matrix44 model;

    virtual void render();
    virtual void update(float dt);

    Entity *parent;

    vt<Entity *> children;

    void addChild(Entity *child);
    void removeChild(Entity *child);

    Matrix44 getGlobalMatrix();
};

class EntityMesh : public Entity
{
public:
    Mesh *mesh = nullptr;
    Texture *texture = nullptr;
    Shader *shader = nullptr;
    Vector4 color;

    // Constructor
    EntityMesh(Mesh *mesh, Shader *shader, Texture *texture);

    void render();
    void update(float dt);
};

class InstancedEntityMesh : public Entity
{
public:
    Mesh *mesh = nullptr;
    Texture *texture = nullptr;
    Shader *shader = nullptr;
    Vector4 color;

    vt<Matrix44> models;

    // Constructor
    InstancedEntityMesh(Mesh *mesh, Shader *shader, Texture *texture);

    void render();
    void update(float dt);
};