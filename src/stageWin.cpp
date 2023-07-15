#include "stageWin.h"
#include "game.h"
#include "world.h"

StageWin::StageWin(bool winning)
{
    cout << "StageWin::StageWin\n";
    this->winning = winning;
}

void StageWin::render()
{

    // Clear the screen in light blue color
    glClearColor(0.0, 0.0, 1.0, 1.0);

    // Clear the window and the depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Write on the center on the screen
    if (!winning)
        drawText(20, 20, "You lose!", Vector3(1, 1, 1), 3);
    else
        drawText(20, 20, "You win!", Vector3(1, 1, 1), 3);

    // Write on the center on the screen
    drawText(20, 60, "Press R to restart", Vector3(1, 1, 1), 3);

    drawText(20, 100, "Press Q to quit", Vector3(1, 1, 1), 3);
    // Swap the buffers
    SDL_GL_SwapWindow(Game::instance->window);
}

void StageWin::update(float dt)
{
    cout << "StageWin::update\n";
    // If q is pressed quit the game
    if (Input::wasKeyPressed(SDL_SCANCODE_Q) || Input::wasKeyPressed(SDL_SCANCODE_ESCAPE))
    {
        exit(0);
    }

    // If r is pressed restart the game
    if (Input::wasKeyPressed(SDL_SCANCODE_R))
    {
        Game::instance->currentStage = INTRO;
        Game::instance->world->reset();
    }
}