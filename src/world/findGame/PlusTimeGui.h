#pragma once
#include "../CardsGame/cardsGame.h"
class PlusTimeGui
{
public:
	void render();

	float existingTime = 0;
	int value;

	vec2 pos;
	vec2 posToMove;
};

