#include "defines.h"
#include "entity.h"

void Entity::addChild(Entity* child)
{
	children.push_back(child);
	child->parent = this;
}

void Entity::removeChild(Entity* child)
{
	auto it = std::find(children.begin(), children.end(), child);
	if (it == children.end())
	{
		std::cerr << "Children out" << std::endl;
		return;
	}

	children.erase(it);
	child->parent = nullptr;
}

Matrix44 Entity::getGlobalMatrix()
{
	if (parent)
		return model * parent->getGlobalMatrix();

	return model;
}

void Entity::render()
{
	for (int i = 0; i < children.size(); i++)
		children[i]->render();
}

void Entity::update(float dt)
{
	for (int i = 0; i < children.size(); i++)
		children[i]->update(dt);
}

// mesh.create