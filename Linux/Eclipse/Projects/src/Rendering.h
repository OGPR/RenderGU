#pragma once
#include <glad/glad.h> // to get OpenGL includes
#include <iostream>
#include "data.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

unsigned int render_setup_cube(float* vertex, unsigned int numberOfEntries)
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
    glBufferData(GL_ARRAY_BUFFER, numberOfEntries * sizeof(float), vertex, GL_STATIC_DRAW);

    //// Connecting vertex attributes (in the vertex shader) to currently bound VBO

    // Create VAO
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);

    // Set OpenGL state to have above VAO bound - need this to change VAO state (call to attrib pointer)
    glBindVertexArray(VAO);

    // Position attribute
    glVertexAttribPointer(0, 3 , GL_FLOAT, GL_FALSE, 5*sizeof(float) , 0);
    glEnableVertexAttribArray(0);

    // Texture attribute
    glVertexAttribPointer(1, 2 , GL_FLOAT, GL_FALSE, 5*sizeof(float) , (void*)(3*sizeof(GL_FLOAT)));
    glEnableVertexAttribArray(1);

    return VAO;
}



void render_draw_cube(
		unsigned int shaderProgram,
		unsigned int VAO,
		bool visualiseDepthBuffer,
		GLubyte activeTexture,
		glm::mat4 model = glm::mat4(1.0f),
		glm::mat4 view = glm::mat4(1.0f),
		glm::mat4 projection = glm::mat4(1.0f)
		)
{
    glUseProgram(shaderProgram);
    glUniform1i(glGetUniformLocation(shaderProgram, "Texture"), activeTexture);
    glUniform1i(glGetUniformLocation(shaderProgram, "visualiseDepthBuffer"), visualiseDepthBuffer);
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "view"), 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
}



void render_draw_rect_transparency(
		unsigned int shaderProgram,
		unsigned int VAO,
		glm::mat4 model = glm::mat4(1.0f),
		glm::mat4 view = glm::mat4(1.0f),
		glm::mat4 projection = glm::mat4(1.0f)
		)
{
    glUseProgram(shaderProgram);
    glUniform1i(glGetUniformLocation(shaderProgram, "Texture"), 7);

    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "view"), 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

    glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
}

void render_draw_rect_window(
		unsigned int shaderProgram,
		unsigned int VAO,
		glm::mat4 model = glm::mat4(1.0f),
		glm::mat4 view = glm::mat4(1.0f),
		glm::mat4 projection = glm::mat4(1.0f)
		)
{
    glUseProgram(shaderProgram);
    glUniform1i(glGetUniformLocation(shaderProgram, "Texture"), 8);

    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "view"), 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

    glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
}


