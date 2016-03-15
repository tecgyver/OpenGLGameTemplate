#include "TerrainRenderer.h"
#include "GLEW/glew.h"
#include "Maths.h"
#include "RenderController.h"

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
	if (RenderController::showWireframe)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	else
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
	for (auto* terrain : terrainList)
	{
		prepareTerrain(terrain);
		loadModelMatrix(terrain);
		glDrawElements(GL_TRIANGLES, terrain->getModel()->getVertexCount(), GL_UNSIGNED_INT, 0);
		unbindTexturedModel();
	}
	if (RenderController::showWireframe)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
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
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, RenderController::minFilter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, RenderController::magFilter);
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
	shader.loadTransformationMatrix(terrain->modelMatrix);
}