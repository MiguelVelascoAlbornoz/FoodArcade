#include "GIF.h"

GIF::GIF(Animation* animation, float timePerFrame, bool repeat)
{
	this->animation = animation;
	this->timePerFrame = timePerFrame;
	time = timePerFrame;
	this->repeat = repeat;
}

void GIF::use(GLenum textureUnit, Shader* shader, const char* name)
{
	if (actualFrame != -1) {
		animation->frames[actualFrame]->bindTexture(textureUnit, shader, name);
		time -= ellapsedTime;
	}
	
	if (time < 0) {
		actualFrame++;
		time = timePerFrame;
		if (actualFrame >= animation->framesCount) {
			if (repeat) {
				actualFrame = 0;
			}
			else {
				actualFrame = -1;
			}
			
		}
	}
}
