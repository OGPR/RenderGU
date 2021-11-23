#pragma once
#include <stdio.h>
/**
* This is so I just don't have to write glfwInit() etc, because:
* - I find it a little hard to read
* - Since other libs like SDL etc apparently work in similar ways, we get a bit of abstraction that can help understanding
*/

#include<glad/glad.h> // Need glad before glew as it includes OpenGL headers
#include<GLFW/glfw3.h>

using Window = GLFWwindow;

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
	glfwSetCursorPosCallback(window, callback);

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

void CheckError()
{
	switch (glGetError())
	{
	case GL_INVALID_ENUM:
	    printf("An unacceptable value is specified for an enumerated argument."
	    		"The offending command is ignored and has no other side effect"
	    		"than to set the error flag.");
	break;
	case GL_INVALID_VALUE:

	    printf("A numeric argument is out of range. The offending command is ignored"
	    		"and has no other side effect than to set the error flag.");
	    break;
	case GL_INVALID_OPERATION:
	    printf("The specified operation is not allowed in the current state."
	    		"The offending command is ignored and has no other side effect than to set"
	    		"the error flag.");
	    break;
	case GL_INVALID_FRAMEBUFFER_OPERATION:
	    printf("The command is trying to render to or read from the framebuffer"
	    		"while the currently bound framebuffer is not framebuffer complete"
	    		"(i.e. the return value from glCheckFramebufferStatus is not case"
	    		"GL_FRAMEBUFFER_COMPLETE). The offending command is ignored and has no other"
	    		"side effect than to set the error flag.");
	    break;
	case GL_OUT_OF_MEMORY:
	    printf("There is not enough memory left to execute the command."
	    		"The state of the GL is undefined, except for the state of the error flags"
	    		", after this error is recorded.");
	    break;
	default:
			printf("Something else has gone wrong\n");

	}

}

