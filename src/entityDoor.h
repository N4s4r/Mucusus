#pragma once
#include "entityMesh.h"

class entityDoor : public EntityMesh
{
public:
	entityDoor();

	bool isClose = true;

	void close();
	void open();

};

