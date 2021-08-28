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

    // Allocate memory for the VBO
    // NOTE: as we are passing in the vertex array, it decays to a pointer
    // so using sizeof(vertex) will only allocate 8 bytes (on 64 bit) of memory for the VBO 
    // In the case of only having the position information and (and only thinking 2-D), this is fine -
    // Not so when adding a z value, or more attributes
    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), vertex, GL_STATIC_DRAW);

    //// Connecting vertex attributes (in the vertex shader) to currently bound VBO 

    // Create VAO
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);

    // Set OpenGL state to have above VAO bound - need this to change VAO state (call to attrib pointer)
    glBindVertexArray(VAO);

    // Position attribute
    glVertexAttribPointer(0, 3 , GL_FLOAT, GL_FALSE, 6 * sizeof(float) , 0);
    glEnableVertexAttribArray(0);

    // Color attribute
    glVertexAttribPointer(1, 3 , GL_FLOAT, GL_FALSE, 6 * sizeof(float) , (const void*)12);
    glEnableVertexAttribArray(1);

    return VAO;


}
void render_draw(unsigned int shaderProgram, unsigned int VAO)
{
    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);
    glPointSize(10);
    glDrawArrays(GL_POINTS, 0, 1);
}

