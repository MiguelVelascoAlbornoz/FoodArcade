#pragma once

#include "../findGame/FindGame.h"
class BombCap
{
public:
	vec2 pos;
	float size;
	Image* image;
	vec2 realSize;
	struct CollisionBox {
		vec2 rectSize;
		vec2 rectPos;
	};
	CollisionBox boxes[3];
	float borderSize;
	BombCap(float size,Image* text);
	void setPos(vec2 pos);
	void render(VAO* s);
};

