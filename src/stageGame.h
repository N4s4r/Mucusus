#pragma once
#include "stage.h"
#include "input.h"
#include "game.h"
#include "entityMeshRoom.h"
#include "entityPlayer.h"

class StageGame : public Stage {
public:
    StageGame();
    virtual void render(EntityMeshRoom* room); //empty body
    virtual void update(double seconds_elapsed, EntityPlayer* player);//empty body
};