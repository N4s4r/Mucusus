#pragma once
#include "stage.h"
#include "input.h"
#include "game.h"
#include "world.h"
#include "entityMeshRoom.h"
#include "entityPlayer.h"
#include "gameHUD.h"
#include "menuGUI.h"

class EnemyManager;

class StageGame : public Stage
{
public:
    Camera cam2d;
    Camera minimap;
    EnemyManager *enemy_manager;

    bool battlePhase = false;

    gameHUD HUD;
    menuGUI *GUI;

    StageGame();

    virtual void render();                       // empty body
    virtual void update(double seconds_elapsed); // empty body

    void updateBattlePhase(double seconds_elapsed);

    void updateMinimap();
    void renderMinimap();
    void renderQuad(Mesh quad, Texture *texture, Camera camera);
    void renderQuad(Mesh quad, Texture *texture);
};