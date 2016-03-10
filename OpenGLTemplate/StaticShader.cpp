#include "StaticShader.h"
#include "Maths.h"


using namespace shaders;
using namespace entities;
using namespace toolbox;

const std::string StaticShader::VERTEX_FILE = std::string("shaders/vertexShader.txt");
const std::string StaticShader::FRAGMENT_FILE = std::string("shaders/fragmentShader.txt");
StaticShader::StaticShader()
	: ShaderProgram(VERTEX_FILE, FRAGMENT_FILE)
{
}


StaticShader::~StaticShader()
{
}

void StaticShader::bindAttributes()
{
	bindAttribute(0, std::string("position"));
	bindAttribute(1, std::string("textureCoords"));
	bindAttribute(2, std::string("normal"));
}

void StaticShader::getAllUniformLocations()
{
	location_transformationMatrix = getUniformLocation(std::string("transformationMatrix"));
	location_projectionMatrix = getUniformLocation(std::string("projectionMatrix"));
	location_viewMatrix = getUniformLocation(std::string("viewMatrix"));
	location_lightPosition = getUniformLocation(std::string("lightPosition"));
	location_lightColor = getUniformLocation(std::string("lightColor"));
	location_shineDamper = getUniformLocation(std::string("shineDamper"));
	location_reflectivity = getUniformLocation(std::string("reflectivity"));
	location_useFakeLighting = getUniformLocation(std::string("useFakeLighting"));
	location_skyColor = getUniformLocation(std::string("skyColor"));
	location_isTextured = getUniformLocation(std::string("isTextured"));
	location_modelColor = getUniformLocation(std::string("modelColor"));
}

void StaticShader::loadIsTextured(bool isTextured)
{
	loadBoolean(location_isTextured, isTextured);
}

void StaticShader::loadModelColor(const glm::vec3& modelColor)
{
	loadVector(location_modelColor, modelColor);
}

void StaticShader::loadSkyColor(float r, float g, float b)
{
	loadVector(location_skyColor, glm::vec3(r, g, b));
}

void StaticShader::loadTransformationMatrix(glm::mat4& matrix)
{
	loadMatrix(location_transformationMatrix, matrix);
}

void StaticShader::loadProjectionMatrix(glm::mat4& matrix)
{
	loadMatrix(location_projectionMatrix, matrix);
}

void StaticShader::loadViewMatrix(Camera& camera)
{
	loadMatrix(location_viewMatrix, camera.viewMatrix);
}

void StaticShader::loadLight(Light& light)
{
	loadVector(location_lightPosition, light.position);
	loadVector(location_lightColor, light.color);
}

void StaticShader::loadShineVariables(float damper, float reflectivity)
{
	loadFloat(location_shineDamper, damper);
	loadFloat(location_reflectivity, reflectivity);
}

void StaticShader::loadUseFakeLighting(bool useFakeLighting)
{
	loadBoolean(location_useFakeLighting, useFakeLighting);
}