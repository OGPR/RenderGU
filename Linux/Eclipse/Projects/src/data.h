#pragma once

float vertex[] =
{
     0.0f, 0.0f, 0.0f, //Position
};

float triangle[] =
{
     -0.5f, -0.5f, 0.0f, // lower-left
     0.0f, 0.5f, 0.0f,   // top-center
     0.5f, -0.5f, 0.0f,  // lower-right
	 1.f, 0.f, 0.f,    // Colors
	 0.f, 1.f, 0.f,
	 0.f, 0.f, 1.f,
	 0.0f, 0.0f,  // texture lower left
	 0.5f, 1.0f,  // texture top-center left
	 1.0f, 0.0f,  // texture lower-right
};

float rectangle[] =
{
    -0.5f,-0.5f,0.f, // bottom left
     0.5f,-0.5f,0.f, // bottom right
    -0.5f, 0.5f,0.f, // top left
     0.5f, 0.5f,0.f, // top right
	 1.f, 0.f, 0.f,    // Colors - only 3 as we want both triangles that will make this rect to have the same
	 0.f, 1.f, 0.f,
	 0.f, 0.f, 1.f,
};

unsigned int indexArray[3*2] =
{
    0, 1, 3, // first triangle
    0, 2, 3, // second triangle
};
