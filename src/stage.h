#pragma once
#include "input.h"
#include "entityMeshRoom.h"
#include "entityPlayer.h"


enum STAGE_ID {
    INTRO = 0,
    GAME = 1,
};

class Stage
{
public:
    Stage() {};
    virtual void render() {};
    virtual void update(double seconds_elapsed) {};
};