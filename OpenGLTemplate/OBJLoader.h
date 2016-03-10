#pragma once
#include <string>
#include <vector>

#include "GLM\glm.hpp"
#include "RawModel.h"
#include "Loader.h"
#include "Vertex.h"
#include "ModelData.h"

namespace objConverter
{
	class OBJLoader
	{
	public:
		OBJLoader();
		~OBJLoader();

		static ModelData* loadObjModel(std::string& fileName, renderEngine::Loader& loader);
	private:
		static void processVertex(glm::vec3& vertex, std::vector<Vertex*>& vertices, std::vector<int>& indices);
		static float convertDataToArrays(std::vector<Vertex*>& vertices, std::vector<glm::vec2>& textures,
			std::vector<glm::vec3>& normals, std::vector<float>& verticesArray, std::vector<float>& texturesArray,
			std::vector<float>& normalsArray);
		static void removeUnusedVertices(std::vector<Vertex*>& vertices);
		static void dealWithAlreadyProcessedVertex(Vertex* previousVertex, int newTextureIndex,
			int newNormalIndex, std::vector<int>& indices, std::vector<Vertex*>& vertices);
	};
}