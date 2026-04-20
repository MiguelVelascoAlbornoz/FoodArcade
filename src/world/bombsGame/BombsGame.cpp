#include "BombsGame.h"


BombsGame::BombsGame() {
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

	std::vector<int> attrib = { 2 };
	squareVao.initialize(vertices, 8, indices, 6, &attrib);
	bombsCap[0] = new BombCap(4,Textures::textures["bombsCapLeft"]);
	bombsCap[1] = new BombCap(4, Textures::textures["bombsCapRight"]);
	bombsCap[0]->setPos(vec2(-projectionSize.x / 2, -projectionSize.y / 4.0f - 10));
	bombsCap[1]->setPos(vec2(projectionSize.x / 2 - bombsCap[1]->realSize.x, -projectionSize.y / 4.0f - 10)); 
	bombsCap[0]->boxes[0] = {vec2(bombsCap[0]->realSize.x,bombsCap[0]->borderSize),bombsCap[0]->pos};
	bombsCap[0]->boxes[1] = {vec2(bombsCap[0]->realSize.x,bombsCap[0]->borderSize),bombsCap[0]->pos+vec2(0.0f,bombsCap[0]->realSize.y- bombsCap[0]->borderSize)};
	bombsCap[0]->boxes[2] = {vec2(bombsCap[0]->borderSize,bombsCap[0]->realSize.y-bombsCap[0]->borderSize*2),bombsCap[0]->pos + vec2(bombsCap[0]->realSize.x - bombsCap[0]->borderSize,bombsCap[0]->borderSize)};
	bombsCap[1]->boxes[0] = { vec2(bombsCap[1]->realSize.x,bombsCap[1]->borderSize),bombsCap[1]->pos };
	bombsCap[1]->boxes[1] = { vec2(bombsCap[1]->realSize.x,bombsCap[1]->borderSize),bombsCap[1]->pos + vec2(0.0f,bombsCap[1]->realSize.y - bombsCap[1]->borderSize) };
	bombsCap[1]->boxes[2] = { vec2(bombsCap[1]->borderSize,bombsCap[1]->realSize.y - bombsCap[1]->borderSize * 2),bombsCap[1]->pos + vec2(0.0f,bombsCap[1]->borderSize)};
	transportadora = new GIF(Textures::animations["transportadora"],0.2,true);
	
}

