#pragma once
#include "GLM/glm.hpp"

namespace entities
{
	class Light
	{
	public:
		Light(glm::vec3& _position, glm::vec3& _color);
		~Light();
		glm::vec3 position;
		glm::vec3 color;
	};
}