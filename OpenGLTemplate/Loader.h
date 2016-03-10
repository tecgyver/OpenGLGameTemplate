#pragma once

#include <vector>

#include "RawModel.h"

namespace renderEngine
{
	class Loader
	{
	public:
		Loader();
		~Loader();
		models::RawModel* loadToVAO(std::vector<float>& positions, std::vector<float>& textureCoords, std::vector<float>& normals, std::vector<int>& indices);
		models::RawModel* loadToVAO(std::vector<float>& positions);
		void cleanup();
		int loadTexture(std::string& filename, int glPixelType);
		void addInstancedAttribute(int vao, int vbo, int attribute, int dataSize, int instancedDataLength, unsigned int offset);
        int createEmptyVbo(int floatCount);
        void updateInstancedVbo(int vbo, int floatsInInstanceData, int instanceDataCount, int maxInstanceDataCount, float *data);
	private:
		std::vector<int> vaos;
		std::vector<int> vbos;
		std::vector<int> textures;

		int createVAO();
		void storeDataInAttributeList(int attributeNumber, int coordinateSize, std::vector<float>& data);
		void unbindVAO();
		void bindIndicesBuffer(std::vector<int>& indices);
	};
}