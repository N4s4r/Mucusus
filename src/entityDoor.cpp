#include "entityDoor.h"
#include "game.h"

EntityDoor::EntityDoor()
{
}

EntityDoor::EntityDoor(Directions direction, bool isExternal)
{
	Vector3 position;
	switch (direction)
	{
	case NORTH:
		model.setTranslation(16.0f, -0.1f, 8.0f);
		rotationFactor = M_PI / 2.0f;
		break;
	case EAST:
		model.setTranslation(8.0f, -0.1f, 16.0f);
		rotationFactor = 0.0f;
		break;
	case SOUTH:
		model.setTranslation(0.0f, -0.1f, 8.0f);
		rotationFactor = -M_PI / 2.0f;
		break;
	case WEST:
		model.setTranslation(8.0f, -0.1f, 0.0f);
		rotationFactor = M_PI;
		break;
	}
	model.rotate(rotationFactor, Vector3(.0f, 1.0f, .0f));
	this->isExternal = isExternal;
	if (isExternal)
	{
		meshFULL = Mesh::Get("data/meshes/Door.obj");
		meshMID = Mesh::Get("data/meshes/Door.obj");
		meshLOW = Mesh::Get("data/meshes/Door.obj");
		texture = Texture::Get("data/textures/externalDoor.tga");
	}
	else
	{
		meshFULL = Mesh::Get("data/meshes/Door.obj");
		meshMID = Mesh::Get("data/meshes/Door.obj");
		meshLOW = Mesh::Get("data/meshes/Door.obj");
		texture = Texture::Get("data/textures/internalDoor.tga");
	}
	shader = Shader::Get("data/shaders/basic.vs", "data/shaders/texture.fs");
}

void EntityDoor::render()
{
	Camera* cam = Game::instance->camera;

	// LODs
	Mesh* mesh = nullptr;
	float distance = cam->eye.distance(getGlobalPosition());
	if (distance < 5 * meshFULL->radius) mesh = meshFULL;
	else if (distance < 25 * meshFULL->radius) mesh = meshMID;
	else if (distance < 100 * meshFULL->radius) mesh = meshLOW;
	else return;

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

void EntityDoor::update(float dt)
{
	
	if (isExternal) return;
	float new_y ;
	Vector3 position = model.getTranslation();
	Vector3 to_pos;
	if (isClosed && position.y != -0.1f) // Close door
	{
		to_pos = position + (Vector3(0.0f, 1.0f, 0.0f).normalize() * closingSpeed * dt);
	}
	else if (!isClosed && position.y != -3.0f) // Open DOor
	{
		to_pos = position + (Vector3(0.0f, -1.0f, 0.0f).normalize() * openingSpeed * dt);
	}
	else
	{
		return;
	}
	model.setTranslation(to_pos.x, clamp(to_pos.y, -3.0f, -0.1f), to_pos.z);
	model.rotate(rotationFactor, Vector3(.0f, 1.0f, .0f));
}