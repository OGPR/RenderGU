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

float line_model[] =
{
0.0f, 1.0f, 0.0f,
0.0f, -1.0f, 0.0f
};

struct LineModel
{
    int numberOfEntries = 3*2;
    float* data = line_model;

    const char* vertexShader = vertexShaderLine;
    const char* fragmentShader = fragmentShaderLine;

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
    };

    void VertexSpecification()
    {
        BindVBO(CreateVBO());
        AllocateMemoryVBO(numberOfEntries, data);
        VAO = CreateVAO(); // Will be returned, and set prior to return, so need to store it here
        BindVAO(VAO);

        Attributes A;
        SetAttribute(A.pos.index, A.pos.size, A.pos.stride, A.pos.offset);
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
            glm::vec3 color,
            glm::mat4 model = glm::mat4(1.0f),
            glm::mat4 view = glm::mat4(1.0f),
            glm::mat4 projection = glm::mat4(1.0f)
    )
    {
        glUseProgram(ShaderProgram);
        glUniform3fv(glGetUniformLocation(ShaderProgram, "color"), 1, glm::value_ptr(color));
        glUniformMatrix4fv(glGetUniformLocation(ShaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(glGetUniformLocation(ShaderProgram, "view"), 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(glGetUniformLocation(ShaderProgram, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

        glBindVertexArray(VAO);
        glLineWidth(5.f);
        glDrawArrays(GL_LINE_STRIP, 0, 2);
    }
};


