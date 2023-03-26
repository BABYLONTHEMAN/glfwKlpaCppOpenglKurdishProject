#include "Material.h"



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
/////////
void sht::UseMaterial(GLuint specularIntensityLocation, GLuint shininessLocation)
{
	glUniform1f(specularIntensityLocation,specularIntensity);
	glUniform1f(shininessLocation,Shininess); // we need to make vector in Camera.h line 19 glm::vec3...

}
////////

sht::~sht()
{
}
