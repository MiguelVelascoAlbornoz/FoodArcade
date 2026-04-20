#pragma once
#include "Card.h"
class CardsGame
{
public:
	  CardsGame();
	  ~CardsGame();
	 void render();
	 void renderGui();
	 VAO cardvao;
	 int currentPlayer = 1;
	 int cardsCount; 
	 int triesCount = 0;
	 Card* lastCard;
	 int cardsInRotation = 0;
	 bool canSelect = true;
	 std::vector<Card> cards;
	 std::vector<Card> player1Cards;
	 float cardsWidth;
	 float cardsHeight;
	 bool canDestroy = false;
	 std::vector<Card> player2Cards;
private:

};

