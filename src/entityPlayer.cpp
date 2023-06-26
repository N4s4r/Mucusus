#include "entityPlayer.h"
#include "input.h"
#include "utils.h"


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

void EntityPlayer::update(float dt, EntityMeshRoom* room)
{
	bool mouse_locked = Game::instance->mouse_locked;
	float speed = dt * mouse_speed; // the speed is defined by the seconds_elapsed so it goes constant

	// example
	angle += (float)dt * 10.0f;

	// mouse input to rotate the cam
	if ((Input::mouse_state & SDL_BUTTON_LEFT) || mouse_locked) // is left button pressed?
	{
		rotatePlayer(Input::mouse_delta.x * 0.001f * camera_rotation_speed, Vector3(0.0f, -1.0f, 0.0f));
		rotatePlayer(Input::mouse_delta.y * 0.001f * camera_rotation_speed, camera->getLocalVector(Vector3(-1.0f, 0.0f, 0.0f)));
	}

	// WASD to move the player around
	if (Input::isKeyPressed(SDL_SCANCODE_W))
	{
		velocity = velocity + (Vector3(0.0f, 0.0f, 1.0f) * player_speed * dt);
		//movePlayer(Vector3(0.0f, 0.0f, 1.0f) * player_speed * dt);
	}
	if (Input::isKeyPressed(SDL_SCANCODE_S))
	{
		velocity = velocity + (Vector3(0.0f, 0.0f, -1.0f) * player_speed * dt);
		//movePlayer(Vector3(0.0f, 0.0f, -1.0f) * player_speed * dt);
	}
	if (Input::isKeyPressed(SDL_SCANCODE_A))
	{
		velocity = velocity + (Vector3(1.0f, 0.0f, 0.0f) * player_speed * dt);
		//movePlayer(Vector3(1.0f, 0.0f, 0.0f) * player_speed * dt);
	}
	if (Input::isKeyPressed(SDL_SCANCODE_D))
	{
		velocity = velocity + (Vector3(-1.0f, 0.0f, 0.0f) * player_speed * dt);
		//movePlayer(Vector3(-1.0f, 0.0f, 0.0f) * player_speed * dt);
	}

	Vector3 to_pos = camera->eye + (velocity);
	Vector3 char_center = to_pos + Vector3(0, 1, 0);

	//collisions
	//std::vector<EntityMesh*> entities = Game::instance->room;
	//EntityMeshRoom * currentRoom = Game::instance->room;
	
	vt<EntityMesh*> roomEntities = room->staticEntities;
	Vector3 current_pos = camera->eye;
	checkCollisionEntities(roomEntities, char_center, dt, to_pos, current_pos);


	velocity = velocity - (velocity * 10.0f * dt);
	movePlayer(velocity);
}
//Collisions
void EntityPlayer::checkCollisionEntities(vt<EntityMesh*>& roomEntities, Vector3& character_center, float dt, Vector3& to_pos, Vector3& playerPos)
{
	for (size_t i = 0; i < roomEntities.size(); i++) {
		EntityMesh* checkEntity = roomEntities[i];
		Vector3 coll;
		Vector3 collnorm;
		if (!checkEntity->mesh->testSphereCollision(checkEntity->model, character_center, 1.0f, coll, collnorm))
			continue;
		std::cout << "Collision" << std::endl;
		//std::cout << "Positionat" << playerPos << std::endl;
		Vector3 pushDirection = normalize(coll - character_center);
		Vector3 push_away = pushDirection * dt * 2;
		//camera->lookAt(Vector3(0.f, 1.f, 0.001f), Vector3(0.f, 1.f, 0.f), Vector3(0.f, 1.f, 0.f));
		to_pos = playerPos - push_away;
		to_pos.y = 0;
	}
}


