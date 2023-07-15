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
#include "stage.h"
#include "stageGame.h"
#include "stageIntro.h"
#include "stageWin.h"
#include "audio.h"
#include "world.h"
#include <cmath>
#include "enemyManager.h"

// Game params
float camera_rotation_speed = 1.0f;
float camera_move_speed = 5.0f;
float camera_jump_speed = 10.0f;

// some globals
// Mesh *mesh = NULL;
// Texture *texture = NULL;
// Shader *shader = NULL;
HCHANNEL channel;
Animation *anim = NULL;
float angle = 0;
float mouse_speed = 100.0f;
FBO *fbo = NULL;

// Enemies

Game *Game::instance = NULL;

Stage *getStage(STAGE_ID id)
{
	return Game::instance->stages[(int)id];
}

Stage *getCurrentStage()
{
	return getStage(Game::instance->currentStage);
}

void Game::setStage(STAGE_ID id)
{
	currentStage = id;
}

void initStages()
{
	Game::instance->stages.reserve(1);
	Game::instance->stages.push_back(new StageIntro());
	Game::instance->stages.push_back(new StageGame());

	Game::instance->stages.push_back(new StageWin(false));
	Game::instance->stages.push_back(new StageWin(true));
	Game::instance->stages.push_back(new StageWin(false));
}

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

	// Load the world
	world = new World();
	world->loadRooms();
	while (world->placedRooms < world->totalRooms)
	{
		world->mapGrid.empty();
		world->placedRooms = 0;
		world->randomLoad();
	}
	world->placeRoomsDoors();
	player = new EntityPlayer();

	// OpenGL flags
	glEnable(GL_CULL_FACE);	 // render both sides of every triangle
	glEnable(GL_DEPTH_TEST); // check the occlusions using the Z buffer

	// create our camera
	camera = new Camera();
	camera->lookAt(Vector3(0.f, 1.f, 0.001f), Vector3(0.f, 0.f, 0.f), Vector3(0.f, 1.f, 0.f)); // position the camera and point to 0,0,0
	camera->setPerspective(70.f, window_width / (float)window_height, 0.1f, 10000.f);		   // set the projection, we want to be perspective

	initStages();
	setStage(STAGE_ID::INTRO);
	shader = Shader::Get("data/shaders/basic.vs", "data/shaders/texture.fs");

	// Create the room
	wall_texture = Texture::Get("data/textures/wall.tga");
	floor_texture = Texture::Get("data/textures/box.tga");

	// Audio
	if (BASS_Init(-1, 44100, 0, 0, NULL) == false)
	{
		// Error with sound device
		cout << "Error with sound device" << endl;
		exit(1);
	}
	channel = Audio::Play("data/audios/SUS_background.wav", BASS_SAMPLE_LOOP);

	// hide the cursor
	SDL_ShowCursor(!mouse_locked); // hide or show the mouse
}

// what to do when the image has to be draw
void Game::render(void)
{
	getCurrentStage()->render();
}

void Game::update(double seconds_elapsed)
{
	if ((Input::mouse_state & SDL_BUTTON_LEFT) || mouse_locked) // is left button pressed?
	{
		camera_yaw += Input::mouse_delta.x * camera_rotation_speed * seconds_elapsed;
		camera_pitch += Input::mouse_delta.y * camera_rotation_speed * seconds_elapsed;

		camera_pitch = clamp(camera_pitch, -M_PI * 0.45, M_PI * 0.45);
	}
	if (Input::isKeyPressed(SDL_SCANCODE_C))
	{
		mouse_locked = !mouse_locked;
	}

	getCurrentStage()->update(seconds_elapsed);
}

// Keyboard event handler (sync input)
void Game::onKeyDown(SDL_KeyboardEvent event)
{
	switch (event.keysym.sym)
	{
	case SDLK_ESCAPE:
		Game::instance->mouse_locked = !Game::instance->mouse_locked;
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
