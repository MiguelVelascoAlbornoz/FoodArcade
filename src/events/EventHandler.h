

#pragma once
#include "../world/Simulation.h"

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	ImGui_ImplGlfw_KeyCallback(window, key, scancode, action, mods);
	Simulation* simulation = (Simulation*)glfwGetWindowUserPointer(window);
	if (action == GLFW_PRESS) {
		switch (key) {
		case GLFW_KEY_ESCAPE:
			simulation->running = false;
		case GLFW_KEY_F11:
			simulation->toggleFullscreen();
		}

	}

}
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
	ImGui_ImplGlfw_MouseButtonCallback(window, button, action, mods);
	if (action == GLFW_PRESS) {
		switch (button) {
		case 0:
			leftClick = true;
		}
	}
	else if (action == GLFW_RELEASE) {
		switch (button) {
		case 0:
			leftClick = false;
		}
	}

}
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
	ImGui_ImplGlfw_ScrollCallback(window, xoffset, yoffset);
	Simulation* simulation = (Simulation*)glfwGetWindowUserPointer(window);
	

}
glm::vec2 screenToOpenGLCoords(int mouseX, int mouseY, int screenWidth, int screenHeight) {
	// Transformar la posición X
	float x = (2.0f * mouseX) / screenWidth - 1.0f;

	// Transformar la posición Y (invertir porque la Y en pantalla es hacia abajo)
	float y = 1.0f - (2.0f * mouseY) / screenHeight;

	return glm::vec2(x, y);
}
void mouse_pos_callback(GLFWwindow* window, double xpos, double ypos) {
	ImGui_ImplGlfw_CursorPosCallback(window, xpos, ypos);
	mousePos.x = xpos;
	mousePos.y = ypos;
	mousePosOpenGl = screenToOpenGLCoords(xpos,ypos,windowSize.x,windowSize.y);
	Camera* camera = ((Simulation*)glfwGetWindowUserPointer(window))->camera;
	PprojectedMousePos = projectedMousePos;
	projectedMousePos = glm::inverse(camera->modelMatrix) * vec4(mousePosOpenGl,0.0f,1.0f);
	
}
