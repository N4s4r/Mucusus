#include "entity.h"

// Constructor
Entity::Entity()
{
    // TODO: Set it correctly
    model.setIdentity();
}

void Entity::addChild(Entity *entity)
{
    entity->parent = this;
    children.push_back(entity);
}

void Entity::removeChild(Entity *entity)
{
    entity->parent = nullptr;
    children.erase(std::find(children.begin(), children.end(), entity));
}

Matrix44 Entity::getGlobalMatrix()
{
    if (parent)
        // TODO : Check the order of the multiplication
        return parent->getGlobalMatrix() * model;
    else
        return model;
}

void Entity::render()
{
    // Render if EntityMesh
    if (dynamic_cast<EntityMesh *>(this))
        ((EntityMesh *)this)->render();

    // Render the entities
    for (Entity *entity : children)
        entity->render();
}

void Entity::update(float dt){};

// Constructor
EntityMesh::EntityMesh(Mesh *mesh, Shader *shader, Texture *texture)
    : Entity()
{
    this->mesh = mesh;
    this->texture = texture;
    this->shader = shader;
}

void EntityMesh::render()
{
    Camera *camera = Camera::current;

    shader->enable();
    shader->setUniform("u_model", model);
    shader->setUniform("u_viewproj", camera->viewprojection_matrix);
    // Slot = 0??
    shader->setTexture("u_texture", texture, 0);

    mesh->render(GL_TRIANGLES);

    shader->disable();
}

void EntityMesh::update(float dt){};

// Constructor
InstancedEntityMesh::InstancedEntityMesh(Mesh *mesh, Shader *shader, Texture *texture)
    : Entity()
{
    this->mesh = mesh;
    this->texture = texture;
    this->shader = shader;
}

void InstancedEntityMesh::render()
{
    Camera *camera = Camera::current;

    shader->enable();
    shader->setUniform("u_viewproj", camera->viewprojection_matrix);
    // Slot = 0??
    shader->setTexture("u_texture", texture, 0);
    EACH(my_model, models)
    {
        shader->setUniform("u_model", my_model);
        mesh->render(GL_TRIANGLES);
    }

    shader->disable();
}

void InstancedEntityMesh::update(float dt){};