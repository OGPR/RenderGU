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
// Simple quad in NDC
float simpleQuad[] =
{
        // positions       // Tex coords
        -1.0f, 1.0f, 0.0f, 0.0f, 1.0f,    //top left
        1.0f, 1.0f, 0.0f, 1.0f, 1.0f,    //top right
        1.0f, -1.0f, 0.0f, 1.0f, 0.0f,	 //bottom right

        -1.0f, 1.0f, 0.0f, 0.0f, 1.0f,	 //top left
        -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,	 //bottom left
        1.0f, -1.0f, 0.0f, 1.0f, 0.0f,	 //bottom right
};

struct SimpleQuadModel
{
    int numberOfEntries = 3*5 + 3*5;
    float* data = simpleQuad;

    const char* vertexShader = vertexShaderSimpleQuad;
    const char* fragmentShader = fragmentShaderSimpleQuad;

    unsigned int ShaderProgram;
    unsigned int VAO;

    struct SimpleQuadAttributes
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

        SimpleQuadAttributes SQA;
        SetAttribute(SQA.pos.index, SQA.pos.size, SQA.pos.stride, SQA.pos.offset);
        SetAttribute(SQA.tex.index, SQA.tex.size, SQA.tex.stride, SQA.tex.offset);
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
            float scrollDistance,
            glm::mat4 model = glm::mat4(1.0f))
    {
        glUseProgram(ShaderProgram);
        glUniform1i(glGetUniformLocation(ShaderProgram, "Texture"), 9);

        GLint LocScrollDistance = glGetUniformLocation(ShaderProgram, "scrollDistance");
        if (LocScrollDistance !=-1)
        {
            glUniform1f(LocScrollDistance, scrollDistance);

        }
        else
        {
            printf("\"scrollDistance\": \n"
                   "does not correspond to an active uniform variable \n"
                   "starts with the reserved prefix \"gl_\" \n "
                   "or is associated with an atomic counter or named uniform block \n");
        }

        glUniformMatrix4fv(glGetUniformLocation(ShaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);
    }
};