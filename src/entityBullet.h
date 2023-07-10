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
    Mesh* mesh;
    Texture* texture;

    EntityEnemy* enemySource = NULL;

    Vector3 direction;
    
    float liveTime;
    
    bool isActive = false;

    void activate();
    void deactivate();

    virtual void update(float dt) override;
};

