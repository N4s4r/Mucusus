#pragma once
#include "entity.h"

#define OPENING_SPEED 1.0f;
#define CLOSING_SPEED 2.0f;

enum Directions {
	NORTH = 0,
	EAST = 1,
	SOUTH = 2,
	WEST = 3,
};

class EntityDoor : public Entity
{
public:
    EntityDoor();
    EntityDoor(Directions direction, bool isExternal);

    Shader* shader;
    Mesh* meshFULL;
    Mesh* meshMID;
    Mesh* meshLOW;
    Texture* texture;

	float closingSpeed = 4.0f;
	float openingSpeed = 1.0f;

	float rotationFactor;

	bool isExternal;
	bool isClosed = true;

	void close() { isClosed = true; };
	void open() { if(!isExternal) isClosed = false; };

    void render();
	void update(float dt);
};

