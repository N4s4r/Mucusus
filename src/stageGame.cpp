#include "stageGame.h"

StageGame::StageGame()
{
}

void StageGame::render(EntityMeshRoom *room)
{
	// set the clear color (the background color)
	glClearColor(0.0, 0.0, 0.0, 1.0);

	// Clear the window and the depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// set the camera as default
	Camera *camera = Game::instance->camera;
	SDL_Window *window = Game::instance->window;
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
	SDL_GL_SwapWindow(window);
}

void StageGame::update(double seconds_elapsed, EntityPlayer* player)
{
	EntityMeshRoom* room = Game::instance->room;
	player->update(seconds_elapsed, room);
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
	if (Game::instance->mouse_locked)
		Input::centerMouse();
}
