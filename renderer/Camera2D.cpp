#include "Camera2D.h"
#include <glm/gtc/matrix_transform.hpp>
Camera2D::Camera2D(float width, float height) :
    width(width), height(height)
{
    recomputeMatrix();
}

void Camera2D::setPosition(const glm::vec2 &pos)
{
    position = pos;
    recomputeMatrix();
}

void Camera2D::setZoom(float z)
{
    zoom = z;
    recomputeMatrix();
}

void Camera2D::resize(float w, float h)
{
    width = w;
    height = h;
    recomputeMatrix();
}

const glm::mat4 &Camera2D::getViewProjection() const
{
    return viewProj;
}

void Camera2D::recomputeMatrix()
{
    float aspect = width/height;

    glm::mat4 proj = glm::ortho(-aspect * zoom,
                                aspect * zoom,
                                -zoom,
                                zoom,
                                -1.0f,
                                1.0f);

    glm::mat4 view = glm::translate(glm::mat4{1.0f}, glm::vec3(-position, 0.0f));


    viewProj = proj * view;
}
