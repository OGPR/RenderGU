#pragma once

#include "../../VertexSpecification_Common.h"
#include "shaders.h"
#include <glad/glad.h> // to get OpenGL includes
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Will get clash with C floor() at call site if you call it floor!
float floor_model[] =
{
    // positions		// Tex coord
    // Tri 1
    //x     y      z
    1.0f, -0.5f,  1.0f, 1.f, 0.f,    //"bottom" right
    -1.0f, -0.5f,  1.0f, 0.f, 0.f,	  //"bottom" left
    -1.0f, -0.5f, -1.0f, 0.f, 1.f,    // "top" left

    // Tri 2
    //x     y      z
    1.0f, -0.5f,  1.0f, 1.f, 0.f,    // "bottom" right"
    -1.0f, -0.5f, -1.0f, 0.f, 1.f,    // "top" left"
    1.0f, -0.5f, -1.0f, 1.f, 1.f,    // "top" right
};

struct FloorModel
{
    int numberOfEntries = 3*6 + 2*6;
    float* data = floor_model;

    const char* vertexShader = vertexShaderFloor;
    const char* fragmentShader = fragmentShaderFloor;

    unsigned int ShaderProgram;
    unsigned int VAO;

    struct FloorAttributes
    {
        struct Position
        {
            unsigned int index = 0;
            unsigned int size = 3;
            GLsizei stride = 5 * sizeof(float);
            const void* offset = 0;
        }pos;

        struct Texture
        {
            unsigned int index = 1;
            unsigned int size = 2;
            GLsizei stride = 5 * sizeof(float) ;
            const void* offset = (void * )(3 * sizeof(float));
        }tex;

    };

    void VertexSpecification()
    {

        BindVBO(CreateVBO());
        AllocateMemoryVBO(numberOfEntries, data);
        VAO = CreateVAO(); // Will be returned, and set prior to return, so need to store it here
        BindVAO(VAO);

        FloorAttributes FA;
        SetAttribute(FA.pos.index, FA.pos.size, FA.pos.stride, FA.pos.offset);
        SetAttribute(FA.tex.index, FA.tex.size, FA.tex.stride, FA.tex.offset);
    }

    void CompileShaders()
    {
        ShaderProgram = linkShaders(compileVertexShader(vertexShader),
                    compileFragmentShader(fragmentShader));
    }

    void RenderSetup()
    {
        VertexSpecification();
        CompileShaders();
    }

    void Render(
            bool visualiseDepthBuffer,
            GLubyte activeTexture,
            glm::mat4 model = glm::mat4(1.0f),
            glm::mat4 view = glm::mat4(1.0f),
            glm::mat4 projection = glm::mat4(1.0f)
    )
    {
        glUseProgram(ShaderProgram);
        glUniform1i(glGetUniformLocation(ShaderProgram, "visualiseDepthBuffer"), visualiseDepthBuffer);
        glUniformMatrix4fv(glGetUniformLocation(ShaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(glGetUniformLocation(ShaderProgram, "view"), 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(glGetUniformLocation(ShaderProgram, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
        glUniform1i(glGetUniformLocation(ShaderProgram, "Texture"), activeTexture);

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);
    }
};
