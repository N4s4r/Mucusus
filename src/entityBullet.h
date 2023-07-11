#pragma once
#include "entity.h"
#include "entityEnemy.h"

#define BULLETLIVETIME 10.0f

class EntityBullet : public Entity
{
public:
	EntityBullet();
    EntityBullet(Mesh* mesh, Shader* shader, Texture* texture);

    Shader* shader;
    Mesh* meshFULL;
    Mesh* meshMID;
    Mesh* meshLOW;
    Texture* texture;

    EntityEnemy* enemySource = nullptr;

    Vector3 direction;

    float velocity;
    float liveTime;
    
    bool isActive = false;

    void activate(EntityEnemy* source = nullptr);
    void deactivate();

    virtual void update(float dt) override;
    void render();
};

