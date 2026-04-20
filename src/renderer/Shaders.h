
#pragma once
#include "Shader.h"
class Shaders {
public:
    // Un mapa para almacenar shaders por su nombre
    static std::unordered_map<std::string, Shader*> shaders;
    static std::vector<Shader*>shadersToSendProjection;
    static void initializeShaders();
    static void destroyShaders();
    static void reloadShaders();

private:
    // Agregar o quitar shaders directamente desde el mapa
   // static Shader* getShader(const std::string& shaderName);
};

