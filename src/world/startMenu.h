#pragma once

#include "asteroidsGame/AsteroidsGame.h"
class startMenu
{
public:
	static bool createCardsGame;;
	static void rendererLogo();
	static CardsGame* cardsGame;
	static FindGame* findGame;
	static BombsGame* bombsGame;
	static AsteroidsGame* asteroidsGame;
	static bool shouldDissableCursor;
	static bool running;
	static std::list<Body> bodies;
private:
};

