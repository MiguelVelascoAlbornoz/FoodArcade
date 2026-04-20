#include "BombCap.h"

BombCap::BombCap(float size,Image* texture)
{
	this->size = size;
	this->image = texture;
	realSize = vec2(texture->width*size,texture->height*size);
	borderSize = 8 * size;
}
void BombCap::setPos(vec2 pos) {
	this->pos = pos;
}

void BombCap::render(VAO* squareVao) {
	Shaders::shaders["bombs"]->uniform1f("size", size);
	Shaders::shaders["bombs"]->uniform1i("isBackground", 0);
	Shaders::shaders["bombs"]->uniform2f("modelPos", pos.x,pos.y);
	image->bindTexture(0, Shaders::shaders["bombs"], "text");
	Shaders::shaders["bombs"]->uniform2f("textSize", image->width, image->height);
	squareVao->draw(GL_TRIANGLES);
}