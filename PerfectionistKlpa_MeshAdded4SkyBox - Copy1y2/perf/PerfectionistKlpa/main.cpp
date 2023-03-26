#pragma once
#define STB_IMAGE_IMPLEMENTATION


#include <SDL.h>
//#undef main
#include<stdio.h>
#include<string>
#include<string.h>
#include <algorithm>
#include<stdlib.h>
#include<cmath>
#include<vector> //array list
#include<fstream>
#include"CommonValues.h"
 
#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include <map>
//#include<glm/mat4x4.hpp> //rotATION TRANSLATION AND SCALE 
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
//#ifndef HEADERFILE_H
//#define HEADERFILE_H
#include "Window.h"
//#include <WinUser.h>
//#include <WinUser.h>
//#include"Light.h"
//#include"PointLight.h"
//#include"DirectionalLight.h"
//#include"SpotLight.h"
//#include"Mesh.h"
//#include"Mesh.h"

//#include"stb_image.h"
//#endif
//#include"CommonValues.h" //
//#include "Window.h"
//////////////#include "Mesh.h"
//#include "Shader.h"
//#include "Camera.h"
//#include "Texture.h"
//#include "DirectionalLight.h"
//#include"SpotLight.h"
//#include "PointLight.h"
//#include "SpotLight.h"



//window dimensions 
//const GLint	WIDTH=800, HEIGHT = 600;
const float toRadians = 3.14159265f / 180.0f;


bool direction = true;
float triOffset = 0.0f; // line 224 while ... 
float triMaxoffset = 0.7f;
float triIncrement = 0.0005f;

float curAngle = 0.0f;

bool sizeDirection = true;
float curSize = 0.4f;
float maxSize = 0.8f;
float minSize = 0.1f;

bool sarawa = false;


////////////////////*************************
////////////class sht h

class sht
{
public:
	sht();
	sht(GLfloat sIntensity, GLfloat shine);
	void UseSht(GLuint specularIntensityLocation, GLuint shininessLocation);
	~sht();
private:
	GLfloat specularIntensity;
	GLfloat Shininess;
};

////////////////////*************************
// class sht cpp
sht::sht()
{
	specularIntensity = 0.0f;
	Shininess = 0.0f;
}
///////////
sht::sht(GLfloat sIntensity, GLfloat shine)
{
	specularIntensity = sIntensity;
	Shininess = shine;

}

void sht::UseSht(GLuint specularIntensityLocation, GLuint shininessLocation)
{
	glUniform1f(specularIntensityLocation, specularIntensity);
	glUniform1f(shininessLocation, Shininess); // we need to make vector in Camera.h line 19 glm::vec3...

}
sht::~sht()
{
}

////////////////////////////////////////////////////**********************************************************************
//// Light h
class Light
{
public:
	Light();
	Light(GLfloat red, GLfloat green, GLfloat blue,
		GLfloat aIntensity, GLfloat dIntensity);

	//void UseLight(GLfloat abmbientIntensityLocation, GLfloat ambientColourLocation,
		//GLfloat directionLocation); 
	//these should be GLuint but nvm GLfloat also works anyway
	//but in Material the Teacher uses GLuint

	~Light();

protected:
	glm::vec3 colour;
	GLfloat ambientIntensity; //is universal lighting 
	//glm::vec3 direction;
	GLfloat diffuseIntensity;
	// diffuse lighting ... is the light coming to a direction and stuff 
};

/////// Light cpp

Light::Light()
{
	colour = glm::vec3(1.0f, 1.0f, 1.0f);
	ambientIntensity = 1.0f;
	//direction = glm::vec3(0.0f, -1.0f, 0.0f);
	diffuseIntensity = 0.0f;
}

Light::Light(GLfloat red, GLfloat green, GLfloat blue, GLfloat aIntensity, GLfloat dIntensity)
{
	colour = glm::vec3(red, green, blue);
	ambientIntensity = aIntensity;
	//direction = glm::vec3(xDir, yDir, zDir);
	diffuseIntensity = dIntensity;
}

