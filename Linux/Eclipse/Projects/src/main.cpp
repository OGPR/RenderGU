//============================================================================
// Name        : main.cpp
// Author      : 
// Copyright   : Your copyright notice
// Description :
//============================================================================


#include "Window.h"
#include "Rendering_Common.h"
#include "scenes/CubeGrassWindowFloor/scene_render.h"
#include "scenes/Skybox/scene_render.h"
#include "models/line/model.h"


// To resize viewport whenever window is resized - define a callback (with following signature)
void framebuffer_size_callback(GLFWwindow* window, int newWidth, int newHeight)
{
    //Note--- this will change viewport location to have lower left corner at (0,0) (how to change this?)
    glViewport(0, 0, newWidth, newHeight);
}

int main()
{
    GLFWwindow* window = Window();

    // Set up axis lines
    LineModel axisX, axisY, axisZ;
    axisX.RenderSetup();
    axisY.RenderSetup();
    axisZ.RenderSetup();

    glm::mat4 modelMat_x(1.0f);
    glm::mat4 modelMat_z(1.0f);
    glm::mat4 modelMat_y(1.0f);
    modelMat_y = glm::translate(modelMat_y, glm::vec3(0.f, 0.f, -1.f));
    modelMat_x = glm::translate(modelMat_x, glm::vec3(0.f, 0.f, -1.f));
    modelMat_x = glm::rotate(modelMat_x, glm::half_pi<float>(), glm::vec3(0.f, 0.f, 1.f));
    modelMat_z = glm::translate(modelMat_z, glm::vec3(0.f, 0.f, -1.f));
    // Offsets to see the axis when axis lines fixed
    modelMat_z = glm::rotate(modelMat_z, glm::half_pi<float>() +0.01f  , glm::vec3(1.f, 0.0001f, 0.f));

    glm::vec3 color_x(1.f, 0.f, 0.f);
    glm::vec3 color_y(0.f, 1.f, 0.f);
    glm::vec3 color_z(0.f, 0.f, 1.f);

    glm::mat4 view(1.f);
    glm::mat4 projection;
    projection = glm::perspective(glm::radians(45.f), 800.f/600.f, 0.1f, 100.f);

    CameraVariables cameraVariables;

    // Test model
    CubeModel cubeModel;
    cubeModel.RenderSetup();



    while(!WindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);


        processInputCamera(window,
                           &cameraVariables,
                           DeltaTime());

        processInput(window,
                     DeltaTime());



        view = glm::mat4(1.0f);
        axisX.Render(color_x, modelMat_x, view, projection);
        axisY.Render(color_y, modelMat_y, view, projection);
        axisZ.Render(color_z, modelMat_z, view, projection);

        view = glm::lookAt(cameraVariables.cameraPos,
                           cameraVariables.cameraPos + cameraVariables.cameraLookDirection, cameraVariables.cameraUp);
        cubeModel.Render(9, false, glm::mat4(1.0f), view, projection);

        //// check and call events, and swap buffers
        PollEvents();
        SwapBuffers(window);
    }

    //SceneRender_CubeGrassWindowFloor(window);
    //SceneRender_Skybox(window);

    Terminate();
    return 0;





}
