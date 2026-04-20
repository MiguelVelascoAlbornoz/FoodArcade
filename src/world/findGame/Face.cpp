#include "Face.h"


bool Face::isSelected(float faceSize) {
	return ImGui::IsMouseClicked(0) && projectedMousePos.x > pos.x && projectedMousePos.x < pos.x + texture->width* faceSize && projectedMousePos.y > pos.y && projectedMousePos.y < pos.y + texture->height* faceSize;
}
void Face::draw(VAO* squareVao, bool bouncing, float faceSize)
{
	pos += velocity*float(ellapsedTime);
	if (!bouncing) {
		if (pos.x > projectionSize.x / 2 - 253 * 1.7 + 1) {
			pos.x = -projectionSize.x / 2 - 32 * faceSize;
		}
		if (pos.x < -projectionSize.x / 2 - 33* faceSize) {
			pos.x = projectionSize.x / 2 - 253 * 1.7;
		}
		if (pos.y > projectionSize.y / 2 + 1) {
			pos.y = -projectionSize.y / 2 - 32 * faceSize;
		}
		if (pos.y < -projectionSize.y / 2 - 33 * faceSize) {
			pos.y = projectionSize.y / 2;
		}
	}
	else {
		if (pos.x > projectionSize.x / 2 - 253 * 1.7 -32* faceSize || pos.x < -projectionSize.x / 2 ) {
			velocity.x *= -1;
		}
	
		if (pos.y > projectionSize.y / 2-32* faceSize || pos.y < -projectionSize.y / 2) {
			velocity.y *= -1;
		}
		
	}
	
	Shaders::shaders["find"]->uniform2f("modelPos", pos.x,pos.y);
	Shaders::shaders["find"]->uniform1f("size", faceSize);
	texture->bindTexture(0,Shaders::shaders["find"],"text");
	Shaders::shaders["find"]->uniform1i("isWanted", 0);
	Shaders::shaders["find"]->uniform2f("textSize", texture->width, texture->height);
	squareVao->draw(GL_TRIANGLES);
	Face* impostorFace;
	ImVec2 mousePos = ImGui::GetMousePos();
}
