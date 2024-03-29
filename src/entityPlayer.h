#pragma once
#include "entity.h"
#include "mesh.h"
#include "entityMeshRoom.h"
#include "entityEnemy.h"
#include "camera.h"
#include "game.h"
#include "world.h"
#include "entityMesh.h"

class EntityPlayer : public Entity
{
public:
	EntityPlayer();
	Vector3 crosshair;
	Camera *camera;
	Mesh *mesh;

	EntityMeshRoom *currentRoom;

	bool statChange = false;
	Vector3 lookingAt;

	// Movement
	float mouse_speed = 100.0f;
	float player_speed = 100.0f;
	float camera_rotation_speed = 1.0f;
	float angle = 0;
	float yaw;
	float gravity_speed = 30.0f;
	float on_ground = 0.2f;

	float jump_cooldown = 0.0f;
	float shootingCD = 0.0f;
	float immunity_remaining = 1.0f;
	Vector3 velocity;

	// Stats
	float maxHealth = 100.0f;
	float health = maxHealth;
	float attack = 1.0f;
	float caddence = 2.0f; // Bullets per second
	float projectileSpeed = 10.0f;
	float playerSpeed = 50.0f;

	void movePlayer(Vector3 delta);
	void rotatePlayer(float angle, const Vector3 &axis);

	void applyInputDamage(EntityEnemy *damageSource);
	// collisions
	bool checkMeshCollision(vt<sCollisionData> &collisions, Matrix44 globalMatrix, Mesh *mesh);
	void update(float dt);
};
