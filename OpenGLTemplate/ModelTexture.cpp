#include "ModelTexture.h"

using namespace textures;
ModelTexture::ModelTexture(int id) : shineDamper(1), reflectivity(0)
{
	textureID = id;
}


ModelTexture::~ModelTexture()
{
}

int ModelTexture::getID()
{
	return textureID;
}