#pragma once

#include<glad/glad.h> // Need glad before glew as it includes OpenGL headers
#include <GLFW/glfw3.h>
#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#endif
#include <glm/detail/type_mat.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Camera.h"

#include "Utility.h"
#include "Rendering_Common.h"
#include "input.h"
#include "models/simple_cube/model.h"


#define SCENERENDERFUNC(Name) \
void SceneRender_##Name (GLFWwindow* window)

SCENERENDERFUNC(Skybox)
{
    // Setup textures
    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

    int width, height, nChannels;
    GLubyte* data;
    const char* faceTextures [6] =
    {
         "right.jpg",
         "left.jpg",
         "top.jpg",
         "bottom.jpg",
         "front.jpg",
         "back.jpg"
    };

    for (GLubyte i = 0; i < 6; ++i)
    {
        data = stbi_load(faceTextures[i], &width, &height, &nChannels, 0);

        if (!data)
        {
            printf("Failed to load texture ", faceTextures[i]);
            stbi_image_free(data);
            continue;
        }

        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                     0,
                     GL_RGB,
                     width,
                     height,
                     0,
                     GL_RGB,
                     GL_UNSIGNED_BYTE,
                     data);

    }

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    // Load Models
    SimpleCubeModel simpleCubeModel;
    simpleCubeModel.RenderSetup();

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
        view = glm::mat4(glm::mat3(view));
        model = glm::mat4(1.0f);
        model = glm::scale(model, glm::vec3(1.0f));
        simpleCubeModel.Render(model,
                               view,
                               projection);

        //// check and call events, and swap buffers
        PollEvents();
        SwapBuffers(window);

    }

}