#pragma once
#include "entity.h"

#define OPENING_SPEED 1.0f;
#define CLOSING_SPEED 2.0f;

struct meshLOD {
    Mesh* meshFULL;
    Mesh* meshMID;
    Mesh* meshLOW;
};

class EntityDoor : public Entity
{
public:
    EntityDoor();
    EntityDoor(meshLOD* mesh, Shader* shader, Texture* texture);

    Shader* shader;
    meshLOD* mesh;
    Texture* texture;

	bool isExternal;
	bool isClosed = true;

	void close();
	void open();

};

