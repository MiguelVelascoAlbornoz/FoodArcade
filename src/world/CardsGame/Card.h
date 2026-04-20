#pragma once
#include "../../renderer/Camera.h"
class Card
{
public:
	bool isSelected();
	void draw(VAO* vao, bool& canSelect);

	vec2 pos;
	bool show = false;
	bool internalShow = false;
	bool isRotating = false;
	vec2 size;
	bool mustRotate = false;
	float timer = 200;

	int playerOwner = 0; //0 nobody; 
	Image* centerImage;
	float currentAngle = 0;
private:

};

