#pragma once

#include<glad/glad.h> // Need glad before glew as it includes OpenGL headers
#include<GLFW/glfw3.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

// OpenGL Texture Set up
void textureSetup()
{
	int img_width, img_height, img_nChannels;
	unsigned char* img_data = stbi_load("container.jpg", &img_width, &img_height, &img_nChannels,0);

	if (!img_data)
		printf("Failed to load texture...");

	unsigned int texture;
	glGenTextures(1,&texture);

	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, img_width, img_height, 0, GL_RGB, GL_UNSIGNED_BYTE, img_data);
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(img_data);

	// Second texture
	//TODO it would be cool to fist check if we _need_ to do this - would have to check where 0.0 is on image y-axis
	stbi_set_flip_vertically_on_load(true);

	img_data = stbi_load("awesomeface.png", &img_width, &img_height, &img_nChannels, 0);


	if (!img_data)
		printf("Failed to load texture 2...");

	unsigned int texture2;
	glGenTextures(1, &texture2);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture2);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, img_width, img_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, img_data);
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_set_flip_vertically_on_load(false);
	stbi_image_free(img_data);

	// Diffuse Lighting map (our 3rd texture here)
	img_data = stbi_load("diffuseMap.png", &img_width, &img_height, &img_nChannels, 0);


	if (!img_data)
		printf("Failed to load texture 3...");

	unsigned int texture3;
	glGenTextures(1, &texture3);

	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, texture3);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, img_width, img_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, img_data);
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(img_data);

	// Ambient Lighting map (our 4th texture here)
	// Same as diffuse at the moment
	img_data = stbi_load("diffuseMap.png", &img_width, &img_height, &img_nChannels, 0);

	if (!img_data)
		printf("Failed to load texture 3...");

	unsigned int texture4;
	glGenTextures(1, &texture4);

	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, texture3);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, img_width, img_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, img_data);
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(img_data);

	// Specular Lighting map (our 5th texture here)
	img_data = stbi_load("specularMap.png", &img_width, &img_height, &img_nChannels, 0);

	if (!img_data)
		printf("Failed to load texture 3...");

	unsigned int texture5;
	glGenTextures(1, &texture5);

	glActiveTexture(GL_TEXTURE4);
	glBindTexture(GL_TEXTURE_2D, texture5);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, img_width, img_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, img_data);
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(img_data);
}