#pragma once

#include<glad/glad.h> // Need glad before glew as it includes OpenGL headers
#include<GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/constants.hpp>
#include "CustomMatrices.h"
#include <vector>

// Camera set up
// Before we had -3 as we were translating the _scene_ back to give the impression of moving.
// Now we have +3 as we are actually moving a camera into the direction we want (+z, out of the scree),
// and keeping the scene fixed. Swapping neg/pos applies to y and x also
glm::vec3 cameraPosHome = glm::vec3(0.f, 0.f, 3.f);
glm::vec3 cameraLookAtHome = glm::vec3(0.f, 0.f, -1.f);
glm::vec3 cameraPos = cameraPosHome;
glm::vec3 cameraLookDirection = glm::vec3(0.f, 0.f, -1.f);
glm::vec3 cameraMoveStep = glm::vec3(1.f, 1.f, 1.f);
float radius = cameraPosHome.z;
glm::vec3 cameraCurrRotAngle = glm::vec3(glm::half_pi<float>(), 0.f, 0.f);
const glm::vec3 cameraRotateStep = glm::vec3(1.f, 1.f, 1.f);
glm::vec3 cameraUp = glm::vec3(0.f, 1.f, 0.f);

std::vector < std::vector<float> > RotMat_zx;
std::vector < std::vector<float> > RotMat_zy;
std::vector < std::vector<float> > RotMat_xy;

static bool vertFlip = false;
static float texture2Amount = 0.2f;
static bool depthTest = true;
static bool wireframeMode = false;
static bool l_pressed = false;
static bool f_pressed = false;
static bool z_pressed = false;

void processInput(GLFWwindow *window, float deltaTime)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_L) == GLFW_RELEASE && l_pressed)
    	l_pressed = false;

    if (glfwGetKey(window, GLFW_KEY_F) == GLFW_RELEASE && f_pressed)
    	l_pressed = false;

    if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_RELEASE && z_pressed)
    	z_pressed = false;

    if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS && !l_pressed && !wireframeMode)
    {
    	l_pressed = true;
    	wireframeMode = true;
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }

    if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS && !l_pressed && wireframeMode)
    {
    	l_pressed = true;
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

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
    	cameraPos += cameraMoveStep.z * deltaTime * cameraLookDirection;
    }

    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
    	cameraPos -= cameraMoveStep.z * deltaTime * cameraLookDirection;
    }

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
    	cameraPos -= glm::normalize(glm::cross(cameraLookDirection, cameraUp)) * cameraMoveStep.x * deltaTime;
    }

    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
    	cameraPos += glm::normalize(glm::cross(cameraLookDirection, cameraUp)) * cameraMoveStep.x * deltaTime;
    }

    if (glfwGetKey(window, GLFW_KEY_KP_4) == GLFW_PRESS
    		|| glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
    {
    	float thetaPrev = cameraCurrRotAngle.y;
    	cameraCurrRotAngle.y -= cameraRotateStep.y * deltaTime;
    	float theta = cameraCurrRotAngle.y -thetaPrev;

		RotMat_zx = YawMatrix(theta);

    	glm::vec3 cameraFrontNew = TransformVec(-cameraLookDirection, RotMat_zx);

    	cameraLookDirection = -cameraFrontNew;
    }

    if (glfwGetKey(window, GLFW_KEY_KP_6) == GLFW_PRESS
    		|| glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
    {
    	float thetaPrev = cameraCurrRotAngle.y;
    	cameraCurrRotAngle.y += cameraRotateStep.y * deltaTime;
    	float theta = cameraCurrRotAngle.y -thetaPrev;

    	RotMat_zx = YawMatrix(theta);

    	glm::vec3 cameraFrontNew = TransformVec(-cameraLookDirection, RotMat_zx);

    	cameraLookDirection = -cameraFrontNew;
    }

    if (glfwGetKey(window, GLFW_KEY_KP_8) == GLFW_PRESS
    		|| glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
    {
    	float thetaPrev = cameraCurrRotAngle.x;
    	cameraCurrRotAngle.x += cameraRotateStep.x * deltaTime;
    	float theta = cameraCurrRotAngle.x -thetaPrev;

    	RotMat_zy = PitchMatrix(theta);
    	glm::vec3 cameraFrontNew = TransformVec(-cameraLookDirection, RotMat_zy);

    	cameraLookDirection = -cameraFrontNew;
    }

    if (glfwGetKey(window, GLFW_KEY_KP_2) == GLFW_PRESS
    		|| glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
    {
    	float thetaPrev = cameraCurrRotAngle.x;
    	cameraCurrRotAngle.x -= cameraRotateStep.x * deltaTime;
    	float theta = cameraCurrRotAngle.x -thetaPrev;

    	RotMat_zy = PitchMatrix(theta);
    	glm::vec3 cameraFrontNew = TransformVec(-cameraLookDirection, RotMat_zy);

    	cameraLookDirection = -cameraFrontNew;
    }

    if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS)
    {
    	float thetaPrev = cameraCurrRotAngle.z;
    	cameraCurrRotAngle.z += cameraRotateStep.z * deltaTime;
    	float theta = cameraCurrRotAngle.z -thetaPrev;

    	RotMat_xy = RollMatrix(theta);
    	glm::vec3 cameraUpNew = TransformVec(cameraUp, RotMat_xy);

    	cameraUp = cameraUpNew;
    }

    if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS)
    {
    	float thetaPrev = cameraCurrRotAngle.z;
    	cameraCurrRotAngle.z -= cameraRotateStep.z * deltaTime;
    	float theta = cameraCurrRotAngle.z -thetaPrev;

    	RotMat_xy = RollMatrix(theta);
    	glm::vec3 cameraUpNew = TransformVec(cameraUp, RotMat_xy);

    	cameraUp = cameraUpNew;
    }

    if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS)
    {
    	cameraUp = glm::vec3(0.f, 1.f, 0.f);
    }


    if (glfwGetKey(window, GLFW_KEY_KP_7) == GLFW_PRESS)
    {
    	cameraPos.y += cameraMoveStep.y * deltaTime;
    }

    if (glfwGetKey(window, GLFW_KEY_KP_9) == GLFW_PRESS)
    {
    	cameraPos.y -= cameraMoveStep.y * deltaTime;
    }

    if (glfwGetKey(window, GLFW_KEY_KP_5) == GLFW_PRESS
    		|| glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS)
    {
    	cameraPos = cameraPosHome;
    	cameraCurrRotAngle = glm::vec3(glm::half_pi<float>(), 0.f, 0.f);
    	cameraLookDirection = cameraLookAtHome;
    	cameraUp = glm::vec3(0.f, 1.f, 0.f);
    }
}

