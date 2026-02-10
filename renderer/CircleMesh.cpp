#include "CircleMesh.h"
#include <vector>
#include <cmath>
void CircleMesh::init()
{
    constexpr int segments = 32;
    std::vector<float> vertices;


    vertices.push_back(0.0f);
    vertices.push_back(0.0f);

    for(int i = 0 ; i <= segments ; i++) {
        float a = i * 2.0f * M_PI / segments;
        vertices.push_back(std::cos(a));
        vertices.push_back(std::sin(a));


    }

    vertexCount = segments + 2; // loop + center

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

void CircleMesh::draw()
{
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLE_FAN, 0, vertexCount);
    glBindVertexArray(0);
}
