#include "Player.h"

void Player::draw(VAO* squareVao)
{
	if (onCoolDown) {
		coolDownTimer += ellapsedTime;
	}
	
	mat4 rotationMatrix = rotate(mat4(1.0f), rotation, vec3(0.0f, 0.0f, 1.0f));
	Shaders::shaders["asteroids"]->uniform1f("size", size);
	Shaders::shaders["asteroids"]->uniform1i("isBackground", 0);
	Shaders::shaders["asteroids"]->uniformMatrix4f("rotationMatrix", 1, GL_FALSE, value_ptr(rotationMatrix));
	Shaders::shaders["asteroids"]->uniform2f("modelPos", pos.x, pos.y);
	Shaders::shaders["asteroids"]->uniform2f("massCenter", massCenter.x, massCenter.y);
	if (onCoolDown) {
		Shaders::shaders["asteroids"]->uniform1i("sparklin", 1);
	}
	else {
		Shaders::shaders["asteroids"]->uniform1i("sparklin", 0);
	}
	Shaders::shaders["asteroids"]->uniform1f("time", currentTime);
	Shaders::shaders["asteroids"]->uniform2f("textSize", texture->width, texture->height);
	texture->bindTexture(0, Shaders::shaders["asteroids"], "text");
	squareVao->draw(GL_TRIANGLES);
	if (drawFire) {
		Shaders::shaders["asteroids"]->uniform2f("textSize", Textures::animations["rocket"]->frames[0]->width, Textures::animations["rocket"]->frames[0]->width);
		gif.use(0, Shaders::shaders["asteroids"], "text");
		squareVao->draw(GL_TRIANGLES);
	}
	Shaders::shaders["asteroids"]->uniform1i("sparklin", 0);

}