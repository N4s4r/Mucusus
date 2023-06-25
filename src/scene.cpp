#include "scene.h"

Scene *Scene::instance = NULL;

Scene::Scene()
{
    root = new Entity();
    root->name = "root";
}

Scene::~Scene()
{
    delete root;
}

void Scene::render()
{
    root->render();
}

void Scene::update(float dt)
{
    root->update(dt);
}

void Scene::parse()
{
    // Load the rooms
    Entity *rooms = new Entity();
    rooms->name = "rooms";

    root->addChild(rooms);

    // Load the enemies

    // Load the projectiles

    // Load the objects
}