void BombsGame::renderBackground() {

	Shaders::shaders["bombs"]->uniform1i("sparkling", 0);
	Shaders::shaders["bombs"]->uniform1f("size", 4);
	Shaders::shaders["bombs"]->uniform1i("isBackground", 1);
	Shaders::shaders["bombs"]->uniform2f("dimensions", projectionSize.x, 300);
	Shaders::shaders["bombs"]->uniform2f("modelPos", -projectionSize.x / 2, 200);
	Shaders::shaders["bombs"]->uniform2f("textSize", Textures::textures["bricks"]->width, Textures::textures["bricks"]->height);
	Textures::textures["bricks"]->bindTexture(0, Shaders::shaders["bombs"], "text");
	squareVao.draw(GL_TRIANGLES);

	Shaders::shaders["bombs"]->bind();
	Shaders::shaders["bombs"]->uniform1f("size", 32);
	Shaders::shaders["bombs"]->uniform1i("isBackground", 1);
	Shaders::shaders["bombs"]->uniform2f("dimensions", projectionSize.x, projectionSize.y / 2 + 200);
	Shaders::shaders["bombs"]->uniform2f("modelPos", -projectionSize.x / 2, -projectionSize.y / 2);
	Shaders::shaders["bombs"]->uniform2f("textSize", Textures::textures["floor"]->width, Textures::textures["floor"]->height);
	Textures::textures["floor"]->bindTexture(0, Shaders::shaders["bombs"], "text");
	squareVao.draw(GL_TRIANGLES);

	Shaders::shaders["bombs"]->uniform1f("size", 4);
	Shaders::shaders["bombs"]->uniform1i("isBackground", 0);
	Shaders::shaders["bombs"]->uniform2f("modelPos", -15 * 4, 200);
	Shaders::shaders["bombs"]->uniform2f("textSize", Textures::textures["door"]->width, Textures::textures["door"]->height);
	Textures::textures["door"]->bindTexture(0, Shaders::shaders["bombs"], "text");
	squareVao.draw(GL_TRIANGLES);

	Shaders::shaders["bombs"]->uniform1f("size", 4);
	Shaders::shaders["bombs"]->uniform1i("isBackground", 0);
	Shaders::shaders["bombs"]->uniform2f("textSize", transportadora->animation->frames[0]->width, transportadora->animation->frames[0]->height);
	Shaders::shaders["bombs"]->uniform2f("modelPos", -8 * 4, -projectionSize.y / 2 - 85 * 4);
	transportadora->use(0, Shaders::shaders["bombs"], "text");
	squareVao.draw(GL_TRIANGLES);

	for (std::list<GIF>::iterator it = gifts.begin(); it != gifts.end(); /* no incrementes aqu� */) {
		(*it).use(0, Shaders::shaders["bombs"], "text");
		Shaders::shaders["bombs"]->uniform1f("size", 4);
		Shaders::shaders["bombs"]->uniform1i("isBackground", 0);
		Shaders::shaders["bombs"]->uniform2f("modelPos", 0, 0);
		Shaders::shaders["bombs"]->uniform2f("textSize", (*it).animation->frames[0]->width, (*it).animation->frames[0]->height);
		squareVao.draw(GL_TRIANGLES);
		if ((*it).actualFrame == -1) {
			// Erase devuelve un iterador v�lido al siguiente elemento
			it = gifts.erase(it);
		}
		else {
			// Incrementa el iterador solo si no se borra
			++it;
		}
	}


	bombsCap[0]->render(&squareVao);
	bombsCap[1]->render(&squareVao);
}
void BombsGame::testCollisionWithSquare(Bomb* bomb, vec2 rectPos, vec2 rectSize) {
	float bombWidth = bomb->gif.animation->frames[0]->width*bomb->size;
	float bombHeight = bomb->gif.animation->frames[0]->height*bomb->size;
	
	if (bomb->pos.x < rectPos.x + rectSize.x && bomb->pos.x + bombWidth > rectPos.x && bomb->pos.y < rectPos.y+rectSize.y && bomb->pos.y + bombHeight > rectPos.y) {
		
		float overlapX;
		float dstToRectRight = abs(bomb->pos.x - (rectPos.x + rectSize.x));
		float dstToRectLeft = abs(bomb->pos.x + bombWidth - rectPos.x);
		bool moveToLeft = false;
		bool moveToUp = false;
		if (dstToRectRight < dstToRectLeft) {
			overlapX = dstToRectRight;
		}
		else {
			overlapX = dstToRectLeft;
			moveToLeft = true;
		}
		float overlapY;
		float dstToRectUp = abs(bomb->pos.y - (rectPos.y + rectSize.y));
		float dstToRectDown = abs(bomb->pos.y + bombHeight - rectPos.y);
		if (dstToRectUp < dstToRectDown) {
			overlapY = dstToRectUp;
			moveToUp = true;
		}
		else {
			overlapY = dstToRectDown;
		}
		if (overlapX < overlapY) {
			// Colisi�n en el eje X (izquierda o derecha)
			bomb->velocity.x = -bomb->velocity.x; // Reflejar velocidad en X
			if (moveToLeft) {
				bomb->pos.x -= overlapX+1;
			}
			else {
				bomb->pos.x += overlapX + 1;
			}
		}
		else {
			// Colisi�n en el eje Y (arriba o abajo)
			bomb->velocity.y = -bomb->velocity.y; // Reflejar velocidad en Y
			if (moveToUp) {
				bomb->pos.y += overlapY + 1;
			} else {
				bomb->pos.y -= overlapY + 1;
			}
		}
	}
}
void BombsGame::render()
{
	if (ImGui::IsMouseReleased(0) && selectedBomb != nullptr) {
		selectedBomb->selected = false;
		selectedBomb = nullptr;
	}
	if (!bombSploding) {
		timeToSpawnBomb -= ellapsedTime;
	}
	else {
		sinceExplosionTime += ellapsedTime;
	}
	if (sinceExplosionTime > .7f && !firstExplosion) {
		firstExplosion = true;
		splodingBomb->exlodeAnimation = true;
		GIF* gif = new GIF(Textures::animations["explosion"],0.1,false);

		ma_sound_start(&Renderer::EXPLOSION);
		splodingBomb->explosionGif = gif;
 	}
	if (sinceExplosionTime > 2 && !secondExplosions) {
		secondExplosions = true;
		for (int i = 0; i < bombs.size(); ++i) {
			if (bombs[i] != splodingBomb && !bombs[i]->inBox) {
				bombs[i]->exlodeAnimation = true;
				ma_sound_start(&Renderer::EXPLOSION);

				GIF* gif = new GIF(Textures::animations["explosion"], 0.1, false);
				bombs[i]->explosionGif = gif;
			}
		}
		bombsCanMove = true;
	}
	if (sinceExplosionTime > 3 && !countScore) {
		countScore = true;
		for (int i = 0; i < bombs.size(); ++i) {
			if (!bombs[i]->exlodeAnimation) {
				score++;
			}
		}

		ma_sound_start(&Renderer::GAME_OVER_SOUND);
		showEndGui = true;
	}
	if (timeToSpawnBomb < 0) {
		bombsCount++;
		timeToSpawnBomb = timeToSpawnBomb = 5.0f / log2(2.0f + gameTimer);
		
		Bomb* bomb = new Bomb();
		std::uniform_int_distribution<> angleDistrib(45, 150);
		int angle = angleDistrib(g);
		if (spawnUp) {
			bomb->pos = vec2(-Textures::textures["cake"]->width*1.4/2, 150 );
			bomb->velocity = vec2(-cos(angle), -sin(angle))*150.0f;
			spawnUp = false;
		}
		else {
			bomb->pos = vec2(-Textures::textures["cake"]->width * 1.4 / 2, -projectionSize.y/2 +50);
			bomb->velocity = vec2(cos(angle), sin(angle)) * 150.0f;
			spawnUp = true;
		}
		std::uniform_int_distribution<> distrib(0, 1);
		if (distrib(g) == 0) {
			bomb->gif = GIF(Textures::animations["cake"],0.1,true);
		}
		else {
			bomb->gif = GIF(Textures::animations["blackCake"], 0.1, true);
		}
		ma_sound_start(&Renderer::CAKE_SPAWN);
			bombs.push_back(bomb);

		
		
		
	}
	Shaders::shaders["bombs"]->bind();
	Shaders::shaders["bombs"]->uniform1f("time", currentTime);
	renderBackground();
	updateBombs();
	Shaders::shaders["bombs"]->unBind();
	gameTimer += ellapsedTime;
	renderGui();

}
int guardarrRecord(int score) {
	const std::string archivoRecord = "assets/scores/highscoreCakes.txt";
	int highScore = 0;

	// Leer el r�cord anterior desde el archivo
	std::ifstream archivoEntrada(archivoRecord);
	if (archivoEntrada.is_open()) {
		archivoEntrada >> highScore;
		archivoEntrada.close();
	}

	// Comparar el puntaje actual con el r�cord anterior
	if (score > highScore) {
		// Guardar el nuevo r�cord
		std::ofstream archivoSalida(archivoRecord);
		if (archivoSalida.is_open()) {
			archivoSalida << score;
			archivoSalida.close();
		}
	}
	return highScore;
}
void BombsGame::renderGui() {
	if (showEndGui) {

		ImGui::SetNextWindowSize(ImVec2(windowSize.x * 0.4, windowSize.x * 0.25)); // 50% del tama�o de la ventana
		ImGui::SetNextWindowPos(ImVec2(windowSize.x * 0.30, windowSize.y * 0.25));
		ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(.2f, .2f, .2f, 1.0f));

		ImGui::Begin("Game_Ended", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoResize);
		ImGui::GetIO().FontGlobalScale = (0.3 / 960) * windowSize.x;

		int bestScore = guardarrRecord(score);

		ImGui::PushFont(Renderer::marioFont);


		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 0.0f, 0.0f, 1.0f));
		ImGui::Text("");
		ImGui::Text("");
		ImGui::Text("                         game over");
		ImGui::Text("");
		ImGui::PopStyleColor();
		ImGui::PopFont();
		ImGui::PushFont(Renderer::marioFontsmall);
		ImGui::Text(std::string("                              your score " + to_string(static_cast<int>(score))).data());
		ImGui::Text(std::string("                              high score " + to_string(static_cast<int>(bestScore))).data());

		ImGui::PopFont();
		ImGui::PushFont(Renderer::marioFont);
		ImGui::Text("");
		if (bestScore < score) {
			ImGui::Text(std::string("           new record ").data());
		}
		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 1.0f, 1.0f, 1.0f));
		ImGui::Text("                 "); ImGui::SameLine(); if (ImGui::Button("return to menu")) {
			canDestroy = true;
			ma_sound_start(&Renderer::MENU_SOUND);
			ma_sound_stop(&Renderer::GAME_OVER_SOUND);
		}
		ImGui::PopStyleColor();
		ImGui::PopFont();
		ImGui::End();
		ImGui::PopStyleColor();
	}
}
void BombsGame::updateBombs() {
	
	for (int i = 0; i < bombs.size(); ++i) {
		
		if (!bombs[i]->selected) {
			for (int j = 0; j < 2; ++j) {
				BombCap* bombCap = bombsCap[j];

				for (int k = 0; k < 3; ++k) {
					BombsGame::testCollisionWithSquare(bombs[i], bombCap->boxes[k].rectPos, bombCap->boxes[k].rectSize);
				}
			}
		}
		if (bombs[i]->gif.animation == Textures::animations["cake"]) {
			bombs[i]->isInBox(bombsCap[1]);
		}
		else {
			bombs[i]->isInBox(bombsCap[0]);
		}
		if (ImGui::IsMouseClicked(0) && bombs[i]->isSelected() && (!bombs[i]->inBox) && !bombSploding) {
			selectedBomb = bombs[i];
			bombs[i]->selected = true;
		}
		if (bombs[i]->livingTime > 10 && !bombSploding) {
			bombSploding = true;
			bombsCanMove = false;
			splodingBomb = bombs[i];
			splodingBomb->size *= 1.4;
			
		}
		if (bombsCanMove) {
			bombs[i]->update();
		}
		
		
		bombs[i]->render(&squareVao);

	}
	if (selectedBomb != nullptr) {
		selectedBomb->pos = projectedMousePos - (selectedBomb->size * vec2(selectedBomb->gif.animation->frames[0]->width, selectedBomb->gif.animation->frames[0]->height)) / 2.0f;
	}
}
BombsGame::~BombsGame() {
	for (int i = 0; i < bombs.size(); ++i) {
		delete bombs[i];
	}
	delete transportadora;
	delete bombsCap[0];
	delete bombsCap[1];
}
