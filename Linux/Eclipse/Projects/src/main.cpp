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
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/constants.hpp>
#include "input.h"

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

    unsigned int VAO_Cube_Raw_Target = render_setup_cube_raw(cube_raw, 6*6*6 );
    unsigned int VAO_Cube_Raw_LightSource = render_setup_cube_raw_lightsource(cube_raw, 6*6*6);



	// OpenGL Texture Set up
    // TODO move out to function/file
	int img_width, img_height, img_nChannels;
	unsigned char* img_data = stbi_load("container.jpg", &img_width, &img_height, &img_nChannels,0);

	if (!img_data)
		printf("Failed to load texture...");

	unsigned int texture;
	glGenTextures(1,&texture);

	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, img_width, img_height, 0, GL_RGB, GL_UNSIGNED_BYTE, img_data);
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(img_data);

	// Second texture
	//TODO it would be cool to fist check if we _need_ to do this - would have to check where 0.0 is on image y-axis
	stbi_set_flip_vertically_on_load(true);

	img_data = stbi_load("awesomeface.png", &img_width, &img_height, &img_nChannels, 0);


	if (!img_data)
		printf("Failed to load texture 2...");

	unsigned int texture2;
	glGenTextures(1, &texture2);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture2);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, img_width, img_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, img_data);
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(img_data);

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
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
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
		view = glm::mat4(1.f);
		view = glm::lookAt(cameraPos, cameraPos + cameraLookDirection, cameraUp);

        model = glm::mat4(1.f);
        model = glm::translate(model, glm::vec3(-0.5f, 0.0f,0.0f));
        glm::vec3 lightSource = glm::vec3(1.f, 1.f, 1.f);
        glm::vec3 ambientReflectance = glm::vec3(1.f, 0.5f, 0.31f);
        glm::vec3 diffuseReflectance = glm::vec3(1.f, 0.5f, 0.31f);
        glm::vec3 specularReflectance = glm::vec3(0.5f, 0.5f, 0.5f);
        unsigned int shine = PhongExp;
        glm::vec3 lightPos = glm::vec3(1.2f, 1.0f, 2.f);
        render_draw_cube_raw_target(
        		shaderProgram_Cube_Raw_Target,
				VAO_Cube_Raw_Target,
				model,
				view,
				projection,
				ambientReflectance,
				diffuseReflectance,
				specularReflectance,
				lightSource,
				lightPos,
				cameraPos,
				shine,
				ambientLight,
				diffuseLight,
				specularLight
				);

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

        //// check and call events, and swap buffers
        PollEvents();
        SwapBuffers(window);
    }


    Terminate();
    return 0;
}
