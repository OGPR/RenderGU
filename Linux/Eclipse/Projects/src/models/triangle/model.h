#pragma once

#include "../../VertexSpecification_Common.h"
#include "shaders.h"
#include "CompileShaders.h"
#include "LinkShaders.h"
#include <glad/glad.h> // to get OpenGL includes
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

float triangle[] =
{
    -0.5f, -0.5f, 0.0f, // lower-left
    0.0f, 0.5f, 0.0f,   // top-center
    0.5f, -0.5f, 0.0f,  // lower-right
    1.f, 0.f, 0.f,    // Colors
    0.f, 1.f, 0.f,
    0.f, 0.f, 1.f
};

struct Triangle
{
    int numberOfEntries = 3*6;
    float* data = triangle;

    const char* vertexShader = vertexShaderTriangle;
    const char* fragmentShader = fragmentShaderTriangle;

    unsigned int ShaderProgram;
    unsigned int VAO;

    struct Attributes
    {
        struct Position
        {
            unsigned int index = 0;
            unsigned int size = 3;
            GLsizei stride = 0;
            const void* offset = 0;
        }pos;

        struct Color
        {
            unsigned int index = 1;
            unsigned int size = 3;
            GLsizei stride = 0 ;
            const void* offset = (void * )(9 * sizeof(float));
        }color;
    };

    void VertexSpecification()
    {

        BindVBO(CreateVBO());
        AllocateMemoryVBO(numberOfEntries, data);
        VAO = CreateVAO(); // Will be returned, and set prior to return, so need to store it here
        BindVAO(VAO);

        Attributes A;
        SetAttribute(A.pos.index, A.pos.size, A.pos.stride, A.pos.offset);
        SetAttribute(A.color.index, A.color.size, A.color.stride, A.color.offset);
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
            glm::mat4 model = glm::mat4(1.0f),
            glm::mat4 view = glm::mat4(1.0f),
            glm::mat4 projection = glm::mat4(1.0f)
    )
    {
        glUseProgram(ShaderProgram);
        glUniformMatrix4fv(glGetUniformLocation(ShaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(glGetUniformLocation(ShaderProgram, "view"), 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(glGetUniformLocation(ShaderProgram, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
    }
};