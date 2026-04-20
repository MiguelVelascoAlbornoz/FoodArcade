#include "Shaders.h"

std::unordered_map<std::string, Shader*> Shaders::shaders;
std::vector<Shader*> Shaders::shadersToSendProjection;
void Shaders::initializeShaders() {

    shaders["cards"] = new Shader("cards");
    shaders["find"] = new Shader("find");
    shaders["bombs"] = new Shader("bombs");
    shaders["asteroids"] = new Shader("asteroids");
    shadersToSendProjection = { shaders["cards"],shaders["find"],shaders["bombs"],shaders["asteroids"] };

}

void Shaders::destroyShaders() {
    for (auto& shaderPair : shaders) {
        delete shaderPair.second;  // Eliminar cada shader
    }
    shaders.clear();  // Limpiar el mapa
}

void Shaders::reloadShaders() {
    for (auto& shaderPair : shaders) {
        shaderPair.second->reload();  // Recargar cada shader
    }
}
