#pragma once
#include "glm/glm.hpp"
#include "Camera2D.h"
#include "Shader.h"
#include "CircleMesh.h"
#include "BackgroundMesh.h"
#include "../platform/Window.h"
class Renderer {
public:
    Renderer(int w, int h);
    void resize(float width, float height);
    void beginFrame(Window*);
    void endFrame(Window*);


    void drawCircle(const glm::vec3& pos, float radius, const glm::vec4 color);
    void drawBackground();

    Camera2D& getCamera() {return camera;}
private:
    Camera2D camera;
    CircleMesh circle;
    BackgroundMesh background;
    Shader circleShader;
    Shader bgShader;

};