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
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

// To resize viewport whenever window is resized - define a callback (with following signature)
void framebuffer_size_callback(GLFWwindow* window, int newWidth, int newHeight)
{
    //Note--- this will change viewport location to have lower left corner at (0,0) (how to change this?)
    glViewport(0, 0, newWidth, newHeight);
}

void createPlane(float* vertexData, unsigned int* shaderProgram, unsigned int* VAO);
void displayPlane(unsigned int shaderProgram, unsigned int VAO, float* colorAmount, bool* fadeIn, glm::vec3* color);

void createPlane_withTex(float* vertexData, unsigned int* shaderProgram, unsigned int* VAO);
void displayPlane_withTex(unsigned int shaderProgram, unsigned int VAO, float* colorAmount, bool* fadeIn);

void display(unsigned int* shaderProgramArr, unsigned int* VAOArr, float* colorAmountArr, bool* fadeInArr, glm::vec3* colorArr);

enum E_DISPLAY_STATE
{
    START_SCREEN_1,
    START_SCREEN_2
}DISPLAY_STATE;

int main()
{
    // Create main window
    GLFWwindow* window = Window();

    // Arrays to store display parameters
    unsigned int shaderProgramArr[2] = {0, 0};
    unsigned int VAOArr[2] = {0, 0};
    float colorAmountArr[2] = {0.0f, 0.0f};
    bool fadeInArr[2] = {true, true};
    glm::vec3 colorArr[2] = {glm::vec3(1.0f), glm::vec3(1.0f)};

    // Create Plane 
    float cube2D[18] = {0}; 
    createPlane(cube2D, &shaderProgramArr[0], &VAOArr[0]);

    
    // Create Plane with Texture 
    float planeWithTexVertexData[30] = {0}; 
    createPlane_withTex(planeWithTexVertexData, &shaderProgramArr[1], &VAOArr[1]);

    printf("ShaderPrograms: %i, %i", shaderProgramArr[0], shaderProgramArr[1]);
    printf("VAOs: %i, %i", VAOArr[0], VAOArr[1]);

    // Load Texture
    glActiveTexture(GL_TEXTURE0);
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    // set the texture wrapping/filtering options (on the currently bound texture object)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load and generate the texture
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char *data = stbi_load("resources/grass.png", &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_set_flip_vertically_on_load(false);
    stbi_image_free(data);


    // Starting display state
    DISPLAY_STATE = START_SCREEN_1;

    while(!WindowShouldClose(window))
    {
        // Process Input
         if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
         {
            glfwSetWindowShouldClose(window, true);
         }


        // Do we switch display state?
        if (colorAmountArr[1] < 0.0f || glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS)
        {
            DISPLAY_STATE = START_SCREEN_2;
        }

        // Draw to screen
        display(shaderProgramArr, VAOArr, colorAmountArr, fadeInArr, colorArr);
        
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
    // Populate vertexData

    // Store first element pointer which we will reset to
    // after populating data
    float* vertexData_0 = vertexData;
    
    // Tri 1
    
    // Row 1 (top left)
    *vertexData++ = -1; // x
    *vertexData++ = 1; // y
    *vertexData++ = 0; // z

    // Row 2 (bottom left)
    *vertexData++ = -1; // x
    *vertexData++ = -1; // y
    *vertexData++ = 0; // z

    // Row 3 (bottom right)
    *vertexData++ = 1; // x
    *vertexData++ = -1; // y
    *vertexData++ = 0; // z
    
    // Tri 2
    
    // Row 4 (top right)
    *vertexData++ = 1; // x
    *vertexData++ = 1; // y
    *vertexData++ = 0; // z
    
    // Row 5 (top left)
    *vertexData++ = -1; // x
    *vertexData++ = 1; // y
    *vertexData++ = 0; // z
    
    // Row 6 (bottom right)
    *vertexData++ = 1; // x
    *vertexData++ = -1; // y
    *vertexData++ = 0; // z

    vertexData = vertexData_0;
    
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

void createPlane_withTex(float* vertexData, unsigned int* shaderProgram, unsigned int* VAO)
{
    
    // Populate modelArr
    
    // Store first element pointer which we will reset to
    // after populating data
    float* vertexData_0 = vertexData;
    
    // Tri 1
    
    // Row 1 (top left)
    *vertexData++ = -1; // x
    *vertexData++ = 1; // y
    *vertexData++ = 0; // z

    // Row 2 (bottom left)
    *vertexData++ = -1; // x
    *vertexData++ = -1; // y
    *vertexData++ = 0; // z

    // Row 3 (bottom right)
    *vertexData++ = 1; // x
    *vertexData++ = -1; // y
    *vertexData++ = 0; // z
    
    // Tri 2
    
    // Row 4 (top right)
    *vertexData++ = 1; // x
    *vertexData++ = 1; // y
    *vertexData++ = 0; // z
    
    // Row 5 (top left)
    *vertexData++ = -1; // x
    *vertexData++ = 1; // y
    *vertexData++ = 0; // z
    
    // Row 6 (bottom right)
    *vertexData++ = 1; // x
    *vertexData++ = -1; // y
    *vertexData++ = 0; // z

    // Texture coords
    // Tri 1

    // (top left)
    *vertexData++ = 0; 
    *vertexData++ = 1; 

    // (bottom left)
    *vertexData++ = 0; 
    *vertexData++ = 0; 

    // (bottom right)
    *vertexData++ = 1; 
    *vertexData++ = 0; 
    
    // Tri 2
    
    // (top right)
    *vertexData++ = 1; 
    *vertexData++ = 1; 
    
    // (top left)
    *vertexData++ = 0; 
    *vertexData++ = 1; 
    
    // (bottom right)
    *vertexData++ = 1; 
    *vertexData++ = 0; 

    vertexData = vertexData_0;
        
    // Write shaders
    const char* vs =
        GLSL(330 core,
        layout(location = 0) in vec3 inPos;
        layout(location = 1) in vec2 inTexCoord;

        out vec2 texCoord;


        void main()
        {
            mat4 modelMat;
            gl_Position = vec4(inPos, 4.0f);
            texCoord = inTexCoord;
        }
        );
    const char* fs =
        GLSL(330 core,
        in vec2 texCoord;
        out vec4 FragColor;

        uniform float multiplier;
        uniform sampler2D Texture;

        float _multiplier;  // local var as can't assign to uniform
        void main()
        {
            _multiplier = multiplier;
            if (_multiplier > 1.0f)
                _multiplier = 1.0f;

            vec4 texColor = texture(Texture, texCoord);
            if (texColor.a < 0.1f)
                discard;

            FragColor = _multiplier * texColor ;
        }
        );

    // Make Shader Program
   *shaderProgram = linkShaders(compileVertexShader(vs), compileFragmentShader(fs));

    // Specify Vertices
    BindVBO(CreateVBO());
    AllocateMemoryVBO(30, vertexData);
    *VAO = CreateVAO();
    BindVAO(*VAO);
    SetAttribute(0, 3, 0, (void*)0);
    SetAttribute(1, 2, 0, (void*)(18 * sizeof(float)));
}

void displayPlane_withTex(unsigned int shaderProgram, unsigned int VAO, float* colorAmount, bool* fadeIn)
{
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(shaderProgram);

        if (*fadeIn)
        {
            *colorAmount += DeltaTime() * 0.2f;
            if (*colorAmount > 1.05f) // To delay the fade out effect (i.e stay at full color), change this (e.g to 1.5f)
                *fadeIn = false;
        }
        else
        {
            *colorAmount -= DeltaTime() * 0.2f;
        }

        glUniform1f(glGetUniformLocation(shaderProgram, "Texture"), 0); 
        glUniform1f(glGetUniformLocation(shaderProgram, "multiplier"), *colorAmount); 
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);
}

void display(unsigned int* shaderProgramArr, unsigned int* VAOArr, float* colorAmountArr, bool* fadeInArr, glm::vec3* colorArr)
{
    switch(DISPLAY_STATE)
    {
        case START_SCREEN_1:
            displayPlane_withTex(*(++shaderProgramArr), *(++VAOArr), &*(++colorAmountArr), &*(++fadeInArr));
            break;
       
        case START_SCREEN_2:
            displayPlane(*shaderProgramArr, *VAOArr, &*colorAmountArr, &*fadeInArr, &*colorArr);
            break;
            
        default:
            break;
    }
}

