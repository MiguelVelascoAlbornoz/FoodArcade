#include "Image.h"




#define _CRT_SECURE_NO_WARNINGS
#define STB_IMAGE_IMPLEMENTATION


// Simple helper function to load an image into a OpenGL texture with common settings

Image::Image(string texturePath)
{
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	/**/float borderColor[] = {1.0f, 0.0f, 0.0f, 0.0f}; // Color rojo, por ejemplo
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);  // Para textura m�s n�tida
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	int chanels = 3;
	unsigned char* data = stbi_load(("assets/textures/" + texturePath).c_str(), &width, &height, &chanels, 0);

	GLenum format = (chanels == 4) ? GL_RGBA : GL_RGB;
	if (data) {

		glTexImage2D(GL_TEXTURE_2D, 0, format, width , height , 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		printf("%s",texturePath.c_str());
		cout << "Failed to load texture" << endl;
	}
	stbi_image_free(data);
}
Image::Image(string path, bool isAnimation)
{
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	/**/float borderColor[] = { 1.0f, 0.0f, 0.0f, 0.0f }; // Color rojo, por ejemplo
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);  // Para textura m�s n�tida
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	int chanels = 3;
	unsigned char* data = stbi_load(("assets/animations/" + path).c_str(), &width, &height, &chanels, 0);

	GLenum format = (chanels == 4) ? GL_RGBA : GL_RGB;
	if (data) {

		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		printf("%s", path.c_str());
		cout << "Failed to load texture" << endl;
	}
	stbi_image_free(data);
}
Image::Image(string texturePath,GLint param)
{
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	/**/float borderColor[] = { 1.0f, 0.0f, 0.0f, 0.0f }; // Color rojo, por ejemplo
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, param);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, param);
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);  // Para textura m�s n�tida
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	int chanels = 3;
	unsigned char* data = stbi_load(("assets/textures/" + texturePath).c_str(), &width, &height, &chanels, 0);

	GLenum format = (chanels == 4) ? GL_RGBA : GL_RGB;
	if (data) {

		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		printf("%s", texturePath.c_str());
		cout << "Failed to load texture" << endl;
	}
	stbi_image_free(data);
}
void Image::bindTexture(GLenum textureUnit,Shader* shader, const char* name) {
	glActiveTexture(textureUnit + GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	shader->uniform1i(name, textureUnit);
}

Image::~Image()
{
	glDeleteTextures(1, &texture);
}
