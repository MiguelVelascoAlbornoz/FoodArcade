#pragma once
#include "Animation.h"



class Textures
{
public:
	static std::unordered_map<std::string, Image*> textures;
	static std::unordered_map<std::string, Animation*> animations;
	static void initializeTextures(); // Función para inicializar las texturas
	static void cleanUpTextures();    // Función para limpiar las texturas


};



