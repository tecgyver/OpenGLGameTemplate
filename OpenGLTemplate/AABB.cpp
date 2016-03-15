#include "AABB.h"


AABB::AABB()
{
}


AABB::~AABB()
{
}

void AABB::getTransformed(const glm::mat4 &modelMatrix, AABB& aabb) const
{
	glm::vec4 currentVertex;
	glm::vec3 currentVertex3;
	aabb.min = glm::vec3(std::numeric_limits<float>::max());
	aabb.max = glm::vec3(std::numeric_limits<float>::lowest());

	currentVertex.w = 1.f;

	for (int i = 0; i < 8; i++)
	{
		currentVertex.x = ((i >> 0) & 1) == 0 ? min.x : max.x;
		currentVertex.y = ((i >> 1) & 1) == 0 ? min.y : max.y;
		currentVertex.z = ((i >> 2) & 1) == 0 ? min.z : max.z;
		currentVertex3 = glm::vec3(modelMatrix * currentVertex);
		aabb.min = glm::min(aabb.min, currentVertex3);
		aabb.max = glm::max(aabb.max, currentVertex3);
	}
	aabb.size = aabb.max - aabb.min;
}