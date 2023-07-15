#pragma once

#include "defines.h"

#include "stage.h"
#include "texture.h"
#include "menuGUI.h"

class StageWin : public Stage
{
public:
    StageWin(bool winning);
    bool winning;

    void render();
    void update(float dt);
};