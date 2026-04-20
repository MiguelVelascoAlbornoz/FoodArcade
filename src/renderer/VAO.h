#pragma once
#include "Renderer.h"
class VAO
{
public:


	VAO();
	void initialize(float* vertices, size_t vertexCount, int* indices, size_t indexCount, std::vector<int>* attribSizes);
	void clean();
	void draw(GLenum mode);
	~VAO();


	GLuint vao;
private:
	size_t indexCount;
};

