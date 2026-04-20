#pragma once
#include "Shaders.h"

using namespace std;
class Image
{
public:
	int width, height;
	Image(string texturePath);
	Image(string path, bool isAnimation);
	Image(string texturePath, GLint param);
	void bindTexture(GLenum textureUnit, Shader* shader, const char* name);

	~Image();
	unsigned int texture;

private:

};

