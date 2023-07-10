#pragma once
#include "stage.h"
#include "camera.h"

class Mesh;
class Texture;

class StageTuto : public Stage
{
public:
    StageTuto();
    virtual void render(void);
    virtual void update(double seconds_elapsed);

    int currentPage = 1;

    vt<Mesh> pages;
    Camera cam2d;

    void renderQuad(Mesh quad, Texture *texture);
};
