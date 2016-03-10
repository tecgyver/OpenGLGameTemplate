#pragma once
#include <string>

#include "ShaderProgram.h"

namespace guis
{
	class GuiShader
		: public shaders::ShaderProgram
	{
	public:
		GuiShader();
		~GuiShader();

		void loadTransformationMatrix(glm::mat4& matrix);

	protected:
		virtual void bindAttributes();
		virtual void getAllUniformLocations();

	private:
		static const std::string VERTEX_FILE;
		static const std::string FRAGMENT_FILE;

		int location_transformationMatrix;
	};
}