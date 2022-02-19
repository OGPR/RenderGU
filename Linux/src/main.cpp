//============================================================================
// Name        : main.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description :
//============================================================================


//macro to write shader programs inline
#ifndef GLSL 
#define GLSL(version,A) "#version " #version "\n" #A
#endif

#include "Window.h"
#include "Utility.h"
#include "CompileShaders.h"
#include "LinkShaders.h"
#include "DeltaTime.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

// To resize viewport whenever window is resized - define a callback (with following signature)
void framebuffer_size_callback(GLFWwindow* window, int newWidth, int newHeight)
{
    //Note--- this will change viewport location to have lower left corner at (0,0) (how to change this?)
    glViewport(0, 0, newWidth, newHeight);
}

void createPlane(float* vertexData, unsigned int* shaderProgram, unsigned int* VAO);
void displayPlane(unsigned int shaderProgram, unsigned int VAO, float* colorAmount, bool* fadeIn, glm::vec3* color);

int main()
{
    // Create main window
    GLFWwindow* window = Window();

    // Create Plane 
    float cube2D[18] = {0}; 
    unsigned int planeShader;
    unsigned int planeVAO;
    createPlane(cube2D, &planeShader, &planeVAO);



    // Fade effect variables 
    float colorAmount = 0.0f;
    bool fadeIn = true;

    // 2D_Cube color
    glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f);


    while(!WindowShouldClose(window))
    {
        // Process Input
         if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
         {
            glfwSetWindowShouldClose(window, true);
         }


        // Draw to screen
        displayPlane(planeShader, planeVAO, &colorAmount, &fadeIn, &color);
        //// check and call events, and swap buffers
        PollEvents();
        SwapBuffers(window);
       
    }




    

    // Exit
    Terminate();
    return 0;





}
//--------------------------------------------------------------------------------------------

void createPlane(float* vertexData, unsigned int* shaderProgram, unsigned int* VAO)
{
    makeCube_2D(vertexData);
    
    // Write shaders
    const char* vs =
        GLSL(330 core,
        layout(location = 0) in vec3 inPos;


        void main()
        {
            gl_Position = vec4(inPos, 2.0f);
        }
        );
    const char* fs =
        GLSL(330 core,
        out vec4 FragColor;

        uniform float multiplier;
        uniform float color_r;
        uniform float color_g;
        uniform float color_b;

        void main()
        {
            FragColor = vec4(multiplier * vec3(color_r, color_g, color_b) , 1.0f);
        }
        );

    // Make Shader Program
   *shaderProgram = linkShaders(compileVertexShader(vs), compileFragmentShader(fs));

    // Specify Vertices
    specifyVertices(vertexData, 18, VAO); 
}

void displayPlane(unsigned int shaderProgram, unsigned int VAO, float* colorAmount, bool* fadeIn, glm::vec3* color)
{
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(shaderProgram);

        if (*fadeIn)
        {
            *colorAmount += DeltaTime() * 0.2f;
            if (*colorAmount > 1.0f) // To delay the fade out effect (i.e stay at full color), change this (e.g to 1.5f)
                *fadeIn = false;
        }
        else
        {
            *colorAmount -= DeltaTime() * 0.2f;
        }



        glUniform1f(glGetUniformLocation(shaderProgram, "multiplier"), *colorAmount); 
        glUniform1f(glGetUniformLocation(shaderProgram, "color_r"), (*color)[0]); 
        glUniform1f(glGetUniformLocation(shaderProgram, "color_g"), (*color)[1]); 
        glUniform1f(glGetUniformLocation(shaderProgram, "color_b"), (*color)[2]); 
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);

}


