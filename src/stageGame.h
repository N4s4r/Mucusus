#pragma once
#include "stage.h"
#include "input.h"
#include "game.h"
#include "entityMeshRoom.h"
#include "entityPlayer.h"

class StageGame : public Stage {
public:
    StageGame();
    virtual void render(); //empty body
    virtual void update(double seconds_elapsed);//empty body
};