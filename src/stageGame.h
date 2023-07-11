#pragma once
#include "stage.h"
#include "input.h"
#include "game.h"
#include "world.h"
#include "entityMeshRoom.h"
#include "entityPlayer.h"
#include "gameHUD.h"

class EnemyManager;

class StageGame : public Stage
{
public:
    Camera cam2d;
    Camera minimap;
    EnemyManager* enemy_manager;

    gameHUD HUD;

    StageGame();
    virtual void render();                       // empty body
    virtual void update(double seconds_elapsed); // empty body

    void updateMinimap();
    void renderMinimap();
    void renderQuad(Mesh quad, Texture *texture, Camera camera);
    void renderQuad(Mesh quad, Texture *texture);
};