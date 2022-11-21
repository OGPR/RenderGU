#pragma once
#include <glad/glad.h> // to get OpenGL includes
#include <GLFW/glfw3.h>
#include "Utility.h"
#include <iostream>

/**
* The rendering window
*/
struct Viewport
{
    GLint LowerLeftX = 0;
    GLint LowerLeftY = 0;
    GLsizei Width = 0;
    GLsizei Height = 0;
};

GLFWwindow* Window(int WindowWidth,
                   int WindowHeight,
                   const char* WindowTitle,
                   int WindowXPos = 2000,
                   int WindowYPos = 250)
{
    Init();
    WindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    WindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    WindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = CreateWindow(WindowWidth, WindowHeight, WindowTitle, NULL, NULL);
    glfwSetWindowPos(window, WindowXPos, WindowYPos);
    if (!window)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        Terminate();
        return nullptr;
    }

    MakeContextCurrent(window);
    //SetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    //SetCursorPosCallback(window, mouse_callback);


    int gladInitialise = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    if (!gladInitialise)
    {
        std::cout << "Failed to initialise GLAD" << std::endl;
        std::cout << "Perhaps you have not called a \"MakeContextCurrent(window) \" function prior?" << std::endl;
        return nullptr;
    }

    Viewport viewport;
    viewport.LowerLeftX = 0;
    viewport.LowerLeftY = 0;
    viewport.Width = WindowWidth;
    viewport.Height = WindowHeight;

    glViewport(viewport.LowerLeftX, viewport.LowerLeftY, viewport.Width, viewport.Height);

    return window;
}
