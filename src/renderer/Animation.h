#pragma once
#include "Image.h"
class Animation
{
public:
	Animation(std::string name,int framesCount);
	~Animation();

	int framesCount;
	std::vector<Image*> frames;
};

