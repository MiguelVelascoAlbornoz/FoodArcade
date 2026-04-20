#include "Animation.h"


Animation::Animation(std::string name, int framesCount)
{
	
	for (int i = 0; i < framesCount; ++i) {
		Image* image = new Image(name + "/" + to_string(i) + ".png",false);
		frames.push_back(image);
	}

	this->framesCount = framesCount;
}

Animation::~Animation()
{
	for (int i = 0; i < frames.size(); ++i) {
		delete frames[i];
	}
}
