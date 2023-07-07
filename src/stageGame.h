#pragma once
#include "stage.h"
#include "input.h"
#include "game.h"
#include "world.h"
#include "entityMeshRoom.h"
#include "entityPlayer.h"

class StageGame : public Stage {
public:
    Camera cam2d;

    // crosshair
    float chW = 20.f;
    float chH = 20.f;
    Mesh crosshair;
    Texture* crosshairTexture;

    StageGame();
    virtual void render(); //empty body
    virtual void update(double seconds_elapsed);//empty body

    void renderHUD();
    void renderQuad(Mesh quad, Texture* texture);
};