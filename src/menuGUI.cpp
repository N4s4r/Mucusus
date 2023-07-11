#include "menuGUI.h"
#include "game.h"
#include "input.h"

menuGUI::menuGUI(vt<char*> menuOptions)
{
	selectionBoxTexture = Texture::Get("data/textures/ceiling.tga");
	pointerTexture = Texture::Get("data/textures/HUD/glove.tga");
	EACH(option, menuOptions)
	{
		GUIText text;
		text.text = option;
		this->menuOptions.push_back(text);

		Mesh quad;
		selectionBoxes.push_back(quad);
	}


	initMenuBoxes();
	menuBoxesInitSize = Game::instance->window_height;
}

int menuGUI::getMenuLength()
{
    return menuOptions.size();
}

void menuGUI::initMenuBoxes()
{
	// Windows size
	int wWidth = Game::instance->window_width;
	int wHeight = Game::instance->window_height;
	float boxW = wWidth / 1.5;
	float boxH = wHeight / 8;
	float boxX = wWidth / 2;
	float yScreenMargin = wHeight * 0.2;
	float boxSpacing = (wHeight - yScreenMargin) / getMenuLength();

	for (int i = 0; i < getMenuLength(); i++)
	{
		float y = boxSpacing * i + yScreenMargin;
		selectionBoxes[i].vertices.clear();
		selectionBoxes[i].createQuad(boxX, y, boxW, boxH, true);

		//TEXT
		menuOptions[i].scale = wWidth / 400;
		menuOptions[i].position = Vector2(boxX - strlen(menuOptions[i].text) * (3 + menuOptions[i].scale), y - 10);
	}
	// Menu selector
	float selX = boxX - boxW / 2 - 50;
	float y = boxSpacing * selectedOption + yScreenMargin;;
	float w = 50;
	float h = 50;
	pointerMesh.vertices.clear();
	pointerMesh.createQuad(selX, y, w, h, true);
}

void menuGUI::moveSelector()
{
	int wWidth = Game::instance->window_width;
	int wHeight = Game::instance->window_height;

	float boxW = wWidth / 1.5;
	float boxH = wHeight / 8;
	float boxX = wWidth / 2;
	float yScreenMargin = wHeight * 0.2;
	float boxSpacing = (wHeight - yScreenMargin) / getMenuLength();

	float selX = boxX - boxW / 2 - 50;
	float y = boxSpacing * selectedOption + yScreenMargin;;
	float w = 50;
	float h = 50;

	// create selector visuals
	pointerMesh.vertices.clear();
	pointerMesh.createQuad(selX, y, w, h, true);
}

void menuGUI::render(Camera* cam2d)
{
	if (menuBoxesInitSize != Game::instance->window_height) { //resize window
		menuBoxesInitSize = Game::instance->window_height;
		initMenuBoxes();
	}

	SDL_Window* window = Game::instance->window;

	// Clear the window and the depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Set the flags
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	cam2d->enable();

	//Render Quads
	for (int i = 0; i < selectionBoxes.size(); i++)
	{
		Mesh quad = selectionBoxes[i];
		renderQuad(quad, selectionBoxTexture, cam2d);
	}
	//Render selector
	renderQuad(pointerMesh, pointerTexture, cam2d);
	// Render text
	for (int i = 0; i < menuOptions.size(); i++)
	{
		GUIText curr = menuOptions[i];
		drawText(curr.position.x, curr.position.y, curr.text, Vector3(1, 1, 1), curr.scale);
	}

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glDisable(GL_BLEND);
	//SDL_GL_SwapWindow(window);
};

void menuGUI::update()
{
	if (Input::wasKeyPressed(SDL_SCANCODE_S)) {
		selectedOption = (selectedOption + 1) % getMenuLength();
		moveSelector();
	}

	if (Input::wasKeyPressed(SDL_SCANCODE_W)) {
		int to_option = (selectedOption - 1) % getMenuLength();
		if (to_option < 0) to_option = getMenuLength() - 1;
		selectedOption = to_option;
		moveSelector();
	}
}

void menuGUI::renderQuad(Mesh quad, Texture* texture, Camera* cam2d)
{
	Shader* qShader = Shader::Get("data/shaders/basic.vs", "data/shaders/gui.fs");

	if (!qShader) return;

	qShader->enable();

	qShader->setUniform("u_color", Vector4(1, 1, 1, 1));
	qShader->setUniform("u_viewprojection", cam2d->viewprojection_matrix);
	if (texture != NULL) {
		qShader->setUniform("u_texture", texture, 0);
	}
	qShader->setUniform("u_time", Game::instance->time);
	qShader->setUniform("u_tex_tiling", 1.0f);
	qShader->setUniform("u_tex_range", Vector4(0, 0, 1, 1));
	qShader->setUniform("u_model", Matrix44());
	quad.render(GL_TRIANGLES);

	qShader->disable();
}