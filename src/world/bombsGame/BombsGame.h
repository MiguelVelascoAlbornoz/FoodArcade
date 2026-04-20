#pragma once

#include "Bomb.h"
class BombsGame
{
public:
	GIF* transportadora;
	bool canDestroy = false;
	void render();
	void renderGui();
	void updateBombs();
	VAO squareVao;
	int score = 0;
	bool countScore = false;
	bool bombSploding = false;
	Bomb* splodingBomb = nullptr;
	bool spawnUp = false;
	BombsGame();
	void renderBackground();
    void testCollisionWithSquare(Bomb *bomb, vec2 rectPos, vec2 rectSize);
    bool bombsCanMove = true;
    int bombsCount = 1;
	float gameTimer = 0;
	bool showEndGui = false;
	~BombsGame();
	BombCap* bombsCap[2];
	std::vector<Bomb*> bombs;
	float timeToSpawnBomb = 5;
	float sinceExplosionTime = 0;
	std::list<GIF> gifts;
	bool firstExplosion = false;
	bool secondExplosions = false;
	Bomb* selectedBomb = nullptr;
};

