#pragma once



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

// Simple quad in NDC
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


