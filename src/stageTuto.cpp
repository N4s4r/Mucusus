#include "stageTuto.h"
//
//StageIntro::StageIntro()
//{
//	// Windows size
//	int wWidth = Game::instance->window_width;
//	int wHeight = Game::instance->window_height;
//	float boxW = wWidth / 1.5;
//	float boxH = wHeight / 8;
//	float boxX = wWidth / 2;
//	float yScreenMargin = wHeight * 0.2;
//	float boxSpacing = (wHeight - yScreenMargin) / MENU_OPTIONS;
//
//	cam2d.view_matrix = Matrix44();
//	cam2d.setOrthographic(0, wWidth, wHeight, 0, -1, 1);
//
//	quadTexture = Texture::Get("data/textures/ceiling.tga");
//	menuSelectorTexture = Texture::Get("data/textures/crosshair.tga");
//	char* options[MENU_OPTIONS] = { "Start Game", "Controls", "Exit", "xd" };
//
//	for (int i = 0; i < MENU_OPTIONS; i++)
//	{
//		float y = boxSpacing * i + yScreenMargin;
//
//		Mesh quad;
//		quad.createQuad(boxX, y, boxW, boxH, true);
//		quads.push_back(quad);
//
//		//TEXT
//		menuText text;
//		text.text = options[i];
//		text.scale = wWidth / 400;
//		text.position = Vector2(boxX - strlen(text.text) * (3 + text.scale), y - 10);
//		labels.push_back(text);
//	}
//	// Menu selector
//	float selX = boxX - boxW / 2 - 50;
//	float y = boxSpacing * selectedOption + yScreenMargin;;
//	float w = 50;
//	float h = 50;
//	menuSelectorMesh.createQuad(selX, y, w, h, true);
//}
//
//void StageIntro::render()
//{
//	SDL_Window* window = Game::instance->window;
//	// set the clear color (the background color)
//	glClearColor(1.0, 0.0, 1.0, 1.0);
//
//	// Clear the window and the depth buffer
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//	// Set the flags
//	glDisable(GL_DEPTH_TEST);
//	glDisable(GL_CULL_FACE);
//	glEnable(GL_BLEND);
//	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//
//	cam2d.enable();
//
//	//Render Quads
//	Texture* texture = quadTexture;
//	for (int i = 0; i < quads.size(); i++)
//	{
//		Mesh quad = quads[i];
//		renderQuad(quad, texture);
//	}
//	//Render selector
//	Mesh selector = menuSelectorMesh;
//	texture = menuSelectorTexture;
//	renderQuad(selector, texture);
//	// Render text
//	for (int i = 0; i < labels.size(); i++)
//	{
//		menuText curr = labels[i];
//		drawText(curr.position.x, curr.position.y, curr.text, Vector3(1, 1, 1), curr.scale);
//	}
//
//
//	glEnable(GL_DEPTH_TEST);
//	glEnable(GL_CULL_FACE);
//	glDisable(GL_BLEND);
//	SDL_GL_SwapWindow(window);
//};
//
//void StageIntro::update(double seconds_elapsed)
//{
//	if (Input::wasKeyPressed(SDL_SCANCODE_S)) {
//		selectedOption = static_cast<menuOption>((selectedOption + 1) % MENU_OPTIONS);
//		changeSelector();
//	}
//
//	if (Input::wasKeyPressed(SDL_SCANCODE_W)) {
//		int to_option = (selectedOption - 1) % MENU_OPTIONS;
//		if (to_option < 0) to_option = MENU_OPTIONS - 1;
//		selectedOption = static_cast<menuOption>(to_option);
//
//		changeSelector();
//	}
//
//	if (Input::wasKeyPressed(SDL_SCANCODE_SPACE)) {
//		switch (selectedOption) {
//		case menuOption::START:
//			Game::instance->setStage(STAGE_ID::GAME);
//			break;
//		case menuOption::TUTO:
//			Game::instance->setStage(STAGE_ID::GAME);
//			break;
//		case menuOption::EXIT:
//			Game::instance->must_exit = true;
//			break;
//		}
//
//	}
//}