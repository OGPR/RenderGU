#pragma once

#include<glad/glad.h> // Need glad before glew as it includes OpenGL headers
#include <GLFW/glfw3.h>
#include <glm/detail/type_mat.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Camera.h"

#include "Utility.h"
#include "Rendering_Common.h"
#include "input.h"
#include "models/triangle/model.h"


#define SCENERENDERFUNC(Name) \
void SceneRender_##Name (GLFWwindow* window)

SCENERENDERFUNC(TransformationMatricesInDepth)
{
    // Load Models
    Triangle triangleModel;
    triangleModel.RenderSetup();

    //// Game loop
    while (!WindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        //// input
        processInput(window,
                     DeltaTime());


        triangleModel.Render();

        //// check and call events, and swap buffers
        PollEvents();
        SwapBuffers(window);

    }

}