static float lastxpos = 0.f;
static float lastypos = 0.f;
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
		if (xpos > lastxpos)
		{
			lastxpos = xpos;
			cameraCurrRotAngle.y += cameraRotateStep.y * 0.005f;
			cameraPos.z = radius * sin(cameraCurrRotAngle.x) * cos(cameraCurrRotAngle.y);
			cameraPos.x = radius * sin(cameraCurrRotAngle.x) * sin(cameraCurrRotAngle.y) ;
			cameraPos.y = radius * cos(cameraCurrRotAngle.x);
		}

		if (xpos < lastxpos)
		{
			lastxpos = xpos;
			cameraCurrRotAngle.y -= cameraRotateStep.y * 0.005f;
			cameraPos.z = radius * sin(cameraCurrRotAngle.x) * cos(cameraCurrRotAngle.y);
			cameraPos.x = radius * sin(cameraCurrRotAngle.x) * sin(cameraCurrRotAngle.y) ;
			cameraPos.y = radius * cos(cameraCurrRotAngle.x);
		}

		if (ypos > lastypos)
		{
			lastypos = ypos;
			cameraCurrRotAngle.x -= cameraRotateStep.x * 0.005f;
			cameraPos.z = radius * sin(cameraCurrRotAngle.x) * cos(cameraCurrRotAngle.y);
			cameraPos.x = radius * sin(cameraCurrRotAngle.x) * sin(cameraCurrRotAngle.y) ;
			cameraPos.y = radius * cos(cameraCurrRotAngle.x);
		}

		if (ypos < lastypos)
		{
			lastypos = ypos;
			cameraCurrRotAngle.x += cameraRotateStep.x * 0.005f;
			cameraPos.z = radius * sin(cameraCurrRotAngle.x) * cos(cameraCurrRotAngle.y);
			cameraPos.x = radius * sin(cameraCurrRotAngle.x) * sin(cameraCurrRotAngle.y) ;
			cameraPos.y = radius * cos(cameraCurrRotAngle.x);
		}
}
