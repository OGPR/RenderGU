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

float simple_cube[] = {
    // positions
    -1.0f,  1.0f, -1.0f,
    -1.0f, -1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,

    -1.0f, -1.0f,  1.0f,
    -1.0f, -1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f,  1.0f,
    -1.0f, -1.0f,  1.0f,

     1.0f, -1.0f, -1.0f,
     1.0f, -1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,

    -1.0f, -1.0f,  1.0f,
    -1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f, -1.0f,  1.0f,
    -1.0f, -1.0f,  1.0f,

    -1.0f,  1.0f, -1.0f,
     1.0f,  1.0f, -1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
    -1.0f,  1.0f,  1.0f,
    -1.0f,  1.0f, -1.0f,

    -1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f,  1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f,  1.0f,
     1.0f, -1.0f,  1.0f
};

struct SimpleCubeModel
{
    int numberOfEntries = 3*6*6;
    float* data = simple_cube;

    const char* vertexShader = vertexShaderSimpleCube;
    const char* fragmentShader = fragmentShaderSimpleCube;

    unsigned int ShaderProgram;
    unsigned int VAO;

    struct Attributes
    {
        struct Position {
            unsigned int index = 0;
            unsigned int size = 3;
            GLsizei stride = 0;
            const void *offset = 0;
        } pos;
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
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
};