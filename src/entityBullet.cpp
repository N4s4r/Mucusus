#include "entityBullet.h"
#include "game.h"
#include "world.h"
#include "entityPlayer.h"
#include "defines.h"
#include "utils.h"

EntityBullet::EntityBullet()
{
	// Load bullet mesh
}

void EntityBullet::activate()
{
	isActive = true;
	liveTime = BULLETLIVETIME;
}

void EntityBullet::deactivate()
{
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

	Vector3 to_pos = position + (direction * player->projectileSpeed * dt);
	vt<sCollisionData> collisions;
	if (checkRoomCollisions(to_pos, collisions, currentRoom))
	{
		deactivate();
		return;
	}
	if (enemySource)
	{

	}

	model.setTranslation(position.x, position.y, position.z);
}
