#include "entityDoor.h"

EntityDoor::EntityDoor()
{
}

EntityDoor::EntityDoor(meshLOD* mesh, Shader* shader, Texture* texture)
{
	this->mesh = mesh;
	this->shader = shader;
	this->texture = texture;
}
