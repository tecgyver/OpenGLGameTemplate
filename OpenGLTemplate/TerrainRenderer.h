#pragma once
#include <vector>

#include "TerrainShader.h"
#include "Terrain.h"
#include "TexturedModel.h"
#include "Entity.h"

namespace renderEngine
{
	class TerrainRenderer
	{
	public:
		TerrainRenderer(shaders::TerrainShader& shader, glm::mat4& projectionMatrix);
		~TerrainRenderer();

		void render(std::vector<terrains::Terrain*>& terrainList);

	private:
		shaders::TerrainShader& shader;

		void prepareTerrain(terrains::Terrain* terrain);
		void unbindTexturedModel();
		void loadModelMatrix(terrains::Terrain* terrain);
	};
}