#pragma once
#include <stdio.h>
/**
* This is so I just don't have to write glfwInit() etc, because:
* - I find it a little hard to read
* - Since other libs like SDL etc apparently work in similar ways, we get a bit of abstraction that can help understanding
*/

#include<glad/glad.h> // Need glad before glew as it includes OpenGL headers
#include<GLFW/glfw3.h>
#include "VertexSpecification_Common.h"

int Init()
{
    return glfwInit();
}

void WindowHint(int hint, int value)
{
    glfwWindowHint(hint, value);
}

GLFWwindow* CreateWindow(int width, int height, const char* title, GLFWmonitor* monitor, GLFWwindow* share)
{
    return glfwCreateWindow(width, height, title, monitor, share);
}

void Terminate()
{
    glfwTerminate();
}

void MakeContextCurrent(GLFWwindow* window)
{
    glfwMakeContextCurrent(window);
}
GLFWframebuffersizefun SetFramebufferSizeCallback(GLFWwindow* window, void (*callback)(GLFWwindow*, int, int))
{
    return glfwSetFramebufferSizeCallback(window, callback);
}

int WindowShouldClose(GLFWwindow* window)
{
    return glfwWindowShouldClose(window);
}

void PollEvents()
{
    glfwPollEvents();
}

void SwapBuffers(GLFWwindow* window)
{
    glfwSwapBuffers(window);
}

void SetInputMode(GLFWwindow* window, int mode, int value)
{
	glfwSetInputMode(window, mode, value);
}

GLFWcursorposfun SetCursorPosCallback(GLFWwindow* window, GLFWcursorposfun callback)
{
	return glfwSetCursorPosCallback(window, callback);
}

void CheckFramebufferStatus()
{
	switch (glCheckFramebufferStatus(GL_FRAMEBUFFER))
	{
		case GL_FRAMEBUFFER_COMPLETE:
			printf("Specified framebuffer is complete\n");
			break;
		case GL_FRAMEBUFFER_UNDEFINED:
			printf("Specified framebuffer is undefined \n");
			break;
		case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:
			printf("Some (or all) of the framebuffer attachment points are framebuffer incomplete\n");
			break;
		case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:
			printf("The framebuffer does not have at least one image attached to it\n");
			break;
		default:
			printf("Something else has gone wrong\n");
	}
}

// Specify Vertices of Model
void specifyVertices(float* model, unsigned short int sizeModelArray, unsigned int* VAO)
{
    BindVBO(CreateVBO());
    
    AllocateMemoryVBO(sizeModelArray, model);

    *VAO = CreateVAO();

    BindVAO(*VAO);

    SetAttribute(0, 3, 0, (void*)0);

}

// To resize viewport whenever window is resized - define a callback (with following signature)
void framebuffer_size_callback(GLFWwindow* window, int newWidth, int newHeight)
{
    //Note--- this will change viewport location to have lower left corner at (0,0) (how to change this?)
    glViewport(0, 0, newWidth, newHeight);
}

void processWindowPos(GLFWwindow* window, int* Width, int* Height)
{
    glfwGetWindowSize(window, Width, Height);
}

