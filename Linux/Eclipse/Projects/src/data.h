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

// CCW winding
float cube[] = {

	/* The vertex annotations are given wrt to the face orientation.
	 * For example the bottom face will have the notion of back and front vertices
	 *
	 * However, left and right faces do not follow this convention as they initially were annotated
	 * with top/bottom notions (made sense visually I think).
	 */

	/// Back Face

	// Tri 1
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, // Bottom left
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // Top right
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f, // Bottom right

	// Tri 2
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // Top right
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, // Bottom right
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // Top Left

    /// Front face

	// Tri 1
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // Bottom left
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // Bottom right
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f, // Top right

	// Tri 2
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f, // Top right
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f, // Top left
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // Bottom left

    /// Left face

	// Tri 1
	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // Top right
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // Top left
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // Bottom left

	// Tri 2
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // Bottom left
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // Bottom right
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // Top right

     /// Right face

	// Tri 1
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // Top left
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // Bottom right
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // Top right

	 // Tri 2
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // Bottom right
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // Top left
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // Bottom left

    // Bottom face

	 // Tri 1
	 -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // Back left
     0.5f, -0.5f, -0.5f,  1.0f, 1.0f, // Back right
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // Front right

	 // Tri 2
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // Front right
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // Front left
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // Back left

    /// Top face

	// Tri 1
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // Back left
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // Front right
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // Back right

	// Tri 2
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // Front right
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // Back left
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, // Front left
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
	// positions		// Tex coords
	0.0f,  0.5f,  0.0f, 0.f, 1.f,    // top left
	0.0f, -0.5f,  0.0f, 0.f, 0.f,	  // bottom left
	1.0f, -0.5f,  0.0f, 1.f, 0.f,    // bottom right

	0.0f,  0.5f,  0.0f, 0.f, 1.f,    // top left
	1.0f, -0.5f,  0.0f, 1.f, 0.f,    // bottom right
	1.0f,  0.5f,  0.0f, 1.f, 1.f,    // top right
};

// Simple quad in NDC - for example for use in off-screen rendering
float simpleQuad[] =
{
	// positions       // Tex coords
	-1.0f, 1.0f, 0.0f, 0.0f, 1.0f,    //top left
	 1.0f, 1.0f, 0.0f, 1.0f, 1.0f,    //top right
	 1.0f, -1.0f, 0.0f, 1.0f, 0.0f,	 //bottom right

	-1.0f, 1.0f, 0.0f, 0.0f, 1.0f,	 //top left
	-1.0f, -1.0f, 0.0f, 0.0f, 0.0f,	 //bottom left
	 1.0f, -1.0f, 0.0f, 1.0f, 0.0f,	 //bottom right
};


