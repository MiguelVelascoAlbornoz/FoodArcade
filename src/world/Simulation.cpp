#include "Simulation.h"





Simulation::Simulation(bool fullscreen)
{
    soundResult = ma_engine_init(NULL, &soundEngine);
    if (soundResult != MA_SUCCESS) {
        std::cerr << "Error al inicializar el motor de audio.\n";
    }   


    if (!initRenderer(fullscreen)) {
		running = false;
        return;
    }


    glfwSetWindowUserPointer(renderer->window,this);
    setup();

}

Simulation::~Simulation()
{
    ma_engine_uninit(&soundEngine);
    delete renderer;
    delete camera;
}

bool Simulation::initRenderer(bool fullscreen)
{
    renderer = new Renderer();
    
    if (!renderer->initRenderer(fullscreen)) {
        return false;
    }

    glfwSetWindowUserPointer(renderer->window, this);


   
    return true;
}

void Simulation::setup() {
    camera = new Camera(vec3(0, 0, 1), 1.0f, renderer->getWindowSize(), 120);
    Textures::initializeTextures();
  
       ma_sound_set_looping(&Renderer::MENU_SOUND, MA_TRUE); // Habilita el loop
       ma_sound_start(&Renderer::MENU_SOUND);

}
void Simulation::update() {
    manageInputs();
    updateLogic();
    updateRender();

}
void Simulation::updateLogic()
{
}
void Simulation::manageInputs() {
    vec3 cameraPos = camera->getPos();
  
  
   

}

void Simulation::updateRender() {
    renderer->background(1.0f, 1.0f, 1.0f);//ponemos y limpiamos background
    glfwSetCursor(renderer->window, renderer->cursor);
    // Start the Dear ImGui frame
   
    newFrameGUI();
    if (startMenu::cardsGame != nullptr) {
        startMenu::cardsGame->render();
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        if (startMenu::cardsGame->canDestroy) {
            delete startMenu::cardsGame;
            startMenu::cardsGame = nullptr;
        }
    }
    else if (startMenu::findGame != nullptr) {
        startMenu::findGame->render();
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        if (startMenu::findGame->canDestroy) {
            delete startMenu::findGame;//
            startMenu::findGame = nullptr;
        }
    }
    else if (startMenu::bombsGame != nullptr) {
        startMenu::bombsGame->render();
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        if (startMenu::bombsGame->canDestroy) {
            delete startMenu::bombsGame;
            startMenu::bombsGame = nullptr;
        }
    }
    else if (startMenu::asteroidsGame != nullptr) {
        startMenu::asteroidsGame->render();
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        if (startMenu::asteroidsGame->showCursor) {
            glfwSetInputMode(renderer->window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        }
        else {
            glfwSetInputMode(renderer->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
           
        }
        if (startMenu::asteroidsGame->canDestroy) {
            delete startMenu::asteroidsGame;
            startMenu::asteroidsGame = nullptr;
            glfwSetInputMode(renderer->window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        }
    }
    else {
        
        startMenu::rendererLogo();

        this->running = startMenu::running;
        if (startMenu::shouldDissableCursor) {
            glfwSetInputMode(renderer->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            startMenu::shouldDissableCursor = false;
            
        } 
    }
  
    //ImGui::PushFont(renderer->gameFont);
    //bool show_demo_window = true;
   // ImGui::ShowDemoWindow(&show_demo_window);

    // Renderizar la imagen como logo en ImGui
    //startMenu::rendererLogo();

    //cardsGame->render(renderer);
      
   // endFrameGUI();

    glfwPollEvents();
   /* camera->shader->uniform1f("time", currentTime);
  

   
    camera->bindShader();//activamos el uso del shader program
   

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
   
    
    
   

    camera->unBindShader();//desactivamos el uso del shader*/

    renderer->update();//actualizamos ventana
}
