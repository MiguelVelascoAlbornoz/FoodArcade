#include "Card.h"


bool Card::isSelected() {
	return ImGui::IsMouseClicked(0) && projectedMousePos.x > pos.x && projectedMousePos.x < pos.x + size.x && projectedMousePos.y > pos.y && projectedMousePos.y < pos.y + size.y;
}
void Card::draw(VAO* vao,bool &canSelect)
{
	

	if (mustRotate && !isRotating) {
		timer -= (1/0.006)* ellapsedTime;
		if (timer <= 0) {
			isRotating = true;
			mustRotate = false;
			timer = 200;
			canSelect = true;
		}	
	}
	
	if (isRotating) {

		if (!internalShow) {
			currentAngle += (0.1/0.006)*ellapsedTime;

			if (currentAngle > 3.14 / 2) {
				show = true;
			}
			if (currentAngle >= 3.14) {
				internalShow = true;
				isRotating = false;
			}
		}
		else {
			currentAngle -= (0.1 / 0.006) * ellapsedTime;
			if (currentAngle < 3.14 / 2) {
				show = false;
			}
			if (currentAngle <= 0) {
				internalShow = false;
				isRotating = false;
			}
		}
		
	}
	mat4 rotation = rotate(mat4(1.0f), currentAngle, vec3(.0f, 1.0f, 0.0f));
	Shaders::shaders["cards"]->uniformMatrix4f("rotation", 1, GL_FALSE, value_ptr(rotation));
	centerImage->bindTexture(2,Shaders::shaders["cards"],"centerImage");
	Shaders::shaders["cards"]->uniform2f("textSize", centerImage->width, centerImage->height);
	if (!show) {
		
		Shaders::shaders["cards"]->uniform1i("show", 0);
	}
	else {
		if (playerOwner == 0) {
			Textures::textures["card_top"]->bindTexture(0, Shaders::shaders["cards"], "card_top");
		}
		else if (playerOwner == 1) {
			Textures::textures["card_top_player1"]->bindTexture(0, Shaders::shaders["cards"], "card_top");
		}
		else {
			Textures::textures["card_top_player2"]->bindTexture(0, Shaders::shaders["cards"], "card_top");
		}
		Shaders::shaders["cards"]->uniform1i("show", 1);
	}
	
	Shaders::shaders["cards"]->uniform2f("modelPos", pos.x, pos.y);
	vao->draw(GL_TRIANGLES);
}
