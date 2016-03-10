#pragma once
#include <vector>

namespace objConverter
{
	class ModelData
	{
	public:
		ModelData(std::vector<float>& vertices, std::vector<float>& textureCoords, std::vector<float>& normals, std::vector<int>& indices,
			std::vector<std::string>& texturePaths);
		~ModelData();

		std::vector<float>& getVertices();
		std::vector<float>& getTextureCoords();
		std::vector<float>& getNormals();
		std::vector<int>& getIndices();
		std::vector<std::string>& getTexturePaths();

	private:
		std::vector<float> vertices;
		std::vector<float> textureCoords;
		std::vector<float> normals;
		std::vector<int> indices;
		std::vector<std::string> texturePaths;
	};
}