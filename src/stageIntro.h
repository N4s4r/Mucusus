#pragma once
#include "stage.h"
#include "game.h"
#include "menuGUI.h"

struct menuText {
    char* text;
    Vector2 position;
    float scale;
};

enum menuOption {
    START = 0,
    TUTOR = 1,
    EXIT = 2,
    XD = 3
};

class StageIntro : public Stage {
public:
    StageIntro();
    virtual void render(void);
    virtual void update(double seconds_elapsed);

    menuGUI* menu;
    Camera cam2d;
};