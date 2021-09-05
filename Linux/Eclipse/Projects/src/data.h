#pragma once

float vertex[] =
{
     0.0f, 0.0f, 0.0f, //Position
};

int modelScaleFactor = 4;
// 4.0f = 1 unit in model space
// Create an equilateral triangle of side length half a model space unit.
// For now, place origin at center of triangle.
// Also, only 2D for now

float triangle[3*6] =
{
     -0.5f * modelScaleFactor, -0.5f* modelScaleFactor, 0.0f,
     0.0f, 0.5f* modelScaleFactor, 0.0f,
     0.5f* modelScaleFactor, -0.5f* modelScaleFactor, 0.0f,
	 1.f, 0.f, 0.f,    // Colors
	 0.f, 1.f, 0.f,
	 0.f, 0.f, 1.f,
};
