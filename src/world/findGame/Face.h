#pragma once

#include "PlusTimeGui.h"
class Face
{
public:
	vec2 pos;
	Image* texture;
	bool impostor = false;

	void draw(VAO* squareVao, bool bouncing,float faceSize);

	vec2 velocity;
	bool isSelected(float faceSize);
};

