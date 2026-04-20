#include "AsteroidsGame.h"

int orientation(vec2 p, vec2 q, vec2 r) {
	double val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
	if (val == 0) return 0;             // Colineales
	return (val > 0) ? 1 : 2;          // 1: Horario, 2: Antihorario
}

// Verificar si dos segmentos se intersectan
bool doIntersect(vec2 p1, vec2 q1, vec2 p2, vec2 q2) {
	int o1 = orientation(p1, q1, p2);
	int o2 = orientation(p1, q1, q2);
	int o3 = orientation(p2, q2, p1);
	int o4 = orientation(p2, q2, q1);

	// Caso general
	if (o1 != o2 && o3 != o4) return true;

	return false; // No hay intersecci�n
}

// Verificar si un punto est� dentro de un cuadril�tero
bool isInside(vec2 p, const vector<vec2>& quad) {
	int count = 0;
	vec2 farPoint = { 1e9, p.y }; // Un punto muy lejos a la derecha

	for (int i = 0; i < 4; ++i) {
		vec2 a = quad[i];
		vec2 b = quad[(i + 1) % 4];
		if (doIntersect(p, farPoint, a, b)) {
			++count;
		}
	}
	return (count % 2 == 1);
}

// Verificar si dos cuadril�teros se intersectan
bool quadrilateralsIntersect(const vector<vec2>& quad1, const vector<vec2>& quad2) {
	// Revisar si alguno de los segmentos de un cuadril�tero intersecta con los del otro
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			if (doIntersect(quad1[i], quad1[(i + 1) % 4], quad2[j], quad2[(j + 1) % 4])) {
				return true;
			}
		}
	}

	// Revisar si un cuadril�tero est� completamente dentro del otro
	if (isInside(quad1[0], quad2) || isInside(quad2[0], quad1)) {
		return true;
	}

	return false;
}

