#include "defines.h"
#include "game.h"
#include "utils.h"
#include "mesh.h"
#include "texture.h"
#include "fbo.h"
#include "shader.h"
#include "input.h"
#include "animation.h"
#include "entity.h"
#include "entityMesh.h"
#include "entityMeshRoom.h"
#include "entityPlayer.h"

#include <cmath>

// Game params
float camera_rotation_speed = 5.0f;
float camera_move_speed = 5.0f;
float camera_jump_speed = 10.0f;

// some globals
// Mesh *mesh = NULL;
// Texture *texture = NULL;
// Shader *shader = NULL;
EntityPlayer *player = NULL;
EntityMeshRoom *room = NULL;
Animation *anim = NULL;
float angle = 0;
float mouse_speed = 100.0f;
FBO *fbo = NULL;

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
	camera->lookAt(Vector3(0.f, 1.f, 0.001f), Vector3(0.f, 0.f, 0.f), Vector3(0.f, 1.f, 0.f)); // position the camera and point to 0,0,0
	camera->setPerspective(70.f, window_width / (float)window_height, 0.1f, 10000.f);		   // set the projection, we want to be perspective
	player = new EntityPlayer();

	shader = Shader::Get("data/shaders/basic.vs", "data/shaders/texture.fs");

	// Create the room
	wall_texture = Texture::Get("data/textures/wall.tga");
	floor_texture = Texture::Get("data/textures/box.tga");
	room = new EntityMeshRoom();
	room->parseScene("room0");

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
	/*
	// create model matrix for cube
	Matrix44 m;
	m.rotate(angle * DEG2RAD, Vector3(0, 1, 0));

	if (shader)
	{9
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
	*/

	room->render();

	// Draw the floor grid
	drawGrid();

	// render the FPS, Draw Calls, etc
	drawText(2, 2, getGPUStats(), Vector3(1, 1, 1), 2);

	// swap between front buffer and back buffer
	SDL_GL_SwapWindow(this->window);
}

void Game::update(double seconds_elapsed)
{

	player->update(seconds_elapsed);
	room->update(seconds_elapsed);

	// if (Input::isKeyPressed(SDL_SCANCODE_LSHIFT))
	// 	speed *= 10; // move faster with left shift
	// if (Input::isKeyPressed(SDL_SCANCODE_W))
	// 	camera->move(Vector3(0.0f, 0.0f, 1.0f) * camera_move_speed);
	// if (Input::isKeyPressed(SDL_SCANCODE_S))
	// 	camera->move(Vector3(0.0f, 0.0f, -1.0f) * camera_move_speed);
	// if (Input::isKeyPressed(SDL_SCANCODE_A))
	// 	camera->move(Vector3(1.0f, 0.0f, 0.0f) * camera_move_speed);
	// if (Input::isKeyPressed(SDL_SCANCODE_D))
	// 	camera->move(Vector3(-1.0f, 0.0f, 0.0f) * camera_move_speed);

	// to navigate with the mouse fixed in the middle
	if (mouse_locked)
		Input::centerMouse();
}

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
