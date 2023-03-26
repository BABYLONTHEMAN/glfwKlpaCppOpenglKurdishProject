#pragma once

#include<GL/glew.h>
class Mesh
{
public:
	Mesh();

	void createMesh(GLfloat *vertices, unsigned int *indices, unsigned int numOfVertices, unsigned int numofIndices);
	void RenderMesh();
	void clearMesh();

	~Mesh();


private:
	GLuint VAO, VBO, IBO;
	GLsizei indexCount;
};

