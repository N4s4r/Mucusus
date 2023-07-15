#include "stageTuto.h"

#include "mesh.h"
#include "texture.h"
#include "game.h"

StageTuto::StageTuto()
{
}

void StageTuto::render(void)
{
    // Clear the screen in light blue color
    glClearColor(0.0, 0.0, 1.0, 1.0);

    // Clear the window and the depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Write on the center on the screen
    drawText(20, 20, "Use WASD to move", Vector3(1, 1, 1), 3);
    drawText(20, 60, "Use the mouse to rotate the camera", Vector3(1, 1, 1), 3);
    drawText(20, 100, "Use RIGHT button to shot", Vector3(1, 1, 1), 3);
    drawText(20, 140, "Use SPACE to jump", Vector3(1, 1, 1), 3);
    drawText(20, 180, "Use ESC to pause", Vector3(1, 1, 1), 3);
    // Swap the buffers
    SDL_GL_SwapWindow(Game::instance->window);
}

void StageTuto::update(double seconds_elapsed)
{
    // Update cooldown
    cooldown -= seconds_elapsed;
    if (cooldown < 0.0f)
    {
        Game::instance->currentStage = GAME;
    }
}
