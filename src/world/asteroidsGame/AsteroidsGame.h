#pragma once
#include "Bullet.h"
class AsteroidsGame

{
public:
	VAO squareVao;
	bool canDestroy = false;
	AsteroidsGame();
	void startLevel();
	void render();
	Player player;
	int level = 1;
	bool playerTouchTime = 0.0f;
	vec2 shootVelocity;
	std::list<Bullet> bullets;
	float lastShootTime = 0;
	bool showCursor = false;
	bool renderEndGui = false;
	bool loseLife = false;
	GIF heartBreakGif = GIF(Textures::animations["heart"],0.1,false);
	bool chooseGUI = false;
	void renderGUI();
	bool doingShoot = false;
	int shootsCount = 0;
	float lastBigShootTime = 0;
	int score = 0;
	int bulletsCount = 5;
	std::list<Body> asteroids;

};

