#pragma once

#include<glad/glad.h> // Need glad before glew as it includes OpenGL headers
#include<GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/constants.hpp>
#include <vector>
#include <assert.h>
using Matrix = std::vector < std::vector<float> >;
using Row = std::vector<float>;

// Note these is not a 4x4 in the homogeneous coordinate sense - I only put the extra
// row of zeros (and zero at the start of each row) because I wanted to offset the index
// (i.e [1][1] is what you expect it to be. This will all go away when I use glm mats and vecs

Matrix YawMatrix (float theta)
{
	return std::vector< std::vector<float> >
	{
		{0, 0, 0, 0},
		{0, cosf(theta), 0, -sinf(theta)},
		{0, 0, 1, 0},
		{0, sinf(theta), 0, cosf(theta)},
	};
}

Matrix PitchMatrix (float theta)
{
	return std::vector< std::vector<float> >
	{
    	    {0, 0, 0, 0},
    	    {0, 1, 0, 0},
    	    {0, 0, cosf(theta), -sinf(theta)},
    	    {0, 0, sinf(theta), cosf(theta)},
	};
}

Matrix RollMatrix (float theta)
{
	return std::vector< std::vector<float> >
	{
		{0, 0, 0, 0},
		{0, cosf(theta), -sinf(theta), 0},
		{0, sinf(theta), cosf(theta), 0},
		{0, 0, 0, 1},
	};
}

glm::vec3 TransformVec(glm::vec3 vec, Matrix transform)
{
	glm::vec3 result;
	result.x =
			vec.x * transform[1][1] + vec.y * transform[1][2] + vec.z * transform[1][3];
	result.y =
			vec.x * transform[2][1] + vec.y * transform[2][2] + vec.z * transform[2][3];
	result.z =
			vec.x * transform[3][1] + vec.y * transform[3][2] + vec.z * transform[3][3];

	return result;
}



Matrix MatMul(Matrix M1, Matrix M2)
{
	/**
	 * Preconditions
	 *
	 * Might be a little silly to go to all this effort for non-zero indexing,
	 * but hey lets do it here anyway!
	 */

	// This one is important. Stronger condition than usual for matrix mult - we are dealing with square Matrices
	assert(M1.size() == 4);
	assert(M2.size() == 4);

	Row firstRow = M1[0];
	for (auto elem : firstRow)
	{
		assert(elem == 0);
	}
	firstRow = M2[0];
	for (auto elem : firstRow)
	{
		assert(elem == 0);
	}

	for (int i = 1; i < 4; ++i)
	{
		assert(M1[i][0] == 0);
		assert(M2[i][0] == 0);
	}

	// End Preconditions

	Matrix result =
	{
		{0.f, 0.f, 0.f, 0.f},
		{0.f, 0.f, 0.f, 0.f},
		{0.f, 0.f, 0.f, 0.f},
		{0.f, 0.f, 0.f, 0.f}
	};

	for (int i = 1; i < 4; ++i)
	{
		for (int j = 1; j < 4; ++j)
		{
			result[i][j] += M1[i][j] * M2[i][j];
		}
	}

	return result;
}



