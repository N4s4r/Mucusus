#pragma once
#include "defines.h"
#include "entityMesh.h"

class EntityMeshRoom : public Entity
{
    struct sRenderData {
        Texture* texture = nullptr;
        Shader* shader = nullptr;
        std::vector<Matrix44> models;
    };

    std::map<std::string, sRenderData> meshes_to_load;

public:
    Matrix44 room_model;
    vt<EntityMesh*> staticEntities;

    EntityMeshRoom();

    bool parseScene(const char* filename);
    void addStaticEntity(EntityMesh* entity);
};
