#pragma once

unsigned int indexArray[3*2] =
{
    0, 1, 3, // first triangle
    0, 2, 3, // second triangle
};

float quad[] =
{
	// positions		// Tex coords
	0.0f,  0.5f,  0.0f, 0.f, 1.f,    // top left
	0.0f, -0.5f,  0.0f, 0.f, 0.f,	  // bottom left
	1.0f, -0.5f,  0.0f, 1.f, 0.f,    // bottom right

	0.0f,  0.5f,  0.0f, 0.f, 1.f,    // top left
	1.0f, -0.5f,  0.0f, 1.f, 0.f,    // bottom right
	1.0f,  0.5f,  0.0f, 1.f, 1.f,    // top right
};



