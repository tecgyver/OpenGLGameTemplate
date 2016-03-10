#pragma once
#include <map>
#include <vector>

#include "AABB.h"
#include "clippingplane.h"
#include "StaticShader.h"
#include "EntityRenderer.h"
#include "TexturedModel.h"
#include "Light.h"
#include "Camera.h"
#include "TerrainShader.h"
#include "TerrainRenderer.h"
#include "Loader.h"

namespace renderEngine
{
	class MasterRenderer
	{
	public:
        MasterRenderer(int width, int height, entities::Camera& _camera, Loader &_loader);
        ~MasterRenderer();

        static const float FOV;
        static void enableBackfaceCulling();
        static void disableBackfaceCulling();
		void cleanup();
        short isAABBinFrustum(AABB &aabb);
		void prepare(std::vector<terrains::Terrain*> &terrainList, std::vector<entities::Entity*> &entityList);
		void renderScene(entities::Light& sun, std::vector<terrains::Terrain*> &terrainList, std::vector<entities::Entity*> &entityList);
		void processEntity(entities::Entity* entity);
		void processTerrain(terrains::Terrain* terrain);

	private:
		static const float NEAR_PLANE;
		static const float FAR_PLANE;
		static const float RED;
		static const float GREEN;
		static const float BLUE;

		Loader& loader;
        entities::Camera& camera;
        ClippingPlane frustum[6];
        glm::vec2 viewportSize;
		int width;
		int height;
		glm::mat4 projectionMatrix;
		shaders::StaticShader* entityShader;
		renderEngine::EntityRenderer* entityRenderer;
		std::map<models::TexturedModel*, std::vector<entities::Entity*>> entitiesMap;
		shaders::TerrainShader* terrainShader;
		renderEngine::TerrainRenderer* terrainRenderer;
		std::vector<terrains::Terrain*> terrainsList;

		void createProjectionMatrix();
        glm::vec2 projectToScreen(const glm::vec3 &pos);
	};
}