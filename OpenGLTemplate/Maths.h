#pragma once
#include "GLM/glm.hpp"
#include "Camera.h"

namespace toolbox
{
	class Maths
	{
	public:
		Maths();
		~Maths();

		static void createTransformationMatrix(glm::mat4& matrix, glm::vec3& translation, float rx, float ry, float rz, float scale);
        static void createViewMatrix(glm::mat4& viewmatrix, entities::Camera& camera, glm::vec3 &xAxis, glm::vec3 &yAxis, glm::vec3 &zAxis);
		static void getRotationBetweenVectors(const glm::vec3 &vecFrom, const glm::vec3 &vecTo, glm::mat3 &rotMat); 
		static void createTransformationMatrix(const glm::vec2 &translation, const glm::vec2 &scale, glm::mat4 &transMat);
    private:
        static glm::mat3 getSkewSymmetricCrossProductMatrix(glm::vec3 &vec);
    };
}
