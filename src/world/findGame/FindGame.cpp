#include "FindGame.h"

FindGame::FindGame() {
	canDestroy = false;
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
	gameCanvasSize = vec2(projectionSize.x-253*1.7,projectionSize.y);
	
	selectImpostor();
	Shaders::shaders["find"]->bind();
	Shaders::shaders["find"]->uniform2f("projectionSize",projectionSize.x,projectionSize.y);
	float circleRadius = 110;//265
	lightCircles[0] = { vec2(projectionSize.x / 2 - 253 * 1.7 - circleRadius - 1,-110),circleRadius,true,{vec2(265, -110),vec2(projectionSize.x / 2 + circleRadius + 1,-110)},circleRadius };
	lightCircles[1] = { vec2(projectionSize.x / 2 + circleRadius + 1,-110),circleRadius,true,{vec2(265, -110),vec2(projectionSize.x / 2 - 253 * 1.7 - circleRadius - 1,-110)},circleRadius };
	 lightCircles[0].speed = 500;
	 lightCircles[1].speed = 500;
	setCircles();
	Shaders::shaders["find"]->unBind();
}
FindGame::~FindGame()
{
}
void FindGame::moveCircles() {
	for (int i = 0; i < 2; ++i) {
		if ( lightCircles[i].movePos.size() >= 1) {
			vec2 dir = normalize(lightCircles[i].movePos[lightCircles[i].movePos.size()-1] - lightCircles[i].pos);
			lightCircles[i].pos += dir * float(lightCircles[i].speed * ellapsedTime);
			setCircles();
			if (length(lightCircles[i].movePos[lightCircles[i].movePos.size()-1] - lightCircles[i].pos) < 10) {
				lightCircles[i].movePos.pop_back();
			    
			}
		}
		if (lightCircles[i].shouldIncrease) {
			lightCircles[i].radius += ellapsedTime*110;
			if (lightCircles[i].radius > 275) {
				lightCircles[i].shouldIncrease = false;
				setYellow = true;
			}
			setCircles();
		}
		
	}
}

