#pragma once
#include "ShaderProgram.h"
#include "Camera.h"
#include "Light.h"

namespace shaders
{
	class TerrainShader :
		public ShaderProgram
	{
	public:
		TerrainShader();
		~TerrainShader();

		void loadTransformationMatrix(glm::mat4& matrix);
		void loadProjectionMatrix(glm::mat4& matrix);
		void loadViewMatrix(entities::Camera& camera);
		void loadLight(entities::Light& light);
		void loadShineVariables(float damper, float reflectivity);
		void loadSkyColor(float r, float g, float b);

	protected:
		virtual void bindAttributes();
		virtual void getAllUniformLocations();

	private:
		static const std::string VERTEX_FILE;
		static const std::string FRAGMENT_FILE;

		int location_transformationMatrix;
		int location_projectionMatrix;
		int location_viewMatrix;
		int location_lightPosition;
		int location_lightColor;
		int location_shineDamper;
		int location_reflectivity;
		int location_skyColor;
	};
}
