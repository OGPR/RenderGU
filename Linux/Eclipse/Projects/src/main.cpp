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
#include <assert.h>

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

    Window* window = CreateWindow(800, 600, "RenderGU", NULL, NULL);
    glfwSetWindowPos(window, 2000, 250);
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

    unsigned int shaderProgram_Cube_no_mix = linkShaders(
        compileVertexShader(vertexShaderSource_Cube),
        compileFragmentShader(fragmentShaderSource_Cube_no_mix));

    unsigned int shaderProgram_Cube_SingleColor = linkShaders(
        compileVertexShader(vertexShaderSource_Cube),
        compileFragmentShader(fragmentShaderSingleColor));

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

    //** Begin Quad stuff
    unsigned int VAO_Quad = vs_quad(quad, 3*5 + 3*5);


    unsigned int shaderProgram_Rect_Transparency = linkShaders(
            compileVertexShader(vertexShaderSource_Rect_Transparency),
            compileFragmentShader(fragmentShaderSource_Rect_Transparency));

    //** End Quad stuff

    //** Begin window stuff
    // Re-using quad VSpec
    unsigned int VAO_Window = vs_quad(quad, 3*5 + 3*5);

    // Re-using quad VShader
    unsigned int shaderProgram_Rect_Window = linkShaders(
            compileVertexShader(vertexShaderSource_Rect_Transparency),
            compileFragmentShader(fragmentShaderSource_Rect_window));

    //** End window stuff

    //** Begin simple quad render stuff
    unsigned int VAO_SimpleQuad = vs_simpleQuad(simpleQuad, 3*5 + 3*5);


    unsigned int shaderProgram_SimpleQuad = linkShaders(
		compileVertexShader(vertexShaderSource_SimpleQuad),
		compileFragmentShader(fragmentShaderSource_SimpleQuad));


    //** End simple quad render stuff

    unsigned int textureTarget = 0;
    textureSetup(&textureTarget);


	//// Transformations
	glm::mat4 model(1.f);
	glm::mat4 view(1.f);
	glm::mat4 projection;
	projection = glm::perspective(glm::radians(45.f), 800.f/600.f, 0.1f, 100.f);

	/// Model specific transformations
	// Those we don't expect to change between frames, so set them one here
	glm::mat4 modelQuad(1.f);
	modelQuad = glm::rotate(modelQuad, glm::half_pi<float>(), glm::vec3(0.f, 1.f, 0.f));
	// modelcoords have been rotated, so keep that in mind on translation
	// Apply offset in z to prevent z-figting
	modelQuad = glm::translate(modelQuad, glm::vec3(0.5f, 0.f,-1.51f));

	glm::mat4 modelWindow(1.f);
	modelWindow = glm::rotate(modelWindow, glm::half_pi<float>(), glm::vec3(0.f, 1.f, 0.f));
	modelWindow = glm::translate(modelWindow, glm::vec3(0.5f, 0.f,-1.8f));

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

    // From print statements in loop below
    // Set up camera for depth/stencil buffer work
	cameraPos = glm::vec3(-3.255120, 0.596114, -0.690018);
	cameraLookDirection = glm::vec3(0.972760, -0.231807, -0.001899);
	cameraCurrRotAngle = glm::vec3(1.804731, 1.572749, 0.000000);
    CameraYaw = cameraCurrRotAngle.y;
    CameraPitch = cameraCurrRotAngle.x;




    glEnable(GL_STENCIL_TEST);

	GLuint fbo;
	glGenFramebuffers(1,&fbo);

	// Render buffer attachment
	GLuint fbo_1; // New framebuffer to attach to
	glGenFramebuffers(1,&fbo_1);
	GLuint rbo;
	glGenRenderbuffers(1,&rbo);

	float scrollDistance = 0.f;

	// Game loop
    while (!WindowShouldClose(window))
    {
		////---- 1st pass - off-screen render------

    	printf("tex target1\n");
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
		glBindFramebuffer(GL_FRAMEBUFFER, fbo);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureTarget, 0);

		// Create renderbuffer for attaching depth to currently bound framebuffer
		glBindRenderbuffer(GL_RENDERBUFFER, rbo);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, 800, 600);
		assert(glGetError() == 0);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);
		CheckFramebufferStatus();

    	currFrameTime = glfwGetTime();
    	deltaTime = currFrameTime - lastFrameTime;
    	lastFrameTime = currFrameTime;

        //// input
        processInput(window, deltaTime);

        if (depthTest)
        {
			glEnable(GL_DEPTH_TEST);

        }
        else
			glDisable(GL_DEPTH_TEST);

        // clear results from previous frame (iteration of loop)
        //glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glStencilMask(0xFF); // make sure stencil  buffer is writable before clearing
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        //// rendering (note this has to be after clear!)
        //render_draw(shaderProgram, VAO, colorChannelValues[colorChannelValuesIdx], false);
        /*if (++frameNumber % 20 == 0)
        {
            colorChannelValuesIdx = ++colorChannelValuesIdx % 8;
        }*/

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


        // To look behind, we have the rear-view at same pos, but looking the opposite way
        CameraYaw += glm::pi<float>();

        // Left/Down to update values, Right/Up to reset to where we were
        YawLeft(&cameraLookDirection, deltaTime);
        YawRight(&cameraLookDirection, deltaTime);
        view = glm::lookAt(cameraPos, cameraPos + cameraLookDirection, cameraUp);

        // Camera Yaw back to original
        CameraYaw -= glm::pi<float>();
        YawLeft(&cameraLookDirection, deltaTime);
        YawRight(&cameraLookDirection, deltaTime);

		// Write to stencil buffer where desired
		// Cube 1
		glStencilFunc(GL_ALWAYS, 1, 0xFF);
		glStencilMask(0xFF);
		glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
		model = glm::mat4(1.f);
		model = glm::translate(model, glm::vec3(-1.0f, 0.0f, -1.0f));
		render_draw_cube(
				shaderProgram_Cube_no_mix,
				VAO_Cube,
				visualiseDepthBuffer,
				0,
				model,
				view,
				projection);

		// Cube 2
		glEnable(GL_CULL_FACE);
		model = glm::mat4(1.f);
		model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
		render_draw_cube(
				shaderProgram_Cube_no_mix,
				VAO_Cube,
				visualiseDepthBuffer,
				0,
				model,
				view,
				projection);

		glDisable(GL_CULL_FACE);

		// Floor
		glStencilMask(0x00); // only cubes for now
		model = glm::mat4(1.f);
		model = glm::scale(model, glm::vec3(5.f, 1.f, 5.f));



		render_draw_floor(
				shaderProgramFloor,
				VAO_Floor,
				visualiseDepthBuffer,
				5,
				model,
				view,
				projection);


		if (stencilTest)
		{
			// Another render pass, borders/outlining
			// Cube 1
			glStencilFunc(GL_NOTEQUAL, 1 , 0xFF);
			//glStencilMask(0xFF);
			//glDisable(GL_DEPTH_TEST);
			glDepthFunc(GL_LESS);
			float scale = 1.1f;

			model = glm::mat4(1.f);
			model = glm::translate(model, glm::vec3(-1.0f, 0.0f, -1.0f));
			model = glm::scale(model, glm::vec3(scale, scale, scale));
			render_draw_cube(
					shaderProgram_Cube_SingleColor,
					VAO_Cube,
					visualiseDepthBuffer,
					0,
					model,
					view,
					projection);
			glDepthFunc(GL_LESS);

			// Cube 2
			model = glm::mat4(1.f);
			model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
			model = glm::scale(model, glm::vec3(scale, scale, scale));
			render_draw_cube(
					shaderProgram_Cube_SingleColor,
					VAO_Cube,
					visualiseDepthBuffer,
					0,
					model,
					view,
					projection);
			//glEnable(GL_DEPTH_TEST);

			// Floor
			model = glm::mat4(1.f);
			model = glm::scale(model, glm::vec3(5.f, 1.f, 5.f));
			render_draw_floor(
					shaderProgramFloor,
					VAO_Floor,
					visualiseDepthBuffer,
					5,
					model,
					view,
					projection);
			}

		// Transparency
		render_draw_rect_transparency(
				shaderProgram_Rect_Transparency,
				VAO_Quad,
				modelQuad,
				view,
				projection
				);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		render_draw_rect_window(
				shaderProgram_Rect_Window,
				VAO_Window,
				modelWindow,
				view,
				projection
				);
		glDisable(GL_BLEND);


		/// Rear-view mirror rendering
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);


		view = glm::lookAt(cameraPos, cameraPos + cameraLookDirection, cameraUp);

				// Write to stencil buffer where desired
				// Cube 1
				glStencilFunc(GL_ALWAYS, 1, 0xFF);
				glStencilMask(0xFF);
				glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
				model = glm::mat4(1.f);
				model = glm::translate(model, glm::vec3(-1.0f, 0.0f, -1.0f));
				render_draw_cube(
						shaderProgram_Cube_no_mix,
						VAO_Cube,
						visualiseDepthBuffer,
						0,
						model,
						view,
						projection);

				// Cube 2
				glEnable(GL_CULL_FACE);
				model = glm::mat4(1.f);
				model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
				render_draw_cube(
						shaderProgram_Cube_no_mix,
						VAO_Cube,
						visualiseDepthBuffer,
						0,
						model,
						view,
						projection);

				glDisable(GL_CULL_FACE);

				// Floor
				glStencilMask(0x00); // only cubes for now
				model = glm::mat4(1.f);
				model = glm::scale(model, glm::vec3(5.f, 1.f, 5.f));



				render_draw_floor(
						shaderProgramFloor,
						VAO_Floor,
						visualiseDepthBuffer,
						5,
						model,
						view,
						projection);


				if (stencilTest)
				{
					// Another render pass, borders/outlining
					// Cube 1
					glStencilFunc(GL_NOTEQUAL, 1 , 0xFF);
					//glStencilMask(0xFF);
					//glDisable(GL_DEPTH_TEST);
					glDepthFunc(GL_LESS);
					float scale = 1.1f;

					model = glm::mat4(1.f);
					model = glm::translate(model, glm::vec3(-1.0f, 0.0f, -1.0f));
					model = glm::scale(model, glm::vec3(scale, scale, scale));
					render_draw_cube(
							shaderProgram_Cube_SingleColor,
							VAO_Cube,
							visualiseDepthBuffer,
							0,
							model,
							view,
							projection);
					glDepthFunc(GL_LESS);

					// Cube 2
					model = glm::mat4(1.f);
					model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
					model = glm::scale(model, glm::vec3(scale, scale, scale));
					render_draw_cube(
							shaderProgram_Cube_SingleColor,
							VAO_Cube,
							visualiseDepthBuffer,
							0,
							model,
							view,
							projection);
					//glEnable(GL_DEPTH_TEST);

					// Floor
					model = glm::mat4(1.f);
					model = glm::scale(model, glm::vec3(5.f, 1.f, 5.f));
					render_draw_floor(
							shaderProgramFloor,
							VAO_Floor,
							visualiseDepthBuffer,
							5,
							model,
							view,
							projection);
					}

				// Transparency
				render_draw_rect_transparency(
						shaderProgram_Rect_Transparency,
						VAO_Quad,
						modelQuad,
						view,
						projection
						);

				glEnable(GL_BLEND);
				glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
				render_draw_rect_window(
						shaderProgram_Rect_Window,
						VAO_Window,
						modelWindow,
						view,
						projection
						);
				glDisable(GL_BLEND);



    	////---- On Screen render pass - render simple quad with scene texture
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		//CheckFramebufferStatus();

		glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // non-black, to see wireframe
		glDisable(GL_DEPTH_TEST); //TODO: needed?

		//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

		//scrollDistance += 0.1f * deltaTime;

		scrollDistance = 0.0f;

		model = glm::translate(model, glm::vec3(0.f, 0.7f, 0));
		model = glm::scale(model, glm::vec3(0.1f, 0.2f, 0));
		render_draw_SimpleQuad(
				shaderProgram_SimpleQuad,
				VAO_SimpleQuad,
				scrollDistance,
				model);



		// Position prints
		// Printed in format to allow for direct copy and paste from console to code
		/*
		if (frameNumber % 40 == 0)
		{
			printf("cameraPos = glm::vec3(%f, %f, %f);\n", cameraPos.x, cameraPos.y, cameraPos.z);
			printf("cameraLookDirection = glm::vec3(%f, %f, %f);\n", cameraLookDirection.x, cameraLookDirection.y, cameraLookDirection.z);
			printf("cameraCurrRotAngle = glm::vec3(%f, %f, %f);\n", cameraCurrRotAngle.x, cameraCurrRotAngle.y, cameraCurrRotAngle.z);
		}
		*/


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
