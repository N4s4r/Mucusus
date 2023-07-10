#pragma once
#include "mesh.h"
#include "texture.h"
#include "camera.h"

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

class gameHUD
{
public:

    gameHUD();

    Camera cam2d;
    int elementsInitSize = 0;

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

    void initHUD();
    void initHUDElements();
    void updateHUDElements();
    void render();

    void renderQuad(Mesh quad, Texture* texture);
};

