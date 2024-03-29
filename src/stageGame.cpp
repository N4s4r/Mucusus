#include "stageGame.h"
#include <iostream>
#include <string>
#include "entityBullet.h"
#include "mesh.h"
#include "enemyManager.h"
#include "entityDoor.h"

#define STARTING_ROOM GRIDWIDTH *GRIDWIDTH / 2

StageGame::StageGame()
{
	enemy_manager = new EnemyManager();
	HUD.initHUD();
	vt<char *> introOptions = {"pause"};
	GUI = new menuGUI(introOptions);
	updateMinimap();
	// Not needed on the first room
	// enemy_manager->fillRoomWithEnemies();
}

void frustrumCulling(EntityMesh *entity, Vector3 camPos)
{
	Vector3 entityPos = entity->getGlobalPosition();
	Mesh *entityMesh = entity->mesh;
	float dist = entityPos.distance(camPos);
	if (dist > 500)
	{
		return;
	}
	if (!Game::instance->camera->testSphereInFrustum(entityPos, entityMesh->radius))
	{
		return;
	}
	entity->render();
}

void frustrumCulling(EntityDoor *door, Vector3 camPos)
{
	Vector3 entityPos = door->getGlobalPosition();
	Mesh *entityMesh = door->meshFULL;
	float dist = entityPos.distance(camPos);
	if (dist > 500)
	{
		return;
	}
	if (!Game::instance->camera->testSphereInFrustum(entityPos, entityMesh->radius))
	{
		return;
	}
	door->render();
}

void StageGame::render()
{
	// EntityMeshRoom* room = Game::instance->room;
	//  set the clear color (the background color)
	glClearColor(0.0, 0.0, 1.0, 1.0);

	// Clear the window and the depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// set the camera as default
	Camera *camera = Game::instance->camera;
	SDL_Window *window = Game::instance->window;
	camera->enable();

	// Update camera
	Matrix44 nPitch, nYaw;
	nPitch.setRotation(Game::instance->camera_pitch, (Vector3(1, 0, 0)));
	nYaw.setRotation(Game::instance->camera_yaw, Vector3(0, -1, 0));
	Matrix44 new_matrix = nPitch * nYaw;
	Game::instance->player->lookingAt = new_matrix.frontVector().normalize();

	EntityPlayer *player = Game::instance->player;
	Vector3 eye = player->model.getTranslation() + Vector3(0, 1, 0);

	camera->lookAt(eye, eye + Game::instance->player->lookingAt, Vector3(0, 1, 0));

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
		if (room)
		{
			EACH(entity, room->staticEntities)
			{
				frustrumCulling(entity, camera->eye);
			}
			EACH(door, room->roomDoors)
			{
				frustrumCulling(door, camera->eye);
			}
		}
	}
	EACH(bullet, Game::instance->world->bulletBuffer)
	{
		if (bullet->isActive)
			bullet->render();
	}
	EntityBullet *sbullet = Game::instance->world->bullet;
	if (sbullet->isActive)
		sbullet->render();

	// render enemies
	enemy_manager->render();

	HUD.render();
	renderMinimap();

	// render the FPS, Draw Calls, etc
	// drawText(2, 2, getGPUStats(), Vector3(1, 1, 1), 2);

	// swap between front buffer and back buffer

	if (!Game::instance->mouse_locked)
	{
		GUI->render(&cam2d);
	}

	SDL_GL_SwapWindow(window);
}

