#pragma once
#include "GLEW\glew.h"
#include "GLM\glm.hpp"

namespace guis
{
	class GuiTexture
	{
	public:
		GuiTexture(GLuint textureID, const glm::vec2 position, const glm::vec2 scale);
		~GuiTexture();

		GLuint getTextureID();
		glm::vec2 getPosition();
		glm::vec2 getScale();

	private:
		GLuint mTextureID;
		glm::vec2 mPosition;
		glm::vec2 mScale;
	};
}