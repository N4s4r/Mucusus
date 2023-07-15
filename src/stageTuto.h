#pragma once
#include "stage.h"
#include "camera.h"

class Mesh;
class Texture;

class StageTuto : public Stage
{
public:
    StageTuto();

    float cooldown = 5.0f;

    void render(void);
    void update(double seconds_elapsed);
};
