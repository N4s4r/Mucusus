#include "entityBullet.h"
#include "game.h"
#include "world.h"
#include "entityPlayer.h"
#include "defines.h"
#include "utils.h"

EntityBullet::EntityBullet()
{
	meshFULL = Mesh::Get("data/meshes/bullet_FULL.obj");
	meshMID = Mesh::Get("data/meshes/bullet_MID.obj");
	meshLOW = Mesh::Get("data/meshes/bullet_LOW.obj");
	shader = Shader::Get("data/shaders/basic.vs", "data/shaders/texture.fs");
	texture = Texture::Get("data/textures/wall2.tga");
}

void EntityBullet::activate(EntityEnemy* source)
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

	World* world = Game::instance->world;
	EntityPlayer* player = Game::instance->player;
	EntityMeshRoom* currentRoom = world->currentRoom;
	Vector3 position = model.getTranslation();
	std::cout << position.x << " " << position.y << " " << position.z << " " << std::endl;

	Matrix44 globalMatrix = getGlobalMatrix();

	Vector3 to_pos = position + (direction.normalize() * velocity * dt);
	vt<sCollisionData> collisions;
	EACH(room, world->mapGrid)
	{
		if (checkRoomCollisions(to_pos, collisions, room))
		{
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
		EACH(enemy, world->activeEnemies)
		{
			if (enemy->checkMeshCollision(collisions, globalMatrix, meshFULL))
			{
				enemy->applyInputDamage(player->attack);
				deactivate();
			}
		}
	}

	model.setTranslation(to_pos.x, to_pos.y, to_pos.z);
}

void EntityBullet::render()
{
	Camera* cam = Game::instance->camera;

	// LODs
	Mesh* mesh = nullptr;
	float distance = cam->eye.distance(getGlobalPosition());
	if (distance < 5 * meshFULL->radius) mesh = meshFULL;
	else if (distance < 25 * meshFULL->radius) mesh = meshMID;
	else if (distance < 100 * meshFULL->radius) mesh = meshLOW;

	float time = Game::instance->time;

	if (!shader)
		return;

	shader->enable();

	shader->setUniform("u_color", Vector4(1, 1, 1, 1));
	shader->setUniform("u_viewprojection", cam->viewprojection_matrix);
	if (texture)
		shader->setUniform("u_texture", texture, 0);
	else glBindTexture(GL_TEXTURE_2D, 0);

	shader->setUniform("u_time", time);
	shader->setUniform("u_tiles", 10.0f);
	Matrix44 mmatrix = getGlobalMatrix();
	shader->setUniform("u_model", mmatrix);

	mesh->render(GL_TRIANGLES);

	shader->disable();
}
