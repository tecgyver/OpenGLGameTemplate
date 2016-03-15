#include "Terrain.h"
#include "Maths.h"

using namespace terrains;
using namespace models;
using namespace textures;
using namespace renderEngine;
using namespace entities;
using namespace toolbox;

const float Terrain::SIZE = 200;
const int Terrain::VERTEX_COUNT = 128;

Terrain::Terrain(int gridX, int gridZ, Loader& loader, ModelTexture* _texture)
{
	texture = _texture;
	x = gridX * SIZE;
	z = gridZ * SIZE;
	model = generateTerrain(loader);
}

Terrain::~Terrain()
{
}

float Terrain::getX()
{
	return x;
}

float Terrain::getZ()
{
	return z;
}

models::RawModel* Terrain::getModel()
{
	return model;
}

textures::ModelTexture* Terrain::getTexture()
{
	return texture;
}


RawModel* Terrain::generateTerrain(Loader& loader)
{
	int count = VERTEX_COUNT * VERTEX_COUNT;
	std::vector<float> vertices;
	vertices.resize(count * 3);
	std::vector<float> normals;
	normals.resize(count * 3);
	std::vector<float> textureCoords;
	textureCoords.resize(count * 2);
	std::vector<int> indices;
	indices.resize(6 * (VERTEX_COUNT - 1)*(VERTEX_COUNT - 1));
	int vertexPointer = 0;
	for (int i = 0; i < VERTEX_COUNT; i++)
	{
		for (int j = 0; j < VERTEX_COUNT; j++)
		{
			vertices[vertexPointer * 3] = (float)j / ((float)VERTEX_COUNT - 1) * SIZE;
			vertices[vertexPointer * 3 + 1] = 0;
			vertices[vertexPointer * 3 + 2] = (float)i / ((float)VERTEX_COUNT - 1) * SIZE;
			normals[vertexPointer * 3] = 0;
			normals[vertexPointer * 3 + 1] = 1;
			normals[vertexPointer * 3 + 2] = 0;
			textureCoords[vertexPointer * 2] = (float)j / ((float)VERTEX_COUNT - 1);
			textureCoords[vertexPointer * 2 + 1] = (float)i / ((float)VERTEX_COUNT - 1);
			vertexPointer++;
		}
	}
	int pointer = 0;
	for (int gz = 0; gz < VERTEX_COUNT - 1; gz++)
	{
		for (int gx = 0; gx < VERTEX_COUNT - 1; gx++)
		{
			int topLeft = (gz*VERTEX_COUNT) + gx;
			int topRight = topLeft + 1;
			int bottomLeft = ((gz + 1)*VERTEX_COUNT) + gx;
			int bottomRight = bottomLeft + 1;
			indices[pointer++] = topLeft;
			indices[pointer++] = bottomLeft;
			indices[pointer++] = topRight;
			indices[pointer++] = topRight;
			indices[pointer++] = bottomLeft;
			indices[pointer++] = bottomRight;
		}
	}
	return loader.loadToVAO(vertices, textureCoords, normals, indices);
}

void Terrain::placeRandom(Entity* entity)
{
	auto* model = entity->model->getRawModel();
	entity->position = glm::vec3(getRandomFloat(x - model->aabb.min.x, x + SIZE - model->aabb.max.x, 2, false), 0, getRandomFloat(z - model->aabb.min.z, z + SIZE - model->aabb.max.z, 2, false));
	entity->increaseRotation(0, getRandomFloat(0, 360.0f, 2, false), 0);
}

float Terrain::getRandomFloat(float min, float max, int decimals, bool includeMax)
{
	return (fmod(rand(), ((max - min) * pow(10, decimals)) + (includeMax ? powf(10, -decimals) : 0)) / pow(10, decimals)) + min;
}

void Terrain::prepareModelMatrix()
{
	modelMatrix = glm::mat4();
	Maths::createTransformationMatrix(modelMatrix, glm::vec3(x, 0, z), 0, 0, 0, 1);
	model->aabb.getTransformed(modelMatrix, aabb);
}