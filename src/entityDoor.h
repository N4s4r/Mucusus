#pragma once
#include "entity.h"

#define OPENING_SPEED 1.0f;
#define CLOSING_SPEED 2.0f;

class EntityDoor : public Entity
{
public:
    EntityDoor();
    EntityDoor(Vector3 position, bool isExternal);

    Shader* shader;
    Mesh* meshFULL;
    Mesh* meshMID;
    Mesh* meshLOW;
    Texture* texture;

	bool isExternal;
	bool isClosed = true;

	void close();
	void open();

    void render();
};

