#pragma once
/**
* This is so I just don't have to write glfwInit() etc, because:
* - I find it a little hard to read
* - Since other libs like SDL etc apparently work in similar ways, we get a bit of abstraction that can help understanding
*/

#include<glad/glad.h> // Need glad before glew as it includes OpenGL headers
#include<GLFW/glfw3.h>

using Window = GLFWwindow;

int Init()
{
    return glfwInit();
}

void WindowHint(int hint, int value)
{
    glfwWindowHint(hint, value);
}

GLFWwindow* CreateWindow(int width, int height, const char* title, GLFWmonitor* monitor, GLFWwindow* share)
{
    return glfwCreateWindow(width, height, title, monitor, share);
}

void Terminate()
{
    glfwTerminate();
}

void MakeContextCurrent(GLFWwindow* window)
{
    glfwMakeContextCurrent(window);
}
GLFWframebuffersizefun SetFramebufferSizeCallback(GLFWwindow* window, void (*callback)(GLFWwindow*, int, int))
{
    return glfwSetFramebufferSizeCallback(window, callback);
}

int WindowShouldClose(GLFWwindow* window)
{
    return glfwWindowShouldClose(window);
}

void PollEvents()
{
    glfwPollEvents();
}

void SwapBuffers(GLFWwindow* window)
{
    glfwSwapBuffers(window);
}

