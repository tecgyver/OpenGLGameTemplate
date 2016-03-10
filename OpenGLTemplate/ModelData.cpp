#include "ModelData.h"

using namespace objConverter;

ModelData::ModelData(std::vector<float>& vertices, std::vector<float>& textureCoords, std::vector<float>& normals, std::vector<int>& indices, std::vector<std::string>& texturePaths)
{
	this->vertices = vertices;
	this->textureCoords = textureCoords;
	this->normals = normals;
	this->indices = indices;
	this->texturePaths = texturePaths;
}

ModelData::~ModelData()
{
}

std::vector<float>& ModelData::getVertices() {
	return vertices;
}

std::vector<float>& ModelData::getTextureCoords() {
	return textureCoords;
}

std::vector<float>& ModelData::getNormals() {
	return normals;
}

std::vector<int>& ModelData::getIndices() {
	return indices;
}

std::vector<std::string>& ModelData::getTexturePaths(){
	return texturePaths;
}