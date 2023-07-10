#include "gameHUD.h"
#include "entityPlayer.h"


gameHUD::gameHUD()
{
}

void gameHUD::initHUD()
{
	crosshair.texture = Texture::Get("data/textures/HUD/crosshair.tga");
	playerSpeed.texture = Texture::Get("data/textures/HUD/speed.tga");
	caddence.texture = Texture::Get("data/textures/HUD/caddence.tga");
	projectileSpeed.texture = Texture::Get("data/textures/HUD/projectile_speed.tga");
	attack.texture = Texture::Get("data/textures/HUD/attack.tga");
	healthBar.texture = Texture::Get("data/textures/HUD/health.tga");
	//minimapFrame.texture = Texture::Get("data/textures/HUD/healthFrame.tga");
	healthFrame.texture = Texture::Get("data/textures/HUD/healthFrame.tga");

	initHUDElements();
	elementsInitSize = Game::instance->window_width;
}

void gameHUD::initHUDElements()
{
	int wWidth = Game::instance->window_width;
	int wHeight = Game::instance->window_height;
	cam2d.view_matrix = Matrix44();
	cam2d.setOrthographic(0, wWidth, wHeight, 0, -1, 1);

	float hudScale = min(wWidth, wHeight) * hudScaleFactor;

	crosshair.mesh.createQuad(wWidth / 2, wHeight / 2, hudScale, hudScale, true);

	int x, y;
	x = 50;
	y = wHeight - 50;
	playerSpeed.mesh.createQuad(x, y, hudScale, hudScale, true);
	sprintf(playerSpeed.statValue.text, "%f", Game::instance->player->playerSpeed);
	playerSpeed.statValue.position = Vector2(x + hudScale + 5, y - hudScale / 3);

	y -= (10 + hudScale);
	caddence.mesh.createQuad(x, y, hudScale, hudScale, true);
	sprintf(caddence.statValue.text, "%f", Game::instance->player->caddence);
	caddence.statValue.position = Vector2(x + hudScale + 5, y - hudScale / 3);

	y -= (10 + hudScale);
	projectileSpeed.mesh.createQuad(x, y, hudScale, hudScale, true);
	sprintf(projectileSpeed.statValue.text, "%f", Game::instance->player->projectileSpeed);
	projectileSpeed.statValue.position = Vector2(x + hudScale + 5, y - hudScale / 3);

	y -= (10 + hudScale);
	attack.mesh.createQuad(x, y, hudScale, hudScale, true);
	sprintf(attack.statValue.text, "%f", Game::instance->player->attack);
	attack.statValue.position = Vector2(x + hudScale + 5, y - hudScale / 3);

	float healthBarMaxLength = hudScale / 10.0f * Game::instance->player->maxHealth;
	float healthBarLength = hudScale / 10.0f * Game::instance->player->health;
	healthBar.mesh.createQuad(50 + healthBarLength / 2, 50, healthBarLength, hudScale / 5.0f, true);

	healthFrame.mesh.createQuad(50 + healthBarMaxLength / 2, 50, healthBarMaxLength, hudScale / 5.0f, true);
}

void gameHUD::updateHUDElements()
{
}

void gameHUD::render()
{
	if (elementsInitSize != Game::instance->window_height) { //resize window
		elementsInitSize = Game::instance->window_height;
		initHUDElements();
	}
	int wWidth = Game::instance->window_width;
	int wHeight = Game::instance->window_height;
	float hudScale = min(wWidth, wHeight) * hudScaleFactor;
	EntityPlayer* player = Game::instance->player;

	SDL_Window* window = Game::instance->window;

	// Set the flags
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	cam2d.enable();

	//Render hud
	renderQuad(crosshair.mesh, crosshair.texture);
	renderQuad(attack.mesh, attack.texture);
	renderQuad(caddence.mesh, caddence.texture);
	renderQuad(playerSpeed.mesh, playerSpeed.texture);
	renderQuad(projectileSpeed.mesh, projectileSpeed.texture);
	renderQuad(healthBar.mesh, healthBar.texture);
	renderQuad(healthFrame.mesh, healthFrame.texture);
	drawText(attack.statValue.position.x, attack.statValue.position.y, attack.statValue.text, Vector3(1, 1, 1), hudScale / 20.0f);
	drawText(caddence.statValue.position.x, caddence.statValue.position.y, caddence.statValue.text, Vector3(1, 1, 1), hudScale / 20.0f);
	drawText(playerSpeed.statValue.position.x, playerSpeed.statValue.position.y, playerSpeed.statValue.text, Vector3(1, 1, 1), hudScale / 20.0f);
	drawText(projectileSpeed.statValue.position.x, projectileSpeed.statValue.position.y, projectileSpeed.statValue.text, Vector3(1, 1, 1), hudScale / 20.0f);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glDisable(GL_BLEND);
}

void gameHUD::renderQuad(Mesh quad, Texture* texture)
{
	Shader* qShader = Shader::Get("data/shaders/basic.vs", "data/shaders/gui.fs");

	if (!qShader) return;

	qShader->enable();

	qShader->setUniform("u_color", Vector4(1, 1, 1, 1));
	qShader->setUniform("u_viewprojection", cam2d.viewprojection_matrix);
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