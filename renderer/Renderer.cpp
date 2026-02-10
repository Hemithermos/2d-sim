#include "Renderer.h"



Renderer::Renderer(int w, int h)
    : camera((float)w, (float)h)
{
    circle.init();
    background.init();
    circleShader.load("assets/shaders/circle.vert", "assets/shaders/circle.frag");
    bgShader.load("assets/shaders/background.vert", "assets/shaders/background.frag");
    camera.setPosition(glm::vec2(0.0f, 0.0f));
    camera.setZoom(5.0f);
}


void Renderer::resize(float width, float height)
{
    glViewport(0,0, (int)width, (int)height);
    camera.resize(width, height);
}

void Renderer::beginFrame(Window* win)
{
    glViewport(0, 0, win->getWidth(), win->getHeight());
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::endFrame(Window* window)
{
    window->swapBuffers();
    window->pollEvents();
}

void Renderer::drawCircle(const glm::vec3 &pos, float radius, const glm::vec4 color)
{
    circleShader.use();
    circleShader.setMat4("u_ViewProj", camera.getViewProjection());
    circleShader.setVec2("u_Position", glm::vec2(pos.x, pos.y));
    circleShader.setFloat("u_Radius", radius);
    circleShader.setVec4("u_Color", color);

    circle.draw();

}

void Renderer::drawBackground()
{
    bgShader.use();
    bgShader.setMat4("uVP", camera.getViewProjection());
    bgShader.setVec3("uColor", glm::vec3(0.2f,0.2f,0.2f));

    background.draw();
}
