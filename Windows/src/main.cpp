//============================================================================
// Name        : main.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description :
//============================================================================


#include "Utility.h"
#include "Rendering.h"
#include <iostream>
#include "Shaders.h"
#include "CompileShaders.h"
#include "LinkShaders.h"
#include "data.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/constants.hpp>
#include "input.h"
#include <assert.h>

// To resize viewport whenever window is resized - define a callback (with following signature)
void framebuffer_size_callback(GLFWwindow* window, int newWidth, int newHeight)
{
    //Note--- this will change viewport location to have lower left corner at (0,0) (how to change this?)
    glViewport(0, 0, newWidth, newHeight);
}

int main()
{
    Init();
    WindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    WindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    WindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    Window* window = CreateWindow(800, 600, "RenderGU_Win0", NULL, NULL);
    if (!window)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        Terminate();
        return -1;
    }

    MakeContextCurrent(window);
    //SetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    //SetCursorPosCallback(window, mouse_callback);


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


    unsigned int shaderProgram_Tri = linkShaders(
        compileVertexShader(vertexShaderSource_Tri),
        compileFragmentShader(fragmentShaderSource_Tri));

    unsigned int VAO_Triangle = render_setup_tri(triangle, 18);

    unsigned int shaderProgram_Point = linkShaders(
        compileVertexShader(vertexShaderSource_Point),
        compileFragmentShader(fragmentShaderSource_Point));

    unsigned int VAO_Point = render_setup_tri(triangle, 3);



	//// Transformations
	glm::mat4 model(1.f);
	glm::mat4 view(1.f);
	glm::mat4 projection;
	projection = glm::perspective(glm::radians(45.f), 800.f/600.f, 0.1f, 100.f);

	/// Model specific transformations
	// Those we don't expect to change between frames, so set them one here
	glm::mat4 modelQuad(1.f);
	modelQuad = glm::rotate(modelQuad, glm::half_pi<float>(), glm::vec3(0.f, 1.f, 0.f));
	// modelcoords have been rotated, so keep that in mind on translation
	// Apply offset in z to prevent z-figting
	modelQuad = glm::translate(modelQuad, glm::vec3(0.5f, 0.f,-1.51f));

	glm::mat4 modelWindow(1.f);
	modelWindow = glm::rotate(modelWindow, glm::half_pi<float>(), glm::vec3(0.f, 1.f, 0.f));
	modelWindow = glm::translate(modelWindow, glm::vec3(0.5f, 0.f,-1.8f));

    // Frame time management variables
    float currFrameTime;
    float lastFrameTime = 0.f;
    float deltaTime;


    // Game loop
    while (!WindowShouldClose(window))
    {


		view = glm::lookAt(cameraPos, cameraPos + cameraLookDirection, cameraUp);
        render_draw(shaderProgram_Point, VAO_Point, false);



        //// check and call events, and swap buffers
        PollEvents();
        SwapBuffers(window);
    }


    Terminate();
    return 0;
}