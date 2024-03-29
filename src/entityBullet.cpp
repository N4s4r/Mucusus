#include "entityBullet.h"
#include "game.h"
#include "world.h"
#include "entityPlayer.h"
#include "defines.h"
#include "utils.h"
#include "entityEnemy.h"
#include "stageGame.h"
#include "game.h"
#include "enemyManager.h"

EntityBullet::EntityBullet()
{
	meshFULL = Mesh::Get("data/meshes/bullet_FULL.obj");
	meshMID = Mesh::Get("data/meshes/bullet_MID.obj");
	meshLOW = Mesh::Get("data/meshes/bullet_LOW.obj");
	shader = Shader::Get("data/shaders/basic.vs", "data/shaders/texture.fs");
	texture = Texture::Get("data/textures/wall.tga");
}

void EntityBullet::activate(EntityEnemy *source)
{
	enemySource = source;
	isActive = true;
	liveTime = BULLETLIVETIME;
}

void EntityBullet::deactivate()
{
	enemySource = nullptr;
	isActive = false;
}

void EntityBullet::update(float dt)
{
	liveTime -= dt;
	if (liveTime < 0.0f)
	{
		deactivate();
		return;
	}

	World *world = Game::instance->world;
	EntityPlayer *player = Game::instance->player;
	EntityMeshRoom *currentRoom = player->currentRoom;
	Vector3 position = model.getTranslation();

	Matrix44 globalMatrix = getGlobalMatrix();

	Vector3 to_pos = position + (direction.normalize() * velocity * dt);
	vt<sCollisionData> collisions;
	EACH(room, world->mapGrid)
	{
		if (!room)
			continue;
		if (checkRoomCollisions(to_pos, collisions, room, 0.2f))
		{
			cout << "Bullet hit wall" << endl;
			deactivate();
			return;
		}
	}
	if (enemySource)
	{
		if (player->checkMeshCollision(collisions, globalMatrix, meshFULL))
		{
			player->applyInputDamage(enemySource);
			deactivate();
		}
	}
	else
	{
		// Check enemy collisions
		StageGame *stageGame = (StageGame *)Game::instance->stages[(int)Game::instance->currentStage];
		EACH(enemy, stageGame->enemy_manager->enemies)
		{
			if (enemy->checkMeshCollision(collisions, globalMatrix, meshFULL))
			{
				enemy->applyInputDamage(player->attack);
				deactivate();
				cout << "Bullet hit enemy" << endl;
			}
		}
	}

	model.setTranslation(to_pos.x, to_pos.y, to_pos.z);
}

void EntityBullet::render()
{
	Camera *cam = Game::instance->camera;

	// LODs
	Mesh *mesh = nullptr;
	float distance = cam->eye.distance(getGlobalPosition());
	if (distance < 5 * meshFULL->radius)
		mesh = meshFULL;
	else if (distance < 25 * meshFULL->radius)
		mesh = meshMID;
	else if (distance < 100 * meshFULL->radius)
		mesh = meshLOW;
	else
		return;

	float time = Game::instance->time;

	if (!shader)
		return;

	shader->enable();

	shader->setUniform("u_color", Vector4(1, 1, 1, 1));
	shader->setUniform("u_viewprojection", cam->viewprojection_matrix);
	if (texture)
		shader->setUniform("u_texture", texture, 0);
	else
		glBindTexture(GL_TEXTURE_2D, 0);

	shader->setUniform("u_time", time);
	shader->setUniform("u_tiles", 10.0f);
	Matrix44 mmatrix = getGlobalMatrix();
	shader->setUniform("u_model", mmatrix);

	mesh->render(GL_TRIANGLES);

	shader->disable();
}
