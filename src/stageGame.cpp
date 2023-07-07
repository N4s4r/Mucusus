#include "stageGame.h"
#include <iostream>
#include <string>

StageGame::StageGame()
{
	processHUD();
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
	if (player->statChange)
	{
		processHUD();
		player->statChange = false;
	}
}

void StageGame::processHUD()
{
	int wWidth = Game::instance->window_width;
	int wHeight = Game::instance->window_height;
	cam2d.view_matrix = Matrix44();
	cam2d.setOrthographic(0, wWidth, wHeight, 0, -1, 1);

	float hudScale = min(wWidth, wHeight) * hudScaleFactor;

	crosshair.mesh.createQuad(wWidth / 2, wHeight / 2, hudScale, hudScale, true);
	crosshair.texture = Texture::Get("data/textures/HUD/crosshair.tga");
	int x, y;
	x = 50;
	y = wHeight - 50;
	playerSpeed.mesh.createQuad(x, y, hudScale, hudScale, true);
	playerSpeed.texture = Texture::Get("data/textures/HUD/speed.tga");
	sprintf(playerSpeed.statValue.text, "%f", Game::instance->player->playerSpeed);
	playerSpeed.statValue.position = Vector2(x + hudScale + 5, y - hudScale / 3);
	y -= (10 + hudScale);
	caddence.mesh.createQuad(x, y, hudScale, hudScale, true);
	caddence.texture = Texture::Get("data/textures/HUD/caddence.tga");
	sprintf(caddence.statValue.text, "%f", Game::instance->player->caddence);
	caddence.statValue.position = Vector2(x + hudScale + 5, y - hudScale / 3);
	y -= (10 + hudScale);
	projectileSpeed.mesh.createQuad(x, y, hudScale, hudScale, true);
	projectileSpeed.texture = Texture::Get("data/textures/HUD/projectile_speed.tga");
	sprintf(projectileSpeed.statValue.text, "%f", Game::instance->player->projectileSpeed);
	projectileSpeed.statValue.position = Vector2(x + hudScale + 5, y - hudScale / 3);
	y -= (10 + hudScale);
	attack.mesh.createQuad(x, y, hudScale, hudScale, true);
	attack.texture = Texture::Get("data/textures/HUD/attack.tga");
	sprintf(attack.statValue.text, "%f", Game::instance->player->attack);
	attack.statValue.position = Vector2(x + hudScale + 5, y - hudScale / 3);

	float healthBarMaxLength = hudScale / 10.0f * Game::instance->player->maxHealth;
	float healthBarLength = hudScale / 10.0f * Game::instance->player->health;
	healthBar.mesh.createQuad(50 + healthBarLength / 2, 50, healthBarLength, hudScale / 5.0f, true);
	healthBar.texture = Texture::Get("data/textures/HUD/health.tga");
	healthFrame.mesh.createQuad(50 + healthBarMaxLength / 2, 50, healthBarMaxLength, hudScale / 5.0f, true);
	healthFrame.texture = Texture::Get("data/textures/HUD/healthFrame.tga");
}

void StageGame::renderHUD()
{
	int wWidth = Game::instance->window_width;
	int wHeight = Game::instance->window_height;
	float hudScale = min(wWidth, wHeight) * hudScaleFactor;
	EntityPlayer* player = Game::instance->player;

	SDL_Window* window = Game::instance->window;

	// Set the flags
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	cam2d.enable();

	//Render hud
	renderQuad(crosshair.mesh, crosshair.texture);
	renderQuad(attack.mesh, attack.texture);
	renderQuad(caddence.mesh, caddence.texture);
	renderQuad(playerSpeed.mesh, playerSpeed.texture);
	renderQuad(projectileSpeed.mesh, projectileSpeed.texture);
	renderQuad(healthBar.mesh, healthBar.texture);
	renderQuad(healthFrame.mesh, healthFrame.texture);
	drawText(attack.statValue.position.x, attack.statValue.position.y, attack.statValue.text, Vector3(1, 1, 1), hudScale/ 20.0f);
	drawText(caddence.statValue.position.x, caddence.statValue.position.y, caddence.statValue.text, Vector3(1, 1, 1), hudScale / 20.0f);
	drawText(playerSpeed.statValue.position.x, playerSpeed.statValue.position.y, playerSpeed.statValue.text, Vector3(1, 1, 1), hudScale / 20.0f);
	drawText(projectileSpeed.statValue.position.x, projectileSpeed.statValue.position.y, projectileSpeed.statValue.text, Vector3(1, 1, 1), hudScale / 20.0f);

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