Light::~Light()
{
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// class PointLight.h


// NOTE Base class is like this class base : public derived { };
class PointLight :
	public Light
{
public:
	PointLight();

	PointLight(GLfloat red, GLfloat green, GLfloat blue,
		GLfloat aIntensity, GLfloat dIntensity,
		GLfloat xPos, GLfloat yPos, GLfloat zPos,
		GLfloat con, GLfloat lin, GLfloat exp);

	void UseLight(GLuint ambientIntensityLocation, GLuint ambientColourLocation,
		GLuint diffuseIntensityLocation, GLuint positionlocation, GLuint constantLocation,
		GLuint linearlocation, GLuint exponentLocation);

	~PointLight();

protected:

	glm::vec3 position;

	GLfloat constant, linear, exponent;
};


//////////////////////////////////////////////////////////////////////////////////////////////
// // class pointlight cpp
//////////////////////////////////////////////////////////////////////////////////////////////




PointLight::PointLight() :Light()
{
	position = glm::vec3(0.0f, 0.0f, 0.0f);
	constant = 1.0f;
	linear = 0.0f;
	exponent = 0.0f;

}
///////////
PointLight::PointLight(GLfloat red, GLfloat green, GLfloat blue,
	GLfloat aIntensity, GLfloat dIntensity,
	GLfloat xPos, GLfloat yPos, GLfloat zPos,
	GLfloat con, GLfloat lin, GLfloat exp) :Light(red, green, blue, aIntensity, dIntensity) {

	position = glm::vec3(xPos, yPos, zPos);
	constant = con;
	linear = lin;
	exponent = exp;
}
//////////

void PointLight::UseLight(GLuint ambientIntensityLocation, GLuint ambientColourLocation,
	GLuint diffuseIntensityLocation, GLuint positionlocation, GLuint constantLocation,
	GLuint linearlocation, GLuint exponentLocation)
{
	glUniform1f(ambientIntensityLocation, ambientIntensity);
	glUniform3f(ambientColourLocation, colour.x, colour.y, colour.z);
	//glUniform3f(directionLocation, direction.x, direction.z, direction.z);
	glUniform1f(diffuseIntensityLocation, diffuseIntensity);
	glUniform3f(positionlocation, position.x, position.y, position.z);
	glUniform1f(constantLocation, constant);
	glUniform1f(linearlocation, linear);
	glUniform1f(exponentLocation, exponent);


}

PointLight::~PointLight()
{
}

//////////////////////////////////////////////////////////////////////////////////////////////
////SPOTLIGHT H
class SpotLight :
	public PointLight
{
public:
	SpotLight();

	SpotLight(GLfloat red, GLfloat green, GLfloat blue,
		GLfloat aIntensity, GLfloat dIntensity,
		GLfloat xPos, GLfloat yPos, GLfloat zPos,
		GLfloat xDir, GLfloat yDir, GLfloat zDir,
		GLfloat con, GLfloat lin, GLfloat exp,
		GLfloat edg);

	void UseLight(GLuint ambientIntensityLocation, GLuint ambientColourLocation,
		GLuint diffuseIntensityLocation, GLuint positionlocation, GLuint directionLocation,
		GLuint constantLocation, GLuint linearlocation, GLuint exponentLocation,
		GLuint edgeLocation);
	//moving the Spotlight 'our Torch around'
	void SetFlash(glm::vec3 pos, glm::vec3 dir);
	~SpotLight();



private:
	glm::vec3 direction;
	GLfloat edge, procEdge;

};

//////////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////////////
////SPOTLIGHT cpp

//default constructor is example()::example()  :  example() 
SpotLight::SpotLight() : PointLight()
{
	direction = glm::vec3(0.0f, -1.0f, 0.0f);
	edge = 0.0f;
	procEdge = cos(glm::radians(edge));
}

SpotLight::SpotLight(GLfloat red, GLfloat green, GLfloat blue,
	GLfloat aIntensity, GLfloat dIntensity,
	GLfloat xPos, GLfloat yPos, GLfloat zPos,
	GLfloat xDir, GLfloat yDir, GLfloat zDir,
	GLfloat con, GLfloat lin, GLfloat exp,
	GLfloat edg) : PointLight(red, green, blue,
		/* point light base constructor*/ aIntensity, dIntensity, xPos, yPos, zPos, con, lin, exp)
{
	//direction = glm::vec3(xDir, yDir, zDir); // normalize it or rendering wrong colors 
	direction = glm::normalize(glm::vec3(xDir, yDir, zDir)); // 
	edge = edg;
	procEdge = cosf(glm::radians(edge));
}
void SpotLight::UseLight(GLuint ambientIntensityLocation, GLuint ambientColourLocation,
	GLuint diffuseIntensityLocation, GLuint positionlocation, GLuint directionLocation,
	GLuint constantLocation, GLuint linearlocation, GLuint exponentLocation,
	GLuint edgeLocation)
{
	////////////////////// la PointLight.cpp yawa copypaste krawa
	glUniform1f(ambientIntensityLocation, ambientIntensity);
	glUniform3f(ambientColourLocation, colour.x, colour.y, colour.z);
	//glUniform3f(directionLocation, direction.x, direction.z, direction.z);
	glUniform1f(diffuseIntensityLocation, diffuseIntensity);
	glUniform3f(positionlocation, position.x, position.y, position.z);
	glUniform1f(constantLocation, constant);
	glUniform1f(linearlocation, linear);
	glUniform1f(exponentLocation, exponent);
	glUniform3f(directionLocation, direction.x, direction.y, direction.z);
	glUniform1f(edgeLocation, procEdge);
	//////////////////////////////////

}

void SpotLight::SetFlash(glm::vec3 pos, glm::vec3 dir)
{
	position = pos;
	direction = dir;
}
///////////////////////////////////////////////
SpotLight::~SpotLight()
{
}

///////////////////////////////////////////////////////////////////////////////////////////////
class DirectionalLight :
	public Light
{
public:
	DirectionalLight();
	DirectionalLight(GLfloat red, GLfloat green, GLfloat blue,
		GLfloat aIntensity, GLfloat dIntensity,
		GLfloat xDir, GLfloat yDir, GLfloat zDir);

	void UseLight(GLfloat ambientIntensityLocation, GLfloat ambientColourLocation,

		GLfloat diffuseIntensityLocation, GLfloat directionLocation);
	~DirectionalLight();
protected:
	glm::vec3 direction;
};

///////////////////////////////////////////////***************************************************************************
////////////////////////////////////////////////////**********************************************************************
//class DirectionalLight .cpp

DirectionalLight::DirectionalLight() :Light()
{
	direction = glm::vec3(0.0f, -1.0f, 0.0f);
}

DirectionalLight::DirectionalLight(GLfloat red, GLfloat green, GLfloat blue,
	GLfloat aIntensity, GLfloat dIntensity,
	GLfloat xDir, GLfloat yDir, GLfloat zDir) :Light(red, green, blue, aIntensity, dIntensity)
{
	direction = glm::vec3(xDir, yDir, zDir);
	//colour = glm::vec3(red, green, blue);
}

void DirectionalLight::UseLight(GLfloat ambientIntensityLocation, GLfloat ambientColourLocation,

	GLfloat diffuseIntensityLocation, GLfloat directionLocation)
{

	glUniform3f(ambientColourLocation, colour.x, colour.y, colour.z);
	glUniform1f(ambientIntensityLocation, ambientIntensity);
	glUniform3f(directionLocation, direction.x, direction.y, direction.z);
	glUniform1f(diffuseIntensityLocation, diffuseIntensity);
}


DirectionalLight::~DirectionalLight()
{
}
//////////////////////////////*****************************************************************************************


// texture h
class Texture
{
public:

	Texture();

	Texture(const char* fileloc);

	////////////////////////////////
	void LoadTexture();
	void useTexture();
	void clearTexture();
	////////////////////////////////
	~Texture();



private:
	GLuint textureID;
	int width, height, bitdepth;
	///////////////
	const char* fileLocation;
};

/////////////////////////////////////////*********************************************************************************
//texture cpp

Texture::Texture()
{
	textureID = 0;
	width = 0;
	height = 0;
	bitdepth = 0;
	fileLocation = "";
	stbi_set_flip_vertically_on_load(true);

}

Texture::Texture(const char* fileloc)
{
	textureID = 0;
	width = 0;
	height = 0;
	bitdepth = 0;
	fileLocation = fileloc;
}
///////////////////////////

void Texture::LoadTexture()
{
	unsigned char *texData = stbi_load(fileLocation, &width, &height, &bitdepth, 0);
	if (!texData)
	{
		printf(" failed ...to do stuff find: %s\n", fileLocation);
		return;
	}
	////// gl stuff
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, texData);
	glGenerateMipmap(GL_TEXTURE_2D);
	///////////////////////////// unbind
	glBindTexture(GL_TEXTURE_2D, 0);

	//stbi_image_free(texData);

}

//////////// Last class we make 18:57 
void Texture::useTexture()
{
	//texture unit and stuff 
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureID);

}

////////////

void Texture::clearTexture()
{

	glDeleteTextures(1, &textureID);
	textureID = 0;
	width = 0;
	height = 0;
	bitdepth = 0;
	fileLocation = "";

}



//free up the memory 
Texture::~Texture()
{
	clearTexture();
}
// ...
////////////Class Mesh .h //*****************************************************************************************

class Mesh
{
public:
	Mesh();

	void createMesh(GLfloat* vertices, unsigned int* indices, unsigned int numOfVertices, unsigned int numofIndices);
	void RenderMesh();
	void clearMesh();

	~Mesh();


protected:
	GLuint VAO, VBO, IBO;
	GLsizei indexCount;
};

////////////Class Mesh Cpp //**************************************************************************************

Mesh::Mesh()
{
	VAO = 0;
	VBO = 0;
	IBO = 0;
	indexCount = 0;

}


void Mesh::createMesh(GLfloat* vertices, unsigned int* indices, unsigned int numOfVertices, unsigned int numOfIndices)

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


