#include "Mesh.h"
//#include "Window.h"
//#include "Texture.h"

Mesh::Mesh()
{
	VAO = 0;
	VBO = 0;
	IBO = 0;
	indexCount = 0;

}


void Mesh::createMesh(GLfloat *vertices, unsigned int *indices, unsigned int numOfVertices, unsigned int numOfIndices)

{
	indexCount = numOfIndices;

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);


	glGenBuffers(1, &IBO);//buffer drwst akain 
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO); //bindy buffer akain
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * numOfIndices, indices, GL_STATIC_DRAW);// zanyary akaina nawi

	glGenBuffers(1, &VBO);//buffer drwst akain 
	glBindBuffer(GL_ARRAY_BUFFER, VBO); //bindy buffer akain
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * numOfVertices, vertices, GL_STATIC_DRAW); // zanyary akaina nawi

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]) * 8, 0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(vertices[0]) * 8, (void*)(sizeof(vertices[0]) * 3));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]) * 8, (void*)(sizeof(vertices[0]) * 5)); //5 jar yay bawlawa ta la 'NX'akawa 
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, 0); //UNBIND
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); //IMPORTANT:NOTE YOU SHOULD UNBIND VAO AFTER YOU UNBIND IBO
	glBindVertexArray(0);//UNBIND
}

void Mesh::RenderMesh()   //called glDrawElements 
{
	glBindVertexArray(VAO);// bakary aheninawa Bindy akain hamw jare ka bakary ahenin
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO); //some times doesn't need to bind this IBO, this for some graphic card buggs
	glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);// wena akeshin  
	//When glDrawElements is called,it uses count sequential elements from an enabled array, starting at indices to construct a sequence of geometric primitives.
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); //unbind IBO ka eshman penama
	glBindVertexArray(0); //unbind VAO ka eshman penama 

}


void Mesh::clearMesh()
{
	if (IBO != 0)
	{
		glDeleteBuffers(1, &IBO);
		IBO = 0;
	}

	if (VBO != 0)
	{
		glDeleteBuffers(1, &VBO);
		VBO = 0;
	}

	if (VAO != 0)
	{
		glDeleteVertexArrays(1, &VAO);
		VAO = 0;

	}
	indexCount = 0;
}


Mesh::~Mesh()
{

	clearMesh();
}
