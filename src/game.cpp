#include "game.h"
#include "utils.h"
#include "mesh.h"
#include "texture.h"
#include "fbo.h"
#include "shader.h"
#include "input.h"
#include "animation.h"
#include "parseScene.cpp"

#include <cmath>

// some globals
Mesh *mesh = NULL;
Texture *texture = NULL;
Shader *shader = NULL;
Animation *anim = NULL;
float angle = 0;
float mouse_speed = 100.0f;
FBO *fbo = NULL;

float delta_yaw, delta_pitch;

Game *Game::instance = NULL;

Game::Game(int window_width, int window_height, SDL_Window *window)
{
	this->window_width = window_width;
	this->window_height = window_height;
	this->window = window;
	instance = this;
	must_exit = false;

	fps = 0;
	frame = 0;
	time = 0.0f;
	elapsed_time = 0.0f;
	mouse_locked = true;

	// OpenGL flags
	glEnable(GL_CULL_FACE);	 // render both sides of every triangle
	glEnable(GL_DEPTH_TEST); // check the occlusions using the Z buffer

	// create our camera
	camera = new Camera();
	camera->lookAt(Vector3(0.f, 100.f, 100.f), Vector3(0.f, 0.f, 0.f), Vector3(0.f, 1.f, 0.f)); // position the camera and point to 0,0,0
	camera->setPerspective(70.f, window_width / (float)window_height, 0.1f, 10000.f);			// set the projection, we want to be perspective

	// load one texture without using the Texture Manager (Texture::Get would use the manager)
	texture = new Texture();
	texture->load("data/texture.tga");

	// example of loading Mesh from Mesh Manager
	mesh = Mesh::Get("data/box.ASE");
	parseScene("data/meshes/myscene.scene");

	// example of shader loading using the shaders manager
	shader = Shader::Get("data/shaders/basic.vs", "data/shaders/texture.fs");

	// hide the cursor
	SDL_ShowCursor(!mouse_locked); // hide or show the mouse
}

// what to do when the image has to be draw
void Game::render(void)
{
	// set the clear color (the background color)
	glClearColor(0.0, 0.0, 0.0, 1.0);

	// Clear the window and the depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// set the camera as default
	camera->enable();

	// set flags
	glDisable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);

	// create model matrix for cube
	Matrix44 m;
	m.rotate(angle * DEG2RAD, Vector3(0, 1, 0));

	if (shader)
	{
		// enable shader
		shader->enable();

		// upload uniforms
		shader->setUniform("u_color", Vector4(1, 1, 1, 1));
		shader->setUniform("u_viewprojection", camera->viewprojection_matrix);
		shader->setUniform("u_texture", texture, 0);
		shader->setUniform("u_model", m);
		shader->setUniform("u_time", time);

		// do the draw call
		mesh->render(GL_TRIANGLES);

		// disable shader
		shader->disable();
	}

	// Draw the floor grid
	drawGrid();

	// render the FPS, Draw Calls, etc
	drawText(2, 2, getGPUStats(), Vector3(1, 1, 1), 2);

	// swap between front buffer and back buffer
	SDL_GL_SwapWindow(this->window);
}

