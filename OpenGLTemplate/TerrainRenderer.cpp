#include "TerrainRenderer.h"
#include "GLEW/glew.h"
#include "Maths.h"

using namespace renderEngine;
using namespace terrains;
using namespace models;
using namespace textures;
using namespace toolbox;
using namespace terrains;

TerrainRenderer::TerrainRenderer(shaders::TerrainShader& _shader, glm::mat4& projectionMatrix) : shader(_shader)
{
	shader.start();
	shader.loadProjectionMatrix(projectionMatrix);
	shader.stop();
}


TerrainRenderer::~TerrainRenderer()
{
}


void TerrainRenderer::render(std::vector<Terrain*>& terrainList)
{
	for (auto* terrain : terrainList)
	{
		prepareTerrain(terrain);
		loadModelMatrix(terrain);
		glDrawElements(GL_TRIANGLES, terrain->getModel()->getVertexCount(), GL_UNSIGNED_INT, 0);
		unbindTexturedModel();
	}
}

void TerrainRenderer::prepareTerrain(Terrain* terrain)
{
	RawModel* rawModel = terrain->getModel();
	glBindVertexArray(rawModel->getVaoID());
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	ModelTexture* texture = terrain->getTexture();
	shader.loadShineVariables(texture->shineDamper, texture->reflectivity);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture->getID());
}

void TerrainRenderer::unbindTexturedModel()
{
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glBindVertexArray(0);
}

void TerrainRenderer::loadModelMatrix(Terrain* terrain)
{
	glm::mat4 transformationMatrix;
	Maths::createTransformationMatrix(transformationMatrix, glm::vec3(terrain->getX(), 0, terrain->getZ()), 0, 0, 0, 1);
	shader.loadTransformationMatrix(transformationMatrix);
}