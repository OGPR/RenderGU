#pragma once

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
struct CameraVariables
{
    glm::vec3 cameraPosHome = glm::vec3(0.f, 0.f, 3.f);
    glm::vec3 cameraLookAtHome = glm::vec3(0.f, 0.f, -1.f);
    glm::vec3 cameraPos = cameraPosHome;
    glm::vec3 cameraLookDirection = glm::vec3(0.f, 0.f, -1.f);
    glm::vec3 cameraMoveStep = glm::vec3(1.f, 1.f, 1.f);
    float radius = cameraPosHome.z;
    glm::vec3 cameraCurrRotAngle = glm::vec3(glm::half_pi<float>(),glm::pi<float>(), 0.f);
    glm::vec3 cameraRotateStep = glm::vec3(1.f, 1.f, 1.f);
    glm::vec3 cameraUp = glm::vec3(0.f, 1.f, 0.f);

    std::vector < std::vector<float> > RotMat_zx;
    std::vector < std::vector<float> > RotMat_zy;
    std::vector < std::vector<float> > RotMat_xy;

    float cameraYaw = cameraCurrRotAngle.y;
    float cameraPitch = cameraCurrRotAngle.x;
};

//// Camera Functions

void UpdateCameraLookDirection(glm::vec3* CameraLookDirection,
                               float* CameraYaw,
                               float* CameraPitch,
                               float* AngleToUpdate,
                               float Change)
{
    *AngleToUpdate += Change;

    CameraLookDirection->x = sin(*CameraPitch)*sin(*CameraYaw);
    CameraLookDirection->z = sin(*CameraPitch)*cos(*CameraYaw);
    CameraLookDirection->y = cos(*CameraPitch);
}
void YawLeft(glm::vec3* CameraLookDirection,
             float* CameraYaw,
             float CameraPitch,
             float CameraRotateStep,
             float deltaTime)
{
    *CameraYaw += CameraRotateStep * deltaTime;

    CameraLookDirection->x = sin(CameraPitch)*sin(*CameraYaw);
    CameraLookDirection->z = sin(CameraPitch)*cos(*CameraYaw);
}

void YawRight(glm::vec3* CameraLookDirection,
              float* CameraYaw,
              float CameraPitch,
              float CameraRotateStep,
              float deltaTime)
{
    *CameraYaw -= CameraRotateStep *deltaTime;

    CameraLookDirection->x = sin(CameraPitch) * sin(*CameraYaw);
    CameraLookDirection->z = sin(CameraPitch) * cos(*CameraYaw);
}

void PitchUp(glm::vec3* CameraLookDirection,
             float CameraYaw,
             float* CameraPitch,
             float CameraRotateStep,
             float deltaTime)
{
    *CameraPitch -= CameraRotateStep * deltaTime;

    CameraLookDirection->x = sin(*CameraPitch)*sin(CameraYaw);
    CameraLookDirection->z = sin(*CameraPitch)*cos(CameraYaw);
    CameraLookDirection->y = cos(*CameraPitch);

}

void PitchDown(glm::vec3* CameraLookDirection,
               float CameraYaw,
               float* CameraPitch,
               float CameraRotateStep,
               float deltaTime)
{
    *CameraPitch += CameraRotateStep * deltaTime;

    CameraLookDirection->x = sin(*CameraPitch)*sin(CameraYaw);
    CameraLookDirection->z = sin(*CameraPitch)*cos(CameraYaw);
    CameraLookDirection->y = cos(*CameraPitch);

}

void processInputCamera(GLFWwindow *window,
                  CameraVariables* cameraVariables,
                  float deltaTime)
{
    if (!cameraVariables)
        return;

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
        cameraVariables->cameraPos = cameraVariables->cameraPosHome;
        cameraVariables->cameraCurrRotAngle = glm::vec3(glm::half_pi<float>(), glm::pi<float>(), 0.f);
        cameraVariables->cameraYaw = cameraVariables->cameraCurrRotAngle.y;
        cameraVariables->cameraPitch = cameraVariables->cameraCurrRotAngle.x;
        cameraVariables->cameraLookDirection = cameraVariables->cameraLookAtHome;
        cameraVariables->cameraUp = glm::vec3(0.f, 1.f, 0.f);
    }


}
