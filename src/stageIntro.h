#pragma once
#include "stage.h"
#include "game.h"



class StageIntro : public Stage {
public:
    StageIntro();
    virtual void render(void);
    virtual void update(double seconds_elapsed);
    //virtual void onKeyDown(SDL_KeyboardEvent event) override;
    //virtual void onMouseButtonDown(SDL_MouseButtonEvent event)override;
    bool wasLeftPressed;
};