void StageGame::update(double seconds_elapsed)
{
	if (Game::instance->mouse_locked)
	{
		World *world = Game::instance->world;
		if (!world->mapGrid[STARTING_ROOM]->isCleared)
			world->setRoomClearStatus(STARTING_ROOM);
		EntityPlayer *player = Game::instance->player;
		player->update(seconds_elapsed);

		// If there is no enemies left, open all doors
		if (enemy_manager->enemies.size() == 0)
		{
			StageGame *stageGame = (StageGame *)Game::instance->stages[(int)Game::instance->currentStage];
			EntityMeshRoom *currentRoom = player->currentRoom;
			// If current room is not visited, continue
			if (currentRoom->isVisited)
			{
				// Open all the doors of all the rooms
				EACH(room, Game::instance->world->mapGrid)
				{
					if (room)
					{
						room->openAllDoors();
					}
				}
				currentRoom->isCleared = true;
				stageGame->battlePhase = false;
			}
		}

		// Update enemies
		enemy_manager->update(seconds_elapsed);

		EACH(bullet, Game::instance->world->bulletBuffer)
		{
			if (bullet->isActive)
				bullet->update(seconds_elapsed);
		}
		EntityBullet *sbullet = Game::instance->world->bullet;
		if (sbullet->isActive)
			sbullet->update(seconds_elapsed);
		// to navigate with the mouse fixed in the middle
		if (Game::instance->mouse_locked)
			Input::centerMouse();
		if (player->statChange)
		{
			HUD.updateHUDElements();
			player->statChange = false;
		}
		EACH(room, Game::instance->world->mapGrid)
		{
			if (room)
			{
				room->update(seconds_elapsed);
			}
		}
		EntityMeshRoom *currentRoom = player->currentRoom;
		// std::cout << currentRoom->roomID << std::endl;
		if (!currentRoom->isCleared)
		{
			if (!currentRoom->isVisited)
			{
				currentRoom->isVisited = true;
				enemy_manager->fillRoomWithEnemies();
			}
			currentRoom->closeAllDoors();
			battlePhase = true;
		}
		updateMinimap();
		if (battlePhase)
			updateBattlePhase(seconds_elapsed);
	}
	else
	{
		GUI->update();
	}

	// Check for winning condition
	World *world = Game::instance->world;
	if (world->CheckWinCondition())
	{
		cout << "You win!" << endl;
		Game::instance->setStage(STAGE_ID::WIN);
	}
	// If pressing C, go to the win stage
	/*if (Input::wasKeyPressed(SDL_SCANCODE_C))
	{
		cout << "You 'win'!" << endl;
		Game::instance->setStage(STAGE_ID::WIN);
	}*/

	// Check for losing condition
	EntityPlayer *player = Game::instance->player;
	if (player->health <= 0)
	{
		cout << "You lose!" << endl;
		Game::instance->setStage(STAGE_ID::LOSE);
	}
	// If pressing L, go to the lose stage
	/*if (Input::wasKeyPressed(SDL_SCANCODE_L))
	{
		cout << "You 'lose'!" << endl;
		Game::instance->setStage(STAGE_ID::LOSE);
	}*/
}

void StageGame::updateBattlePhase(double seconds_elapsed)
{
}

void StageGame::updateMinimap()
{
	int wWidth = Game::instance->window_width;
	int wHeight = Game::instance->window_height;
	minimap.view_matrix = Matrix44();
	int mmX = 300;
	int mmY = 300;
	int mmW = Game::instance->player->maxHealth;
	int mmH = Game::instance->player->health;
	minimap.setOrthographic(mmX, mmW, mmH, mmY, -1, 1);

	// minimapFrame.mesh.createQuad(mmX, mmY, mmW, mmH, true);
}

void StageGame::renderMinimap()
{
	int wWidth = Game::instance->window_width;
	int wHeight = Game::instance->window_height;
	// float hudScale = min(wWidth, wHeight) * hudScaleFactor;
	EntityPlayer *player = Game::instance->player;

	SDL_Window *window = Game::instance->window;

	// Set the flags
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	minimap.enable();

	////Render minimap
	// renderQuad(minimapFrame.mesh, minimapFrame.texture, minimap);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glDisable(GL_BLEND);
}

void StageGame::renderQuad(Mesh quad, Texture *texture, Camera camera)
{
	Shader *qShader = Shader::Get("data/shaders/basic.vs", "data/shaders/gui.fs");

	if (!qShader)
		return;

	qShader->enable();

	qShader->setUniform("u_color", Vector4(1, 1, 1, 1));
	qShader->setUniform("u_viewprojection", camera.viewprojection_matrix);
	if (texture != NULL)
	{
		qShader->setUniform("u_texture", texture, 0);
	}
	qShader->setUniform("u_time", Game::instance->time);
	qShader->setUniform("u_tex_tiling", 1.0f);
	qShader->setUniform("u_tex_range", Vector4(0, 0, 1, 1));
	qShader->setUniform("u_model", Matrix44());
	quad.render(GL_TRIANGLES);

	qShader->disable();
}