void Game::update(double seconds_elapsed)
{
	float speed = seconds_elapsed * mouse_speed; // the speed is defined by the seconds_elapsed so it goes constant

	// example
	angle += (float)seconds_elapsed * 10.0f;

	// mouse input to rotate the cam
	if ((Input::mouse_state & SDL_BUTTON_LEFT) || mouse_locked) // is left button pressed?
	{
		camera->rotate(Input::mouse_delta.x * 0.005f, Vector3(0.0f, -1.0f, 0.0f));
		camera->rotate(Input::mouse_delta.y * 0.005f, camera->getLocalVector(Vector3(-1.0f, 0.0f, 0.0f)));
	}

	// Camera rotation
	delta_yaw += Input::mouse_delta.y * 0.005f;
	delta_pitch += Input::mouse_delta.x * 0.005f;

	delta_yaw = clamp(delta_yaw, -M_PI * 0.25, M_PI * 0.25);

	Matrix44 nPitch, nYaw;
	nPitch.setRotation(delta_pitch, (Vector3(0, -1, 0)));
	nYaw.setRotation(delta_yaw, (camera->getLocalVector(Vector3(-1, 0, 0))));
	Matrix44 new_matrix = nPitch * nYaw;

	camera->fromRotationMatrix(new_matrix);

	// player movement world.cpp
	/*

	if (!isOnfloor) {
		player->velocity.y += -2.5;
	}
	else {
		//jump
		if (Input::isKeyPressed(ESPACIO))
		{
			player->velocity.y += 3;
		}
	}

	*/
	// async input to move the camera around
	if (Input::isKeyPressed(SDL_SCANCODE_LSHIFT))
		speed *= 10; // move faster with left shift
	if (Input::isKeyPressed(SDL_SCANCODE_W) || Input::isKeyPressed(SDL_SCANCODE_UP))
		camera->move(Vector3(0.0f, 0.0f, 1.0f) * speed);
	if (Input::isKeyPressed(SDL_SCANCODE_S) || Input::isKeyPressed(SDL_SCANCODE_DOWN))
		camera->move(Vector3(0.0f, 0.0f, -1.0f) * speed);
	if (Input::isKeyPressed(SDL_SCANCODE_A) || Input::isKeyPressed(SDL_SCANCODE_LEFT))
		camera->move(Vector3(1.0f, 0.0f, 0.0f) * speed);
	if (Input::isKeyPressed(SDL_SCANCODE_D) || Input::isKeyPressed(SDL_SCANCODE_RIGHT))
		camera->move(Vector3(-1.0f, 0.0f, 0.0f) * speed);
	/*
	player->velocity += move_dir * player->speed;

	// Update player's position
	position += player->velocity * seconds_elapsed;

	// Decrease velocity when not moving
	player->velocity.x = player->velocity.x * 0.5f;
	player->velocity.y = player->velocity.y * 0.5f;


	Wall collisions
	if (checkPlayerCollisions(position + player->velocity))
	{
		for (const sCOllsisionData& collision : collisions) {

			float up_factor = collicion.colNormal.dot(Vector(0, 1, 0));
			if (up_dactor > 0.8) {
				isOnFloor = true;
			}
			else {
				para surfear las paredes en vez de clavarte
				Vector3 newDir = player->velocity.dot(collision.colNormal) * collision.colNormal;
				player->velocity.x += newDir.x;
				player->velocity.y += newDir.y;
	}


	*/
	// to navigate with the mouse fixed in the middle
	if (mouse_locked)
		Input::centerMouse();
}

/*
CHECK AVISTATION
bool World::checkLineOfSight(const Matrix44 obs, const Matrix44 target)
{
	Vector3 front = obs.frontVector();
	Vector3 toTarget = normalize(target.getTranslation() - obs.getTranslation());

	Vector3 ray_origin = target.getTranslation();
	Vector3 ray_direction = to_target;



	if (toTarget.dor(front) > 0.5)
	{
		for (auto Rntity e : root.children)
		{
			EntityCollider* ec = dynamic_cast<EntityCollider*>(e);
			if (!ec) continue;

			if (ec->mesh->testRayCollision(
				ec->model,
				ray_origin,
				ray_direction,
				Vector3(),
				Vector3())) return false;
		}
		return true;
	}

	return false;
}

*/

// Keyboard event handler (sync input)
void Game::onKeyDown(SDL_KeyboardEvent event)
{
	switch (event.keysym.sym)
	{
	case SDLK_ESCAPE:
		must_exit = true;
		break; // ESC key, kill the app
	case SDLK_F1:
		Shader::ReloadAll();
		break;
	}
}

void Game::onKeyUp(SDL_KeyboardEvent event)
{
}

void Game::onGamepadButtonDown(SDL_JoyButtonEvent event)
{
}

void Game::onGamepadButtonUp(SDL_JoyButtonEvent event)
{
}

void Game::onMouseButtonDown(SDL_MouseButtonEvent event)
{
	if (event.button == SDL_BUTTON_MIDDLE) // middle mouse
	{
		mouse_locked = !mouse_locked;
		SDL_ShowCursor(!mouse_locked);
	}
}

void Game::onMouseButtonUp(SDL_MouseButtonEvent event)
{
}

void Game::onMouseWheel(SDL_MouseWheelEvent event)
{
	mouse_speed *= event.y > 0 ? 1.1 : 0.9;
}

void Game::onResize(int width, int height)
{
	std::cout << "window resized: " << width << "," << height << std::endl;
	glViewport(0, 0, width, height);
	camera->aspect = width / (float)height;
	window_width = width;
	window_height = height;
}
