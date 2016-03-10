#pragma once
#include <map>
#include <vector>

#include "TexturedModel.h"
#include "Entity.h"
#include "StaticShader.h"
#include "Camera.h"

namespace renderEngine
{
	class EntityRenderer
	{
	public:
		EntityRenderer(shaders::StaticShader& _shader, glm::mat4& projectionMatrix);
		~EntityRenderer();

		void render(std::map<models::TexturedModel*, std::vector<entities::Entity*>>& entitiesMap); 

	private:
		shaders::StaticShader& shader;

		void prepareUntexturedModel(models::RawModel* rawModel);
		void prepareTexturedModel(models::TexturedModel* model); 
		void unbindTexturedModel();
		void prepareInstance(entities::Entity* entity);
	};
}