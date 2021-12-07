#pragma once
#include <glad/glad.h> // to get OpenGL includes
#include <iostream>
#include "data.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

void Render(
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
    glUniform1i(glGetUniformLocation(shaderProgram, "visualiseDepthBuffer"), visualiseDepthBuffer);
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "view"), 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
    glUniform1i(glGetUniformLocation(shaderProgram, "Texture"), activeTexture);

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}
