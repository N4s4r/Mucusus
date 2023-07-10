#include "defines.h"
#include "entityMeshRoom.h"
#include "utils.h"
#include <fstream>
#include <map>
#include "entityMesh.h"

EntityMeshRoom::EntityMeshRoom()
{
	// E_wall = new EntityMesh(Game::instance->Z_wall_mesh, Game::instance->wall_texture, Matrix44::IDENTITY);
	// W_wall = new EntityMesh(Game::instance->Z_wall_mesh, Game::instance->wall_texture, Matrix44::IDENTITY);
	// N_wall = new EntityMesh(Game::instance->X_wall_mesh, Game::instance->wall_texture, Matrix44::IDENTITY);
	// S_wall = new EntityMesh(Game::instance->X_wall_mesh, Game::instance->wall_texture, Matrix44::IDENTITY);
	// floor = new EntityMesh(Game::instance->floor_mesh, Game::instance->floor_texture, Matrix44::IDENTITY);
	// ceiling = new EntityMesh(Game::instance->floor_mesh, Game::instance->floor_texture, Matrix44::IDENTITY);
	// N_wall->model.rotate(-90 * DEG2RAD, Vector3(1, 0, 0));
	// N_wall->model.translate(0, 4, -2);
	// S_wall->model.rotate(-90 * DEG2RAD, Vector3(1, 0, 0));
	// S_wall->model.translate(0, -4, -2);
	// E_wall->model.rotate(-90 * DEG2RAD, Vector3(0, 1, 0));
	// E_wall->model.rotate(-90 * DEG2RAD, Vector3(1, 0, 0));
	// E_wall->model.translate(0, -6, -2);
	// W_wall->model.rotate(-90 * DEG2RAD, Vector3(0, 1, 0));
	// W_wall->model.rotate(-90 * DEG2RAD, Vector3(1, 0, 0));
	// W_wall->model.translate(0, 6, -2);
	// ceiling->model.translate(0, 4, 0);
}

