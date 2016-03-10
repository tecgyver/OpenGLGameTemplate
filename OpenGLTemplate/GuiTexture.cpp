#include "GuiTexture.h"


using namespace guis;

GuiTexture::GuiTexture(GLuint textureID, const glm::vec2 position, const glm::vec2 scale)
{
	mTextureID = textureID;
	mPosition = position;
	mScale = scale;
}


GuiTexture::~GuiTexture()
{
}

GLuint GuiTexture::getTextureID()
{
	return mTextureID;
}

glm::vec2 GuiTexture::getPosition()
{
	return mPosition;
}

glm::vec2 GuiTexture::getScale()
{
	return mScale;
}