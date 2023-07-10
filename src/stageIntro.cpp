#include "stageIntro.h"
#include "input.h"

#define MENU_OPTIONS 4

StageIntro::StageIntro() 
{
	vt<char*> introOptions = { "start", "tuto", "exit", "xD" };
	menu = new menuGUI(introOptions);
}

void StageIntro::render() 
{
	glClearColor(1.0, 0.0, 1.0, 1.0);
	int wWidth = Game::instance->window_width;
	int wHeight = Game::instance->window_height;
	cam2d.view_matrix = Matrix44();
	cam2d.setOrthographic(0, wWidth, wHeight, 0, -1, 1);
	menu->render(&cam2d);
};

void StageIntro::update(double seconds_elapsed) 
{
	if (Input::wasKeyPressed(SDL_SCANCODE_SPACE)) {
		switch (menu->selectedOption) {
			case menuOption::START:
				Game::instance->setStage(STAGE_ID::GAME);
				break;
			case menuOption::TUTOR:
				Game::instance->setStage(STAGE_ID::GAME);
				break;
			case menuOption::EXIT:
				Game::instance->must_exit = true;
				break;
		}
	}
	menu->update();
}
;