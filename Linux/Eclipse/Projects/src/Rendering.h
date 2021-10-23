#pragma once
#include <glad/glad.h> // to get OpenGL includes
#include <iostream>
#include "data.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

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

unsigned int render_setup(float* vertex, unsigned int numberOfEntries)
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
    glVertexAttribPointer(0, 3 , GL_FLOAT, GL_FALSE, 0 , 0);
    glEnableVertexAttribArray(0);

    return VAO;

}
unsigned int render_setup_tri(float* vertex, unsigned int numberOfEntries)
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
    glVertexAttribPointer(0, 3 , GL_FLOAT, GL_FALSE, 0 , 0);
    glEnableVertexAttribArray(0);

    // Color attribute
    glVertexAttribPointer(1, 3 , GL_FLOAT, GL_FALSE, 0 , (void*)(9*sizeof(GL_FLOAT)));
    glEnableVertexAttribArray(1);

    // Texture attribute
    // Note second arg needs to be 2 (we have 2 componentes per the texture vertex attribute)
    glVertexAttribPointer(2, 2 , GL_FLOAT, GL_FALSE, 0 , (void*)(18*sizeof(GL_FLOAT)));
    glEnableVertexAttribArray(2);


    return VAO;

}

unsigned int render_setup_rect(float* vertex, unsigned int numberOfEntries)
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
    glVertexAttribPointer(0, 3 , GL_FLOAT, GL_FALSE, 0 , 0);
    glEnableVertexAttribArray(0);

    // Color attribute
    glVertexAttribPointer(1, 3 , GL_FLOAT, GL_FALSE, 0 , (void*)(12*sizeof(GL_FLOAT)));
    glEnableVertexAttribArray(1);

    // Texture attribute
    glVertexAttribPointer(2, 2 , GL_FLOAT, GL_FALSE, 0 , (void*)(21*sizeof(GL_FLOAT)));
    glEnableVertexAttribArray(2);

    // Create EBO
    unsigned int EBO;
    glGenBuffers(1, &EBO);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, numberOfEntries * sizeof(float), indexArray, GL_STATIC_DRAW);

    return EBO;
}

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

unsigned int render_setup_cube_raw(float* vertex, unsigned int numberOfEntries)
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
    glVertexAttribPointer(0, 3 , GL_FLOAT, GL_FALSE, 8*sizeof(float) , 0);
    glEnableVertexAttribArray(0);

    // Normal attribute
    glVertexAttribPointer(1, 3 , GL_FLOAT, GL_FALSE, 8*sizeof(float) , (void *)(3*sizeof(float)));
    glEnableVertexAttribArray(1);

    // Texture coords attribute
    glVertexAttribPointer(2, 2 , GL_FLOAT, GL_FALSE, 8*sizeof(float) , (void *)(6*sizeof(float)));
    glEnableVertexAttribArray(2);

    return VAO;
}

unsigned int render_setup_cube_raw_lightsource(float* vertex, unsigned int numberOfEntries)
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
    glVertexAttribPointer(0, 3 , GL_FLOAT, GL_FALSE, 8*sizeof(float) , 0);
    glEnableVertexAttribArray(0);

    return VAO;
}

void render_draw(unsigned int shaderProgram, unsigned int VAO, GLfloat* channelValue, bool triangle)
{
    glUseProgram(shaderProgram);
    
    // TODO Investigate whether I can move the location code out (I think I can)
    GLint locRChannelValue = glGetUniformLocation(shaderProgram, "R_ChannelValue");
    GLint locGChannelValue = glGetUniformLocation(shaderProgram, "G_ChannelValue");
    GLint locBChannelValue = glGetUniformLocation(shaderProgram, "B_ChannelValue");
    if (locRChannelValue != -1 && locGChannelValue != -1 && locBChannelValue !=1)
    {
        glUniform1f(locRChannelValue, *channelValue++);
        glUniform1f(locGChannelValue, *channelValue++);
        glUniform1f(locBChannelValue, *channelValue++);
    }
    glBindVertexArray(VAO);
    if (!triangle)
    {
		glPointSize(10);
		glDrawArrays(GL_POINTS, 0, 1);
    }
    else
    {
		glDrawArrays(GL_TRIANGLES, 0, 3);
    }
}

