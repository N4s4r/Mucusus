#pragma once
#include "entity.h"
#include "mesh.h"
#include "entityMeshRoom.h"
#include "camera.h"
#include "game.h"
#include "world.h"

class EntityPlayer :public Entity
{
public:
	EntityPlayer();
	Vector3 crosshair;
	Camera* camera;
	Mesh* mesh;

	//Movement
	float mouse_speed = 100.0f;
	float player_speed = 100.0f;
	float camera_rotation_speed = 5.0f;
	float angle = 0;
	float yaw;
	float gravity_speed = 30.0f;
	float on_ground = 0.2f;
	float jump_cooldown = 0.0f;
	Vector3 velocity;


	void movePlayer(Vector3 delta);
	void rotatePlayer(float angle, const Vector3& axis);

	//collisions
	void update(float dt);
};
