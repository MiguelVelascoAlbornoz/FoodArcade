#include "Textures.h"


std::unordered_map<std::string, Image*> Textures::textures;
std::unordered_map<std::string, Animation*> Textures::animations;


 void Textures::initializeTextures()
 {
	 textures["bombsGame_icon"] = new Image("bombsGame_icon.png");
	 textures["card_back"] = new Image("card_back.png");
	 textures["card_top"] = new Image("card_top.png");
	 textures["card_top_player2"] = new Image("card_top_player2.png");
	 textures["card_top_player1"] = new Image("card_top_player1.png");
	 textures["poker_background"] = new Image("poker_background.png");
	 textures["pear"] = new Image("pear.png");
	 textures["strawberry"] = new Image("strawberry.png");
	 textures["watermelon"] = new Image("watermelon.png");
	 textures["apple"] = new Image("apple.png");
	 textures["orange"] = new Image("orange.png");
	 textures["cherry"] = new Image("cherry.png");
	 textures["blueberries"] = new Image("blueberries.png");
	 textures["grapes"] = new Image("grapes.png");
	 textures["granade"] = new Image("granade.png");
	 textures["milk"] = new Image("milk.png");
	 textures["orange"] = new Image("orange.png");
	 textures["lemon"] = new Image("lemon.png");
	 textures["green_lemon"] = new Image("green_lemon.png");
	 textures["mango"] = new Image("mango.png");
	 textures["coke"] = new Image("coke.png");
	 textures["banana"] = new Image("banana.png");
	 textures["cranberries"] = new Image("cranberries.png");
	 textures["honey"] = new Image("granade.png");
	 textures["fish"] = new Image("fish.png");
	 textures["stars_background"] = new Image("stars_background.png",GL_REPEAT);
	 textures["board"] = new Image("board.png");
	 textures["cardsGame_icon"] = new Image("cardsGame_icon.png");
	 textures["wanted"] = new Image("wanted.png");
	 textures["hot_dog"] = new Image("hot_dog.png");
	 textures["pizza"] = new Image("pizza.png");
	 textures["french_potatos"] = new Image("french_potatos.png");
	 textures["burger"] = new Image("burger.png");
	 textures["yellow"] = new Image("yellow.png");

	 textures["findGame_icon"] = new Image("findGame_icon.png");
	 textures["bricks"] = new Image("bricks.png",GL_REPEAT);
	 textures["door"] = new Image("door.png");
	 textures["floor"] = new Image("floor.png",GL_REPEAT);
	 textures["transportadora"] = new Image("transportadora.png");
	 textures["bombsCapLeft"] = new Image("bombsCapLeft.png");
	 textures["bombsCapRight"] = new Image("bombsCapRight.png");

	 animations["explosion"] = new Animation("explosion",7);
	 animations["transportadora"] = new Animation("transportadora", 4);
	 animations["cake"] = new Animation("cake", 5);
	 animations["blackCake"] = new Animation("blackCake", 5);
	 animations["rocket"] = new Animation("rocket", 6);
	 animations["heart"] = new Animation("heart", 8);
	 textures["pan"] = new Image("pan.png");
	 textures["cheese"] = new Image("cheese.png");
	 textures["egg"] = new Image("egg.png");
	 textures["steak"] = new Image("steak.png");

	 textures["fried_chicken"] = new Image("fried_chicken.png");
	 textures["cake"] = new Image("cake.png");
	 textures["heart"] = new Image("heart.png");
	 textures["asteroids_icon"] = new Image("asteroids_icon.png");
	/* for (int i = 1; i <= 120; ++i) {
	* 
		 std::string path = "water/0";
		 if (i < 10) {
			 path = path + "00";

		 } else
		 if (i < 100) {
			 path = path + "0";
		 }
		 
		 path = path + to_string(i)+".png";
		
		 water->push_back(new Image(path));

	 }*/
 }


 void Textures::cleanUpTextures()
 {
	 for (auto& texturePair : textures) {
		 delete texturePair.second;  // Eliminar cada shader
	 }
	 for (auto& texturePair : animations) {
		 delete texturePair.second;  // Eliminar cada shader
	 }
	 textures.clear();  // Limpiar el mapa
	 animations.clear();

 }
