#include "Bomb.h"


bool Bomb::isSelected() {
	return  PprojectedMousePos.x > pos.x && PprojectedMousePos.x < pos.x + gif.animation->frames[0]->width * size && PprojectedMousePos.y > pos.y && PprojectedMousePos.y < pos.y + gif.animation->frames[0]->height * size;
}

Bomb::~Bomb()
{

}

void Bomb::render(VAO* squareVao) {
	if (!exlodeAnimation) {
		if (setBig) {
			Shaders::shaders["bombs"]->uniform1i("sparkling", 1);
			
		}
		else {
			Shaders::shaders["bombs"]->uniform1i("sparkling", 0);
		}

		Shaders::shaders["bombs"]->uniform1f("size", size);
		Shaders::shaders["bombs"]->uniform1i("isBackground", 0);
		Shaders::shaders["bombs"]->uniform2f("modelPos", pos.x, pos.y);
		Shaders::shaders["bombs"]->uniform2f("textSize",gif.animation->frames[0]->width, gif.animation->frames[0]->height);
		gif.use(0, Shaders::shaders["bombs"], "text");
		squareVao->draw(GL_TRIANGLES);
	}
	else if (explosionGif != nullptr && explosionGif->actualFrame != -1){
		Shaders::shaders["bombs"]->uniform1f("size", size*1.4);
		Shaders::shaders["bombs"]->uniform1i("isBackground", 0);
		Shaders::shaders["bombs"]->uniform2f("modelPos", pos.x, pos.y);
		explosionGif->use(0, Shaders::shaders["bombs"], "text");
		Shaders::shaders["bombs"]->uniform2f("textSize", explosionGif->animation->frames[0]->width, explosionGif->animation->frames[0]->height);
		squareVao->draw(GL_TRIANGLES);
	}
	else if (explosionGif != nullptr){
		delete explosionGif;
		explosionGif = nullptr;
	}
	

}
void Bomb::update()
{
	if (!exlodeAnimation) {
		if (!selected) {
			if (pos.x < -projectionSize.x / 2 || pos.x > projectionSize.x / 2 - gif.animation->frames[0]->width * 1.4) {
				velocity.x *= -1;
			}
			if (pos.y < -projectionSize.y / 2 || pos.y > 200 - gif.animation->frames[0]->height * 1.4) {
				velocity.y *= -1;
			}
			pos += velocity * float(ellapsedTime);
		}
		if (livingTime >= 7 && !setBig) {
			size *= 1.4;
			ma_sound_start(&Renderer::FUSE);
			setBig = true;
		}


		if (!inBox) {
			livingTime += ellapsedTime;
		}
	}
	
	
	
	
}
bool Bomb::testCollisionWithSquare(Bomb* bomb, vec2 rectPos, vec2 rectSize) {
	float bombWidth = bomb->gif.animation->frames[0]->width * bomb->size;
	float bombHeight = bomb->gif.animation->frames[0]->height * bomb->size;

	if (bomb->pos.x < rectPos.x + rectSize.x && bomb->pos.x + bombWidth > rectPos.x && bomb->pos.y < rectPos.y + rectSize.y && bomb->pos.y + bombHeight > rectPos.y) {

		return true;
	}
	return false;
}
void Bomb::isInBox(BombCap* bombCap)
{
	    bool org = inBox;
		inBox = Bomb::testCollisionWithSquare(this, bombCap->pos, bombCap->realSize);
		if (!org && inBox && setBig) {
			size /= 1.4;
			setBig = false;
			livingTime = 0;
		}
}
