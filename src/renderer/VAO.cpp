#include "VAO.h"

VAO::VAO()
{

}
void VAO::initialize(float* vertices, size_t vertexCount, int* indices, size_t indexCount, std::vector<int>* attribSizes ) {
    this->indexCount = indexCount;
    int attribCount = attribSizes->size();
    int stride = 0;
    for (int i = 0; i < attribCount; ++i) {
        stride += ((*attribSizes)[i]);
    }
    GLuint VBO, EBO;
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertexCount * sizeof(float), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount * sizeof(unsigned int), indices, GL_STATIC_DRAW);
    int offset = 0;
    for (int i = 0; i < attribCount; ++i) {
        int attribSize = ((*attribSizes)[i]);
        glVertexAttribPointer(i, attribSize, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*)(offset * sizeof(float)));
        glEnableVertexAttribArray(i);
        offset += attribSize;

    }



    glBindVertexArray(0);

    //  
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}
void VAO::clean()
{
    glDeleteVertexArrays(1, &vao);
    indexCount = 0;
}
void VAO::draw(GLenum mode) {
    glBindVertexArray(vao);
    glDrawElements(mode, indexCount, GL_UNSIGNED_INT, 0);
}
VAO::~VAO()
{

    glDeleteVertexArrays(1, &vao);
}


