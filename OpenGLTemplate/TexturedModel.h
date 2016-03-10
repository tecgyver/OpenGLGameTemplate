#pragma once
#include "RawModel.h"
#include "ModelTexture.h"

namespace models
{
	class TexturedModel
	{
	public:
		TexturedModel(RawModel* model, textures::ModelTexture* texture);
		~TexturedModel();

		RawModel* getRawModel();
		textures::ModelTexture* getTexture();

	private:
		RawModel* rawModel;
		textures::ModelTexture* texture;
	};
}
