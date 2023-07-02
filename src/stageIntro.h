#pragma once
#include "stage.h"
#include "game.h"

struct menuText {
    char* text;
    Vector2 position;
    float scale;
};

enum menuOption {
    START = 0,
    TUTO = 1,
    EXIT = 2,
    XD = 3
};

class StageIntro : public Stage {
public:
    StageIntro();
    virtual void render(void);
    virtual void update(double seconds_elapsed);
    //virtual void onKeyDown(SDL_KeyboardEvent event) override;
    //virtual void onMouseButtonDown(SDL_MouseButtonEvent event)override;
    bool wasLeftPressed;
    int initSize = 0;
    menuOption selectedOption = START;
    Texture* quadTexture;

    // Menu ponter
    Texture* menuSelectorTexture;
    Mesh menuSelectorMesh;


    vt<Mesh> quads;
    vt<menuText> labels;
    Camera cam2d;

    //Textures
    //Texture* example = Texture::Get("data/example.png")
    
    void changeSelector();
    void renderQuad(Mesh quad, Texture* texture);
    void movePointer();

};