//////////////////////////////*****************************************************************************************
// Camera h

class Camera
{
public:
	Camera();
	Camera(glm::vec3 startPosition, glm::vec3 startUp, GLfloat startYaw, GLfloat startPitch, GLfloat startMoveSpeed, GLfloat startTurnSpeed);
	void keyControl(bool* keys, GLfloat deltaTime);
	void mouseControl(GLfloat Xchange, GLfloat Ychange);

	glm::vec3 getCameraPosition();
	glm::vec3 getCameraDirection();
	glm::mat4 calculateViewMatrix();
	
	

	~Camera();

private:
	glm::vec3 position;
	glm::vec3 front;
	glm::vec3 up;
	glm::vec3 right;
	glm::vec3 worldUp;

	GLfloat yaw;
	GLfloat pitch;

	GLfloat moveSpeed;
	GLfloat turnSpeed;
	void Update();
};

//////////////////////////////*****************************************************************************************
// Camera Cpp

Camera::Camera() {}

Camera::Camera(glm::vec3 startPosition, glm::vec3 startUp, GLfloat startYaw, GLfloat startPitch, GLfloat startMoveSpeed, GLfloat startTurnSpeed)
{
	position = startPosition;
	worldUp = startUp;
	yaw = startYaw;
	pitch = startPitch;
	front = glm::vec3(0.0f, 0.0f, -1.0f);
	moveSpeed = startMoveSpeed;
	turnSpeed = startTurnSpeed;

	Update();
}
/////////////
void Camera::keyControl(bool* keys, GLfloat deltaTime)
{
	//delta time is toslow down frames in games otherwise have 10k frame per second
	GLfloat velocity = moveSpeed * deltaTime;

	if (keys[GLFW_KEY_W])
	{
		position += front * velocity;
	}
	if (keys[GLFW_KEY_S])
	{
		position -= front * velocity;
	}
	if (keys[GLFW_KEY_A])
	{
		position -= right * velocity;
	}
	if (keys[GLFW_KEY_D])
	{
		position += right * velocity;
	}
	if (keys[GLFW_KEY_R]) //rotate 
	{
		sarawa = true;
	}
	if (keys[GLFW_KEY_F]) //reset rotate
	{
		sarawa = false;
	}
}

void Camera::mouseControl(GLfloat Xchange, GLfloat Ychange)
{
	Xchange *= turnSpeed;
	Ychange *= turnSpeed;
	yaw += Xchange;
	pitch += Ychange;

	if (pitch > 89.0f)
	{
		pitch = 89.0f;

	}
	if (pitch < -89.0f)
	{
		pitch = -89.0f;
	}

	Update();
}

glm::mat4 Camera::calculateViewMatrix()
{

	return glm::lookAt(position, position + front, up); //lookAt functioneka wata bnwara :)


}
//////////////
///vec3 for shininess and stuff specular lighting 
glm::vec3 Camera::getCameraPosition()
{
	return position; // hold that position and pass it into our shader , now we go to shader vert ...
}
//////////////
glm::vec3 Camera::getCameraDirection()
{
	return glm::normalize(front);
}

//////////////
void Camera::Update()
{
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	front = glm::normalize(front);

	right = glm::normalize(glm::cross(front, worldUp));
	up = glm::normalize(glm::cross(right, front));
}

Camera::~Camera()
{
}

////////
Camera camera;
///////


////////////////////////////////////////SHADER CLASS 
// 
// 
//////////////////////////////*****************************************************************************************
//
// class sht h



///////////////////////////////////////////////***************************************************************************

////////////////////////////////////////////////////**********************************************************************
// ///////////////////////////////////////////////***************************************************************************
////////////////////////////////////////////////////**********************************************************************
// ///////////////////////////////////////////////***************************************************************************
////////////////////////////////////////////////////**********************************************************************
// ///////////////////////////////////////////////***************************************************************************
////////////////////////////////////////////////////**********************************************************************
// ///////////////////////////////////////////////***************************************************************************
////////////////////////////////////////////////////**********************************************************************
// ///////////////////////////////////////////////***************************************************************************
////////////////////////////////////////////////////**********************************************************************
// ///////////////////////////////////////////////***************************************************************************
////////////////////////////////////////////////////**********************************************************************


sht shinyMaterial;
sht dullMaterial;

DirectionalLight mainLight;
PointLight pointLights[MAX_POINT_LIGHTS];
SpotLight spotLights[MAX_SPOT_LIGHTS];

GLfloat 	deltaTime = 0.0f;
GLfloat 	lastTime = 0.0f;

// Vertex Shader
static const char* vShader = "Shaders/shader.vert";
// Fragment Shader
static const char* fShader = "Shaders/shader.frag";

void calcAverageNormals(unsigned int* indices, unsigned int indiceCount, GLfloat* vertices, unsigned int verticeCount,
	unsigned int VLength, unsigned int normalOffset)
{
	for (size_t i = 0; i < indiceCount; i += 3)
	{
		unsigned int in0 = indices[i] * VLength;
		unsigned int in1 = indices[i + 1] * VLength;
		unsigned int in2 = indices[i + 2] * VLength;
		glm::vec3 v1(vertices[in1] - vertices[in0], vertices[in1 + 1] - vertices[in0 + 1], vertices[in1 + 2] - vertices[in0 + 2]);
		glm::vec3 v2(vertices[in2] - vertices[in0], vertices[in2 + 1] - vertices[in0 + 1], vertices[in2 + 2] - vertices[in0 + 2]);
		glm::vec3 normal = glm::cross(v1, v2);
		normal = glm::normalize(normal);

		in0 += normalOffset; in1 += normalOffset; in2 += normalOffset;
		vertices[in0] += normal.x; 	vertices[in0 + 1] += normal.y; 	vertices[in0 + 2] += normal.z;
		vertices[in1] += normal.x; 	vertices[in1 + 1] += normal.y; 	vertices[in1 + 2] += normal.z;
		vertices[in2] += normal.x; 	vertices[in2 + 1] += normal.y; 	vertices[in2 + 2] += normal.z;
	}

	for (size_t i = 0; i < verticeCount / VLength; i++)
	{

		unsigned int nOffset = i * VLength + normalOffset;
		glm::vec3 vec(vertices[nOffset], vertices[nOffset + 1], vertices[nOffset + 2]);
		vec = glm::normalize(vec);
		vertices[nOffset] = vec.x; vertices[nOffset + 1] = vec.y; vertices[nOffset + 2] = vec.z;
	}
}






// shader h  
class Shader
{
public:
	Shader();

	//this reads file and pass to compileShader(); 
	void createFromString(const char* vertexCode, const char* fragmentCode);
	//little bit code in shader here 40:21 vid clearn up code 
	void createFromFiles(const char* vertexLocation, const char* fragmentlocation);
	void Validate(); //<><><<>>><<<><<><><><>
	std::string ReadFile(const char* fileLocation);