void FindGame::startLevel() {

	if (lightCircles[0].movePos.size() == 0 && lightCircles[1].movePos.size() == 0 && !levelRunning) {
		iconsSize = (2.5 + 2.5 * 5) / (level + 5);
		std::cout << iconsSize << std::endl;;
		renderLevel = false;
		timeCounting = true;
		renderTime = true;
		if (level == 1 || level == 2 || level == 3) {
			              
			generateQuadLevel();
			//everyoneInEachDirection(0.25);
			//everyoneInEachDirectionBouncing(0.25);
		}
		else if (level == 4 || level == 5){
			generateNoiseLevel(0.25);
			



		
		}
		else {
			std::uniform_int_distribution<> distrib(0, 100);
			int p = distrib(g);
			if (p <= 20) {
				generateQuadLevel();
				
			}
			else if (p > 20 && p <= 40) {
				everyoneInEachDirection(0.5);
			}
			else if (p > 40 && p <= 60) {
				generateNoiseLevel(0.5);
			}
			else if (p > 60 && p <= 80) {
				generateQuadsMoveVertical(1);
			}
			else if (p > 80 && p <= 100) {
				everyoneInEachDirectionBouncing(0.5);
			}
		}
		levelRunning = true;
	}
}
void FindGame::passLevel() {
	faces.clear();
	impostorFace->velocity = vec2(0.0f);
	faces.push_back(*impostorFace);
	bouncing = false;
	lightCircles[0].shouldIncrease = true;
	lightCircles[1].shouldIncrease = true;
	

	

	if (round(time) <= 0) {
		countGameEnd = true;
		gameEndTimer = 0;
	}
	else {
		interfaceTime = 0;
		PlusTimeGui gui;
		gui.pos = impostorFace->pos;
		gui.value = 5;
		plusTimeGuis.push_back(gui);
		inInterface = true;
		timeCounting = false;
		level++;
		canSumTime = true;
	}
	
	

}
void FindGame::selectImpostor() {
	std::uniform_int_distribution<> distrib(0, 3);
	
	int impostorNr = distrib(g);
	switch (impostorNr) {
	case 0:
		possibleIcons = { Textures::textures["hot_dog"],Textures::textures["pizza"] ,Textures::textures["burger"] };
		this->impostor = Textures::textures["french_potatos"];
		break;
	case 1:
		possibleIcons = { Textures::textures["pizza"] ,Textures::textures["burger"],Textures::textures["french_potatos"] };
		this->impostor = Textures::textures["hot_dog"];
		break;
	case 2:
		possibleIcons = { Textures::textures["burger"],Textures::textures["french_potatos"] ,Textures::textures["hot_dog"] };
		this->impostor = Textures::textures["pizza"];
		break;
	case 3:
		possibleIcons = { Textures::textures["pizza"],Textures::textures["french_potatos"] ,Textures::textures["hot_dog"] };
		this->impostor = Textures::textures["burger"];
		break;
	}
}
void::FindGame::gen() {

}
void FindGame::generateQuadLevel() {

	int facesCount = (int)((gameCanvasSize.x / (32.0 * iconsSize)) * (gameCanvasSize.y / (32.0 * iconsSize)));
	int a;
	std::uniform_int_distribution<> distrib(0, 2);
	faces.clear();
	faces.reserve((size_t)(facesCount*1.5));
	printf("Quad level ");
	printf("x:%f, y:%f, facesCount:%d\n", gameCanvasSize.x, gameCanvasSize.y, facesCount);
	for (int i = (int)(-projectionSize.x / 2.0); i < (int)(projectionSize.x / 2.0 - 253.0 * 1.7 - 16.0 * iconsSize); i += (int)(32.0 * iconsSize)) {
		for (int j = (int)(-projectionSize.y / 2.0); j < (int)(projectionSize.y / 2.0 - 16.0 * iconsSize); j += (int)(32.0 * iconsSize)) {
			Face face;

			int nr = distrib(g);

			face.pos.x = (float)i;
			face.pos.y = (float)j;
			face.texture = possibleIcons[nr];
			faces.push_back(face);
		}
	}
	printf("Faces generated:%d\n", (int)faces.size());
	std::uniform_int_distribution<> distribb(0, (int)faces.size() - 1);

	int nr = distribb(g);

	faces[nr].impostor = true;
	faces[nr].texture = impostor;
	impostorIndex = nr;
	impostorFace = &faces[impostorIndex];
}
void FindGame::generateNoiseLevel(float facesFactor) {
	int facesCount = (int)(((gameCanvasSize.x / (32.0 * iconsSize)) * (gameCanvasSize.y / (32.0 * iconsSize))) * facesFactor);
	int disX = (int)(projectionSize.x - 253.0 * 1.7 - 16.0 * iconsSize);
	int disY = (int)(projectionSize.y - 16.0 * iconsSize);
	std::uniform_int_distribution<> distribX((int)(-projectionSize.x / 2.0), (int)(projectionSize.x / 2.0 - 253.0 * 1.7 - 16.0 * iconsSize));
	std::uniform_int_distribution<> distribY((int)(-projectionSize.y / 2.0), (int)(projectionSize.y / 2.0 - 16.0 * iconsSize));
	std::uniform_int_distribution<> distrib(0, 2);
		faces.reserve((size_t)(facesCount*1.1));
	printf("Noise level, facesCount:%d, disX:%d-%d, disY:%d-%d\n", facesCount, distribX.a(), distribX.b(), distribY.a(), distribY.b());
	for (int i = 0; i < facesCount; ++i) {
			Face face;
			

			int nr = distrib(g);

			face.pos.x = (float)distribX(g);
			face.pos.y = (float)distribY(g);
			face.texture = possibleIcons[nr];
			faces.push_back(face);
		}
	
	int nr = (int)faces.size() - 1;
	faces[nr].impostor = true;
faces[nr].texture = impostor;
impostorIndex = nr;
impostorFace = &faces[impostorIndex];
}
void FindGame::everyoneInEachDirectionBouncing(float facesFactor) {
	bouncing = true;
	
	int facesCount = (gameCanvasSize.x / (32 * iconsSize)) * (gameCanvasSize.y / (32 * iconsSize)) * facesFactor;
	std::uniform_int_distribution<> distribX(-projectionSize.x / 2, projectionSize.x / 2 - 253 * 1.7 - 32 * iconsSize);
	std::uniform_int_distribution<> distribY(-projectionSize.y / 2, projectionSize.y / 2 - 32 * iconsSize);
	std::uniform_int_distribution<> distrib(0, 2);
	std::uniform_int_distribution<> direccionDisttrib(-1000, 1000);
	printf("Everyone in each direction bouncing level\n");
	for (int i = 0; i < facesCount; ++i) {
		Face face;
		

		int nr = distrib(g);

		face.pos.x = distribX(g);
		face.pos.y = distribY(g);
		face.texture = possibleIcons[nr];
		vec2 direction = vec2(direccionDisttrib(g), direccionDisttrib(g));
		direction = normalize(direction)*50.0f;
		face.velocity = direction;
		faces.push_back(face);
	}
	int nr = (int)faces.size()-1;
	faces[nr].impostor = true;
faces[nr].texture = impostor;
impostorIndex = nr;
impostorFace = &faces[impostorIndex];

}
void FindGame::everyoneInEachDirection(float facesFactor) {
	int facesCount = (gameCanvasSize.x / (32 * iconsSize)) * (gameCanvasSize.y / (32 * iconsSize)) * facesFactor;
	std::uniform_int_distribution<> distribX(-projectionSize.x / 2, projectionSize.x / 2 - 253 * 1.7 - 16 * iconsSize);
	std::uniform_int_distribution<> distribY(-projectionSize.y / 2, projectionSize.y / 2 - 16 * iconsSize);
	std::uniform_int_distribution<> distrib(0, 2);
	std::uniform_int_distribution<> direccionDisttrib(-1000, 1000);
	std::vector<vec2> directions;
	printf("Everyone in each direction level\n");
	for (int i = 0; i < 4; ++i) {
		vec2 direction = vec2(direccionDisttrib(g), direccionDisttrib(g));
		direction = normalize(direction);
		directions.push_back(direction);
	}
	for (int i = 0; i < facesCount; ++i) {
		Face face;


		int nr = distrib(g);

		face.pos.x = distribX(g);
		face.pos.y = distribY(g);
		face.texture = possibleIcons[nr];
		face.velocity = directions[nr] * 50.0f;
		faces.push_back(face);
	}
	int nr = (int)faces.size() - 1;
	faces[nr].impostor = true;
	faces[nr].texture = impostor;
	faces[nr].velocity = directions[3]*50.0f;
	impostorIndex = nr;
	impostorFace = &faces[impostorIndex];



}
void FindGame::generateQuadsMoveVertical(float v) {
	int facesCount = (gameCanvasSize.x / (32 * iconsSize)) * (gameCanvasSize.y / (32 * iconsSize));
	int a;
	printf("Quads move vertical level\n");
	std::uniform_int_distribution<> d(0, 1);
	std::uniform_int_distribution<> distrib(0, 2);
	for (int i = -projectionSize.x / 2; i < projectionSize.x / 2 - 253 * 1.7 -16*iconsSize; i += 32 * iconsSize) {
		

		int movingDir = d(g);
		vec2 velocity;
		if (movingDir == 0) {
			velocity = vec2(0, 50)*v;
		}
		else {
			velocity = vec2(0, -50)*v;
		}
		for (int j = -projectionSize.y / 2; j < projectionSize.y / 2; j += 32 * iconsSize) {
			Face face;
			

			int nr = distrib(g);
			face.velocity = velocity;
			face.pos.x = i;
			face.pos.y = j;
			face.texture = possibleIcons[nr];
			faces.push_back(face);
		}
	}
	std::uniform_int_distribution<> distribb(0, (int)faces.size() - 1);

	int nr = distribb(g);


	Face* randomFace = (&faces[nr]);
	randomFace->impostor = true;
	randomFace->texture = impostor;

	impostorFace = randomFace;
}
void FindGame::gameEnd() {
	faces.clear();
	if (!renderEndGui) {
		ma_sound_start(&Renderer::GAME_OVER_SOUND);
	}
	renderEndGui = true;

}
void FindGame::render()
{
	if (countGameEnd) {
		gameEndTimer += ellapsedTime;
	}

	if (gameEndTimer > 3) {
		gameEnd();
	}
	if (round(time) <= 0 && !countGameEnd) {
		passLevel();
	}
	if (timeCounting) {
		lastSecond = time;
		time -= ellapsedTime;
	}
	if (floor(lastSecond) != floor(time) && floor(time) < floor(lastSecond) && time > 0) {
		ma_sound_start(&Renderer::TIMER);
	}
	if (inInterface ) {
		interfaceTime += ellapsedTime;
	}
	if (interfaceTime > 2 && canSumTime) {

		neededTime = time + 5;
		canSumTime = false;
		sumTimeTimer = 0;
	}
	if (time   < neededTime && sumTimeTimer > 0.08) {
		if (time > 0) {
			ma_sound_stop(&Renderer::GAIN_TIME);
			ma_sound_start(&Renderer::GAIN_TIME);
		}
		
		time+=1;
		sumTimeTimer = 0;
	
	}
	else {
		sumTimeTimer += ellapsedTime;
	}
	
	
	if (interfaceTime > 4.5) {
		inInterface = false;
		interfaceTime = 0;
		setYellow = false;
		renderLevel = true;
		renderTime = false;
		levelRunning = false;
		int circleRadius = 110;
		Light light0 = { vec2(projectionSize.x / 2 - 253 * 1.7 - circleRadius - 1,-110),(float)circleRadius,true,{vec2(265, -110)},(float)circleRadius };
		Light light1 = { vec2(projectionSize.x / 2 + circleRadius + 1,-110),(float)circleRadius,true,{vec2(265, -110)},(float)circleRadius };
		light0.speed = 500;
		light1.speed = 500;
		lightCircles[0] = light0;
		lightCircles[1] = light1;
		selectImpostor();
		neededTime = 0;
		faces.clear();
	}
	startLevel();
	Shaders::shaders["find"]->bind();

	moveCircles();
	if (setYellow) {
		Shaders::shaders["find"]->uniform1f("size", 5000);
		Shaders::shaders["find"]->uniform2f("modelPos", -projectionSize.x / 2, -projectionSize.y / 2);
		Textures::textures["yellow"]->bindTexture(0, Shaders::shaders["find"], "text");
		Shaders::shaders["find"]->uniform1i("isWanted", 0);
		Shaders::shaders["find"]->uniform2f("textSize", Textures::textures["yellow"]->width, Textures::textures["yellow"]->height);
		squareVao.draw(GL_TRIANGLES);
	}
	Shaders::shaders["find"]->uniform1f("size",1.7);
	Shaders::shaders["find"]->uniform2f("modelPos", projectionSize.x/2-253*1.7, -projectionSize.y/2);
	Shaders::shaders["find"]->uniform1i("isWanted", 1);
	Shaders::shaders["find"]->uniform2f("textSize", Textures::textures["wanted"]->width, Textures::textures["wanted"]->height);
	Textures::textures["wanted"]->bindTexture(0, Shaders::shaders["find"], "text");
	squareVao.draw(GL_TRIANGLES);
	impostor->bindTexture(0, Shaders::shaders["find"], "text");
	Shaders::shaders["find"]->uniform1f("size", 3.1);
	Shaders::shaders["find"]->uniform2f("modelPos",215,-140);
	Shaders::shaders["find"]->uniform2f("textSize", impostor->width, impostor->height);
	squareVao.draw(GL_TRIANGLES);
	alreadyInteracted = false;
	bool negativeInteracted = false;
	vec2 interactedPos;
	for (int i = 0; i < faces.size(); ++i) {
		faces[i].draw(&squareVao,bouncing,iconsSize);
		if (faces[i].isSelected(iconsSize)) {
			
			if (faces[i].impostor && !inInterface) {
				passLevel();
				alreadyInteracted = true;
				ma_sound_start(&Renderer::CORRECT_ANSWER);
			}
			else if (!inInterface){
				negativeInteracted = true;
				interactedPos = faces[i].pos;
				ma_sound_start(&Renderer::INVALID_ANSWER);

			}
		
		}
	}
	if (negativeInteracted && !alreadyInteracted) {
		time -= 10;
		PlusTimeGui gui;
		gui.pos = interactedPos;
		gui.value = -10;
		alreadyInteracted = true;

		plusTimeGuis.push_back(gui);
	}
	
	renderGui();
	Shaders::shaders["find"]->unBind();

}
int guardarRecord(int score) {
	const std::string archivoRecord = "assets/scores/highscore.txt";
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

void FindGame::setCircles()
{
	for (int i = 0; i < 2; ++i) {
		std::string baseName = "lightCircles["+to_string(i) + "]";
		Shaders::shaders["find"]->uniform2f((baseName + ".position").c_str(),lightCircles[i].pos.x, lightCircles[i].pos.y);
		Shaders::shaders["find"]->uniform1f((baseName + ".radius").c_str(), lightCircles[i].radius);
	}
}
void FindGame::renderGui() {
	
	for (std::list<PlusTimeGui>::iterator it = plusTimeGuis.begin(); it != plusTimeGuis.end(); /* no incrementes aqu� */) {
		(*it).render();
		if ((*it).existingTime > 2) {
			// Erase devuelve un iterador v�lido al siguiente elemento
			it = plusTimeGuis.erase(it);
		}
		else {
			// Incrementa el iterador solo si no se borra
			++it;
		}
	}
	if (renderEndGui) {

		ImGui::SetNextWindowSize(ImVec2(windowSize.x * 0.4, windowSize.x * 0.25)); // 50% del tama�o de la ventana
		ImGui::SetNextWindowPos(ImVec2(windowSize.x * 0.30, windowSize.y * 0.25));
		ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(.2f, .2f, .2f, 1.0f));

		ImGui::Begin("Game_Ended", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoResize);
		ImGui::GetIO().FontGlobalScale = (0.3 / 960) * windowSize.x;

		int bestScore = guardarRecord(level);

		ImGui::PushFont(Renderer::marioFont);

		
		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 0.0f,0.0f, 1.0f));
		ImGui::Text("");
		ImGui::Text("");
		ImGui::Text("                         game over");
		ImGui::Text("");
		ImGui::PopStyleColor();
		ImGui::PopFont();
		ImGui::PushFont(Renderer::marioFontsmall);
		ImGui::Text(std::string("                              your score " + to_string(static_cast<int>(level))).data());
		ImGui::Text(std::string("                              high score " + to_string(static_cast<int>(bestScore))).data());
		
		ImGui::PopFont();
		ImGui::PushFont(Renderer::marioFont);
		ImGui::Text("");
		if (bestScore < level) {
			ImGui::Text(std::string("           new record " ).data());
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
	if (renderLevel) {
		ImGui::SetNextWindowSize(ImVec2(windowSize.x * 0.5, windowSize.x * 0.03)); // 50% del tama�o de la ventana
		ImGui::SetNextWindowPos(ImVec2(windowSize.x * 0.72, windowSize.y * 0.91));

		ImGui::Begin("level", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoBackground);
		ImGui::GetIO().FontGlobalScale = (0.3 / 960) * windowSize.x;



		ImGui::PushFont(Renderer::marioFont);

		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 1.0f, 0.0f, 1.0f));
		ImGui::Text(string("level " +to_string(level)).c_str());



		ImGui::PopStyleColor();
		ImGui::PopFont();
		ImGui::End();


	}
	if (renderTime) {
		ImGui::SetNextWindowSize(ImVec2(windowSize.x * 0.5, windowSize.x * 0.05)); // 50% del tama�o de la ventana
		ImGui::SetNextWindowPos(ImVec2(windowSize.x * 0.75, windowSize.y * 0.23));

		ImGui::Begin("time", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoBackground);
		ImGui::GetIO().FontGlobalScale = (0.2 / 960) * windowSize.x;



		ImGui::PushFont(Renderer::marioFont);

		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 1.0f, 0.0f, 1.0f));
		ImGui::Text("time");



		ImGui::PopStyleColor();
		ImGui::PopFont();
		ImGui::End();

		ImGui::SetNextWindowSize(ImVec2(windowSize.x * 0.5, windowSize.x * 0.1)); // 50% del tama�o de la ventana
		ImGui::SetNextWindowPos(ImVec2(windowSize.x * 0.728, windowSize.y * 0.245));

		ImGui::Begin("time2", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoBackground);
		ImGui::GetIO().FontGlobalScale = (1.1 / 960) * windowSize.x;



		ImGui::PushFont(Renderer::marioFont);
		int timeToShow = int(time);
		if (time < 10) {
			timeToShow *= -1;
		}
		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 1.0f, 0.0f, 1.0f));
		ImGui::Text(to_string(timeToShow).c_str());



		ImGui::PopStyleColor();
		ImGui::PopFont();
		ImGui::End();
	}
}

