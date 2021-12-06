#pragma once

#include<glad/glad.h> // Need glad before glew as it includes OpenGL headers
#include<GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/constants.hpp>
#include "CustomMatrices.h"
#include <vector>
#include <iostream>
#include <limits.h>
#include "Camera.h"


static bool vertFlip = false;
static float texture2Amount = 0.2f;
static bool depthTest = true;
static bool visualiseDepthBuffer = false;
static bool stencilTest = false;
static bool wireframeMode = false;
static bool l_pressed = false;
static bool f_pressed = false;
static bool z_pressed = false;
static unsigned int PhongExp = 32;
static unsigned int uintMax = UINT_MAX;
static bool p_pressed = false;
static bool o_pressed = false;
static bool _1_pressed = false;
static bool _2_pressed = false;
static bool _3_pressed = false;
static bool _4_pressed = false;
static bool _5_pressed = false;
static bool _6_pressed = false;
static bool _7_pressed = false;
static bool f1_pressed = false;
static bool f2_pressed = false;
static bool ambientLight = true;
static bool diffuseLight = true;
static bool specularLight = true;
static bool isLightDirectional = true;
static bool isLightPoint = false;
static bool isLightSpot = false;
static bool attenuation = false;

void processInput(GLFWwindow *window,
                  CameraVariables* cameraVariables,
                  float deltaTime)
{
    // TODO still process other input if no camera
    if (!cameraVariables)
        return;

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
        cameraVariables->cameraPos +=
                cameraVariables->cameraMoveStep.z * deltaTime * cameraVariables->cameraLookDirection;

    }

    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        cameraVariables->cameraPos -=
                cameraVariables->cameraMoveStep.z * deltaTime * cameraVariables->cameraLookDirection;
    }

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        cameraVariables->cameraPos -=
                glm::normalize(glm::cross(
                        cameraVariables->cameraLookDirection, cameraVariables->cameraUp))
                        * cameraVariables->cameraMoveStep.x * deltaTime;
    }

    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        cameraVariables->cameraPos += glm::normalize(glm::cross(
                cameraVariables->cameraLookDirection, cameraVariables->cameraUp))
                        * cameraVariables->cameraMoveStep.x * deltaTime;
    }

    if (glfwGetKey(window, GLFW_KEY_KP_4) == GLFW_PRESS
    		|| glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
    {
        YawLeft(&cameraVariables->cameraLookDirection,
                &cameraVariables->cameraYaw,
                cameraVariables->cameraPitch,
                cameraVariables->cameraCurrRotAngle.y,
                deltaTime);
    }

    if (glfwGetKey(window, GLFW_KEY_KP_6) == GLFW_PRESS
    		|| glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
    {
        YawRight(&cameraVariables->cameraLookDirection,
                 &cameraVariables->cameraYaw,
                 cameraVariables->cameraPitch,
                 cameraVariables->cameraCurrRotAngle.y,
                 deltaTime);
    }

    if (glfwGetKey(window, GLFW_KEY_KP_8) == GLFW_PRESS
    		|| glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
    {
        PitchUp(&cameraVariables->cameraLookDirection,
                cameraVariables->cameraYaw,
                &cameraVariables->cameraPitch,
                cameraVariables->cameraCurrRotAngle.x,
                deltaTime);
    }

    if (glfwGetKey(window, GLFW_KEY_KP_2) == GLFW_PRESS
    		|| glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
    {
        PitchDown(&cameraVariables->cameraLookDirection,
                  cameraVariables->cameraYaw,
                  &cameraVariables->cameraPitch,
                  cameraVariables->cameraCurrRotAngle.x,
                  deltaTime);
    }

    if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS)
    {
    	float thetaPrev = cameraVariables->cameraCurrRotAngle.z;
        cameraVariables->cameraCurrRotAngle.z += cameraVariables->cameraRotateStep.z * deltaTime;
    	float theta = cameraVariables->cameraCurrRotAngle.z -thetaPrev;

        cameraVariables->RotMat_xy = RollMatrix(theta);
    	glm::vec3 cameraUpNew = TransformVec(cameraVariables->cameraUp, cameraVariables->RotMat_xy);

        cameraVariables->cameraUp = cameraUpNew;
    }

    if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS)
    {
    	float thetaPrev = cameraVariables->cameraCurrRotAngle.z;
        cameraVariables->cameraCurrRotAngle.z -= cameraVariables->cameraRotateStep.z * deltaTime;
    	float theta = cameraVariables->cameraCurrRotAngle.z -thetaPrev;

        cameraVariables->RotMat_xy = RollMatrix(theta);
    	glm::vec3 cameraUpNew = TransformVec(cameraVariables->cameraUp, cameraVariables->RotMat_xy);

        cameraVariables->cameraUp = cameraUpNew;
    }

    if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS)
    {
        cameraVariables->cameraUp = glm::vec3(0.f, 1.f, 0.f);
    }


    if (glfwGetKey(window, GLFW_KEY_KP_7) == GLFW_PRESS)
    {
        cameraVariables->cameraPos.y += cameraVariables->cameraMoveStep.y * deltaTime;
    }

    if (glfwGetKey(window, GLFW_KEY_KP_9) == GLFW_PRESS)
    {
        cameraVariables->cameraPos.y -= cameraVariables->cameraMoveStep.y * deltaTime;
    }

    if (glfwGetKey(window, GLFW_KEY_KP_5) == GLFW_PRESS
    		|| glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS)
    {
    	// TODO come back to this;
        cameraVariables->cameraPos = cameraVariables->cameraPosHome;
        cameraVariables->cameraCurrRotAngle = glm::vec3(glm::half_pi<float>(), glm::pi<float>(), 0.f);
        cameraVariables->cameraYaw = cameraVariables->cameraCurrRotAngle.y;
        cameraVariables->cameraPitch = cameraVariables->cameraCurrRotAngle.x;
        cameraVariables->cameraLookDirection = cameraVariables->cameraLookAtHome;
        cameraVariables->cameraUp = glm::vec3(0.f, 1.f, 0.f);
    }

    if (glfwGetKey(window, GLFW_KEY_P) == GLFW_RELEASE && p_pressed)
    	p_pressed = false;

    if (glfwGetKey(window, GLFW_KEY_O) == GLFW_RELEASE && o_pressed)
    	o_pressed = false;

    if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS && !p_pressed)
    {

    	p_pressed = true;
    	if (PhongExp != uintMax/2 + 1)
			PhongExp <<= 1;
    	std::cout << PhongExp << std::endl;
    }

    if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS && !o_pressed)
    {
    	o_pressed = true;
    	PhongExp >>= 1;
    	PhongExp = PhongExp >= 1 ? PhongExp : 1;
    	std::cout << PhongExp << std::endl;
    }

    if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS)
    	PhongExp = 32;

    if (glfwGetKey(window, GLFW_KEY_1) == GLFW_RELEASE && _1_pressed)
    	_1_pressed = false;

    if (glfwGetKey(window, GLFW_KEY_2) == GLFW_RELEASE && _2_pressed)
    	_2_pressed = false;

    if (glfwGetKey(window, GLFW_KEY_3) == GLFW_RELEASE && _3_pressed)
    	_3_pressed = false;

    if (glfwGetKey(window, GLFW_KEY_4) == GLFW_RELEASE && _4_pressed)
    	_4_pressed = false;

    if (glfwGetKey(window, GLFW_KEY_5) == GLFW_RELEASE && _5_pressed)
    	_5_pressed = false;

    if (glfwGetKey(window, GLFW_KEY_6) == GLFW_RELEASE && _6_pressed)
    	_6_pressed = false;

    if (glfwGetKey(window, GLFW_KEY_7) == GLFW_RELEASE && _7_pressed)
    	_7_pressed = false;

    if (glfwGetKey(window, GLFW_KEY_F1) == GLFW_RELEASE && f1_pressed)
    	f1_pressed = false;

    if (glfwGetKey(window, GLFW_KEY_F2) == GLFW_RELEASE && f2_pressed)
    	f2_pressed = false;

    if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS && !_1_pressed)
    {
    	_1_pressed = true;
    	ambientLight = !ambientLight;
    }

    if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS && !_2_pressed)
    {
    	_2_pressed = true;
    	diffuseLight = !diffuseLight;
    }

    if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS && !_3_pressed)
    {
    	_3_pressed = true;
    	specularLight = !specularLight;
    }

    if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS && !_4_pressed)
    {
    	_4_pressed = true;
    	isLightDirectional = !isLightDirectional;
    	isLightPoint = false;
    	isLightSpot = false;
    }

    if (glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS && !_5_pressed)
    {
    	_5_pressed = true;
    	isLightPoint = !isLightPoint;
    	isLightDirectional = false;
    	isLightSpot = false;
    }

    if (glfwGetKey(window, GLFW_KEY_6) == GLFW_PRESS && !_6_pressed)
    {
    	_6_pressed = true;
    	isLightSpot = !isLightSpot;
    	isLightDirectional = false;
    	isLightPoint = false;
    }

    if (glfwGetKey(window, GLFW_KEY_7) == GLFW_PRESS && !_7_pressed)
    {
    	_7_pressed = true;
    	attenuation = !attenuation;
    }

    if (glfwGetKey(window, GLFW_KEY_F1) == GLFW_PRESS && !f1_pressed)
    {
    	f1_pressed = true;
    	visualiseDepthBuffer = !visualiseDepthBuffer;
    }

    if (glfwGetKey(window, GLFW_KEY_F2) == GLFW_PRESS && !f2_pressed)
    {
    	f2_pressed = true;
    	stencilTest = !stencilTest;
    }

}

static float lastxpos = 0.f;
static float lastypos = 0.f;

//TODO Mouse
/*
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
*/