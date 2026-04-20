#include "PlusTimeGui.h"

void PlusTimeGui::render()
{
	if (existingTime < 0.7) {
		pos.y += ellapsedTime * 100;
	}
	
	
	ImGui::SetNextWindowSize(ImVec2(windowSize.x * 0.5, windowSize.x * 0.1)); // 50% del tamaño de la ventana
	vec2 a = (vec2(pos.x+projectionSize.x/2,-pos.y+projectionSize.y/2)/projectionSize)*windowSize;
	ImGui::SetNextWindowPos(ImVec2(a.x,a.y-windowSize.x*0.04));

	ImGui::Begin("plusTimeGui", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoBackground);
	ImGui::GetIO().FontGlobalScale = (0.7 / 960) * windowSize.x;
	existingTime += ellapsedTime;


	ImGui::PushFont(Renderer::minecraftFont);

	ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 0.52f, 0.52f, 1.0f));
	std::string result;

	if (value >= 0) {
		result = "+" + std::to_string(value);
	}
	else {
		result = std::to_string(value); // Ya incluye el signo negativo
	}

	ImGui::Text(result.c_str());



	ImGui::PopStyleColor();
	ImGui::PopFont();
	ImGui::End();

}