	GLuint GetProjectionLocation();
	GLuint GetModelLocation();
	GLuint GetViewLocation();
	GLuint GetAmbientIntensityLocation();
	GLuint GetAmbientColourLocation();
	GLuint GetDiffuseIntensityLocation();
	GLuint GetDirectionLocation();
	GLuint GetSpecularIntensityLocation();
	GLuint GetShininessLocation();
	GLuint GetEyePositionLocation();
	GLuint GetSkyColourLocation();

	//we add another function point light lecture 'NOTE: pass it as a pointer * to &mainLight address 
	void SetDirectionalLight(DirectionalLight* dLight);
	void SetPointLights(PointLight* pLight, unsigned int lightCount);
	void SetSpotLights(SpotLight* sLight, unsigned int lightCount);
	void useShader();
	void clearShader();
public:
	void RenderPass(glm::mat4 viewMatrix, glm::mat4 projectionMatrix);
	~Shader();

private:
	int pointLightCount;
	int spotLightCount;



	GLuint shaderID, uniformProjection, uniformModel, uniformView, uniformEyePosition,
		//uniformAmbientIntensity,uniformAmbientColour,uniformDiffuseIntensity,UniformDirection,
		uniformSpecularIntensity, uniformShininess,location_skyColour;
	///Struct
	struct
	{
		GLuint uniformColour;
		GLuint uniformAmbientIntensity;
		GLuint uniformDiffuseIntensity;

		GLuint uniformDirection;
	} uniformDirectionalLight;

	////////End Struct
	GLuint uniformPointLightCount;
	////// another Struct

	struct
	{
		GLuint uniformColour;
		GLuint uniformAmbientIntensity;
		GLuint uniformDiffuseIntensity;

		GLuint uniformPosition;
		GLuint uniformConstant;
		GLuint uniformlinear;
		GLuint uniformExponent;
	} uniformPointLight[MAX_POINT_LIGHTS];

	///////
	GLuint uniformSpotLightCount;
	struct
	{
		GLuint uniformColour;
		GLuint uniformAmbientIntensity;
		GLuint uniformDiffuseIntensity;

		GLuint uniformPosition;
		GLuint uniformConstant;
		GLuint uniformlinear;
		GLuint uniformExponent;

		GLuint uniformDirection;
		GLuint uniformedge;

	} uniformSpotLight[MAX_SPOT_LIGHTS];

	void compileShader(const char* vertexCode, const char* fragmentCode);
	void AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType);
};
///////////Put DirectionalLight Here before shader goddamit 
// //

//////////////////////////////*****************************************************************************************
// shader cpp
Shader::Shader()
{
	shaderID = 0;
	uniformModel = 0;
	uniformProjection = 0;

	pointLightCount = 0;
	spotLightCount = 0;
}

void Shader::createFromString(const char* vertexCode, const char* fragmentCode)

{
	compileShader(vertexCode, fragmentCode);
}

void Shader::createFromFiles(const char* vertexLocation, const char* fragmentLocation)
{
	std::string vertexString = ReadFile(vertexLocation);
	std::string fragmentString = ReadFile(fragmentLocation);
	const char* vertexCode = vertexString.c_str();
	const char* fragmentCode = fragmentString.c_str();

	compileShader(vertexCode, fragmentCode);

}

std::string Shader::ReadFile(const char* fileLocation)
{
	std::string content;
	std::ifstream fileStream(fileLocation, std::ios::in);

	if (!fileStream.is_open()) {


		printf("Failed to read %s| File doesn not exist.", fileLocation);
		return "";
	}

	std::string line = "";
	while (!fileStream.eof())
	{
		std::getline(fileStream, line);
		content.append(line + "\n");
	}
	fileStream.close();
	return content;
}

void Shader::Validate()
{
	GLint result = 0;
	GLchar eLog[1024] = { 0 };

	glValidateProgram(shaderID);
	glGetProgramiv(shaderID, GL_VALIDATE_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(shaderID, sizeof(eLog), NULL, eLog);
		printf("Error validating program: '%s'\n", eLog);
		return;
	}
}
Window mainWindow;
std::vector<Mesh*> MeshList;
std::vector<Shader>shaderList;
void createShaders() {
	Shader* shader1 = new Shader();
	shader1->createFromFiles(vShader, fShader);
	shaderList.push_back(*shader1);
}

void Shader::compileShader(const char* vertexCode, const char* fragmentCode)

