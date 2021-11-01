//============================================================================
// Name        : main.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description :
//============================================================================


#include "Utility.h"
#include "Rendering.h"
#include <iostream>
#include "Shaders.h"
#include "CompileShaders.h"
#include "LinkShaders.h"
#include "data.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/constants.hpp>
#include "input.h"
#include "Textures.h"
#include "VertexSpecification.h"

// To resize viewport whenever window is resized - define a callback (with following signature)
void framebuffer_size_callback(GLFWwindow* window, int newWidth, int newHeight)
{
    //Note--- this will change viewport location to have lower left corner at (0,0) (how to change this?)
    glViewport(0, 0, newWidth, newHeight);
}




int main()
{
    Init();
    WindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    WindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    WindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    Window* window = CreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (!window)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        Terminate();
        return -1;
    }

    MakeContextCurrent(window);
    //SetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    //SetCursorPosCallback(window, mouse_callback);


    int gladInitialise = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    if (!gladInitialise)
    {
        std::cout << "Failed to initialise GLAD" << std::endl;
        std::cout << "Perhaps you have not called a \"MakeContextCurrent(window) \" function prior?" << std::endl;
        return -1;
    }

    Viewport viewport;
    viewport.LowerLeftX = 0;
    viewport.LowerLeftY = 0;
    viewport.Width = /*0.9 */ 800;
    viewport.Height = /*0.9 */ 600;

    glViewport(viewport.LowerLeftX, viewport.LowerLeftY, viewport.Width, viewport.Height);


    unsigned int shaderProgram = linkShaders(
        compileVertexShader(vertexShaderSource),
        compileFragmentShader(fragmentShaderSource));

    unsigned int shaderProgram_Tri = linkShaders(
        compileVertexShader(vertexShaderSource_Tri),
        compileFragmentShader(fragmentShaderSource_Tri));

    unsigned int shaderProgram_Rect = linkShaders(
        compileVertexShader(vertexShaderSource_Rect),
        compileFragmentShader(fragmentShaderSource_Rect));

    unsigned int shaderProgram_Cube = linkShaders(
        compileVertexShader(vertexShaderSource_Cube),
        compileFragmentShader(fragmentShaderSource_Cube));

    unsigned int shaderProgram_Cube_Raw_Target = linkShaders(
        compileVertexShader(vertexShaderSource_Cube_Raw_Target),
        compileFragmentShader(fragmentShaderSource_Cube_Raw_Target));

    unsigned int shaderProgram_Cube_Raw_LightSource = linkShaders(
        compileVertexShader(vertexShaderSource_Cube_Raw_LightSource),
        compileFragmentShader(fragmentShaderSource_Cube_Raw_LightSource));

    unsigned int VAO = render_setup(vertex, 3);
    unsigned int VAO_Triangle = render_setup_tri(triangle, 24);

    unsigned int EBO = render_setup_rect(rectangle, 29);

    unsigned int VAO_Cube = render_setup_cube(cube, 5*6*6);

    unsigned int VAO_Cube_Raw_Target = render_setup_cube_raw(cube_raw, 8*6*6 );
    unsigned int VAO_Cube_Raw_LightSource = render_setup_cube_raw_lightsource(cube_raw, 8*6*6);

    //** Begin Floor stuff
    unsigned int VAO_Floor = vs_floor(our_floor, 18 + 12);


    unsigned int shaderProgramFloor = linkShaders(
        compileVertexShader(vertexShaderFloor),
        compileFragmentShader(fragmentShaderFloor));

    //** End Floor stuff



    textureSetup();


	//// Transformations
	glm::mat4 model(1.f);
	glm::mat4 view(1.f);
	glm::mat4 projection;
	projection = glm::perspective(glm::radians(45.f), 800.f/600.f, 0.1f, 100.f);

    GLfloat colorChannelValues[8][3] =
    {
        {0.f, 0.f, 0.f},
        {1.f, 0.f, 0.f},
        {1.f, 1.f, 0.f},
        {0.f, 1.f, 1.f},
        {0.f, 0.f, 1.f},
        {0.f, 1.f, 0.f},
        {1.f, 0.f, 1.f},
        {1.f, 1.f, 1.f},
    };
    GLint64 frameNumber = 0;
    GLchar colorChannelValuesIdx = 0;

    // These are abosolute world positions - model matrix
    // will need to be reset to place cubes as desired (otherwise we will get
    // relative positions)
    const char numberOfCubePositions = 10;
    glm::vec3 cubePositions[numberOfCubePositions] =
    {
        glm::vec3(0.f, 0.f, 0.f),
        glm::vec3(2.f, 5.f, -15.f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3( 2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3( 1.3f, -2.0f, -2.5f),
		glm::vec3( 1.5f,  2.0f, -2.5f),
		glm::vec3( 1.5f,  0.2f, -1.5f),
		glm::vec3(-1.3f,  1.0f, -1.5f)
    };

    // Frame time management variables
    float currFrameTime;
    float lastFrameTime = 0.f;
    float deltaTime;

    // Game loop
    while (!WindowShouldClose(window))
    {
    	currFrameTime = glfwGetTime();
    	deltaTime = currFrameTime - lastFrameTime;
    	lastFrameTime = currFrameTime;
        //// input
        processInput(window, deltaTime);

        if (depthTest)
			glEnable(GL_DEPTH_TEST);
        else
			glDisable(GL_DEPTH_TEST);

        // clear results from previous frame (iteration of loop)
        //glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //// rendering (note this has to be after clear!)
        //render_draw(shaderProgram, VAO, colorChannelValues[colorChannelValuesIdx], false);
        if (++frameNumber % 20 == 0)
        {
            colorChannelValuesIdx = ++colorChannelValuesIdx % 8;
        }

        // Place many cubes
        /*
        for (char i = 0; i < numberOfCubePositions; i++)
        {
        	model = glm::mat4(1.f);
        	model = glm::translate(model, cubePositions[i]);
			//model = glm::rotate(model, (float)glfwGetTime() * 0.1f * glm::radians(50.f), glm::vec3(0.5f,1.f,0.f));

			view = glm::mat4(1.f);
			view = glm::lookAt(cameraPos, cameraPos + cameraLookDirection, cameraUp);

			render_draw_cube(
					shaderProgram_Cube,
					VAO_Cube,
					vertFlip,
					texture2Amount,
					model,
					view,
					projection);


        }
        */

		view = glm::lookAt(cameraPos, cameraPos + cameraLookDirection, cameraUp);
        render_draw_floor(
        		shaderProgramFloor,
				VAO_Floor,
				model,
				view,
				projection);


        /*
		view = glm::mat4(1.f);
		view = glm::lookAt(cameraPos, cameraPos + cameraLookDirection, cameraUp);

        glm::vec3 lightSource = glm::vec3(1.f, 1.f, 1.f);
        glm::vec3 lightAmbient = glm::vec3(0.2f, 0.2f, 0.2f);
        glm::vec3 lightDiffuse = glm::vec3(0.5f, 0.5f, 0.5f);
        glm::vec3 lightSpecular = glm::vec3(1.f, 1.f, 1.f);
        unsigned int shine = PhongExp;
        glm::vec3 lightPos = glm::vec3(1.2f, 1.0f, 2.f);
        glm::vec3 lightDirection = glm::vec3(-1.f, 0.f, 0.f);

        for (char i = 0; i < numberOfCubePositions; ++i)
        {
			model = glm::mat4(1.f);
			model = glm::translate(model, cubePositions[i]);
			float angle = 20.f * i;
			model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));

			// Attenuation factors for
			// F_att = 1/(K_c + K_l*d + K_q*d*d), where
			// F_att is the attenuation value, K_c are constants, and
			// d is the distance from the fragment to the light source
			float K_c = 1.f;
			float K_l = 0.09f;
			float K_q = 0.032f;

			render_draw_cube_raw_target(
					shaderProgram_Cube_Raw_Target,
					VAO_Cube_Raw_Target,
					model,
					view,
					projection,
					lightSource,
					lightAmbient,
					lightDiffuse,
					lightSpecular,
					lightPos,
					cameraPos,
					cameraLookDirection,
					shine,
					ambientLight,
					diffuseLight,
					specularLight,
					lightDirection,
					isLightDirectional,
					isLightPoint,
					isLightSpot,
					K_c,
					K_l,
					K_q,
					attenuation
					);

        }

        if (isLightPoint)
        {
			model = glm::mat4(1.f);
			model = glm::translate(model, lightPos);
			model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
			render_draw_cube_raw_lightsource(
					shaderProgram_Cube_Raw_LightSource,
					VAO_Cube_Raw_LightSource,
					model,
					view,
					projection,
					lightSource);
        }
        */


        //// check and call events, and swap buffers
        PollEvents();
        SwapBuffers(window);
    }


    Terminate();
    return 0;
}
