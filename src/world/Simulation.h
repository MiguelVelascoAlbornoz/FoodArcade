#pragma once


#include "startMenu.h"

#include "World.h"

class Simulation
{
public:
	Simulation(bool fullscreen);;
	~Simulation();
	bool initRenderer(bool fullacreen);

	void setup();
	Camera* camera;

	void updateRender();
	void endFrameGUI() {
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}
	void newFrameGUI() {
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}
	const Renderer* getRenderer() { return renderer; };
	bool running = true;
	void toggleFullscreen() { 
		renderer->toggleFullscreen(); 
		};
	void manageInputs();
	void update();
	void updateLogic();
	World* world;
private:

	Renderer* renderer;

};

