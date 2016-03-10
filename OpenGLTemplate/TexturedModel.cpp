#include "TexturedModel.h"

using namespace models;
using namespace textures;

TexturedModel::TexturedModel(RawModel* _rawModel, ModelTexture* _texture)
{
	rawModel = _rawModel;
	texture = _texture;
}


TexturedModel::~TexturedModel()
{
}

RawModel* TexturedModel::getRawModel()
{
	return rawModel;
}

ModelTexture* TexturedModel::getTexture()
{
	return texture;
}