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




// To resize viewport whenever window is resized - define a callback (with following signature)
void framebuffer_size_callback(GLFWwindow* window, int newWidth, int newHeight)
{
    //Note--- this will change viewport location to have lower left corner at (0,0) (how to change this?)
    glViewport(0, 0, newWidth, newHeight);
}

static bool vertFlip = false;
static float texture2Amount = 0.2f;
static bool depthTest = true;
static bool wireframeMode = false;
static bool w_pressed = false;
static bool f_pressed = false;
static bool z_pressed = false;
static float cameraPosZ = -3.f;
static float cameraMoveStepZ = 0.1f;
static float cameraPosX = 0.f;
static float cameraMoveStepX = 0.1f;
static float cameraPosY = 0.f;
static float cameraMoveStepY = 0.1f;
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_RELEASE && w_pressed)
    	w_pressed = false;

    if (glfwGetKey(window, GLFW_KEY_F) == GLFW_RELEASE && f_pressed)
    	f_pressed = false;

    if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_RELEASE && z_pressed)
    	z_pressed = false;

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS && !w_pressed && !wireframeMode)
    {
    	w_pressed = true;
    	wireframeMode = true;
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS && !w_pressed && wireframeMode)
    {
    	w_pressed = true;
    	wireframeMode = false;
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }

    if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS && !f_pressed && !vertFlip)
    {
    	f_pressed = true;
    	vertFlip = true;
    }

    if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS && !f_pressed && vertFlip)
    {
    	f_pressed = true;
    	vertFlip = false;
    }

    if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS && !z_pressed && !depthTest)
    {
    	z_pressed = true;
    	depthTest = true;
    }

    if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS && !z_pressed && depthTest)
    {
    	z_pressed = true;
    	depthTest = false;
    }
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
    	texture2Amount += 0.0025f;

    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
    	texture2Amount -= 0.0025f;

    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
    	texture2Amount = 0.2f;

    if (glfwGetKey(window, GLFW_KEY_KP_2) == GLFW_PRESS)
    	cameraPosZ -= cameraMoveStepZ;

    if (glfwGetKey(window, GLFW_KEY_KP_8) == GLFW_PRESS)
    	cameraPosZ += cameraMoveStepZ;

    if (glfwGetKey(window, GLFW_KEY_KP_4) == GLFW_PRESS)
    	cameraPosX += cameraMoveStepX;

    if (glfwGetKey(window, GLFW_KEY_KP_6) == GLFW_PRESS)
    	cameraPosX -= cameraMoveStepX;

    if (glfwGetKey(window, GLFW_KEY_KP_7) == GLFW_PRESS)
    	cameraPosY -= cameraMoveStepY;

    if (glfwGetKey(window, GLFW_KEY_KP_9) == GLFW_PRESS)
    	cameraPosY += cameraMoveStepY;

    if (glfwGetKey(window, GLFW_KEY_KP_5) == GLFW_PRESS)
    {
    	cameraPosZ = -3.f;
    	cameraPosX = 0.f;
    	cameraPosY = 0.f;
    }
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


    unsigned int VAO = render_setup(vertex, 3);
    unsigned int VAO_Triangle = render_setup_tri(triangle, 24);

    unsigned int EBO = render_setup_rect(rectangle, 29);

    unsigned int VAO_Cube = render_setup_cube(cube, 5*6*6);



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
	//model = glm::rotate(model, glm::radians(45.f), glm::vec3(0.f,1.f,0.f));
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

    // Game loop
    while (!WindowShouldClose(window))
    {
        //// input
        processInput(window);

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
        for (char i = 0; i < numberOfCubePositions; i++)
        {
        	model = glm::mat4(1.f);
        	model = glm::translate(model, cubePositions[i]);
			model = glm::rotate(model, (float)glfwGetTime() * 0.1f * glm::radians(50.f), glm::vec3(0.5f,1.f,0.f));

			view = glm::mat4(1.f);
			view = glm::translate(view, glm::vec3(cameraPosX, cameraPosY, cameraPosZ));

			render_draw_cube(
					shaderProgram_Cube,
					VAO_Cube,
					vertFlip,
					texture2Amount,
					model,
					view,
					projection);

        }

        //// check and call events, and swap buffers
        PollEvents();
        SwapBuffers(window);
    }


    Terminate();
    return 0;
}
