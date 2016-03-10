#pragma once
#include "RawModel.h"
#include "ModelTexture.h"
#include "Loader.h"
#include "Entity.h"

namespace terrains
{
	class Terrain
	{
	public:
		Terrain(int gridX, int gridZ, renderEngine::Loader& loader, textures::ModelTexture* _texture);
		~Terrain();

		float getX();
		float getZ();
		models::RawModel* getModel();
		textures::ModelTexture* getTexture();
		void placeRandom(entities::Entity* entity);

	private:
		static const float SIZE;
		static const int VERTEX_COUNT;

		float x;
		float z;
		models::RawModel* model;
		textures::ModelTexture* texture;

		models::RawModel* generateTerrain(renderEngine::Loader& loader);
		float getRandomFloat(float min, float max, int decimals, bool includeMax);
	};
}
