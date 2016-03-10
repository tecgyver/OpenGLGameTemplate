#pragma once
#include "TexturedModel.h"
#include "GLM/glm.hpp"

namespace entities
{
	class Entity
	{
	public:
		Entity(models::TexturedModel* _model, glm::vec3& _position, float _rotX, float _rotY, float _rotZ, float _scale);
		~Entity();
		models::TexturedModel* model;
		glm::vec3 position;
		float rotX, rotY, rotZ;
		float scale;

		void increasePosition(float dx, float dy, float dz);
		void increaseRotation(float dx, float dy, float dz);

	private:
	};
}