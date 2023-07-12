#include "entityPlayer.h"
#include "input.h"
#include "utils.h"
#include "defines.h"

EntityPlayer::EntityPlayer()
{
	camera = Game::instance->camera;
	int roomID = GRIDHEIGHT * GRIDHEIGHT / 2;
	int i = roomID % GRIDHEIGHT;
	int j = roomID / GRIDHEIGHT;
	Vector3 playerPosition = Vector3(j * 16.0f + 8.0f, 0.5f, i * 16.0f + 8.0f);
	model.setTranslation(playerPosition.x , playerPosition.y, playerPosition.z);
}

void EntityPlayer::movePlayer(Vector3 delta)
{
	model.setTranslation(delta.x, delta.y, delta.z);
}

bool checkPlayerOnGround(const Vector3& position, vt<sCollisionData>& collisions, EntityMeshRoom* room)
{
	float sphereRadius = 1.f;
	Vector3 colPoint, colNormal;

	EACH(e, room->staticEntities)
	{
		Mesh* mesh = e->mesh;
		if (mesh->testRayCollision(e->model, position, Vector3(0, -1, 0), colPoint, colNormal, 1.0f))
		{
			return true;
		}
	}

	return !collisions.empty();
}

void EntityPlayer::applyInputDamage(EntityEnemy* damageSource)
{
	health -= damageSource->damage;
}

bool EntityPlayer::checkMeshCollision(vt<sCollisionData>& collisions, Matrix44 globalMatrix, Mesh* mesh)
{
	Vector3 position = model.getTranslation();

	float sphereRadius = 0.5f;
	Vector3 colPoint, colNormal;
	if (mesh->testSphereCollision(globalMatrix, position, sphereRadius, colPoint, colNormal))
	{
		collisions.push_back({ colPoint, colNormal.normalize() });
	}
	return !collisions.empty();
}

void EntityPlayer::update(float dt)
{
	World* world = Game::instance->world;
	bool mouse_locked = Game::instance->mouse_locked;
	float speed = dt * mouse_speed; // the speed is defined by the seconds_elapsed so it goes constant
	EntityMeshRoom* currentRoom = world->currentRoom;
	Vector3 position = model.getTranslation();

	// mouse input to rotate the cam
		//Update camera
	Matrix44 nYaw;
	nYaw.setRotation(Game::instance->camera_yaw, Vector3(0, -1, 0));
	Vector3 forward = nYaw.frontVector();
	Vector3 right = nYaw.rightVector();

	// WASD to move the player around
	if (Input::isKeyPressed(SDL_SCANCODE_W))
	{
		velocity = velocity + (forward.normalize() * playerSpeed * dt);
	}
	if (Input::isKeyPressed(SDL_SCANCODE_S))
	{
		velocity = velocity - (forward.normalize() * playerSpeed * dt);
	}
	if (Input::isKeyPressed(SDL_SCANCODE_A))
	{
		velocity = velocity + (right.normalize() * playerSpeed * dt);
	}
	if (Input::isKeyPressed(SDL_SCANCODE_D))
	{
		velocity = velocity - (right.normalize() * playerSpeed * dt);
	}
	if (shootingCD == 0.0f && Input::isMousePressed(SDL_BUTTON_LEFT))
	{
		Vector3 bulletDir = Game::instance->camera->center;
		Game::instance->world->shootBullet(lookingAt);
		shootingCD = 1 / caddence; 
	}
	if (on_ground > 0 && Input::isKeyPressed(SDL_SCANCODE_SPACE) && jump_cooldown == 0.0f)
	{
		velocity.y = 10.0f;
		jump_cooldown = 0.1f;
	}
	// Gravity
	velocity.y = clamp(velocity.y - gravity_speed * dt, -100.0f, 10000.0f);

	Vector3 to_pos = position + velocity * dt;
	vt<sCollisionData> collisions;
	EACH(room, world->mapGrid)
	{
		if (!room) continue;
		if (checkRoomCollisions(to_pos, collisions, room, 0.5f))
		{
			EACH(collision, collisions)
			{
				//position += collision.colNormal.normalize() * 0.0005f;
				Vector3 newDir = velocity.dot(collision.colNormal);
				newDir = newDir * collision.colNormal;

				velocity.x -= newDir.x;
				velocity.z -= newDir.z;
				velocity.y -= newDir.y;
			}
		}
		// Update on_ground
		vt<sCollisionData> ground_collisions;
		if (checkPlayerOnGround(position, ground_collisions, room))
		{
			on_ground = 0.2f;
		}
	}

	position = position + velocity * dt;
	velocity.x = velocity.x - (velocity.x * 10.0f * dt);
	velocity.z = velocity.z - (velocity.z * 10.0f * dt);
	
	model.setTranslation(position.x, position.y, position.z);
	if (Input::isKeyPressed(SDL_SCANCODE_R))
	{
		health -= 1.0f;
		statChange = true;
	}
	if (Input::isKeyPressed(SDL_SCANCODE_T))
	{
		health += 1.0f;
		statChange = true;
	}
	if (Input::isKeyPressed(SDL_SCANCODE_Y))
	{
		maxHealth += 1.0f;
		statChange = true;
	}
	if (Input::isKeyPressed(SDL_SCANCODE_U))
	{
		maxHealth -= 1.0f;
		statChange = true;
	}

	// update timers
	on_ground = clamp(on_ground - dt, 0.0f, 999.0f);
	jump_cooldown = clamp(jump_cooldown - dt, 0.0f, 999.0f);
	shootingCD = clamp(shootingCD - dt, 0.0f, 999.0f);

	//if (statChange) 

	//std::cout << position.x << position.y << position.z << std::endl;
	/*std::cout << on_ground << std::endl;*/
}