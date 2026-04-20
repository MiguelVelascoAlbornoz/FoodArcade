#pragma once
#include "Textures.h"

class GIF
{
public:
	GIF(Animation* animation, float timePerFrame, bool repeat);
	void use(GLenum textureUnit, Shader* shader, const char* name);
	float timePerFrame;
	bool repeat;
	float time = 0;
	int actualFrame = 0;
	Animation* animation;

};