{

	shaderID = glCreateProgram();
	if (!shaderID) {
		printf("error fragment creating ...");

		return;

	}


	AddShader(shaderID, vertexCode, GL_VERTEX_SHADER);
	AddShader(shaderID, fragmentCode, GL_FRAGMENT_SHADER);


	//chunk of code 27:30 

	GLint result = 0;
	GLchar eLog[1024] = { 0 };

	glLinkProgram(shaderID);
	glGetProgramiv(shaderID, GL_LINK_STATUS, &result);

	if (!result)
	{
		glGetProgramInfoLog(shaderID, sizeof(eLog), NULL, eLog);
		printf("Error Linking Program  %d shader: '%s ", eLog);
		return;

	}
	glValidateProgram(shaderID);
	glGetProgramiv(shaderID, GL_VALIDATE_STATUS, &result);

	if (!result)
	{
		glGetProgramInfoLog(shaderID, sizeof(eLog), NULL, eLog);
		printf("Error Validating Program  %d shader: '%s ", eLog);
		return;

	}
	//uniformModel = glGetUniformLocation(shader, "xMove");
	uniformProjection = glGetUniformLocation(shaderID, "projection"); //idy projection axata naw variably uniformProjection
	uniformModel = glGetUniformLocation(shaderID, "model"); //idy model axata naw variably uniformModel uniformProjection
	uniformView = glGetUniformLocation(shaderID, "view");
	uniformDirectionalLight.uniformColour = glGetUniformLocation(shaderID, "directionalLight.base.colour");
	uniformDirectionalLight.uniformAmbientIntensity = glGetUniformLocation(shaderID, "directionalLight.base.ambientIntensity");
	uniformDirectionalLight.uniformDirection = glGetUniformLocation(shaderID, "directionalLight.direction"); //no .base for direction
	uniformDirectionalLight.uniformDiffuseIntensity = glGetUniformLocation(shaderID, "directionalLight.base.diffuseIntensity");
	uniformSpecularIntensity = glGetUniformLocation(shaderID, "sht.specularIntensity");
	uniformShininess = glGetUniformLocation(shaderID, "sht.shininess");
	uniformEyePosition = glGetUniformLocation(shaderID, "eyePosition");

	uniformPointLightCount = glGetUniformLocation(shaderID, "pointLightCount");
	location_skyColour = glGetUniformLocation(shaderID, "skyColour");
	
	//POINT
	for (size_t i = 0; i < MAX_POINT_LIGHTS; i++)       ///// these are all sets our uniform location values
	{
		char lockBuff[100] = { '\0' };
		snprintf(lockBuff, sizeof(lockBuff), "pointLights[%d].base.colour", i);
		uniformPointLight[i].uniformColour = glGetUniformLocation(shaderID, lockBuff);
		snprintf(lockBuff, sizeof(lockBuff), "pointLights[%d].base.ambientIntensity", i);
		uniformPointLight[i].uniformAmbientIntensity = glGetUniformLocation(shaderID, lockBuff);
		snprintf(lockBuff, sizeof(lockBuff), "pointLights[%d].base.diffuseIntensity", i);
		uniformPointLight[i].uniformDiffuseIntensity = glGetUniformLocation(shaderID, lockBuff);
		snprintf(lockBuff, sizeof(lockBuff), "pointLights[%d].position", i);
		uniformPointLight[i].uniformPosition = glGetUniformLocation(shaderID, lockBuff);
		snprintf(lockBuff, sizeof(lockBuff), "pointLights[%d].constant", i);
		uniformPointLight[i].uniformConstant = glGetUniformLocation(shaderID, lockBuff);
		snprintf(lockBuff, sizeof(lockBuff), "pointLights[%d].linear", i);
		uniformPointLight[i].uniformlinear = glGetUniformLocation(shaderID, lockBuff);
		snprintf(lockBuff, sizeof(lockBuff), "pointLights[%d].exponent", i);
		uniformPointLight[i].uniformExponent = glGetUniformLocation(shaderID, lockBuff);
		uniformPointLight[i].uniformExponent = glGetUniformLocation(shaderID, lockBuff);
	}
	///////////// SPOT
	uniformSpotLightCount = glGetUniformLocation(shaderID, "spotLightCount");

	for (size_t i = 0; i < MAX_SPOT_LIGHTS; i++)       ///// these are all sets our uniform location values
	{
		char lockBuff[100] = { '\0' };
		snprintf(lockBuff, sizeof(lockBuff), "spotLights[%d].base.base.colour", i);
		uniformSpotLight[i].uniformColour = glGetUniformLocation(shaderID, lockBuff);
		snprintf(lockBuff, sizeof(lockBuff), "spotLights[%d].base.base.ambientIntensity", i);
		uniformSpotLight[i].uniformAmbientIntensity = glGetUniformLocation(shaderID, lockBuff);
		snprintf(lockBuff, sizeof(lockBuff), "spotLights[%d].base.base.diffuseIntensity", i);
		uniformSpotLight[i].uniformDiffuseIntensity = glGetUniformLocation(shaderID, lockBuff);
		snprintf(lockBuff, sizeof(lockBuff), "spotLights[%d].base.position", i);
		uniformSpotLight[i].uniformPosition = glGetUniformLocation(shaderID, lockBuff);
		snprintf(lockBuff, sizeof(lockBuff), "spotLights[%d].base.constant", i);
		uniformSpotLight[i].uniformConstant = glGetUniformLocation(shaderID, lockBuff);
		snprintf(lockBuff, sizeof(lockBuff), "spotLights[%d].base.linear", i);
		uniformSpotLight[i].uniformlinear = glGetUniformLocation(shaderID, lockBuff);
		snprintf(lockBuff, sizeof(lockBuff), "spotLights[%d].base.exponent", i);
		uniformSpotLight[i].uniformExponent = glGetUniformLocation(shaderID, lockBuff);
		snprintf(lockBuff, sizeof(lockBuff), "spotLights[%d].direction", i);
		uniformSpotLight[i].uniformDirection = glGetUniformLocation(shaderID, lockBuff);
		snprintf(lockBuff, sizeof(lockBuff), "spotLights[%d].edge", i);
		uniformSpotLight[i].uniformedge = glGetUniformLocation(shaderID, lockBuff);

	}
}

void loadSkyColour(float r, float g, float b)
{
	glm::vec3(1.0f, 0.0f, 0.0f);
}

GLuint Shader::GetProjectionLocation()
{
	return uniformProjection;
}
GLuint Shader::GetModelLocation()
{
	return uniformModel;
}
GLuint Shader::GetViewLocation()
{
	return uniformView;
}

GLuint Shader::GetSkyColourLocation()
{
	return location_skyColour;
}
GLuint Shader::GetAmbientColourLocation()
{
	return uniformDirectionalLight.uniformColour;
}
GLuint Shader::GetAmbientIntensityLocation()
{
	return uniformDirectionalLight.uniformAmbientIntensity;
}
GLuint Shader::GetDiffuseIntensityLocation()
{
	return uniformDirectionalLight.uniformDiffuseIntensity;

}
GLuint Shader::GetDirectionLocation()
{
	return uniformDirectionalLight.uniformDirection;
}
/////////////////
GLuint Shader::GetSpecularIntensityLocation() {
	return uniformSpecularIntensity;
}
GLuint Shader::GetShininessLocation() {
	return uniformShininess;
}
GLuint Shader::GetEyePositionLocation() {
	return uniformEyePosition;
}


//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>/////////
void Shader::SetDirectionalLight(DirectionalLight* dLight)
{
	dLight->UseLight(uniformDirectionalLight.uniformAmbientIntensity, uniformDirectionalLight.uniformColour,
		uniformDirectionalLight.uniformDiffuseIntensity, uniformDirectionalLight.uniformDirection);
}
/////////Point Light <<<<<<<<<<<<<<<
void Shader::SetPointLights(PointLight* pLight, unsigned int lightCount)
{
	if (lightCount > MAX_POINT_LIGHTS) lightCount = MAX_POINT_LIGHTS;
	glUniform1i(uniformPointLightCount, lightCount);
	for (size_t i = 0; i < lightCount; i++)
	{
		pLight[i].UseLight(uniformPointLight[i].uniformAmbientIntensity, uniformPointLight[i].uniformColour,
			uniformPointLight[i].uniformDiffuseIntensity, uniformPointLight[i].uniformPosition,
			uniformPointLight[i].uniformConstant, uniformPointLight[i].uniformlinear,
			uniformPointLight[i].uniformExponent);

	}
}
void Shader::SetSpotLights(SpotLight* sLight, unsigned int lightCount)
{
	if (lightCount > MAX_SPOT_LIGHTS) lightCount = MAX_SPOT_LIGHTS;
	glUniform1i(uniformSpotLightCount, lightCount);
	for (size_t i = 0; i < lightCount; i++)
	{
		sLight[i].UseLight(uniformSpotLight[i].uniformAmbientIntensity, uniformSpotLight[i].uniformColour,
			uniformSpotLight[i].uniformDiffuseIntensity, uniformSpotLight[i].uniformPosition, uniformSpotLight[i].uniformDirection,
			uniformSpotLight[i].uniformConstant, uniformSpotLight[i].uniformlinear,
			uniformSpotLight[i].uniformExponent, uniformSpotLight[i].uniformedge);

	}
}
////////<,,,,,,,,,,,,,,,,,,,,,,,,,,,,


void Shader::useShader()

{
	glUseProgram(shaderID);

}



void Shader::clearShader() {
	if (shaderID != 0) {

		glDeleteProgram(shaderID);
		shaderID = 0;

	}
	uniformModel = 0;
	uniformProjection = 0;
}

void Shader::AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType)

