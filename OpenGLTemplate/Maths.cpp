#include "Maths.h"
#include "GLM/gtc/matrix_transform.hpp"

using namespace toolbox;
using namespace entities;

Maths::Maths()
{
}


Maths::~Maths()
{
}


void Maths::createTransformationMatrix(glm::mat4& matrix, glm::vec3& translation, float rx, float ry, float rz, float scale)
{
	matrix = glm::translate(matrix, translation);
	matrix = glm::rotate(matrix, glm::radians(rx), glm::vec3(1, 0, 0));
	matrix = glm::rotate(matrix, glm::radians(ry), glm::vec3(0, 1, 0));
	matrix = glm::rotate(matrix, glm::radians(rz), glm::vec3(0, 0, 1));
	matrix = glm::scale(matrix, glm::vec3(scale, scale, scale));
}

void Maths::createViewMatrix(glm::mat4& viewmatrix, Camera& camera, glm::vec3& xAxis, glm::vec3& yAxis, glm::vec3& zAxis)
{
	viewmatrix = glm::rotate(viewmatrix, glm::radians(camera.basePitch), glm::vec3(1, 0, 0));
	viewmatrix = glm::rotate(viewmatrix, glm::radians(camera.baseYaw), glm::vec3(0, 1, 0));
	viewmatrix = glm::rotate(viewmatrix, glm::radians(camera.baseRoll), glm::vec3(0, 0, 1));
	viewmatrix = glm::rotate(viewmatrix, glm::radians(camera.pitch), xAxis);
	viewmatrix = glm::rotate(viewmatrix, glm::radians(camera.yaw), yAxis);
	viewmatrix = glm::rotate(viewmatrix, glm::radians(camera.roll), zAxis);
	viewmatrix = glm::translate(viewmatrix, -camera.position);
}

void Maths::getRotationBetweenVectors(const glm::vec3& vecFrom, const glm::vec3& vecTo, glm::mat3& rotMat)
{
	auto v = glm::cross(vecFrom, vecTo);
	auto s = glm::length(v);
	if (s > 0)
	{
		auto c = glm::dot(vecFrom, vecTo);
		auto skew = getSkewSymmetricCrossProductMatrix(v);
		rotMat = glm::mat3() + skew + (skew * skew) * ((1 - c) / (s * s));
	}
	else
	{
		if (vecFrom == -vecTo)
		{
			rotMat = -glm::mat3();
		}
		else
		{
			rotMat = glm::mat3();
		}
	}
}

glm::mat3 Maths::getSkewSymmetricCrossProductMatrix(glm::vec3& vec)
{
	return glm::mat3(0, -vec.z, vec.y,
		vec.z, 0, -vec.x,
		-vec.y, vec.x, 0);
}

void Maths::createTransformationMatrix(const glm::vec2 &translation, const glm::vec2 &scale, glm::mat4 &matrix) {
	matrix = glm::translate(matrix, glm::vec3(translation, 0.f));
	matrix = glm::scale(matrix, glm::vec3(scale, 1));
}
