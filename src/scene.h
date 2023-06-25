#pragma once

#include "defines.h"
#include "entity.h"

class Scene
{
public:
    static Scene *instance;

    Scene();
    ~Scene();

    Entity *root;

    void render();
    void update(float dt);

    void parse();
};