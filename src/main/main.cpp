//#include "Simulation.hpp"
//Simulation* simulation; // Instancia de la clase Simulation
//VERSION 1.0


#include "../events/EventHandler.h"





double endTime = 0;
double currentTime = 0;
double lastSecond = 0; //cuanta el tiempo en que se marco el ultimo segundo
double ellapsedTime = 0; ///tiempo entre un frame y otro
bool mouseScalling = false;
bool mouseFoving = false;
HWND consoleWindow; //Thread de la consola
static double fps = 0;
vec2 projectedMousePos;
vec2 PprojectedMousePos;
vec2 mousePosOpenGl;
vec2 mousePos;
vec2 lastMousePos;
vec2 mouseDelta;
bool leftClick = false;
bool showFps = false;
vec2 projectionSize;
Simulation* simulation;
using namespace std;
vec2 windowSize;
std::queue<std::string> commandQueue; // Cola para almacenar los comandos entrantes desde la consola
std::mutex queueMutex; // Mutex para proteger la cola de accesos concurrentes
std::random_device rd;
std::mt19937 g;
ma_engine soundEngine;
ma_result soundResult;

//int WINAPI WinMain(
//	HINSTANCE hInstance,      // Identificador de instancia actual
//	HINSTANCE hPrevInstance,  // Identificador de instancia previa (siempre NULL en sistemas modernos)
//	LPSTR lpCmdLine,          // L�nea de comandos como una cadena de caracteres
//	int nCmdShow              // Bandera que indica c�mo debe mostrarse la ventana
//) {    // Estado de visualizaci�n de la ventana
int main(){
	printf(PROJECT_NAME);
	printf(" v\n Testeo \n");
	printf("\n");
	simulation = new Simulation(true); // Crea una instancia de Simulation
	g = mt19937((rd()));
	glfwSetKeyCallback(simulation->getRenderer()->window, keyCallback);
	glfwSetCursorPosCallback(simulation->getRenderer()->window, mouse_pos_callback);
	glfwSetMouseButtonCallback(simulation->getRenderer()->window, mouse_button_callback);
	glfwSetScrollCallback(simulation->getRenderer()->window, scroll_callback);

	

	while (simulation->running && !glfwWindowShouldClose(simulation->getRenderer()->window)) {

		currentTime = (glfwGetTime());;


		if (currentTime - lastSecond >= 1) {//On every second event

			lastSecond = currentTime;
			if (showFps)  std::cout << fps << std::endl;

		}
		mouseDelta.x = 0;;
		mouseDelta.y = 0;
		


		simulation->update();

		//

		//Update time
		endTime = glfwGetTime();
		ellapsedTime = endTime - currentTime;
		fps = 1 / ellapsedTime;
	//	std::cout << fps <<  std::endl;
	
	}
	
	delete simulation; // Libera la memoria de la instancia de Simulation*/
	return 0;
}