{

	GLuint theShader = glCreateShader(shaderType);
	const GLchar* theCode[1];
	theCode[0] = shaderCode;

	GLint codeLength[1];
	codeLength[0] = strlen(shaderCode);

	glShaderSource(theShader, 1, theCode, codeLength);
	glCompileShader(theShader);///////////////////////////

	GLint result = 0;
	GLchar eLog[1024] = { 0 };


	glGetShaderiv(theShader, GL_COMPILE_STATUS, &result);

	if (!result)
	{
		glGetShaderInfoLog(theShader, sizeof(eLog), NULL, eLog);
		printf("Error compiling %d shader: '%s'\n", shaderType, eLog);
		return;

	}
	glAttachShader(theProgram, theShader);

}

Shader::~Shader()
{
	clearShader();

}
/////////////////////////////////////////*********************************************************************************
// 
Texture brick;
Texture kurd;
Texture fog;



void CreateObjects()
{
	unsigned int indices[] = {
		0, 3, 1,
		1, 3, 2,
		2, 3, 0,
		0, 1, 2
	};

	GLfloat vertices[] = {
		//	x      y      z			u	  v			nx	  ny    nz
			-1.0f, -1.0f, -0.6f,		0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
			0.0f, -1.0f, 1.0f,		0.5f, 0.0f,		0.0f, 0.0f, 0.0f,
			1.0f, -1.0f, -0.6f,		1.0f, 0.0f,		0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f,		0.5f, 1.0f,		0.0f, 0.0f, 0.0f
	};

	unsigned int floorIndices[] = {
		0, 2, 1,
		1, 2, 3
	};

	GLfloat floorVertices[] = {
		-6.0f, 0.0f, -6.0f,		0.0f, 0.0f,		0.0f, -1.0f, 0.0f,
		6.0f, 0.0f, -6.0f,		5.0f, 0.0f,		0.0f, -1.0f, 0.0f,
		-6.0f, 0.0f, 6.0f,		0.0f, 5.0f,		0.0f, -1.0f, 0.0f,
		6.0f, 0.0f, 6.0f,		5.0f, 5.0f,		0.0f, -1.0f, 0.0f
	};


	calcAverageNormals(indices, 12, vertices, 32, 8, 5);

	Mesh* obj1 = new Mesh(); //initialize everything to zero VBO = 0 .... etc 
	obj1->createMesh(vertices, indices, 32, 12); // 12 vertices for now
	MeshList.push_back(obj1);

	Mesh* obj2 = new Mesh(); //initialize everything to zero VBO = 0 .... etc 
	obj2->createMesh(vertices, indices, 32, 12); // 12 vertices for now
	MeshList.push_back(obj2);

	Mesh* obj3 = new Mesh(); //
	obj3->createMesh(floorVertices, floorIndices, 32, 6); // 
	MeshList.push_back(obj3);
}
// 
// ////
/////////////////////////////////////////*********************************************************************************


/////////////////////////////////////////*********************************************************************************
// RenderPass

// 
// 
/////////////////////////////////////////*********************************************************************************
/////////////////////////////////////////*********************************************************************************
// class SkyBox h
class skyBox
{


public:
	skyBox();

	skyBox(std::vector<std::string> faceLocations);
	void DrawSkybox(glm::mat4 viewMatrix, glm::mat4 projectionMatrix);

	~skyBox();

private:
	Mesh* skyMesh;
	Shader* skyShader;

	GLuint textureID;
	GLuint uniformProjection, uniformView;


};
skyBox skybox;
//////////////////// RenderPass

// ///////////////////
// class SkyBox cpp

skyBox::skyBox()
{
}
skyBox::skyBox(std::vector<std::string> faceLocations)
{
	//shader setup for skybox
	skyShader = new Shader();
	//stbi_set_flip_vertically_on_load(true);
	stbi_set_flip_vertically_on_load(false);
	//stbi_set_flip_vertically_on_load(false);
	skyShader->createFromFiles("Shaders/skyBox.vert", "Shaders/skyBox.frag");
	uniformProjection = skyShader->GetProjectionLocation();
	uniformView = skyShader->GetViewLocation();
	//Texture setup for skybox
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
	//stbi_set_flip_vertically_on_load(true);
	int width, height, bitdepth;
	for (size_t i = 0; i < 6; i++)
	{
		unsigned char *texData = stbi_load(faceLocations[i].c_str(), &width, &height, &bitdepth, 0);
		if (!texData)
		{
			printf(" failed ...to do stuff find: %s\n", faceLocations[i].c_str());
			return;
		}

		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, texData);
		stbi_image_free(texData);
		//stbi_set_flip_vertically_on_load(true);

	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//stbi_set_flip_vertically_on_load(true);

	//Mesh Setup for SkyBox
	unsigned int skyBoxindices[] = {
		//front
		0,1,2,
		2,1,3,
		//right
		2,3,5,
		5,3,7,
		//back
		5,7,4,
		4,7,6,
		//left
		4,6,0,
		0,6,1,
		//top
		4,0,5,
		5,0,2,
		//bottom
		1,6,3,
		3,6,7
	};

	float skyBoxVertices[] = {
		-1.0f,1.0f,-1.0f,      0.0f, 0.0f,   0.0f,0.0f,0.0f,
		-1.0f,-1.0f,-1.0f,     0.0f, 0.0f,   0.0f,0.0f,0.0f,
		1.0f,1.0f,-1.0f,       0.0f, 0.0f,   0.0f,0.0f,0.0f,
		1.0f,-1.0f,-1.0f,      0.0f, 0.0f,   0.0f,0.0f,0.0f,


		-1.0f,1.0f,1.0f,      0.0f, 0.0f,   0.0f,0.0f,0.0f,
		1.0f,1.0f,1.0f,       0.0f, 0.0f,   0.0f,0.0f,0.0f,
		-1.0f,-1.0f,1.0f,     0.0f, 0.0f,   0.0f,0.0f,0.0f,
		1.0f,-1.0f,1.0f,      0.0f, 0.0f,   0.0f,0.0f,0.0f
	};
	skyMesh = new Mesh();
	skyMesh->createMesh(skyBoxVertices, skyBoxindices, 64, 36);

}

void skyBox::DrawSkybox(glm::mat4 viewMatrix, glm::mat4 projectionMatrix) {

	viewMatrix = glm::mat4(glm::mat3(viewMatrix));
	glDepthMask(GL_FALSE);
	
	//stbi_set_flip_vertically_on_load(false);

	skyShader->useShader();

	glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
	glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(viewMatrix));

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
	skyMesh->RenderMesh();

	glDepthMask(GL_TRUE);
}



skyBox::~skyBox() {}




