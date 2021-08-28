#include "Utility.h"
#include "Rendering.h"
#include <iostream>
#include "Shaders.h"
#include "CompileShaders.h"
#include "LinkShaders.h"
#include "data.h"


// To resize viewport whenever window is resized - define a callback (with following signature)
void framebuffer_size_callback(GLFWwindow* window, int newWidth, int newHeight)
{
    //Note--- this will change viewport location to have lower left corner at (0,0) (how to change this?)
    glViewport(0, 0, newWidth, newHeight);
}

void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

int main()
{
    Init();
    WindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    WindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    WindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    Window* window = CreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (!window)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        Terminate();
        return -1;
    }

    MakeContextCurrent(window);

    
    int gladInitialise = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    if (!gladInitialise)
    {
        std::cout << "Failed to initialise GLAD" << std::endl;
        std::cout << "Perhaps you have not called a \"MakeContextCurrent(window) \" function prior?" << std::endl;
        return -1;
    }

    Viewport viewport;
    viewport.LowerLeftX = 0;
    viewport.LowerLeftY = 0;
    viewport.Width = /*0.9 */ 800;
    viewport.Height = /*0.9 */ 600;

    glViewport(viewport.LowerLeftX, viewport.LowerLeftY, viewport.Width, viewport.Height);


    unsigned int shaderProgram = linkShaders(
        compileVertexShader(vertexShaderSource),
        compileFragmentShader(fragmentShaderSource));

    unsigned int VAO = render_setup(vertex);


    // Game loop
    GLfloat colorChannelValues[3] = { 0.f, 0.f, 0.f };
    GLboolean change = true;
    GLint64 frameNumber = 0;
    while (!WindowShouldClose(window))
    {
        //// input
        processInput(window);

        // clear results from previous frame (iteration of loop)
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        //// rendering (note this has to be after clear!)
        render_draw(shaderProgram, VAO, colorChannelValues);
        if (change)
        {
            colorChannelValues[0] = 1.f;
            colorChannelValues[1] = 1.f;
            colorChannelValues[2] = 1.f;
        }
        else
        {
            colorChannelValues[0] = 0.f;
            colorChannelValues[1] = 0.f;
            colorChannelValues[2] = 0.f;
        }
        if (++frameNumber % 20 == 0)
        {
            change = !change;
        }

        //// check and call events, and swap buffers
        PollEvents();
        SwapBuffers(window);
    }


    Terminate();
    return 0;
}