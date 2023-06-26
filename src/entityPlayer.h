#pragma once
#include "entity.h"
#include "mesh.h"
#include "entityMeshRoom.h"
#include "camera.h"
#include "game.h"

class EntityPlayer :public Entity
{
public:
	EntityPlayer();
	Camera* camera;
	Mesh* mesh;

	void movePlayer(Vector3 delta);
	void rotatePlayer(float angle, const Vector3& axis);

	//collisions
	void update(float dt);

};