/////////////////////////////////////////*********************************************************************************
// ///////////----------------------------------------------------------------------------------- renderpass
void Shader::RenderPass(glm::mat4 viewMatrix, glm::mat4 projectionMatrix)
{
	glfwPollEvents();
	//glViewport(0, 0, 1366, 768);
	
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	skybox.DrawSkybox(viewMatrix, projectionMatrix);
	
	//glUseProgram(shader);

	shaderList[0].useShader();
	uniformModel = shaderList[0].GetModelLocation();
	uniformProjection = shaderList[0].GetProjectionLocation();
	uniformView = shaderList[0].GetViewLocation();
	//uniformAmbientColour = shaderList[0].GetAmbientColourLocation();
	//uniformAmbientIntensity = shaderList[0].GetAmbientIntensityLocation();
	//uniformDirection = shaderList[0].GetDirectionLocation();
	//uniformDiffuseintensity = shaderList[0].GetDiffuseIntensityLocation();
	uniformEyePosition = shaderList[0].GetEyePositionLocation();
	uniformSpecularIntensity = shaderList[0].GetSpecularIntensityLocation();
	uniformShininess = shaderList[0].GetShininessLocation();
	

	glm::vec3 LowerLight = camera.getCameraPosition();
	LowerLight.y -= 0.3f;
	spotLights[0].SetFlash(LowerLight, camera.getCameraDirection()); //moving Torch 'Spotlight.cpp, .h

	shaderList[0].SetDirectionalLight(&mainLight);
	shaderList[0].SetPointLights(pointLights, pointLightCount);
	shaderList[0].SetSpotLights(spotLights, spotLightCount);

	//mainLight.UseLight(uniformAmbientIntensity, uniformAmbientColour,
		//uniformDiffuseintensity,uniformDirection);

	//glm 
	glm::mat4 model(1.0f);

	glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
	glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
	glUniform3f(uniformEyePosition, camera.getCameraPosition().x, camera.getCameraPosition().y,
		camera.getCameraPosition().z);

	//CreateObjects();
	//createShaders();
	
}
// ///////////--------------------------------------------------------------------------------

