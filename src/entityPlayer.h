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

	//Movement
	float mouse_speed = 100.0f;
	float player_speed = 5.0f;
	float camera_rotation_speed = 5.0f;
	float angle = 0;


	void movePlayer(Vector3 delta);
	void rotatePlayer(float angle, const Vector3& axis);

	//collisions
	void update(float dt);

};
