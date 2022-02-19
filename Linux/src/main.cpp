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

int main()
{
    // Create main window
    GLFWwindow* window = Window();

    // Create model
    float cube2D[18] = {0}; 
    makeCube_2D(cube2D);

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
        uniform vec3 color;

        void main()
        {
            FragColor = vec4(multiplier * color , 1.0f);
        }
        );

    // Make Shader Program
    unsigned int ShaderProgram = linkShaders(
                                    compileVertexShader(vs),
                                    compileFragmentShader(fs)
                                    );
    


    

    // Specify Vertices
    int VAO;
    specifyVertices(cube2D, 18); 


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
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(ShaderProgram);

        if (fadeIn)
        {
            colorAmount += DeltaTime() * 0.2f;
            if (colorAmount > 1.0f) // To delay the fade out effect (i.e stay at full color), change this (e.g to 1.5f)
                fadeIn = false;
        }
        else
        {
            colorAmount -= DeltaTime() * 0.2f;
        }



        glUniform1f(glGetUniformLocation(ShaderProgram, "multiplier"), colorAmount); 
        glUniform3fv(glGetUniformLocation(ShaderProgram, "color"), 1, glm::value_ptr(color)); 
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);

        //// check and call events, and swap buffers
        PollEvents();
        SwapBuffers(window);
       
    }




    

    // Exit
    Terminate();
    return 0;





}
