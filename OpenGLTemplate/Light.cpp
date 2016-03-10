#include "Light.h"

using namespace entities;
Light::Light(glm::vec3& _position, glm::vec3& _color)
{
	position = _position;
	color = _color;
}


Light::~Light()
{
}
