#pragma once

#include <GLFW/glfw3.h>

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
#include "Textures.h"
#include "VertexSpecification_Common.h"
#include <assert.h>
#include "Camera.h"
#include "Window.h"
#include "models/floor/model.h"
#include "models/floor/shaders.h"
#include "Rendering_Common.h"
#include "models/simple_quad/model.h"

#define SCENERENDERFUNC(Name) \
void SceneRender_##Name (GLFWwindow* window)

SCENERENDERFUNC(CubeGrassWindowFloor)
{
    //Register models
    FloorModel floorModel;
    floorModel.RenderSetup();

    SimpleQuadModel simpleQuadModel;
    simpleQuadModel.RenderSetup();




    unsigned int shaderProgram_Cube_no_mix = linkShaders(
            compileVertexShader(vertexShaderSource_Cube),
            compileFragmentShader(fragmentShaderSource_Cube_no_mix));

    unsigned int shaderProgram_Cube_SingleColor = linkShaders(
            compileVertexShader(vertexShaderSource_Cube),
            compileFragmentShader(fragmentShaderSingleColor));



    unsigned int VAO_Cube = render_setup_cube(cube, 5*6*6);




    //** Begin Quad stuff
    unsigned int VAO_Quad = vs_quad(quad, 3*5 + 3*5);


    unsigned int shaderProgram_Rect_Transparency = linkShaders(
            compileVertexShader(vertexShaderSource_Rect_Transparency),
            compileFragmentShader(fragmentShaderSource_Rect_Transparency));

    //** End Quad stuff

    //** Begin window stuff
    // Re-using quad VSpec
    unsigned int VAO_Window = vs_quad(quad, 3*5 + 3*5);

    // Re-using quad VShader
    unsigned int shaderProgram_Rect_Window = linkShaders(
            compileVertexShader(vertexShaderSource_Rect_Transparency),
            compileFragmentShader(fragmentShaderSource_Rect_window));

    //** End window stuff

    unsigned int textureTarget = 0;
    textureSetup(&textureTarget);


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





    // From print statements in loop below
    // Set up camera for depth/stencil buffer work
    CameraVariables cameraVariables;
    cameraVariables.cameraPos = glm::vec3(-3.255120, 0.596114, -0.690018);
    cameraVariables.cameraLookDirection = glm::vec3(0.972760, -0.231807, -0.001899);
    cameraVariables.cameraCurrRotAngle = glm::vec3(1.804731, 1.572749, 0.000000);
    cameraVariables.cameraYaw = cameraVariables.cameraCurrRotAngle.y;
    cameraVariables.cameraPitch = cameraVariables.cameraCurrRotAngle.x;




    glEnable(GL_STENCIL_TEST);

    GLuint fbo;
    glGenFramebuffers(1,&fbo);

    // Render buffer attachment
    GLuint fbo_1; // New framebuffer to attach to
    glGenFramebuffers(1,&fbo_1);
    GLuint rbo;
    glGenRenderbuffers(1,&rbo);

    float scrollDistance = 0.f;

    //// Game loop
    while (!WindowShouldClose(window))
    {
        //// input
        processInputCamera(window,
                           &cameraVariables,
                           DeltaTime());
        processInput(window,
                     DeltaTime());

        ////---- 1st pass - off-screen render------

        printf("tex target1\n");
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
        glBindFramebuffer(GL_FRAMEBUFFER, fbo);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureTarget, 0);

        // Create renderbuffer for attaching depth to currently bound framebuffer
        glBindRenderbuffer(GL_RENDERBUFFER, rbo);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, 800, 600);
        assert(glGetError() == 0);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);
        CheckFramebufferStatus();



        if (depthTest)
        {
            glEnable(GL_DEPTH_TEST);

        }
        else
            glDisable(GL_DEPTH_TEST);

        // clear results from previous frame (iteration of loop)
        //glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glStencilMask(0xFF); // make sure stencil  buffer is writable before clearing
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);




        // To look behind, we have the rear-view at same pos, but looking the opposite way
        // Changing the camera look direction via pitch will give the desired result.
        UpdateCameraLookDirection(&cameraVariables.cameraLookDirection,
                                  &cameraVariables.cameraYaw,
                                  &cameraVariables.cameraPitch,
                                  &cameraVariables.cameraPitch,
                                  glm::pi<float>());

        view = glm::lookAt(cameraVariables.cameraPos,
                           cameraVariables.cameraPos + cameraVariables.cameraLookDirection,
                           cameraVariables.cameraUp);

        // Reset look direction to original
        UpdateCameraLookDirection(&cameraVariables.cameraLookDirection,
                                  &cameraVariables.cameraYaw,
                                  &cameraVariables.cameraPitch,
                                  &cameraVariables.cameraPitch,
                                  -glm::pi<float>());


        // Write to stencil buffer where desired
        // Cube 1
        glStencilFunc(GL_ALWAYS, 1, 0xFF);
        glStencilMask(0xFF);
        glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
        model = glm::mat4(1.f);
        model = glm::translate(model, glm::vec3(-1.0f, 0.0f, -1.0f));
        render_draw_cube(
                shaderProgram_Cube_no_mix,
                VAO_Cube,
                visualiseDepthBuffer,
                0,
                model,
                view,
                projection);

        // Cube 2
        glEnable(GL_CULL_FACE);
        model = glm::mat4(1.f);
        model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
        render_draw_cube(
                shaderProgram_Cube_no_mix,
                VAO_Cube,
                visualiseDepthBuffer,
                0,
                model,
                view,
                projection);

        glDisable(GL_CULL_FACE);

        // Floor
        glStencilMask(0x00); // only cubes for now
        model = glm::mat4(1.f);
        model = glm::scale(model, glm::vec3(5.f, 1.f, 5.f));



        floorModel.Render(visualiseDepthBuffer,
               5,
                           model,
                           view,
                           projection);


        if (stencilTest)
        {
            // Another render pass, borders/outlining
            // Cube 1
            glStencilFunc(GL_NOTEQUAL, 1 , 0xFF);
            //glStencilMask(0xFF);
            //glDisable(GL_DEPTH_TEST);
            glDepthFunc(GL_LESS);
            float scale = 1.1f;

            model = glm::mat4(1.f);
            model = glm::translate(model, glm::vec3(-1.0f, 0.0f, -1.0f));
            model = glm::scale(model, glm::vec3(scale, scale, scale));
            render_draw_cube(
                    shaderProgram_Cube_SingleColor,
                    VAO_Cube,
                    visualiseDepthBuffer,
                    0,
                    model,
                    view,
                    projection);
            glDepthFunc(GL_LESS);

            // Cube 2
            model = glm::mat4(1.f);
            model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
            model = glm::scale(model, glm::vec3(scale, scale, scale));
            render_draw_cube(
                    shaderProgram_Cube_SingleColor,
                    VAO_Cube,
                    visualiseDepthBuffer,
                    0,
                    model,
                    view,
                    projection);
            //glEnable(GL_DEPTH_TEST);

            // Floor
            model = glm::mat4(1.f);
            model = glm::scale(model, glm::vec3(5.f, 1.f, 5.f));
            floorModel.Render(visualiseDepthBuffer,
                   5,
                               model,
                               view,
                               projection);
        }

        // Transparency
        render_draw_rect_transparency(
                shaderProgram_Rect_Transparency,
                VAO_Quad,
                modelQuad,
                view,
                projection
        );

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        render_draw_rect_window(
                shaderProgram_Rect_Window,
                VAO_Window,
                modelWindow,
                view,
                projection
        );
        glDisable(GL_BLEND);


        /// Rendering scene as normal

        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);


        view = glm::lookAt(cameraVariables.cameraPos,
                           cameraVariables.cameraPos + cameraVariables.cameraLookDirection,
                           cameraVariables.cameraUp);

        // Write to stencil buffer where desired
        // Cube 1
        glStencilFunc(GL_ALWAYS, 1, 0xFF);
        glStencilMask(0xFF);
        glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
        model = glm::mat4(1.f);
        model = glm::translate(model, glm::vec3(-1.0f, 0.0f, -1.0f));
        render_draw_cube(
                shaderProgram_Cube_no_mix,
                VAO_Cube,
                visualiseDepthBuffer,
                0,
                model,
                view,
                projection);

        // Cube 2
        glEnable(GL_CULL_FACE);
        model = glm::mat4(1.f);
        model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
        render_draw_cube(
                shaderProgram_Cube_no_mix,
                VAO_Cube,
                visualiseDepthBuffer,
                0,
                model,
                view,
                projection);

        glDisable(GL_CULL_FACE);

        // Floor
        glStencilMask(0x00); // only cubes for now
        model = glm::mat4(1.f);
        model = glm::scale(model, glm::vec3(5.f, 1.f, 5.f));



        floorModel.Render(visualiseDepthBuffer,
                          5,
                          model,
                          view,
                          projection);


        if (stencilTest)
        {
            // Another render pass, borders/outlining
            // Cube 1
            glStencilFunc(GL_NOTEQUAL, 1 , 0xFF);
            //glStencilMask(0xFF);
            //glDisable(GL_DEPTH_TEST);
            glDepthFunc(GL_LESS);
            float scale = 1.1f;

            model = glm::mat4(1.f);
            model = glm::translate(model, glm::vec3(-1.0f, 0.0f, -1.0f));
            model = glm::scale(model, glm::vec3(scale, scale, scale));
            render_draw_cube(
                    shaderProgram_Cube_SingleColor,
                    VAO_Cube,
                    visualiseDepthBuffer,
                    0,
                    model,
                    view,
                    projection);
            glDepthFunc(GL_LESS);

            // Cube 2
            model = glm::mat4(1.f);
            model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
            model = glm::scale(model, glm::vec3(scale, scale, scale));
            render_draw_cube(
                    shaderProgram_Cube_SingleColor,
                    VAO_Cube,
                    visualiseDepthBuffer,
                    0,
                    model,
                    view,
                    projection);
            //glEnable(GL_DEPTH_TEST);

            // Floor
            model = glm::mat4(1.f);
            model = glm::scale(model, glm::vec3(5.f, 1.f, 5.f));

            floorModel.Render(visualiseDepthBuffer,
                              5,
                              model,
                              view,
                              projection);

        }

        // Transparency
        render_draw_rect_transparency(
                shaderProgram_Rect_Transparency,
                VAO_Quad,
                modelQuad,
                view,
                projection
        );

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        render_draw_rect_window(
                shaderProgram_Rect_Window,
                VAO_Window,
                modelWindow,
                view,
                projection
        );
        glDisable(GL_BLEND);



        ////---- On Screen render pass - render simple quad with scene texture
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        //CheckFramebufferStatus();

        glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // non-black, to see wireframe
        glDisable(GL_DEPTH_TEST); //TODO: needed?

        //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        //scrollDistance += 0.1f * deltaTime;

        scrollDistance = 0.0f;

        model = glm::translate(model, glm::vec3(0.f, 0.7f, 0));
        model = glm::scale(model, glm::vec3(0.1f, 0.2f, 0));

        simpleQuadModel.Render(scrollDistance,
                               model);





        //// check and call events, and swap buffers
        PollEvents();
        SwapBuffers(window);
    }



}