#include "defines.h"
#include "entityMeshRoom.h"
#include "utils.h"
#include <fstream>
#include <map>


EntityMeshRoom::EntityMeshRoom()
{
    //E_wall = new EntityMesh(Game::instance->Z_wall_mesh, Game::instance->wall_texture, Matrix44::IDENTITY);
    //W_wall = new EntityMesh(Game::instance->Z_wall_mesh, Game::instance->wall_texture, Matrix44::IDENTITY);
    //N_wall = new EntityMesh(Game::instance->X_wall_mesh, Game::instance->wall_texture, Matrix44::IDENTITY);
    //S_wall = new EntityMesh(Game::instance->X_wall_mesh, Game::instance->wall_texture, Matrix44::IDENTITY);
    //floor = new EntityMesh(Game::instance->floor_mesh, Game::instance->floor_texture, Matrix44::IDENTITY);
    //ceiling = new EntityMesh(Game::instance->floor_mesh, Game::instance->floor_texture, Matrix44::IDENTITY);
    //N_wall->model.rotate(-90 * DEG2RAD, Vector3(1, 0, 0));
    //N_wall->model.translate(0, 4, -2);
    //S_wall->model.rotate(-90 * DEG2RAD, Vector3(1, 0, 0));
    //S_wall->model.translate(0, -4, -2);
    //E_wall->model.rotate(-90 * DEG2RAD, Vector3(0, 1, 0));
    //E_wall->model.rotate(-90 * DEG2RAD, Vector3(1, 0, 0));
    //E_wall->model.translate(0, -6, -2);
    //W_wall->model.rotate(-90 * DEG2RAD, Vector3(0, 1, 0));
    //W_wall->model.rotate(-90 * DEG2RAD, Vector3(1, 0, 0));
    //W_wall->model.translate(0, 6, -2);
    //ceiling->model.translate(0, 4, 0);
}


bool EntityMeshRoom::parseScene(const char* roomName)
{
	// You could fill the map manually to add shader and texture for each mesh
	// If the mesh is not in the map, you can use the MTL file to render its colors
	
	meshes_to_load["meshes/Cylinder.001.obj"] = { Texture::Get("data/textures/wall.tga"), Shader::Get("data/shaders/basic.vs", "data/shaders/texture.fs") };

	std::cout << " + Scene loading: " << roomName << "..." << std::endl;

	std::ifstream file("data/rooms/" + std::string(roomName) + "/myscene.scene");

	if (!file.good()) {
		std::cerr << "Scene [ERROR]" << " File not found!" << std::endl;
		return false;
	}

	std::string scene_info, mesh_name, model_data;
	file >> scene_info; file >> scene_info;
	int mesh_count = 0;

	// Read file line by line and store mesh path and model info in separated variables
	while (file >> mesh_name >> model_data)
	{
		// Get all 16 matrix floats
		std::vector<std::string> tokens = tokenize(model_data, ",");

		// Fill matrix converting chars to floats
		Matrix44 model;
		for (int t = 0; t < tokens.size(); ++t) {
			model.m[t] = (float)atof(tokens[t].c_str());
		}

		// Add model to mesh list (might be instanced!)
		sRenderData& render_data = meshes_to_load[mesh_name];
		render_data.models.push_back(model);
		mesh_count++;
	}

	// Iterate through meshes loaded and create corresponding entities
	for (auto data : meshes_to_load) {

		mesh_name = "data/rooms/" + std::string(roomName) + "/" + data.first;
		sRenderData& render_data = data.second;

		// No transforms, anything to do here
		if (render_data.models.empty())
			continue;

		if (render_data.shader == nullptr)
			render_data.shader = Game::instance->shader;

		// Create instanced entity
		//if (render_data.models.size() > 1) {
		//	InstancedEntityMesh* new_entity = new InstancedEntityMesh(Mesh::Get(mesh_name.c_str()), render_data.shader, render_data.texture);
		//	// Add all instances
		//	new_entity->models = render_data.models;
		//	// Add entity to scene root
		//	root.addChild(new_entity);
		//}
		//// Create normal entity
		//else {
			EntityMesh* new_entity = new EntityMesh(Mesh::Get(mesh_name.c_str()), render_data.shader, render_data.texture);
			new_entity->model = render_data.models[0];
			// Add entity to scene root
			addChild(new_entity);
		//}
	}

	std::cout << "Scene [OK]" << " Meshes added: " << mesh_count << std::endl;
	return true;
}