/////////////////////////////////////////*********************************************************************************
int main(int argc, char* argv[])
{
	mainWindow = Window(1920, 1080); //1280 , 1024 or 1024, 768 mainWindow = Window(1366, 768);
	
	mainWindow.initialise();
	

	CreateObjects();
	createShaders();
	
	camera = Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -60.0f, 0.0f, 5.0f, 0.5f);
	////////////////////////////*****************************************************************************
	fog = Texture("Textures/grass.png"); // Textures/brick.png Textures/kurd.png Textures/kurdi.png Textures/slemani.png Alla
	fog.LoadTexture();
	brick = Texture("Textures/grass.png"); // Textures/brick.png Textures/kurd.png Textures/kurdi.png Textures/slemani.png Alla
	brick.LoadTexture();
	kurd = Texture("Textures/slemani.png");
	kurd.LoadTexture(); //kurd = Texture("Textures/kurd.png");   sand.LoadTexture(); 
	//kurd.LoadTexture();      sumer.LoadTexture();    grass.LoadTexture();
	//0.0f, 1.0f, 1.0f, 0.2f); is green 
	shinyMaterial = sht(1.0f, 256); // shininess is going like 2 4 16 32 ...etc
	dullMaterial = sht(0.3f, 4);
	mainLight = DirectionalLight(1.0f, 1.0f, 1.0f,// Matrix Green RGB: 
		0.1f, 0.1f,   //ambient , diffuse
		0.0f, 0.0f, -1.0f);

	unsigned int pointLightCount = 0;
	//////&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&& PointLight Stuff
	pointLights[0] = PointLight(0.0f, 3.0f, 0.0f,
		0.0f, 1.0f,
		0.0f, 0.0f, 0.0f,
		0.3f, 0.2f, 0.1f);
	/////&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
	/////////////////////////////////////***********************************************
	//pointLightCount++;
	pointLights[1] = PointLight(0.0f, 1.0f, 0.0f,
		0.0f, 1.0f,
		-4.0f, 2.0f, 0.0f,
		0.3f, 0.1f, 0.1f);
	//pointLightCount++;
	/////&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
	/////////////////////////////////////*******************SPOTLIGHT******************
	unsigned int spotLightCount = 0;
	spotLights[0] = SpotLight(0.0f, 0.0f, 1.0f, //rangy Torchaka
		0.0f, 1.0f,
		0.0f, 0.0f, 0.0f, //side
		0.0f, -1.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		20.0f); //how wide is our spread of angle of the SpotLight 'TORCH' is
	spotLightCount++;
	////////////////////////////////////////////////////////
	spotLights[1] = SpotLight(0.0f, 0.0f, 1.0f,
		0.0f, 1.0f,
		0.0f, 0.0f, 0.0f, //side
		-100.0f, -1.0f, 0.0f,//far to left , ....,....
		1.0f, 0.0f, 0.0f,//attenuation , .....,....
		20.0f); //how wide is our spread of angle of the SpotLight 'TORCH' is
	spotLightCount++;
	/////&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
	/////////////////////////////////////***********************************************
	//SKYBOX
	
	std::vector<std::string> skyboxFaces;
	//stbi_set_flip_vertically_on_load(true);
	//skyboxFaces.push_back("Textures/skybox/xpos.png"); Textures/slemani.png
	skyboxFaces.push_back("Textures/skybox/xpos.png");
	skyboxFaces.push_back("Textures/skybox/xneg.png");
	skyboxFaces.push_back("Textures/skybox/ypos.png");
	skyboxFaces.push_back("Textures/skybox/yneg.png");
	skyboxFaces.push_back("Textures/skybox/zpos.png");
	skyboxFaces.push_back("Textures/skybox/zneg.png");
	skybox = skyBox(skyboxFaces);
	
	//Camera Movement ***************************************************************
	/*
	glm::mat4 view;
	float radius = 2.0f;
	float camX = sin(SDL_GetTicks() / 1000.0f) * radius;
	float camZ = cos(SDL_GetTicks() / 1000.0f) * radius;

	view = glm::lookAt(
		glm::vec3(camX, 0.0f, camZ) + parentEntity.position,
		parentEntity.position,
		glm::vec3(0.0f, 1.0f, 0.0f));

	glUniformMatrix4fv(
		glGetUniformLocation(shader, "viewingMatrix"), 1, false, glm::value_ptr(view));
	*/
	//EndOfCamera Movement ***************************************************************


	/* 	skyboxFaces.push_back("Textures/skybox/xpos.png");
	skyboxFaces.push_back("Textures/skybox/xneg.png");
	skyboxFaces.push_back("Textures/skybox/yneg.png");
	skyboxFaces.push_back("Textures/skybox/ypos.png");
	skyboxFaces.push_back("Textures/skybox/zpos.png");
	skyboxFaces.push_back("Textures/skybox/zneg.png");*/
	skyBox skybox;
	//create Triangle
	GLuint uniformProjection = 0, uniformModel = 0, uniformView = 0, uniformEyePosition = 0,
		//uniformAmbientIntensity = 0, uniformAmbientColour = 0, uniformDirection = 0, uniformDiffuseintensity = 0,
		uniformSpecularIntensity = 0, uniformShininess = 0;
	/*glm::mat4 projection = glm::perspective(glm::radians(45.0f),
		(GLfloat)mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 100.0f);
		*/
	
		

	/*  MessageBox  https://learn.microsoft.com/en-us/windows/win32/dlgbox/using-dialog-boxes
		int DisplayConfirmSaveAsMessageBox();
	{
		int msgboxID = MessageBox(
			NULL,
			L"temp.txt already exists.\nDo you want to replace it?",
			L"Confirm Save As",
			MB_ICONEXCLAMATION | MB_YESNO
		);

		if (msgboxID == IDYES)
		{
			// TODO: add code
		}

		return msgboxID;
	}*/
		//loop untill window closes
	while (!mainWindow.getShouldclose())
	{
		GLfloat now = glfwGetTime(); //IF you using SDL instead of GLFW then ...SDL_getperformancecounter()
		deltaTime = now - lastTime; //for milliSeconds (now - lastTime)* 1000  SDL_getperformanceFrequency()
		lastTime = now;
		//Get + Handle user input ... any event keyboard mouse stuff user moving
		glfwPollEvents();

		camera.keyControl(mainWindow.getsKeys(), deltaTime);
		camera.mouseControl(mainWindow.getXchange(), mainWindow.getYchange());
		//clear windpw
		//glViewport(0, 0, 0.0f, 0.0f); //DELETE LINE----IF NOT COMPILED

		/////////////////////////////<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
		//glViewport(0, 0, 1366, 768);

		

		//skybox.DrawSkybox(viewMatrix, projectionMatrix);

		//glUseProgram(shader);

		shaderList[0].useShader();
		uniformModel = shaderList[0].GetModelLocation();
		uniformProjection = shaderList[0].GetProjectionLocation();
		uniformView = shaderList[0].GetViewLocation();
		//uniformAmbientColour = shaderList[0].GetAmbientColourLocation();
		//uniformAmbientIntensity = shaderList[0].GetAmbientIntensityLocation();
		//uniformDirection = shaderList[0].GetDirectionLocation();
		//uniformDiffuseintensity = shaderList[0].GetDiffuseIntensityLocation();
		uniformEyePosition = shaderList[0].GetEyePositionLocation();
		uniformSpecularIntensity = shaderList[0].GetSpecularIntensityLocation();
		uniformShininess = shaderList[0].GetShininessLocation();

		glm::vec3 LowerLight = camera.getCameraPosition();
		LowerLight.y -= 0.3f;
		spotLights[0].SetFlash(LowerLight, camera.getCameraDirection()); //moving Torch 'Spotlight.cpp, .h

		shaderList[0].SetDirectionalLight(&mainLight);
		shaderList[0].SetPointLights(pointLights, pointLightCount);
		shaderList[0].SetSpotLights(spotLights, spotLightCount);

		//mainLight.UseLight(uniformAmbientIntensity, uniformAmbientColour,
			//uniformDiffuseintensity,uniformDirection);

		//glm 


		//glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
		glUniform3f(uniformEyePosition, camera.getCameraPosition().x, camera.getCameraPosition().y,
			camera.getCameraPosition().z);


		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//////////////////////////////<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
		
		glm::mat4 model(1.0f);


		
		//glm::mat4 viewMatrix = glm::mat4 Camera::calculateViewMatrix() { return glm::lookAt(position, position + front, up); };
		//glm::mat4 projectionMatrix = glm::perspective(glm::radians(45.0f), (float)800 / (float)600, 0.1f, 100.0f);
		
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -2.5f));
		//model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));
		//model = glm::rotate(model, curAngle * toRadians, glm::vec3(0.0f, 1.0f, 0.0f)); // order of transforming is important which one comes 1st

		// glUniform1f(uniformXMove,triOffset); //set uniformXmove to the value of triOffset
		glm::mat4 projection = glm::perspective(glm::radians(60.0f), (GLfloat)mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 100.0f);

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

		/////////////////////////////////////////////////////////<><><><><><><><><><><><><><><><><>
		//stbi_set_flip_vertically_on_load(false);
		Shader renderpassObj;
		//renderpassObj.RenderPass(camera.calculateViewMatrix(),projection );
		/////////////////////////////////////////////////////////////<>-<>-<><-><->-<->-<->-<->-<><->
		renderpassObj.RenderPass(camera.calculateViewMatrix(), projection);

		stbi_set_flip_vertically_on_load(true);

		////use Alla**********
		//////////////////////////////////
		brick.useTexture();
		shinyMaterial.UseSht(uniformSpecularIntensity, uniformShininess);
		MeshList[0]->RenderMesh(); //////////mesh 00000000000000000000000000000000000000000

		model = glm::mat4(1.0f);
		//model = glm::translate(model, glm::vec3(0.1f, 2, 2.5f));
		//model = glm::translate(model, glm::vec3(triOffset, 0.0f, 0.0f));
		//model = glm::scale(model, glm::vec3(curSize, curSize, 1.0f));
		 model = glm::rotate(model, curAngle * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		 //model = glm::rotate(, curAngle * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		 if (sarawa)
		 {
			 model = glm::translate(model, glm::vec3(0.0f, -1.0f, 0.0f));
			 model = glm::rotate(model, curAngle , glm::vec3(1.0f, -1.0f, 0.0f));

		 }
		/////////////////////////////

		if (direction)
		{triOffset += triIncrement;}
		else
		{triOffset -= triIncrement;}
		if (abs(triOffset) >= triMaxoffset) //abs means absolute 
		{direction = !direction;  //its a switch 
		}
		curAngle += 0.01f;
		if (curAngle >= 360)
		{	curAngle -= 360;
		}
		if (sizeDirection) {
			curSize += 0.0001f;}
		else
		{curSize -= 0.0001f;}

		if (curSize >= maxSize || curSize <= minSize)
		{sizeDirection = !sizeDirection;}
		//////////////////////////////
		//model = glm::rotate(glm::mat4(1.0f), 15.14f, glm::vec3(8, 10, 10));
		//while (true) {
			//glm::rotate(model, glm::radians(5.f), glm::vec3(1, 0, 0));  // 5 degrees each iteration
		//}
		//model = glm::rotate(model, 1, glm::vec3(2.5f, 2.5f, 2.5f));
		//amodel = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));	//model = glm::scale(model, glm::vec3(curSize, curSize, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

		kurd.useTexture(); //dwham dana put it right above MeshList[1]->RenderMesh();
		dullMaterial.UseSht(uniformSpecularIntensity, uniformShininess);

		MeshList[1]->RenderMesh();
		//////////////////////
		model = glm::mat4(1.0f);
		//model = glm::rotate(model, curAngle * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));

	
		model = glm::translate(model, glm::vec3(0.0f, -2.0f, 0.0f));
		//model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));	//////////////////////////////////////
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

		fog.useTexture(); ////////////////////////////////////////////////
		shinyMaterial.UseSht(uniformSpecularIntensity, uniformShininess);

		MeshList[2]->RenderMesh();
		///////////////////////////////
	
		


		glUseProgram(0);
		//mainWindow.swapbuffers();
		mainWindow.swapbuffers();
	}

	return 0;
}
