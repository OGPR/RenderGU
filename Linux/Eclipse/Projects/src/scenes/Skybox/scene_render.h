#pragma once

#include<glad/glad.h> // Need glad before glew as it includes OpenGL headers
#include <GLFW/glfw3.h>
#include <glm/detail/type_mat.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Camera.h"

#include "Utility.h"
#include "Rendering_Common.h"
#include "input.h"
#include "models/skybox/model.h"
#include "setup_cubemap.h"
#include "models/cube/model.h"


#define SCENERENDERFUNC(Name) \
void SceneRender_##Name (GLFWwindow* window)

SCENERENDERFUNC(Skybox)
{
    unsigned int cubemapTex = setupCubemap();

    // Load Models
    SimpleCubeModel simpleCubeModel;
    simpleCubeModel.RenderSetup();

    FloorModel floorModel;
    floorModel.RenderSetup();

    CubeModel cubeModel;
    cubeModel.RenderSetup();

    //// Transformations
    glm::mat4 model(1.f);
    glm::mat4 view(1.f);
    glm::mat4 projection;
    projection = glm::perspective(glm::radians(45.f), 800.f/600.f, 0.1f, 100.f);

    CameraVariables cameraVariables;

    //Start inside the skybox
    cameraVariables.cameraPos = glm::vec3(0.f);

    //// Game loop
    while (!WindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        //// input
        processInputCamera(window,
                           &cameraVariables,
                           DeltaTime());
        processInput(window,
                     DeltaTime());

        view = glm::lookAt(cameraVariables.cameraPos,
                           cameraVariables.cameraPos + cameraVariables.cameraLookDirection,
                           cameraVariables.cameraUp);

        // Remove translation, keep rotation
        glm::mat4 skyboxView = glm::mat4(glm::mat3(view));
        model = glm::mat4(1.0f);
        model = glm::scale(model, glm::vec3(1.0f));

        simpleCubeModel.Render(cubemapTex,
                               model,
                               skyboxView,
                               projection);

        floorModel.Render(visualiseDepthBuffer,
                          5,
                          model,
                          view,
                          projection);

        cubeModel.Render(5,
                         visualiseDepthBuffer,
                         model,
                         view,
                         projection);

        //// check and call events, and swap buffers
        PollEvents();
        SwapBuffers(window);

    }

}