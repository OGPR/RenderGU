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

// CCW winding
float cube[] = {

	/* The vertex annotations are given wrt to the face orientation.
	 * For example the bottom face will have the notion of back and front vertices
	 *
	 * However, left and right faces do not follow this convention as they initially were annotated
	 * with top/bottom notions (made sense visually I think).
	 */

	/// Back Face

	// Tri 1
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, // Bottom left
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // Top right
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f, // Bottom right

	// Tri 2
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // Top right
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, // Bottom right
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // Top Left

    /// Front face

	// Tri 1
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // Bottom left
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // Bottom right
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f, // Top right

	// Tri 2
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f, // Top right
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f, // Top left
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // Bottom left

    /// Left face

	// Tri 1
	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // Top right
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // Top left
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // Bottom left

	// Tri 2
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // Bottom left
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // Bottom right
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // Top right

     /// Right face

	// Tri 1
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // Top left
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // Bottom right
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // Top right

	 // Tri 2
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // Bottom right
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // Top left
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // Bottom left

    // Bottom face

	 // Tri 1
	 -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // Back left
     0.5f, -0.5f, -0.5f,  1.0f, 1.0f, // Back right
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // Front right

	 // Tri 2
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // Front right
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // Front left
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // Back left

    /// Top face

	// Tri 1
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // Back left
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // Front right
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // Back right

	// Tri 2
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // Front right
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // Back left
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, // Front left
};

struct CubeModel
{
    int numberOfEntries = 5*6*6;
    float* data = cube;

    const char* vertexShader = vertexShaderCube;
    const char* fragmentShader = fragmentShaderCube;

    unsigned int ShaderProgram;
    unsigned int VAO;

    struct Attributes
    {
        struct Position {
            unsigned int index = 0;
            unsigned int size = 3;
            GLsizei stride = 5 * sizeof(float);
            const void *offset = 0;
        } pos;

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

        Attributes A;
        SetAttribute(A.pos.index, A.pos.size, A.pos.stride, A.pos.offset);
        SetAttribute(A.tex.index, A.tex.size, A.tex.stride, A.tex.offset);
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

    void Render(GLuint activeTexture,
                bool visualiseDepthBuffer,
                glm::mat4 model = glm::mat4(1.0f),
                glm::mat4 view = glm::mat4(1.0f),
                glm::mat4 projection = glm::mat4(1.0f)
    )
    {
        glUseProgram(ShaderProgram);
        glUniform1i(glGetUniformLocation(ShaderProgram, "Texture"), activeTexture);
        glUniform1i(glGetUniformLocation(ShaderProgram, "visualiseDepthBuffer"), visualiseDepthBuffer);
        glUniformMatrix4fv(glGetUniformLocation(ShaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(glGetUniformLocation(ShaderProgram, "view"), 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(glGetUniformLocation(ShaderProgram, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
};
