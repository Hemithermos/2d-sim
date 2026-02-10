#pragma once

#include <glm/glm.hpp>

class Camera2D {
public:
    Camera2D(float width, float height);
    void setPosition(const glm::vec2& pos);

    void setZoom(float zoom);

    void resize(float width, float height);

    const glm::mat4& getViewProjection() const;


private:
    void recomputeMatrix();
    glm::vec2 position{0.0f};
    float zoom = 1.0f;
    float width;
    float height;
    glm::mat4 viewProj{1.0f};

};