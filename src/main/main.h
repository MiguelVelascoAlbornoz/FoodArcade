#ifndef MAIN_H
#define MAIN_H
#include <queue>
#include <mutex>
#include <list>

#define GLEW_STATIC
#include <glew/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <sstream>
#include <memory>
#include <fstream>
#include <iostream>
#include <unordered_map>

#include <imGUI/imgui_impl_glfw.h>
#include <imGUI/imgui_impl_opengl3.h>
#include <imGUI/imgui.h>
#include <algorithm>
#include <cmath>
#include <random>

#include <stbImage/stb_image.h>
#include <string>
#include <thread>
#include <windows.h>
#include <miniAudio/miniAudio.h>
using namespace glm;
#pragma once
extern std::queue<std::string> commandQueue; // Cola para almacenar los comandos entrantes desde la consola
extern std::mutex queueMutex; // Mutex para proteger la cola de accesos concurrentes
extern bool showFps;
extern ma_engine soundEngine;
extern ma_result soundResult;
extern vec2 mousePosOpenGl;
extern vec2 projectedMousePos;
extern vec2 PprojectedMousePos;

extern vec2 mousePos;
extern vec2 lastMousePos;
extern vec2 mouseDelta;
extern vec2 projectionSize;
extern double currentTime;
extern bool leftClick;
extern double ellapsedTime;
extern bool mouseScalling;
extern bool mouseFoving;
extern vec2 windowSize;
extern std::random_device rd;
extern std::mt19937 g;

#endif