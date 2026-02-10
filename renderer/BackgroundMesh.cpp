#include "BackgroundMesh.h"
#include <vector>
#include <cmath>
void BackgroundMesh::init()
{
    std::vector<float> vertices = {
        -8.0f, -4.5f,
         8.0f, -4.5f,
         8.0f,  4.5f,
        -8.0f,  4.5f};
    vertexCount = 4;




    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);


    glBufferData(
        GL_ARRAY_BUFFER,
        vertices.size() * sizeof(float),
        vertices.data(),
        GL_STATIC_DRAW
    );

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), nullptr);
    glBindVertexArray(0);

}

void BackgroundMesh::draw()
{
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLE_FAN, 0, vertexCount);

    glBindVertexArray(0);
}