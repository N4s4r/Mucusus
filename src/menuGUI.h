#pragma once
#include "includes.h"
#include "utils.h"
#include "camera.h"
#include "texture.h"
#include "mesh.h"

struct GUIText {
    char* text;
    Vector2 position;
    float scale;
};

class menuGUI
{
public:
    menuGUI();
    menuGUI(vt<char*> menuOptions);
    void render(Camera* cam);
    void update();
    int menuBoxesInitSize = 0;

    vt<GUIText> menuOptions;
    int selectedOption = 0;

    Texture* selectionBoxTexture;
    Texture* pointerTexture;

    vt<Mesh> selectionBoxes;
    Mesh pointerMesh;

    int getMenuLength();


    void moveSelector();
    void renderQuad(Mesh quad, Texture* texture, Camera* cam2d);
    void movePointer();

    void initMenuBoxes();
};

