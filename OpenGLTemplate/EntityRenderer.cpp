#include "EntityRenderer.h"
#include "GLEW/glew.h"
#include "Maths.h"
#include "GLM/gtc/matrix_transform.hpp"
#include "ModelTexture.h"
#include "MasterRenderer.h"


using namespace renderEngine;
using namespace models;
using namespace entities;
using namespace toolbox;
using namespace textures;
using namespace shaders;

EntityRenderer::EntityRenderer(StaticShader& _shader, glm::mat4& projectionMatrix) : shader(_shader)
{
	shader.start();
	shader.loadProjectionMatrix(projectionMatrix);
	shader.stop();
}


EntityRenderer::~EntityRenderer()
{
}

void EntityRenderer::render(std::map<TexturedModel*, std::vector<Entity*>>& entitiesMap)
{
	for (auto& keypair : entitiesMap)
	{
		if (keypair.first->getTexture() != NULL)
		{
			prepareTexturedModel(keypair.first);
		}
		else
		{
			prepareUntexturedModel(keypair.first->getRawModel());
		}
		auto& batch = keypair.second;
		for (auto& instance : batch)
		{
			prepareInstance(instance);
			glDrawElements(GL_TRIANGLES, instance->model->getRawModel()->getVertexCount(), GL_UNSIGNED_INT, 0);
		}
		unbindTexturedModel();
	}
}

void EntityRenderer::prepareUntexturedModel(models::RawModel* rawModel)
{
	glBindVertexArray(rawModel->getVaoID());
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	shader.loadUseFakeLighting(false);
	shader.loadShineVariables(1.f, 0.f);
	shader.loadIsTextured(false);
	shader.loadModelColor(rawModel->modelColor);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void EntityRenderer::prepareTexturedModel(models::TexturedModel* model)
{
	RawModel* rawModel = model->getRawModel();
	glBindVertexArray(rawModel->getVaoID());
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	ModelTexture* texture = model->getTexture();
	if (texture->hasTransparency)
		MasterRenderer::disableBackfaceCulling();
	shader.loadUseFakeLighting(texture->useFakeLighting);
	shader.loadShineVariables(texture->shineDamper, texture->reflectivity);
	shader.loadIsTextured(false);
	shader.loadModelColor(rawModel->modelColor);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture->getID());
}

void EntityRenderer::unbindTexturedModel()
{
	MasterRenderer::enableBackfaceCulling();
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glBindVertexArray(0);
}

void EntityRenderer::prepareInstance(entities::Entity* entity)
{
	glm::mat4 transformationMatrix;
	Maths::createTransformationMatrix(transformationMatrix, entity->position, entity->rotX, entity->rotY, entity->rotZ, entity->scale);
	shader.loadTransformationMatrix(transformationMatrix);
}