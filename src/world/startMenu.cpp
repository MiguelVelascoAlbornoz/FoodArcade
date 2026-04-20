#include "startMenu.h"
 bool startMenu::createCardsGame;
  CardsGame* startMenu::cardsGame;
  FindGame* startMenu::findGame;
  BombsGame* startMenu::bombsGame;
  AsteroidsGame* startMenu::asteroidsGame;
  bool startMenu::shouldDissableCursor  = false;
  bool startMenu::running = true;
  std::list<Body> startMenu::bodies;
void startMenu::rendererLogo()
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
        VAO squareVao;
        std::vector<int> attrib = { 2 };
        squareVao.initialize(vertices, 8, indices, 6, &attrib);
        std::uniform_int_distribution<> randomTime(0,500);
        if (randomTime(g) == 1) {
            Body bodyToAdd;
            vector<Image*> images = { Textures::textures["burger"],Textures::textures["cake"],Textures::textures["cheese"],
                                      Textures::textures["cherry"],Textures::textures["coke"],Textures::textures["cranberries"],
                                      Textures::textures["egg"],Textures::textures["fish"],Textures::textures["french_potatos"],
                                      Textures::textures["fried_chicken"],Textures::textures["granade"],Textures::textures["grapes"],
                                      Textures::textures["green_lemon"],Textures::textures["honey"],Textures::textures["hot_dog"],Textures::textures["lemon"],Textures::textures["mango"],Textures::textures["milk"],Textures::textures["orange"],Textures::textures["pan"],Textures::textures["pear"],Textures::textures["pizza"],Textures::textures["steak"],Textures::textures["strawberry"],Textures::textures["watermelon"] };
            std::uniform_int_distribution<> ran(0,images.size()-1);
            bodyToAdd.texture = images[ran(g)];
            std::uniform_int_distribution<> randomX(-projectionSize.x/2-bodyToAdd.texture->width/2, projectionSize.x/2-bodyToAdd.texture->width / 2);
            bodyToAdd.pos = vec2(randomX(g), projectionSize.y / 2 + bodyToAdd.texture->height);
            std::uniform_int_distribution<> angle(0,360);
            bodyToAdd.rotation = (angle(g)/180.0f)*3.14f;
            bodyToAdd.velocity = vec2(0.0f, -100);
            
            bodies.push_back(bodyToAdd);
        }
     
        Shaders::shaders["bombs"]->bind();
        Shaders::shaders["bombs"]->uniform1i("sparkling", 0);
        Shaders::shaders["bombs"]->uniform1f("size", 2.5);
        Shaders::shaders["bombs"]->uniform1i("isBackground", 1);
        Shaders::shaders["bombs"]->uniform2f("dimensions", projectionSize.x, projectionSize.y);
        Shaders::shaders["bombs"]->uniform2f("modelPos", -projectionSize.x/2,-projectionSize.y/2);
        Textures::textures["stars_background"]->bindTexture(0, Shaders::shaders["bombs"], "text");
        Shaders::shaders["bombs"]->uniform2f("textSize", Textures::textures["stars_background"]->width, Textures::textures["stars_background"]->height);
        squareVao.draw(GL_TRIANGLES);
    Shaders::shaders["asteroids"]->bind();
    for (std::list<Body>::iterator it = bodies.begin(); it != bodies.end(); /* no incrementes aqu� */) {
        (*it).update(false);
        (*it).draw(&squareVao);
        
        if ((*it).pos.y < -projectionSize.y / 2-(*it).texture->height*2) {
           it = bodies.erase(it);
        }
        else {
            ++it;
        }
      
      
    }
    Shaders::shaders["asteroids"]->bind();
    
    ImVec2 pos = ImVec2(windowSize.x * 0.3, windowSize.y * 0.25);
    ImVec2 imageSizeInScreen(Textures::textures["board"]->width * windowSize.x / 400, Textures::textures["board"]->height * windowSize.x / 400);
    ImVec2 iconSizeInScreen(Textures::textures["cardsGame_icon"]->width * windowSize.x / 3350, Textures::textures["cardsGame_icon"]->height * windowSize.x / 3475);
    ImGui::SetNextWindowSize(imageSizeInScreen);
    ImGui::SetNextWindowPos(pos);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
    ImGui::Begin("cardsGame2", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
    
    
   ImGui::Image((ImTextureID)(intptr_t)Textures::textures["board"]->texture, imageSizeInScreen, ImVec2(0, 0), ImVec2(1, 1));
   ImGui::SetCursorPos(ImVec2(0.0101*windowSize.x, 0.0125 * windowSize.x));
   ImGui::Image((ImTextureID)(intptr_t)Textures::textures["cardsGame_icon"]->texture, iconSizeInScreen, ImVec2(0., 0.), ImVec2(1, 1));
      

       
       
    
    if (ImGui::IsWindowHovered() ) {
        ImDrawList* drawList = ImGui::GetWindowDrawList();
        ImVec2 topLeft(pos.x,pos.y);
        drawList->AddRectFilled(topLeft,ImVec2(pos.x+imageSizeInScreen.x,pos.y+imageSizeInScreen.y) , IM_COL32(255, 255, 255, 50));
        if (ImGui::IsMouseClicked(ImGuiMouseButton_Left)) {
            startMenu::cardsGame = new CardsGame();
            ma_sound_stop(&Renderer::MENU_SOUND);
        }
      
    }
    ImGui::End();
    ImGui::PopStyleVar();

    imageSizeInScreen = ImVec2(Textures::textures["board"]->width * windowSize.x / 400, Textures::textures["board"]->height * windowSize.x / 400);
    iconSizeInScreen = ImVec2(Textures::textures["findGame_icon"]->width * windowSize.x / 3350, Textures::textures["findGame_icon"]->height * windowSize.x / 3475);
    ImGui::SetNextWindowSize(imageSizeInScreen);
    pos = ImVec2(windowSize.x * 0.3, windowSize.y * 0.65);
    ImGui::SetNextWindowPos(pos);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
    ImGui::Begin("findGame", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
    {
    
        ImGui::Image((ImTextureID)(intptr_t)Textures::textures["board"]->texture, imageSizeInScreen, ImVec2(0, 0), ImVec2(1, 1));
        ImGui::SetCursorPos(ImVec2(0.0101*windowSize.x, 0.0125 * windowSize.x));
        ImGui::Image((ImTextureID)(intptr_t)Textures::textures["findGame_icon"]->texture, iconSizeInScreen, ImVec2(0., 0.), ImVec2(1, 1));
      

       
       
    }
    if (ImGui::IsWindowHovered() ) {
        ImDrawList* drawList = ImGui::GetWindowDrawList();
 
        drawList->AddRectFilled(pos, ImVec2(pos.x+imageSizeInScreen.x,pos.y + imageSizeInScreen.y) , IM_COL32(255, 255, 255, 50));
        if (ImGui::IsMouseClicked(ImGuiMouseButton_Left)) {
            startMenu::findGame = new FindGame();;
            startMenu::findGame->canDestroy = false;
            ma_sound_stop(&Renderer::MENU_SOUND);
        
        }
      
    }
    ImGui::End();
    ImGui::PopStyleVar();
   
 

    imageSizeInScreen = ImVec2(Textures::textures["board"]->width * windowSize.x / 400, Textures::textures["board"]->height * windowSize.x / 400);
    iconSizeInScreen = ImVec2(Textures::textures["bombsGame_icon"]->width * windowSize.x / 3350, Textures::textures["bombsGame_icon"]->height * windowSize.x / 3475);
    ImGui::SetNextWindowSize(imageSizeInScreen);
    pos = ImVec2(windowSize.x * 0.55, windowSize.y * 0.25);
    ImGui::SetNextWindowPos(pos);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
    ImGui::Begin("bombsGame", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
    {

        ImGui::Image((ImTextureID)(intptr_t)Textures::textures["board"]->texture, imageSizeInScreen, ImVec2(0, 0), ImVec2(1, 1));
        ImGui::SetCursorPos(ImVec2(0.0101 * windowSize.x, 0.0125 * windowSize.x));
        ImGui::Image((ImTextureID)(intptr_t)Textures::textures["bombsGame_icon"]->texture, iconSizeInScreen, ImVec2(0., 0.), ImVec2(1, 1));




    }
    if (ImGui::IsWindowHovered()) {
        ImDrawList* drawList = ImGui::GetWindowDrawList();

        drawList->AddRectFilled(pos, ImVec2(pos.x + imageSizeInScreen.x,pos.y + imageSizeInScreen.y), IM_COL32(255, 255, 255, 50));
        if (ImGui::IsMouseClicked(ImGuiMouseButton_Left)) {
            startMenu::bombsGame = new BombsGame();
            ma_sound_stop(&Renderer::MENU_SOUND);
        }

    }
    ImGui::End();
    ImGui::PopStyleVar();



    imageSizeInScreen = ImVec2(Textures::textures["board"]->width * windowSize.x / 400, Textures::textures["board"]->height * windowSize.x / 400);
    iconSizeInScreen = ImVec2(Textures::textures["asteroids_icon"]->width * windowSize.x / 3350, Textures::textures["asteroids_icon"]->height * windowSize.x / 3475);
    ImGui::SetNextWindowSize(imageSizeInScreen);
    pos = ImVec2(windowSize.x * 0.55, windowSize.y * 0.65);
    ImGui::SetNextWindowPos(pos);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
    ImGui::Begin("asteroidsGame", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
    {

        ImGui::Image((ImTextureID)(intptr_t)Textures::textures["board"]->texture, imageSizeInScreen, ImVec2(0, 0), ImVec2(1, 1));
        ImGui::SetCursorPos(ImVec2(0.0101 * windowSize.x, 0.0125 * windowSize.x));
        ImGui::Image((ImTextureID)(intptr_t)Textures::textures["asteroids_icon"]->texture, iconSizeInScreen, ImVec2(0., 0.), ImVec2(1, 1));




    }
    if (ImGui::IsWindowHovered()) {
        ImDrawList* drawList = ImGui::GetWindowDrawList();

        drawList->AddRectFilled(pos, ImVec2(pos.x+ imageSizeInScreen.x,pos.y+ imageSizeInScreen.y), IM_COL32(255, 255, 255, 50));
        if (ImGui::IsMouseClicked(ImGuiMouseButton_Left)) {
            startMenu::shouldDissableCursor = true;
            startMenu::asteroidsGame = new AsteroidsGame();
            ma_sound_stop(&Renderer::MENU_SOUND);
        }

    }
    ImGui::End();
    ImGui::PopStyleVar();
    ImGui::SetNextWindowSize(ImVec2(windowSize.x * 0.4, windowSize.x * 0.25)); // 50% del tama�o de la ventana
    ImGui::SetNextWindowPos(ImVec2(windowSize.x * 0.7, windowSize.y * 0.55));
    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(.2f, .2f, .2f, 1.0f));

    ImGui::Begin("Game_Ended", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoBackground);
    ImGui::GetIO().FontGlobalScale = (0.3 / 960) * windowSize.x;

  

    ImGui::PushFont(Renderer::marioFont);


    ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 0.0f, 0.0f, 1.0f));





    ImGui::Text("                 "); ImGui::SameLine(); if (ImGui::Button(" EXIT")) {
        startMenu::running = false;;
    }
    ImGui::PopStyleColor();
    ImGui::PopFont();
    ImGui::End();
    ImGui::PopStyleColor();



    ImGui::SetNextWindowSize(ImVec2(windowSize.x * 0.7, windowSize.x * 0.1)); // 50% del tama�o de la ventana
    ImGui::SetNextWindowPos(ImVec2(windowSize.x * 0.16, windowSize.y * 0.047));
    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(.5f, .2f,.8f, .5f));

    ImGui::Begin("titleBACKGROUND", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoResize);






    ImGui::PopStyleColor();
    ImGui::End();



    ImGui::SetNextWindowSize(ImVec2(windowSize.x * 0.9, windowSize.x * 0.1)); // 50% del tama�o de la ventana
    ImGui::SetNextWindowPos(ImVec2(windowSize.x * 0.17, windowSize.y * 0.05));
    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(.2f, .2f, .2f, 1.0f));

    ImGui::Begin("title", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoBackground);
    ImGui::GetIO().FontGlobalScale = (1.25 / 960) * windowSize.x;



    ImGui::PushFont(Renderer::marioFont);


    ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 1.0f, 1.0f, 1.0f));





    ImGui::Text("food arcade"); 
    ImGui::PopStyleColor();
    ImGui::PopFont();
    ImGui::End();

    ImGui::PopStyleColor();


    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

}
