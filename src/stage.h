#pragma once
#include "input.h"

enum STAGE_ID
{
    INTRO = 0,
    GAME = 1,
    TUTO = 2,
    WIN = 3,
    LOSE = 4
};

class Stage
{
public:
    Stage(){};
    virtual void render(){};
    virtual void update(double seconds_elapsed){};
};