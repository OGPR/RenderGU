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
	 0.f,0.f,       // texture bottom left
	 1.f,0.f,		//texture bottom right
	 0.f,1.f,		//texture top left
	 1.f, 1.f,		//top right
};

unsigned int indexArray[3*2] =
{
    0, 1, 3, // first triangle
    0, 2, 3, // second triangle
};

float cube[] = {
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};

float cube_forIndexedDraw[] =
{
	//front face
    -0.5f,-0.5f,0.5f, // bottom left
     0.5f,-0.5f,0.5f, // bottom right
    -0.5f, 0.5f,0.5f, // top left
     0.5f, 0.5f,0.5f, // top right
	 0.f,0.f,       // texture bottom left
	 1.f,0.f,		//texture bottom right
	 0.f,1.f,		//texture top left
	 1.f, 1.f,		//top right

	//back face
    -0.5f,-0.5f,-0.5f, // bottom left
     0.5f,-0.5f,-0.5f, // bottom right
    -0.5f, 0.5f,-0.5f, // top left
     0.5f, 0.5f,-0.5f, // top right
	 0.f,0.f,       // texture bottom left
	 1.f,0.f,		//texture bottom right
	 0.f,1.f,		//texture top left
	 1.f, 1.f,		//top right

	//top face
    -0.5f, 0.5f,0.5f, // front left
     0.5f, 0.5f,0.5f, // front right
    -0.5f, 0.5f,-0.5f, // back left
     0.5f, 0.5f,-0.5f, // back right
	 0.f,0.f,       // texture bottom left
	 1.f,0.f,		//texture bottom right
	 0.f,1.f,		//texture top left
	 1.f, 1.f,		//top right

	//bottom face
    -0.5f,-0.5f,0.5f, // front left
     0.5f,-0.5f,0.5f, // front right
    -0.5f, -0.5f,-0.5f, // back left
     0.5f, -0.5f,-0.5f, // back right
	 0.f,0.f,       // texture bottom left
	 1.f,0.f,		//texture bottom right
	 0.f,1.f,		//texture top left
	 1.f, 1.f,		//top right

	//left face
    -0.5f,-0.5f,0.5f, // front bottom
     -0.5f,0.5f,0.5f, // front top
    -0.5f, -0.5f,-0.5f, // back bottom
     -0.5f, 0.5f,-0.5f, // back top
	 0.f,0.f,       // texture bottom left
	 1.f,0.f,		//texture bottom right
	 0.f,1.f,		//texture top left
	 1.f, 1.f,		//top right

	//right face
    0.5f,-0.5f,0.5f, // front bottom
    0.5f,0.5f,0.5f, // front top
    0.5f, -0.5f,-0.5f, // back bottom
    0.5f, 0.5f,-0.5f, // back top
	 0.f,0.f,       // texture bottom left
	 1.f,0.f,		//texture bottom right
	 0.f,1.f,		//texture top left
	 1.f, 1.f,		//top right
};

float cube_raw[] =
{
	// positions          // normals           // texture coords
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
};

// Will get clash with C floor() at call site if you call it floor!
float our_floor[] =
{
	// positions		// Tex coord
	// Tri 1
	//x     y      z
	 1.0f, -0.5f,  1.0f, 1.f, 0.f,    //"bottom" right
	-1.0f, -0.5f,  1.0f, 0.f, 0.f,	  //"bottom" left
	-1.0f, -0.5f, -1.0f, 0.f, 1.f,    // "top" left

	// Tri 2
	//x     y      z
	 1.0f, -0.5f,  1.0f, 1.f, 0.f,    // "bottom" right"
	-1.0f, -0.5f, -1.0f, 0.f, 1.f,    // "top" left"
	 1.0f, -0.5f, -1.0f, 1.f, 1.f,    // "top" right
};

float quad[] =
{
	// positions
	0.0f,  0.5f,  0.0f,
	0.0f, -0.5f,  0.0f,
	1.0f, -0.5f,  0.0f,

	0.0f,  0.5f,  0.0f,
	1.0f, -0.5f,  0.0f,
	1.0f,  0.5f,  0.0f,
};


