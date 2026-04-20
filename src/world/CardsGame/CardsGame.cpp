#include "CardsGame.h"





 CardsGame::CardsGame() {
	float vertices[] = {
		1,1,
		0,1,
		0,0,
		1,0
	};
	int indices[] = {
		0,1,2,
		0,3,2
	};
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	 cardsCount = 4;
	 cardsHeight = projectionSize.y / cardsCount;
	 cardsWidth = cardsHeight/1.5;
	std::vector<int> attrib = {2};
	cardvao.initialize(vertices,8,indices,6,&attrib);

	Shaders::shaders["cards"]->bind();
	Textures::textures["card_top"]->bindTexture(0, Shaders::shaders["cards"], "card_top");
	Textures::textures["card_back"]->bindTexture(1, Shaders::shaders["cards"], "card_back");
	Textures::textures["poker_background"]->bindTexture(3, Shaders::shaders["cards"],"background");
	Shaders::shaders["cards"]->uniform1i("cardWidth", cardsWidth);
	Shaders::shaders["cards"]->unBind();

	std::vector<string> types = {"green_lemon","lemon","mango","strawberry","blueberries","cherry","watermelon","grapes",
		                         "green_lemon","lemon","mango","strawberry","blueberries","cherry","watermelon","grapes"};
	std::random_device rd;  // Semilla aleatoria del sistema
	std::mt19937 g(rd());   // Generador de n�meros aleatorios basado en Mersenne Twister

	// Mezclar el vector
	std::shuffle(types.begin(), types.end(), g);
	for (int i = 0; i < cardsCount; ++i) {
		for (int j = 0; j < cardsCount; ++j) {
			Card card;
			card.pos.x = i * cardsWidth - (cardsCount * cardsWidth) / 2;
			card.pos.y = j * cardsHeight - projectionSize.y / 2;
			card.size = vec2(cardsWidth, cardsHeight);
			card.centerImage = Textures::textures[types[i*cardsCount+j]];
			cards.push_back(card);
		}
	}
}
 CardsGame::~CardsGame() {
	
}
void CardsGame::render() {
	//renderer->background(.0f, .6f, 0.0f);//ponemos y limpiamos background

	Shaders::shaders["cards"]->bind();
	Shaders::shaders["cards"]->uniform1i("isBackground", 1);

	cardvao.draw(GL_TRIANGLES);
	Shaders::shaders["cards"]->uniform1i("isBackground", 0);
	Shaders::shaders["cards"]->uniform1i("cardWidth", cardsWidth*1.05);
	for (int i = 0; i < cards.size(); ++i) {
		if (cards[i].isSelected() && cards[i].playerOwner == 0 && !cards[i].isRotating && &cards[i] != lastCard && !cards[i].mustRotate && canSelect) {

			ma_sound_start(&Renderer::CARD_FLIP);
			cards[i].isRotating = true;//la carta rota
			if (triesCount == 0) {
				lastCard = &cards[i];
				triesCount++;
			} else
			if (triesCount == 1) {
				if (lastCard->centerImage == cards[i].centerImage) {
					triesCount = 0;
					cards[i].playerOwner = currentPlayer;   //el jugador gana las cartas
					lastCard->playerOwner = currentPlayer;
					 ma_sound_start(&Renderer::CARDS_GAIN);
					if (currentPlayer == 1) {
						Card card1 = cards[i];
						Card card2 = (*lastCard);
						card1.pos.x = 244;
						card2.pos.x = 244;
						card1.pos.y = 120 - (static_cast<float>(player1Cards.size()) * 25);
						
						player1Cards.push_back(card1);
						card2.pos.y = 120 - (static_cast<float>(player1Cards.size()) * 25);
						player1Cards.push_back(card2);

					}
					else {
						Card card1 = cards[i];
						Card card2 = (*lastCard);
						card1.pos = vec2(387, 120 - (static_cast<float>(player2Cards.size()) * 25));;
					
				
						
						player2Cards.push_back(card1);
						card2.pos= vec2(387, 120 - (static_cast<float>(player2Cards.size()) *25));
						player2Cards.push_back(card2);
					}
					lastCard = nullptr;
					
				}
				else {
					triesCount = 0;
					cards[i].mustRotate = true;
					lastCard->mustRotate = true;
					canSelect = false;
					lastCard = nullptr;
					currentPlayer = currentPlayer == 1 ? 2 : 1;
				}
			}
			
			
		}
		cards[i].draw(&cardvao, canSelect);
	}


	renderGui();
	if (player1Cards.size() + player2Cards.size() == cards.size()) {


		ImGui::SetNextWindowSize(ImVec2(windowSize.x * 0.4, windowSize.x * 0.25)); // 50% del tama�o de la ventana
		ImGui::SetNextWindowPos(ImVec2(windowSize.x * 0.30, windowSize.y * 0.25));
		ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(.2f, .2f, .2f, 1.0f) );

		ImGui::Begin("Game_Ended", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoResize);
		ImGui::GetIO().FontGlobalScale = (0.3 / 960) * windowSize.x;
	


		ImGui::PushFont(Renderer::marioFont);
		vec3 color;
		std::string text;
		if (player1Cards.size() > player2Cards.size()) {
			color = vec3(.0f, .0f,1.0f);
			text = "                    player 1 wins";
		}
		else if (player1Cards.size() < player2Cards.size()) {
			color = vec3(1.0f, .0f, .0f);
			text = "                    player 2 wins";
		} 
		else {
			color = vec3(1.0f, 1.0f, 1.0f);
			text = "                                  tie";
		}
		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(color.x,color.y,color.z,1.0f));
		ImGui::Text("");
		ImGui::Text("");
		ImGui::Text(text.data());
		ImGui::Text("");
		ImGui::PopStyleColor();
		ImGui::PopFont();
		ImGui::PushFont(Renderer::marioFontsmall);
		ImGui::Text(std::string("                 player 1 score " +to_string( static_cast<int>(player1Cards.size()))).data());
		ImGui::Text(std::string("                 player 2 score " + to_string(static_cast<int>(player2Cards.size()))).data());
		ImGui::PopFont();
		ImGui::PushFont(Renderer::marioFont);
		ImGui::Text("");

		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 1.0f, 1.0f, 1.0f));
		ImGui::Text("                 "); ImGui::SameLine(); if (ImGui::Button("return to menu")) {
			ma_sound_start(&Renderer::MENU_SOUND);
			ma_sound_stop(&Renderer::GAME_OVER_SOUND);
			canDestroy = true;
		}
		ImGui::PopStyleColor();
		ImGui::PopFont();
		ImGui::End();
		ImGui::PopStyleColor();
		
	}
}
void CardsGame::renderGui() {

	Shaders::shaders["cards"]->uniform1i("cardWidth", cardsWidth*0.45);

	for (int i = 0; i < player1Cards.size(); ++i) {

	player1Cards[i].draw(&cardvao, canSelect);
	}
	for (int i = 0; i < player2Cards.size(); ++i) {

		player2Cards[i].draw(&cardvao, canSelect);
	}
	Shaders::shaders["cards"]->unBind();
	ImGui::SetNextWindowSize(ImVec2(windowSize.x * 0.29, windowSize.x * 0.03)); // 50% del tama�o de la ventana
	ImGui::SetNextWindowPos(ImVec2(windowSize.x * 0.014, windowSize.y * 0.45));
	ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(1.0f, 1.0f, 1.f, .8f));
	ImGui::Begin("Texto", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoResize);
	ImGui::GetIO().FontGlobalScale = (0.3 / 960) * windowSize.x;



	ImGui::PushFont(Renderer::marioFont);
	
	if (currentPlayer == 1) {
		
		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.0f, 0.0f, 1.0f, 1.0f));
		ImGui::Text("player 1 is selecting");
	}
	else {

		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 0.0f, 0.0f, 1.0f));
		ImGui::Text("player 2 is selecting");
	}

	ImGui::PopStyleColor();
	ImGui::PopFont();
	ImGui::End();

	ImGui::SetNextWindowSize(ImVec2(windowSize.x * 0.05, windowSize.x * 0.03)); // 50% del tama�o de la ventana
	ImGui::SetNextWindowPos(ImVec2(windowSize.x * 0.75, windowSize.y * 0.1));

	ImGui::Begin("p1", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoResize);
	ImGui::GetIO().FontGlobalScale = (0.3 / 960) * windowSize.x;



	ImGui::PushFont(Renderer::marioFont);

		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.0f, 0.0f, 1.0f, 1.0f));
		ImGui::Text("p1: ");

	

	ImGui::PopStyleColor();
	ImGui::PopFont();
	ImGui::End();

	ImGui::SetNextWindowSize(ImVec2(windowSize.x * 0.05, windowSize.x * 0.03)); 
	ImGui::SetNextWindowPos(ImVec2(windowSize.x * 0.9, windowSize.y * 0.1));

	ImGui::Begin("p2", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoResize);
	ImGui::GetIO().FontGlobalScale = (0.3 / 960) * windowSize.x;



	ImGui::PushFont(Renderer::marioFont);

	ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 0.0f, .0f, 1.0f));
	ImGui::Text("p2: ");



	ImGui::PopStyleColor();
	ImGui::PopFont();
	ImGui::End();
	ImGui::PopStyleColor();
}