AsteroidsGame::AsteroidsGame()
{
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
	player.massCenter = vec2(9.5 * player.size, 9.5 * player.size);
	player.texture = Textures::textures["pan"];
	player.atrito = 0.995;
	startLevel();
}
void AsteroidsGame::startLevel() {
	player.onCoolDown = true;
	int asteroidsCount = level ;
	std::vector<Image*> possibleTextures = {
	Textures::textures["apple"],Textures::textures["banana"], Textures::textures["cheese"], Textures::textures["honey"], Textures::textures["granade"], Textures::textures["egg"],
	Textures::textures["pear"], Textures::textures["steak"], Textures::textures["fish"], Textures::textures["orange"], Textures::textures["fried_chicken"],Textures::textures["milk"],Textures::textures["coke"]
	};
	for (int i = 0; i < asteroidsCount; ++i) {
		Body asteroidToAdd;
		std::uniform_int_distribution<> d(0, possibleTextures.size() - 1);
		asteroidToAdd.texture = possibleTextures[d(g)];
		std::uniform_int_distribution<> sizeDistrib(0, 3000);
		asteroidToAdd.size = sizeDistrib(g) / 1000 + 4;
		asteroidToAdd.massCenter = vec2(asteroidToAdd.texture->width * asteroidToAdd.size / 2, asteroidToAdd.texture->height * asteroidToAdd.size / 2);
		std::uniform_int_distribution<> randomX(-projectionSize.x / 2, projectionSize.x / 2);
		std::uniform_int_distribution<> randomY(-projectionSize.y / 2, projectionSize.y / 2);
		vec2 finalPos = vec2(randomX(g), randomY(g));
		while (sqrt(finalPos.x*finalPos.x+finalPos.y*finalPos.y) <200){
			finalPos = vec2(randomX(g), randomY(g));
		}
		asteroidToAdd.pos = finalPos;
		std::uniform_int_distribution<> angleDistrib(0, 360);
		std::uniform_int_distribution<> velocityDistrib(4, 10);
		std::uniform_int_distribution<> angularSpeedDistrib(-300, 300);
		int angle = angleDistrib(g);
		asteroidToAdd.velocity = vec2(cos(angle),sin(angle))*float(velocityDistrib(g));
		asteroidToAdd.angularVelocity = angularSpeedDistrib(g)/100;
		asteroids.push_back(asteroidToAdd);
		
	}
}
void AsteroidsGame::render()
{
	if (player.lifes <= 0) {
		if (!renderEndGui) {
			       ma_sound_start(&Renderer::MENU_SOUND);
				   ma_sound_stop(&Renderer::GAME_OVER_SOUND);
		}
		renderEndGui = true;
		asteroids.clear();
	}
	if (asteroids.size() <= 0) {
		player.pos = vec2(0.0f);
		
		chooseGUI = true;
	}
	if (ImGui::IsKeyDown(ImGuiKey_A)) {
		player.angularVelocity += 8*ellapsedTime;
	}
	if (ImGui::IsKeyDown(ImGuiKey_D)) { 
		player.angularVelocity += -8*ellapsedTime;
	} 
	if (ImGui::IsKeyDown(ImGuiKey_Space) && currentTime - lastBigShootTime > 0.2) {
		
		ma_sound_start(&Renderer::LASER);
		doingShoot = true;
		
		lastBigShootTime = currentTime;
		lastShootTime = currentTime;
		Bullet bulletToAdd;
		bulletToAdd.texture = Textures::textures["floor"];
		bulletToAdd.size = 1;
		shootVelocity = player.velocity+ vec2(cos(player.rotation + 3.14 / 4 + 3.14), sin(player.rotation + 3.14 / 4 + 3.14))*400.0f;
		bulletToAdd.velocity = shootVelocity;
		bulletToAdd.pos = player.pos+player.massCenter;
		bullets.push_back(bulletToAdd);
	}
	if (doingShoot && currentTime - lastShootTime > 0.01) {
		shootsCount++;
		lastShootTime = currentTime;
		if (shootsCount > bulletsCount-2) {
			doingShoot = false;
			shootsCount = 0;
		}
		else {
			Bullet bulletToAdd;
			bulletToAdd.texture = Textures::textures["floor"];
			bulletToAdd.size = 1;
			bulletToAdd.velocity = shootVelocity;
			bulletToAdd.pos = player.pos + player.massCenter;
			bullets.push_back(bulletToAdd);
		}
		
	}
	if (ImGui::IsKeyDown(ImGuiKey_W)) {
		player.velocity += vec2(cos(player.rotation+3.14/4+3.14),sin(player.rotation+ 3.14 / 4+3.14))*250.0f*float(ellapsedTime);

		player.drawFire = true;
	}
	else {
		player.drawFire = false;
	}
	if (player.coolDownTimer > 3) {
		player.onCoolDown = false;
		player.coolDownTimer = 0.0f;
	}
	player.update(true);
	player.calculateVertices();
	Shaders::shaders["asteroids"]->bind();

	for (std::list<Body>::iterator it = asteroids.begin(); it != asteroids.end(); /* no incrementes aqu� */) {
		(*it).update(true);
		(*it).draw(&squareVao);

		
		(*it).calculateVertices();
		if (quadrilateralsIntersect(player.vertices, (*it).vertices) && !player.onCoolDown) {
			player.onCoolDown = true;
			player.lifes--;
			ma_sound_start(&Renderer::DAMAGE);
			loseLife = true;
		}

		/*	if ((*it).actualFrame == -1) {
			// Erase devuelve un iterador v�lido al siguiente elemento
			it = gifts.erase(it);
		}
		else {
			// Incrementa el iterador solo si no se borra
			++it;
		}*/
		++it;
	}
	std::vector<Body> killedBodies;
	for (std::list<Bullet>::iterator it = bullets.begin(); it != bullets.end(); /* no incrementes aqu� */) {
		(*it).update(true);
		(*it).draw(&squareVao);
		(*it).calculateVertices();
		
		for (std::list<Body>::iterator jt = asteroids.begin(); jt != asteroids.end(); /* no incrementes aqu� */) {
			

			if (quadrilateralsIntersect((*it).vertices, (*jt).vertices)) {

				// Erase devuelve un iterador v�lido al siguiente elemento
				killedBodies.push_back((*jt));
				score += (*jt).size;
				jt = asteroids.erase(jt);
		
				(*it).shouldDestroy = true;
				
				break;
			} else {
				// Incrementa el iterador solo si no se borra
				++jt;
			}
		}
			if ((*it).livingTime > 3 || (*it).shouldDestroy) {
				// Erase devuelve un iterador v�lido al siguiente elemento
				it = bullets.erase(it);
			}
			else {
				// Incrementa el iterador solo si no se borra
				++it;
			}
			
	
	}
	for (int i = 0; i < killedBodies.size(); ++i) {
		for (int j = 0; j < 2; ++j) {
			Body asteroidToAdd;

			asteroidToAdd.texture = killedBodies[i].texture;
			std::uniform_int_distribution<> sizeDistrib(0, 1000);
			asteroidToAdd.size = killedBodies[i].size/(sizeDistrib(g) / 1000 + 1.5);
			if (asteroidToAdd.size < 0.6) {
				break;
			}
			asteroidToAdd.massCenter = vec2(asteroidToAdd.texture->width * asteroidToAdd.size / 2, asteroidToAdd.texture->height * asteroidToAdd.size / 2);
			
	

			asteroidToAdd.pos = killedBodies[i].pos;
			std::uniform_int_distribution<> angleDistrib(-45, 45);
			std::uniform_int_distribution<> velocityDistrib(0, 1000);

			std::uniform_int_distribution<> angularSpeedDistrib(-300, 300);
			int angle = angleDistrib(g);
			float sizeFactor =.1f;
			if (killedBodies[i].size > 0.1f){
				sizeFactor = killedBodies[i].size;
			}  // Evitar divisiones por cero
			vec2 finalVelocity = vec4(killedBodies[i].velocity * ( 1.2f+float(velocityDistrib(g))/1000), 0.0f, 1.0f) * rotate(mat4(1.0f), float(angleDistrib(g)), vec3(0.0f, 0.0f, 1.0f));
			asteroidToAdd.velocity = finalVelocity;
			asteroidToAdd.angularVelocity = killedBodies[i].angularVelocity*(1.0f+float(velocityDistrib(g))/1000);
			asteroids.push_back(asteroidToAdd);
	  }
	}
	player.draw(&squareVao);
	if (!loseLife) {
		for (int i = 0; i < player.lifes; ++i) {
			Shaders::shaders["asteroids"]->uniform1f("size", 2);
			Shaders::shaders["asteroids"]->uniform1i("isBackground", 0);
			Shaders::shaders["asteroids"]->uniformMatrix4f("rotationMatrix", 1, GL_FALSE, value_ptr(mat4(1.0f)));
			Shaders::shaders["asteroids"]->uniform2f("modelPos", -projectionSize.x / 2 * 0.95 + i * 25, projectionSize.y / 2 * 0.85);
			Shaders::shaders["asteroids"]->uniform2f("massCenter", 0, 0);
			Shaders::shaders["asteroids"]->uniform2f("textSize", Textures::textures["heart"]->width, Textures::textures["heart"]->height);
			Textures::textures["heart"]->bindTexture(0, Shaders::shaders["asteroids"], "text");
			squareVao.draw(GL_TRIANGLES);
		}
	}
	else {
		for (int i = 0; i < player.lifes; ++i) {
			Shaders::shaders["asteroids"]->uniform1f("size", 2);
			Shaders::shaders["asteroids"]->uniform1i("isBackground", 0);
			Shaders::shaders["asteroids"]->uniformMatrix4f("rotationMatrix", 1, GL_FALSE, value_ptr(mat4(1.0f)));
			Shaders::shaders["asteroids"]->uniform2f("modelPos", -projectionSize.x / 2 * 0.95 + i * 25, projectionSize.y / 2 * 0.85);
			Shaders::shaders["asteroids"]->uniform2f("massCenter", 0, 0);
			Shaders::shaders["asteroids"]->uniform2f("textSize", Textures::textures["heart"]->width, Textures::textures["heart"]->height);
			Textures::textures["heart"]->bindTexture(0, Shaders::shaders["asteroids"], "text");
			squareVao.draw(GL_TRIANGLES);
		}
		if (heartBreakGif.actualFrame == -1) {
			heartBreakGif.actualFrame = 0;
			loseLife = false;
		}
		else {
			Shaders::shaders["asteroids"]->uniform1f("size", 2);
			Shaders::shaders["asteroids"]->uniform1i("isBackground", 0);
			Shaders::shaders["asteroids"]->uniformMatrix4f("rotationMatrix", 1, GL_FALSE, value_ptr(mat4(1.0f)));
			Shaders::shaders["asteroids"]->uniform2f("modelPos", -projectionSize.x / 2 * 0.95 + (player.lifes) * 25, projectionSize.y / 2 * 0.85);
			Shaders::shaders["asteroids"]->uniform2f("massCenter", 0, 0);
			Shaders::shaders["asteroids"]->uniform2f("textSize", Textures::textures["heart"]->width, Textures::textures["heart"]->height);
			heartBreakGif.use(0, Shaders::shaders["asteroids"], "text");
			squareVao.draw(GL_TRIANGLES);
		}
		
	}
	
	Shaders::shaders["asteroids"]->unBind();
	renderGUI();
}
int saveRecord(int score) {
	const std::string archivoRecord = "assets/scores/highscoreAsteroids.txt";
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
void AsteroidsGame::renderGUI()
{
	ImGui::SetNextWindowSize(ImVec2(windowSize.x * 0.6, windowSize.x * 0.2)); // 50% del tama�o de la ventana
	ImGui::SetNextWindowPos(ImVec2(windowSize.x * 0.75, windowSize.y * 0.02));

	ImGui::Begin("score", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoBackground);
	ImGui::GetIO().FontGlobalScale = (0.3 / 960) * windowSize.x;



	ImGui::PushFont(Renderer::marioFont);

	ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 1.0f, 1.0f, 1.0f));
	ImGui::Text(std::string("score "+ to_string(score)).c_str());



	ImGui::PopStyleColor();
	ImGui::PopFont();
	ImGui::End();
	if (renderEndGui) {
		showCursor = true;
		ImGui::SetNextWindowSize(ImVec2(windowSize.x * 0.4, windowSize.x * 0.25)); // 50% del tama�o de la ventana
		ImGui::SetNextWindowPos(ImVec2(windowSize.x * 0.30, windowSize.y * 0.25));
		ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(.2f, .2f, .2f, 1.0f));

		ImGui::Begin("gameEnd", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoResize);
		ImGui::GetIO().FontGlobalScale = (0.3 / 960) * windowSize.x;

		int bestScore = saveRecord(score);

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
	} else 
	if (chooseGUI) {
		showCursor = true;
		ImGui::SetNextWindowSize(ImVec2(windowSize.x * 0.4, windowSize.x * 0.2)); // 50% del tama�o de la ventana
		ImGui::SetNextWindowPos(ImVec2(windowSize.x * 0.30, windowSize.y * 0.25));
		ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(.2f, .2f, .2f, 1.0f));

		ImGui::Begin("choose", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoResize);
		ImGui::GetIO().FontGlobalScale = (0.3 / 960) * windowSize.x;

		

		ImGui::PushFont(Renderer::marioFont);


		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 1.0f,1.0f, 1.0f));
		ImGui::Text("");
		ImGui::Text("");
		ImGui::Text("                           choose");
		ImGui::Text("");
		ImGui::PopStyleColor();
		ImGui::PopFont();
		ImGui::PushFont(Renderer::marioFontsmall);


		ImGui::PopFont();
		ImGui::PushFont(Renderer::marioFont);
		ImGui::Text("");

		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 1.0f, 1.0f, 1.0f));
		//ImGui::Text("                 "); ImGui::SameLine(); if (ImGui::Button("return to menu")) canDestroy = true;
		ImGui::Text("    "); ImGui::SameLine();
		if (ImGui::Button("extra life")) {
			player.lifes += 3;
			chooseGUI = false;
			showCursor = false;
			level++;
			ma_sound_start(&Renderer::POWER_UP);
			startLevel();
		}
		ImGui::SameLine();
		ImGui::Text(""); ImGui::SameLine();
		if (ImGui::Button("extra bullet")) {
			bulletsCount+=3;
			chooseGUI = false;
			ma_sound_start(&Renderer::POWER_UP);
			showCursor = false;
			level++;
			startLevel();
		}
		ImGui::PopStyleColor();
		ImGui::PopFont();
		ImGui::End();
		ImGui::PopStyleColor();
	}
}
