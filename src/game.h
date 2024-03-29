/*  by Javi Agenjo 2013 UPF  javi.agenjo@gmail.com
	This class encapsulates the game, is in charge of creating the game, getting the user input, process the update and render.
*/

#pragma once
#include "includes.h"
#include "camera.h"
#include "utils.h"
#include "shader.h"
#include "mesh.h"
#include "stage.h"

class EntityMeshRoom;
class EntityPlayer;
class World;

class Game
{
public:
	static Game *instance;

	// window
	SDL_Window *window;
	int window_width;
	int window_height;

	// some globals
	long frame;
	float time;
	float elapsed_time;
	int fps;
	bool must_exit;

	// some vars
	Camera *camera; // our global camera
	float camera_yaw = 0;
	float camera_pitch = 0;

	Shader *shader; // our global shader
	EntityMeshRoom *room = NULL;
	EntityPlayer *player = NULL;
	World *world = NULL;

	vt<Stage *> stages;
	STAGE_ID currentStage;

	// EntityMeshRoom* room;

	// Some public meshes
	Mesh *X_wall_mesh = Mesh::Get("data/meshes/X_wall.obj");
	Mesh *Z_wall_mesh = Mesh::Get("data/meshes/Z_wall.obj");
	Mesh *floor_mesh = Mesh::Get("data/meshes/floor.obj");
	Texture *wall_texture = NULL;
	Texture *floor_texture = NULL;

	bool mouse_locked; // tells if the mouse is locked (not seen)

	Game(int window_width, int window_height, SDL_Window *window);

	Game();

	void setStage(STAGE_ID id);

	// main functions
	void render(void);
	void update(double dt);

	// events
	void onKeyDown(SDL_KeyboardEvent event);
	void onKeyUp(SDL_KeyboardEvent event);
	void onMouseButtonDown(SDL_MouseButtonEvent event);
	void onMouseButtonUp(SDL_MouseButtonEvent event);
	void onMouseWheel(SDL_MouseWheelEvent event);
	void onGamepadButtonDown(SDL_JoyButtonEvent event);
	void onGamepadButtonUp(SDL_JoyButtonEvent event);
	void onResize(int width, int height);
};
