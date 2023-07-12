#include "entityDoor.h"
#include "game.h"

EntityDoor::EntityDoor()
{
}

EntityDoor::EntityDoor(Vector3 position, bool isExternal)
{
	this->isExternal = true;
	if (isExternal)
	{
		meshFULL = Mesh::Get("data/meshes/InteractiveDoor_FULL.obj");
		meshMID = Mesh::Get("data/meshes/InteractiveDoor_MID.obj");
		meshLOW = Mesh::Get("data/meshes/InteractiveDoor_LOW.obj");
	}
	else
	{
		meshFULL = Mesh::Get("data/meshes/InteractiveDoor_FULL.obj");
		meshMID = Mesh::Get("data/meshes/InteractiveDoor_MID.obj");
		meshLOW = Mesh::Get("data/meshes/InteractiveDoor_LOW.obj");
	}
	shader = Shader::Get("data/shaders/basic.vs", "data/shaders/texture.fs");
	texture = Texture::Get("data/textures/wall2.tga");
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