void render_draw_indexArray(
		unsigned int shaderProgram,
		unsigned int EBO,
		bool vertFlip = false,
		float texture2Amount = 0.2f,
		glm::mat4 model = glm::mat4(1.0f),
		glm::mat4 view = glm::mat4(1.0f),
		glm::mat4 projection = glm::mat4(1.0f)
		)
{
    glUseProgram(shaderProgram);
    glUniform1i(glGetUniformLocation(shaderProgram, "Texture2"), 1);
    glUniform1i(glGetUniformLocation(shaderProgram, "vertFlip"), vertFlip);
    glUniform1f(glGetUniformLocation(shaderProgram, "texture2Amount"), texture2Amount);
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "view"), 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void render_draw_cube(
		unsigned int shaderProgram,
		unsigned int VAO,
		bool vertFlip = false,
		float texture2Amount = 0.2f,
		glm::mat4 model = glm::mat4(1.0f),
		glm::mat4 view = glm::mat4(1.0f),
		glm::mat4 projection = glm::mat4(1.0f)
		)
{
    glUseProgram(shaderProgram);
    glUniform1i(glGetUniformLocation(shaderProgram, "Texture2"), 1);
    glUniform1i(glGetUniformLocation(shaderProgram, "vertFlip"), vertFlip);
    glUniform1f(glGetUniformLocation(shaderProgram, "texture2Amount"), texture2Amount);
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "view"), 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
}

void render_draw_cube_raw_target(
		unsigned int shaderProgram,
		unsigned int VAO,
		glm::mat4 model = glm::mat4(1.0f),
		glm::mat4 view = glm::mat4(1.0f),
		glm::mat4 projection = glm::mat4(1.0f),
		glm::vec3 lightSource = glm::vec3(1.0f),
		glm::vec3 lightAmbient = glm::vec3(1.0f),
		glm::vec3 lightDiffuse = glm::vec3(1.0f),
		glm::vec3 lightSpecular = glm::vec3(1.0f),
		glm::vec3 lightPos = glm::vec3(0.f),
		glm::vec3 viewPos = glm::vec3(0.f),
		unsigned int shine = 32,
		bool ambientLight = true,
		bool diffuseLight = true,
		bool specularLight = true
		)
{
    glUseProgram(shaderProgram);
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "view"), 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
    glUniform3fv(glGetUniformLocation(shaderProgram, "light.source"), 1, glm::value_ptr(lightSource));
    glUniform3fv(glGetUniformLocation(shaderProgram, "light.ambient"), 1, glm::value_ptr(lightAmbient));
    glUniform3fv(glGetUniformLocation(shaderProgram, "light.diffuse"), 1, glm::value_ptr(lightDiffuse));
    glUniform3fv(glGetUniformLocation(shaderProgram, "light.specular"), 1, glm::value_ptr(lightSpecular));
    glUniform3fv(glGetUniformLocation(shaderProgram, "lightPos"), 1, glm::value_ptr(lightPos));
    glUniform3fv(glGetUniformLocation(shaderProgram, "viewPos"), 1, glm::value_ptr(viewPos));
    glUniform1ui(glGetUniformLocation(shaderProgram, "material.shine"), shine);
    glUniform1i(glGetUniformLocation(shaderProgram, "ambientLight"), ambientLight);
    glUniform1i(glGetUniformLocation(shaderProgram, "diffuseLight"), diffuseLight);
    glUniform1i(glGetUniformLocation(shaderProgram, "specularLight"), specularLight );
    glUniform1i(glGetUniformLocation(shaderProgram, "material.ambientMap"), 3);
    glUniform1i(glGetUniformLocation(shaderProgram, "material.diffuseMap"), 2);
    glUniform1i(glGetUniformLocation(shaderProgram, "material.specularMap"), 4);

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
}

void render_draw_cube_raw_lightsource(
		unsigned int shaderProgram,
		unsigned int VAO,
		glm::mat4 model = glm::mat4(1.0f),
		glm::mat4 view = glm::mat4(1.0f),
		glm::mat4 projection = glm::mat4(1.0f),
		glm::vec3 lightSource = glm::vec3(1.0f)
		)
{
    glUseProgram(shaderProgram);
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "view"), 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
    glUniform3fv(glGetUniformLocation(shaderProgram, "lightSource"), 1,glm::value_ptr(lightSource));

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
}
