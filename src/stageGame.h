#pragma once
#include "stage.h"
#include "input.h"
#include "game.h"
#include "world.h"
#include "entityMeshRoom.h"
#include "entityPlayer.h"

struct hudValue {
    char text[4];
    Vector2 position;
};

struct hudElement 
{
    Mesh mesh;
    Texture* texture;
    hudValue statValue;
};

class StageGame : public Stage {
public:
    Camera cam2d;

    // crosshair
    float chW = 20.f;
    float chH = 20.f;

    float hudScaleFactor = 1.0f / 16.0f;

    //HUD
    hudElement crosshair;
    hudElement attack;
    hudElement caddence;
    hudElement projectileSpeed;
    hudElement playerSpeed;
    hudElement healthBar;
    hudElement healthFrame;

    StageGame();
    virtual void render(); //empty body
    virtual void update(double seconds_elapsed);//empty body

    void processHUD();
    void renderHUD();
    void renderQuad(Mesh quad, Texture* texture);
};