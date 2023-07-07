#include "stageGame.h"

StageGame::StageGame()
{
	int wWidth = Game::instance->window_width;
	int wHeight = Game::instance->window_height;
	cam2d.view_matrix = Matrix44();
	cam2d.setOrthographic(0, wWidth, wHeight, 0, -1, 1);

	crosshair.createQuad(wWidth/2, wHeight/2, chW, chH, true);
	crosshairTexture = Texture::Get("data/textures/HUD/crosshair.tga");
}

void StageGame::render()
{
	//EntityMeshRoom* room = Game::instance->room;
	// set the clear color (the background color)
	glClearColor(0.0, 0.0, 1.0, 1.0);

	// Clear the window and the depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// set the camera as default
	Camera *camera = Game::instance->camera;
	SDL_Window *window = Game::instance->window;
	camera->enable();

	//Update camera
	Matrix44 nPitch, nYaw;
	nPitch.setRotation(Game::instance->camera_pitch, (Vector3(1, 0, 0)));
	nYaw.setRotation(Game::instance->camera_yaw, Vector3(0, -1, 0));
	Matrix44 new_matrix = nPitch * nYaw;

	EntityPlayer* player = Game::instance->player;
	Vector3 eye = player->model.getTranslation() + Vector3(0, 1, 0);

	camera->lookAt(eye, eye + new_matrix.frontVector().normalize(), Vector3(0, 1, 0));

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

	EACH(room, Game::instance->world->mapGrid)
	{
		room->render();
	}
	renderHUD();

	// render the FPS, Draw Calls, etc
	drawText(2, 2, getGPUStats(), Vector3(1, 1, 1), 2);

	// swap between front buffer and back buffer
	SDL_GL_SwapWindow(window);
}

void StageGame::update(double seconds_elapsed)
{
	EntityPlayer* player = Game::instance->player;
	EntityMeshRoom* room = Game::instance->room;
	player->update(seconds_elapsed);
	room->update(seconds_elapsed);

	// to navigate with the mouse fixed in the middle
	if (Game::instance->mouse_locked)
		Input::centerMouse();
}

void StageGame::renderHUD()
{
	EntityPlayer* player = Game::instance->player;

	SDL_Window* window = Game::instance->window;

	// Set the flags
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	cam2d.enable();

	//Render Crosshair
	renderQuad(crosshair, crosshairTexture);


	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glDisable(GL_BLEND);
}

void StageGame::renderQuad(Mesh quad, Texture* texture)
{
	Shader* qShader = Shader::Get("data/shaders/basic.vs", "data/shaders/gui.fs");

	if (!qShader) return;

	qShader->enable();

	qShader->setUniform("u_color", Vector4(1, 1, 1, 1));
	qShader->setUniform("u_viewprojection", cam2d.viewprojection_matrix);
	if (texture != NULL) {
		qShader->setUniform("u_texture", texture, 0);
	}
	qShader->setUniform("u_time", Game::instance->time);
	qShader->setUniform("u_tex_tiling", 1.0f);
	qShader->setUniform("u_tex_range", Vector4(0, 0, 1, 1));
	qShader->setUniform("u_model", Matrix44());
	quad.render(GL_TRIANGLES);

	qShader->disable();
}