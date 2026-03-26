#pragma once 
#include <glad/glad.h>
#include "../settings/Settings.h"
class BackgroundMesh {
public:
    void init();
    void draw();


private:
    GLuint vao = 0;
    GLuint vbo = 0;
    int vertexCount = 0;
};