#pragma once

#include "GLM\glm.hpp"

class AABB
{
public:
	AABB();
	~AABB();

	glm::vec3 min;
	glm::vec3 max;
	glm::vec3 size;

	void getTransformed(const glm::mat4 &modelMatrix, AABB& aabb) const;
};

