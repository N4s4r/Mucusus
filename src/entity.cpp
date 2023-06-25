#include "entity.h"

Entity::Entity()
{
    // Set default values
    name = "";
    model.setIdentity();
    parent = nullptr;
}

Entity::~Entity()
{
    // Delete it from its parent
    if (parent)
    {
        parent->removeChild(this);
    }
    // Delete children
    FOR(i, 0, children.size())
    {
        delete children[i];
    }
}

void Entity::render()
{
    if (dynamic_cast<EntityMesh *>(this))
    {
        ((EntityMesh *)this)->render();
    }

    // Render children
    FOR(i, 0, children.size())
    {
        children[i]->render();
    }
}

void Entity::update(float dt)
{
    if (dynamic_cast<EntityMesh *>(this))
    {
        ((EntityMesh *)this)->update(dt);
    }

    // Update children
    FOR(i, 0, children.size())
    {
        children[i]->update(dt);
    }
}

void Entity::addChild(Entity *child)
{
    children.push_back(child);
    child->parent = this;
}

void Entity::removeChild(Entity *child)
{
    int index = -1;
    FOR(i, 0, children.size())
    {
        if (children[i] == child)
        {
            index = i;
            break;
        }
    }
    if (index != -1)
    {
        children.erase(children.begin() + index);
    }
}

Matrix44 Entity::getGlobalMatrix()
{
    if (parent)
        return model * parent->getGlobalMatrix();
    return model;
}

EntityMesh::EntityMesh(Mesh *mesh, Shader *shader, Texture *texture)
{
    this->mesh = mesh;
    this->texture = texture;
    this->shader = shader;
    color = Vector4(1, 1, 1, 1);
}

void EntityMesh::render()
{
    Camera *camera = Camera::current;
    shader->enable();
    shader->setUniform("u_color", color);
    shader->setUniform("u_model", model);
    shader->setUniform("u_viewprojection", camera->viewprojection_matrix);
    shader->setTexture("u_texture", texture, 0);
    mesh->render(GL_TRIANGLES);
    shader->disable();
}

void EntityMesh::update(float dt)
{
    // Don't do anything by default
}

InstancedEntityMesh::InstancedEntityMesh(Mesh *mesh, Shader *shader, Texture *texture)
{
    this->mesh = mesh;
    this->texture = texture;
    this->shader = shader;
    color = Vector4(1, 1, 1, 1);
}

void InstancedEntityMesh::render()
{
    Camera *camera = Camera::current;
    shader->enable();
    shader->setUniform("u_color", color);
    shader->setUniform("u_viewprojection", camera->viewprojection_matrix);
    shader->setTexture("u_texture", texture, 0);
    EACH(model, models)
    {
        shader->setUniform("u_model", model);
        mesh->render(GL_TRIANGLES);
    }
    shader->disable();
};

void InstancedEntityMesh::update(float dt)
{
    // Don't do anything by default
}