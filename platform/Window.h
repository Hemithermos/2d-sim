#pragma once

#include <string>
#include <functional>


struct GLFWwindow;


class Window {
public:
    Window(int width, int height, const std::string& title);
    ~Window();

    bool isOpen() const;
    void pollEvents();
    void swapBuffers();


    int getWidth() const {return width;}
    int getHeight() const {return height;}


    void setResizeCallback(const std::function<void(int, int)>& callback);

    GLFWwindow* getNativeHandle() const {return window;}


private:
    GLFWwindow* window = nullptr;
    int width = 0;
    int height = 0;


    static void framebufferCallback(GLFWwindow* window, int w, int h);
    std::function<void(int, int)> resizeCallback;
};