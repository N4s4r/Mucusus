#include "entityPlayer.h"
#include "input.h"


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

	// WASD to move the camera around
	if (Input::isKeyPressed(SDL_SCANCODE_W))
	{
		movePlayer(Vector3(0.0f, 0.0f, 1.0f) * player_speed * dt);
	}
	if (Input::isKeyPressed(SDL_SCANCODE_S))
	{
		movePlayer(Vector3(0.0f, 0.0f, -1.0f) * player_speed * dt);
	}
	if (Input::isKeyPressed(SDL_SCANCODE_A))
	{
		movePlayer(Vector3(1.0f, 0.0f, 0.0f) * player_speed * dt);
	}
	if (Input::isKeyPressed(SDL_SCANCODE_D))
	{
		movePlayer(Vector3(-1.0f, 0.0f, 0.0f) * player_speed * dt);
	}
	//collisions
	//std::vector<EntityMesh*> entities = Game::instance->emr;
	//EntityMeshRoom * currentRoom = Game::instance->room;
	//Vector3 current_pos = getPosition();
	//if 
}


