#pragma once
#include "ShaderProgram.h"
#include "Camera.h"
#include "Light.h"

namespace shaders
{
	class StaticShader :
		public ShaderProgram
	{
	public:
		StaticShader();
		~StaticShader();
		void loadTransformationMatrix(glm::mat4& matrix);
		void loadProjectionMatrix(glm::mat4& matrix);
		void loadViewMatrix(entities::Camera& camera); 
		void loadLight(entities::Light& light);
		void loadShineVariables(float damper, float reflectivity);
		void loadUseFakeLighting(bool useFakeLighting);
		void loadEnableTransparency(bool useFakeLighting);
		void loadSkyColor(float r, float g, float b);
		void loadIsTextured(bool isTextured);
		void loadModelColor(const glm::vec3& modelColor);

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
		int location_useFakeLighting;
		int location_skyColor;
		int location_isTextured;
		int location_modelColor;
		int location_enableTransparency;
	};
}