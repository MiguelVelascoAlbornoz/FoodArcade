#pragma once
#include "BombCap.h"
class Bomb
{
public:
	vec2 pos = vec2(0.0f);
	bool isSelected();
	~Bomb();
	void render(VAO* squareVao);
	void update();
    bool testCollisionWithSquare(Bomb *bomb, vec2 rectPos, vec2 rectSize);
    float livingTime = 0;
    bool selected = false;
	bool setBig = false;
	GIF gif = GIF(Textures::animations["cake"],0.1,true);
	vec2 velocity = vec2(100.0f,100.0f);
	float size = 1.4;
	bool inBox = false;
	bool exlodeAnimation = false;
	GIF* explosionGif;
	void isInBox(BombCap* bombCap);
};

