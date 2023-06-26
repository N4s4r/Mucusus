#include "entityPlayer.h"


EntityPlayer::EntityPlayer()
{
	camera = Game::instance->camera;
	//mesh = Mesh::createQuad(0,0);
}

void EntityPlayer::movePlayer(Vector3 delta)
{
	camera->XZmove(delta);
}

void EntityPlayer::rotatePlayer(float angle, const Vector3& axis)
{
	camera->rotate(angle, axis);
	camera->rotate(angle, axis);
}

void EntityPlayer::update(float dt)
{
	//collisions
	//std::vector<EntityMesh*> entities = Game::instance->emr;
	//EntityMeshRoom * currentRoom = Game::instance->room;
	//Vector3 current_pos = getPosition();
	//if 
}


