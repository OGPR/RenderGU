#pragma once
#include <GLAD/glad.h> // to get OpenGL includes
#include <iostream>
#include "data.h"

/**
* The rendering window
*/
struct Viewport
{
    GLint LowerLeftX = 0;
    GLint LowerLeftY = 0;
    GLsizei Width = 0;
    GLsizei Height = 0;
};

unsigned int render_setup(float* vertex)
{
    ////// Vertex Specification

    // Create VBO
    unsigned int VBO;
    glGenBuffers(1, &VBO);

    // Set openGL state to have above VBO bound
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    // Send VBO to GPU
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex), vertex, GL_STATIC_DRAW);

    //// Connecting vertex attributes (in the vertex shader) to currently bound VBO 

    // Create VAO
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);

    // Set OpenGL state to have above VAO bound - need this to change VAO state (call to attrib pointer)
    glBindVertexArray(VAO);

    unsigned int positionAttributeIndex = 0;
    unsigned int positionAttributeSize = 3;
    GLsizei stride = 0;
    const void* offset = (void*)0;
    

    glVertexAttribPointer(positionAttributeIndex, positionAttributeSize , GL_FLOAT, GL_FALSE, stride , offset);
    glEnableVertexAttribArray(positionAttributeIndex);

    return VAO;


}
void render_draw(unsigned int shaderProgram, unsigned int VAO)
{
    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);
    glPointSize(10);
    glDrawArrays(GL_POINTS, 0, 1);
}

