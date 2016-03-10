#pragma once
#include "GLM/glm.hpp"
#include "AABB.h"

namespace models
{
	class RawModel
	{
	public:
		RawModel(int vaoID, int vertexCount);
		~RawModel();

		const int& getVaoID();
		const int& getVertexCount();
		AABB aabb;
		glm::vec3 modelColor;

	private:
		int vaoID;
		int vertexCount;
	};
}