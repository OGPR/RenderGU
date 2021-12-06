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
glm::vec3 cameraPosHome = glm::vec3(0.f, 0.f, 3.f);
glm::vec3 cameraLookAtHome = glm::vec3(0.f, 0.f, -1.f);
glm::vec3 cameraPos = cameraPosHome;
glm::vec3 cameraLookDirection = glm::vec3(0.f, 0.f, -1.f);
glm::vec3 cameraMoveStep = glm::vec3(1.f, 1.f, 1.f);
float radius = cameraPosHome.z;
glm::vec3 cameraCurrRotAngle = glm::vec3(glm::half_pi<float>(),glm::pi<float>(), 0.f);
const glm::vec3 cameraRotateStep = glm::vec3(1.f, 1.f, 1.f);
glm::vec3 cameraUp = glm::vec3(0.f, 1.f, 0.f);

std::vector < std::vector<float> > RotMat_zx;
std::vector < std::vector<float> > RotMat_zy;
std::vector < std::vector<float> > RotMat_xy;

//// Camera Functions
//TODO put into separate camera code
float CameraYaw = cameraCurrRotAngle.y;
float CameraPitch = cameraCurrRotAngle.x;

void UpdateCameraLookDirection(glm::vec3* CameraLookDirection,
                               float *AngleToUpdate,
                               float Change)
{
    *AngleToUpdate += Change;

    CameraLookDirection->x = sin(CameraPitch)*sin(CameraYaw);
    CameraLookDirection->z = sin(CameraPitch)*cos(CameraYaw);
    CameraLookDirection->y = cos(CameraPitch);
}
void YawLeft(glm::vec3* CameraLookDirection, float deltaTime)
{
    CameraYaw += cameraRotateStep.y * deltaTime;

    CameraLookDirection->x = sin(CameraPitch)*sin(CameraYaw);
    CameraLookDirection->z = sin(CameraPitch)*cos(CameraYaw);
}

void YawRight(glm::vec3* CameraLookDirection, float deltaTime)
{
    CameraYaw -= cameraRotateStep.y *deltaTime;

    CameraLookDirection->x = sin(CameraPitch) * sin(CameraYaw);
    CameraLookDirection->z = sin(CameraPitch) * cos(CameraYaw);
}

void PitchUp(glm::vec3* CameraLookDirection, float deltaTime)
{
    CameraPitch -= cameraRotateStep.x * deltaTime;

    CameraLookDirection->x = sin(CameraPitch)*sin(CameraYaw);
    CameraLookDirection->z = sin(CameraPitch)*cos(CameraYaw);
    CameraLookDirection->y = cos(CameraPitch);

}

void PitchDown(glm::vec3* CameraLookDirection, float deltaTime)
{
    CameraPitch += cameraRotateStep.x * deltaTime;

    CameraLookDirection->x = sin(CameraPitch)*sin(CameraYaw);
    CameraLookDirection->z = sin(CameraPitch)*cos(CameraYaw);
    CameraLookDirection->y = cos(CameraPitch);

}
////