bool EntityMeshRoom::parseScene(const char *roomName)
{
	// You could fill the map manually to add shader and texture for each mesh
	// If the mesh is not in the map, you can use the MTL file to render its colors

	//  meshes_to_load["meshes/Ceiling.obj"] = { Texture::Get("data/textures/ceiling.tga"), Shader::Get("data/shaders/basic.vs", "data/shaders/texture.fs") };
	//  meshes_to_load["meshes/Floor.obj"] = { Texture::Get("data/textures/floor.tga"), Shader::Get("data/shaders/basic.vs", "data/shaders/texture.fs") };
	//  meshes_to_load["meshes/pilarsEast.obj"] = { Texture::Get("data/textures/pilar.tga"), Shader::Get("data/shaders/basic.vs", "data/shaders/texture.fs") };
	//  meshes_to_load["meshes/pilarsWest.obj"] = { Texture::Get("data/textures/pilar.tga"), Shader::Get("data/shaders/basic.vs", "data/shaders/texture.fs") };
	//  meshes_to_load["meshes/pilarsSouth.obj"] = { Texture::Get("data/textures/pilar.tga"), Shader::Get("data/shaders/basic.vs", "data/shaders/texture.fs") };
	//  meshes_to_load["meshes/pilarsNorth.obj"] = { Texture::Get("data/textures/pilar.tga"), Shader::Get("data/shaders/basic.vs", "data/shaders/texture.fs") };
	//  meshes_to_load["meshes/bigaEast.obj"] = { Texture::Get("data/textures/biga.tga"), Shader::Get("data/shaders/basic.vs", "data/shaders/texture.fs") };
	//  meshes_to_load["meshes/bigaWest.obj"] = { Texture::Get("data/textures/biga.tga"), Shader::Get("data/shaders/basic.vs", "data/shaders/texture.fs") };
	//  meshes_to_load["meshes/bigaSouth.obj"] = { Texture::Get("data/textures/biga.tga"), Shader::Get("data/shaders/basic.vs", "data/shaders/texture.fs") };
	//  meshes_to_load["meshes/bigaNorth.obj"] = { Texture::Get("data/textures/biga.tga"), Shader::Get("data/shaders/basic.vs", "data/shaders/texture.fs") };
	//  meshes_to_load["meshes/wallEast.obj"] = { Texture::Get("data/textures/wall2.tga"), Shader::Get("data/shaders/basic.vs", "data/shaders/texture.fs") };
	//  meshes_to_load["meshes/wallWest.obj"] = { Texture::Get("data/textures/wall2.tga"), Shader::Get("data/shaders/basic.vs", "data/shaders/texture.fs") };
	//  meshes_to_load["meshes/wallSouth.obj"] = { Texture::Get("data/textures/wall2.tga"), Shader::Get("data/shaders/basic.vs", "data/shaders/texture.fs") };
	//  meshes_to_load["meshes/wallNorth.obj"] = { Texture::Get("data/textures/biga.tga"), Shader::Get("data/shaders/basic.vs", "data/shaders/texture.fs") };
	//  meshes_to_load["meshes/MidCube.obj"] = { Texture::Get("data/textures/wall2.tga"), Shader::Get("data/shaders/basic.vs", "data/shaders/texture.fs") };
	//  meshes_to_load["meshes/diagonalNW.obj"] = { Texture::Get("data/textures/wall2.tga"), Shader::Get("data/shaders/basic.vs", "data/shaders/texture.fs") };
	//  meshes_to_load["meshes/diagonalSW.obj"] = { Texture::Get("data/textures/wall2.tga"), Shader::Get("data/shaders/basic.vs", "data/shaders/texture.fs") };
	//  meshes_to_load["meshes/diagonalNE.obj"] = { Texture::Get("data/textures/wall2.tga"), Shader::Get("data/shaders/basic.vs", "data/shaders/texture.fs") };
	//  meshes_to_load["meshes/diagonalSE.obj"] = { Texture::Get("data/textures/wall2.tga"), Shader::Get("data/shaders/basic.vs", "data/shaders/texture.fs") };

	meshes_to_load["meshes/Ceiling.obj"].texture = Texture::Get("data/textures/ceiling.tga");
	meshes_to_load["meshes/Ceiling.obj"].shader = Shader::Get("data/shaders/basic.vs", "data/shaders/texture.fs");
	meshes_to_load["meshes/Floor.obj"].texture = Texture::Get("data/textures/floor.tga");
	meshes_to_load["meshes/Floor.obj"].shader = Shader::Get("data/shaders/basic.vs", "data/shaders/texture.fs");
	meshes_to_load["meshes/pilarsEast.obj"].texture = Texture::Get("data/textures/pilar.tga");
	meshes_to_load["meshes/pilarsEast.obj"].shader = Shader::Get("data/shaders/basic.vs", "data/shaders/texture.fs");
	meshes_to_load["meshes/pilarsWest.obj"].texture = Texture::Get("data/textures/pilar.tga");
	meshes_to_load["meshes/pilarsWest.obj"].shader = Shader::Get("data/shaders/basic.vs", "data/shaders/texture.fs");
	meshes_to_load["meshes/pilarsSouth.obj"].texture = Texture::Get("data/textures/pilar.tga");
	meshes_to_load["meshes/pilarsSouth.obj"].shader = Shader::Get("data/shaders/basic.vs", "data/shaders/texture.fs");
	meshes_to_load["meshes/pilarsNorth.obj"].texture = Texture::Get("data/textures/pilar.tga");
	meshes_to_load["meshes/pilarsNorth.obj"].shader = Shader::Get("data/shaders/basic.vs", "data/shaders/texture.fs");
	meshes_to_load["meshes/bigaEast.obj"].texture = Texture::Get("data/textures/biga.tga");
	meshes_to_load["meshes/bigaEast.obj"].shader = Shader::Get("data/shaders/basic.vs", "data/shaders/texture.fs");
	meshes_to_load["meshes/bigaWest.obj"].texture = Texture::Get("data/textures/biga.tga");
	meshes_to_load["meshes/bigaWest.obj"].shader = Shader::Get("data/shaders/basic.vs", "data/shaders/texture.fs");
	meshes_to_load["meshes/bigaSouth.obj"].texture = Texture::Get("data/textures/biga.tga");
	meshes_to_load["meshes/bigaSouth.obj"].shader = Shader::Get("data/shaders/basic.vs", "data/shaders/texture.fs");
	meshes_to_load["meshes/bigaNorth.obj"].texture = Texture::Get("data/textures/biga.tga");
	meshes_to_load["meshes/bigaNorth.obj"].shader = Shader::Get("data/shaders/basic.vs", "data/shaders/texture.fs");
	meshes_to_load["meshes/wallEast.obj"].texture = Texture::Get("data/textures/wall2.tga");
	meshes_to_load["meshes/wallEast.obj"].shader = Shader::Get("data/shaders/basic.vs", "data/shaders/texture.fs");
	meshes_to_load["meshes/wallWest.obj"].texture = Texture::Get("data/textures/wall2.tga");
	meshes_to_load["meshes/wallWest.obj"].shader = Shader::Get("data/shaders/basic.vs", "data/shaders/texture.fs");
	meshes_to_load["meshes/wallSouth.obj"].texture = Texture::Get("data/textures/wall2.tga");
	meshes_to_load["meshes/wallSouth.obj"].shader = Shader::Get("data/shaders/basic.vs", "data/shaders/texture.fs");
	meshes_to_load["meshes/wallNorth.obj"].texture = Texture::Get("data/textures/biga.tga");
	meshes_to_load["meshes/wallNorth.obj"].shader = Shader::Get("data/shaders/basic.vs", "data/shaders/texture.fs");
	meshes_to_load["meshes/MidCube.obj"].texture = Texture::Get("data/textures/wall2.tga");
	meshes_to_load["meshes/MidCube.obj"].shader = Shader::Get("data/shaders/basic.vs", "data/shaders/texture.fs");
	meshes_to_load["meshes/diagonalNW.obj"].texture = Texture::Get("data/textures/wall2.tga");
	meshes_to_load["meshes/diagonalNW.obj"].shader = Shader::Get("data/shaders/basic.vs", "data/shaders/texture.fs");
	meshes_to_load["meshes/diagonalSW.obj"].texture = Texture::Get("data/textures/wall2.tga");
	meshes_to_load["meshes/diagonalSW.obj"].shader = Shader::Get("data/shaders/basic.vs", "data/shaders/texture.fs");
	meshes_to_load["meshes/diagonalNE.obj"].texture = Texture::Get("data/textures/wall2.tga");
	meshes_to_load["meshes/diagonalNE.obj"].shader = Shader::Get("data/shaders/basic.vs", "data/shaders/texture.fs");
	meshes_to_load["meshes/diagonalSE.obj"].texture = Texture::Get("data/textures/wall2.tga");
	meshes_to_load["meshes/diagonalSE.obj"].shader = Shader::Get("data/shaders/basic.vs", "data/shaders/texture.fs");

	// vt<str> paths = { "meshes/Ceiling.obj", "meshes/Floor.obj", "meshes/frameEast.obj", "meshes/frameWest.obj", "meshes/frameSouth.obj", "meshes/frameNorth.obj", "meshes/wallEast.obj", "meshes/wallWest.obj", "meshes/wallSouth.obj", "meshes/wallNorth.obj" };
	// EACH(path, paths)
	//{
	//	meshes_to_load[path].texture = Texture::Get("data/textures/wall.tga");
	//	meshes_to_load[path].shader = Shader::Get("data/shaders/basic.vs", "data/shaders/texture.fs");
	// }

	std::cout << " + Scene loading: " << roomName << "..." << std::endl;

	std::ifstream file("data/rooms/" + std::string(roomName) + "/myscene.scene");

	if (!file.good())
	{
		std::cerr << "Scene [ERROR]"
				  << " File not found!" << std::endl;
		return false;
	}

	std::string scene_info, mesh_name, model_data, entity_name;
	file >> scene_info;
	file >> scene_info;
	int mesh_count = 0;

	// Read file line by line and store mesh path and model info in separated variables
	while (file >> mesh_name >> model_data)
	{
		// Get all 16 matrix floats
		std::vector<std::string> tokens = tokenize(model_data, ",");

		// Fill matrix converting chars to floats
		Matrix44 model;
		for (int t = 0; t < tokens.size(); ++t)
		{
			model.m[t] = (float)atof(tokens[t].c_str());
		}

		// Add model to mesh list (might be instanced!)
		sRenderData &render_data = meshes_to_load[mesh_name];
		render_data.models.push_back(model);
		mesh_count++;
	}

	// Iterate through meshes loaded and create corresponding entities
	for (auto data : meshes_to_load)
	{
		entity_name = data.first;
		mesh_name = "data/rooms/" + std::string(roomName) + "/" + entity_name;
		sRenderData &render_data = data.second;

		// No transforms, anything to do here
		if (render_data.models.empty())
			continue;

		if (render_data.shader == nullptr)
			render_data.shader = Game::instance->shader;

		// Create instanced entity
		// if (render_data.models.size() > 1) {
		//	InstancedEntityMesh* new_entity = new InstancedEntityMesh(Mesh::Get(mesh_name.c_str()), render_data.shader, render_data.texture);
		//	// Add all instances
		//	new_entity->models = render_data.models;
		//	// Add entity to scene root
		//	root.addChild(new_entity);
		// }
		//// Create normal entity
		// else {
		EntityMesh *new_entity = new EntityMesh(Mesh::Get(mesh_name.c_str()), render_data.shader, render_data.texture);
		new_entity->model = render_data.models[0];
		// Add entity to scene root
		addChild(new_entity);
		addStaticEntity(new_entity);
		//}
		if (entity_name == "meshes/Ceiling.obj")
			ceiling = new_entity;
		else if (entity_name == "meshes/Floor.obj")
			floor = new_entity;
		else if (entity_name == "meshes/pilarsEast.obj")
			pilarEast = new_entity;
		else if (entity_name == "meshes/pilarsWest.obj")
			pilarWest = new_entity;
		else if (entity_name == "meshes/pilarsSouth.obj")
			pilarSouth = new_entity;
		else if (entity_name == "meshes/pilarsNorth.obj")
			pilarNorth = new_entity;
		else if (entity_name == "meshes/bigaEast.obj")
			bigaEast = new_entity;
		else if (entity_name == "meshes/bigaWest.obj")
			bigaWest = new_entity;
		else if (entity_name == "meshes/bigaSouth.obj")
			bigaSouth = new_entity;
		else if (entity_name == "meshes/bigaNorth.obj")
			bigaNorth = new_entity;
		else if (entity_name == "meshes/wallEast.obj")
			wallEast = new_entity;
		else if (entity_name == "meshes/wallWest.obj")
			wallWest = new_entity;
		else if (entity_name == "meshes/wallSouth.obj")
			wallSouth = new_entity;
		else if (entity_name == "meshes/wallNorth.obj")
			wallNorth = new_entity;
		else if (entity_name == "meshes/MidCube.obj")
			midCube = new_entity;
		else if (entity_name == "meshes/diagonalNW.obj")
			diagonalNW = new_entity;
		else if (entity_name == "meshes/diagonalSW.obj")
			diagonalSW = new_entity;
		else if (entity_name == "meshes/diagonalNE.obj")
			diagonalNE = new_entity;
		else if (entity_name == "meshes/diagonalSE.obj")
			diagonalSE = new_entity;
	}

	std::cout << "Scene [OK]"
			  << " Meshes added: " << mesh_count << std::endl;
	return true;
}

void EntityMeshRoom::addStaticEntity(EntityMesh *entity)
{
	staticEntities.push_back(entity);
}
