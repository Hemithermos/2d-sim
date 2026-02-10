#pragma once 
#include <glad/glad.h>
class CircleMesh {
public:
    void init();
    void draw();


private:
    GLuint vao = 0;
    GLuint vbo = 0;
    int vertexCount = 0;
};