#include "Window.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>


Window::Window(int width, int height, const std::string &title)
    : width(width), height(height)
{
    if(!glfwInit()) {
        std::cerr << "Failed to iniate glfw\n";
        return;
    }


    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);

    if(!window) {
        std::cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        return;
    }

    glfwMakeContextCurrent(window);

    if(!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cerr << "Failed to initialize Glad\n";
        return;
    }

    glfwSetWindowUserPointer(window, this);
    glfwSetFramebufferSizeCallback(window, framebufferCallback);
    glViewport(0,0, width, height);
}

Window::~Window()
{
    glfwDestroyWindow(window);
    glfwTerminate();
}

bool Window::isOpen() const
{
    return window && !glfwWindowShouldClose(window);
}

void Window::pollEvents()
{
    glfwPollEvents();
}

void Window::swapBuffers()
{
    glfwSwapBuffers(window);
}

void Window::setResizeCallback(const std::function<void(int, int)> &callback)
{
    resizeCallback = callback;
}

void Window::framebufferCallback(GLFWwindow *win, int w, int h)
{
    auto* self = static_cast<Window*>(glfwGetWindowUserPointer(win));
    if(!self) return;


    self->width = w;
    self->height = h;


    glViewport(0,0,w,h);
    if(self->resizeCallback) {
        self->resizeCallback(w,h);
    }
}
