#pragma once
#include "../bombsGame/BombsGame.h"
class Body
{
public:
	vec2 massCenter = vec2(0.0f);
	virtual void update(bool tp);
	virtual void draw(VAO* s);
	vec2 pos = vec2(0.0f);
	vector<vec2> vertices = {vec2(),vec2(),vec2(),vec2()};
	void calculateVertices();
	float rotation = 0;
	float angularVelocity = 0;
	vec2 velocity = vec2(0.0f);
	vec2 aceleration = vec2(0.0f);
	float size = 2;
	Image* texture;
	GIF gif = GIF(Textures::animations["rocket"],0.1,true);
	bool drawFire = false;
	float atrito = 1.0f;
};

