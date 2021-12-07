#pragma once


//** Begin Helper function declarations
unsigned int CreateVBO();
void BindVBO(unsigned int VBO);
void AllocateMemoryVBO(unsigned int numberOfEntries, float* vertexArray);
unsigned int CreateVAO();
void BindVAO(unsigned int VAO);
void SetAttribute(GLuint index, GLint size, GLsizei stride, const void* offset);

//** End Helper function declarations

//** Begin Helper data structures declarations

struct QuadData
{
	int numberOfEntries = 3*5 + 3*5;
	float* data = quad;
} _quadData;

struct QuadAttributes
{
	struct Position
	{
		unsigned int index = 0;
		unsigned int size = 3;
		GLsizei stride = 5 * sizeof(float);
		const void* offset = 0;
	}pos;

	struct Texture
	{
		unsigned int index = 1;
		unsigned int size = 2;
		GLsizei stride = 5 * sizeof(float) ;
		const void* offset = (void * )(3 * sizeof(float));
	}tex;

};

struct SimpleQuadData
{
	int numberOfEntries = 3*5 + 3*5;
	float* data = simpleQuad;
} _simpleQuadData;

struct SimpleQuadAttributes
{
	struct Position
	{
		unsigned int index = 0;
		unsigned int size = 3;
		GLsizei stride = 5 * sizeof(float);
		const void* offset = 0;
	}pos;

	struct Texture
	{
		unsigned int index = 1;
		unsigned int size = 2;
		GLsizei stride = 5 * sizeof(float) ;
		const void* offset = (void * )(3 * sizeof(float));
	}tex;

};

//** End Helper data structures declarations

unsigned int vs_quad(float* vertex, unsigned int numberOfEntries)
{
	if (_quadData.numberOfEntries != numberOfEntries)
	{
		printf("Rendering the quad:\n");
		printf("Expected number of entries to be %d, but have received %d", _quadData.numberOfEntries, numberOfEntries);
		printf("\n Rendering has continued, but if is not what you expect, this might be one of the reasons why.");
	}

	BindVBO(CreateVBO());
	AllocateMemoryVBO(numberOfEntries, vertex);
	unsigned int VAO = CreateVAO(); // Will be returned, and set prior to return, so need to store it here
	BindVAO(VAO);

	QuadAttributes QA;
	SetAttribute(QA.pos.index, QA.pos.size, QA.pos.stride, QA.pos.offset);
	SetAttribute(QA.tex.index, QA.tex.size, QA.tex.stride, QA.tex.offset);

	return VAO;
}

unsigned int vs_simpleQuad(float* vertex, unsigned int numberOfEntries)
{
	if (_simpleQuadData.numberOfEntries != numberOfEntries)
	{
		printf("Rendering the simple quad:\n");
		printf("Expected number of entries to be %d, but have received %d", _simpleQuadData.numberOfEntries, numberOfEntries);
		printf("\n Rendering has continued, but if is not what you expect, this might be one of the reasons why.");
	}

	BindVBO(CreateVBO());
	AllocateMemoryVBO(numberOfEntries, vertex);
	unsigned int VAO = CreateVAO(); // Will be returned, and set prior to return, so need to store it here
	BindVAO(VAO);

	SimpleQuadAttributes SQA;
	SetAttribute(SQA.pos.index, SQA.pos.size, SQA.pos.stride, SQA.pos.offset);
	SetAttribute(SQA.tex.index, SQA.tex.size, SQA.tex.stride, SQA.tex.offset);

	return VAO;
}

//** Begin Helper function definitions
unsigned int CreateVBO()
{
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	return VBO;
}

void BindVBO(unsigned int VBO)
{
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
}

void AllocateMemoryVBO(unsigned int numberOfEntries, float* vertexArray)
{
    glBufferData(GL_ARRAY_BUFFER, numberOfEntries * sizeof(float), vertexArray, GL_STATIC_DRAW);
}

unsigned int CreateVAO()
{
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	return VAO;
}
void BindVAO(unsigned int VAO)
{
	glBindVertexArray(VAO);
}

void SetAttribute(GLuint index, GLint size, GLsizei stride, const void* offset)
{
    glVertexAttribPointer(index, size , GL_FLOAT, GL_FALSE, stride , offset);
    glEnableVertexAttribArray(index);
}
//** End Helper function definitions

//** Begin Helper data structures definitions

//** End Helper data structures definitions
