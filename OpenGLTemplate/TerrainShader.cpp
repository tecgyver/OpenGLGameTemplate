#include "TerrainShader.h"
#include "Maths.h"

using namespace shaders;
using namespace entities;
using namespace toolbox;

const std::string TerrainShader::VERTEX_FILE = std::string("shaders/terrainVertexShader.txt");
const std::string TerrainShader::FRAGMENT_FILE = std::string("shaders/terrainFragmentShader.txt");
TerrainShader::TerrainShader()
	: ShaderProgram(VERTEX_FILE, FRAGMENT_FILE)
{
}


TerrainShader::~TerrainShader()
{
}

void TerrainShader::bindAttributes()
{
	bindAttribute(0, std::string("position"));
	bindAttribute(1, std::string("textureCoords"));
	bindAttribute(2, std::string("normal"));
}

void TerrainShader::getAllUniformLocations()
{
	location_transformationMatrix = getUniformLocation(std::string("transformationMatrix"));
	location_projectionMatrix = getUniformLocation(std::string("projectionMatrix"));
	location_viewMatrix = getUniformLocation(std::string("viewMatrix"));
	location_lightPosition = getUniformLocation(std::string("lightPosition"));
	location_lightColor = getUniformLocation(std::string("lightColor"));
	location_shineDamper = getUniformLocation(std::string("shineDamper"));
	location_reflectivity = getUniformLocation(std::string("reflectivity"));
	location_skyColor = getUniformLocation(std::string("skyColor"));
}

void TerrainShader::loadTransformationMatrix(glm::mat4& matrix)
{
	loadMatrix(location_transformationMatrix, matrix);
}

void TerrainShader::loadProjectionMatrix(glm::mat4& matrix)
{
	loadMatrix(location_projectionMatrix, matrix);
}

void TerrainShader::loadViewMatrix(Camera &camera)
{
    loadMatrix(location_viewMatrix, camera.viewMatrix);
}

void TerrainShader::loadLight(Light& light)
{
	loadVector(location_lightPosition, light.position);
	loadVector(location_lightColor, light.color);
}

void TerrainShader::loadShineVariables(float damper, float reflectivity)
{
	loadFloat(location_shineDamper, damper);
	loadFloat(location_reflectivity, reflectivity);
}

void TerrainShader::loadSkyColor(float r, float g, float b)
{
	loadVector(location_skyColor, glm::vec3(r, g, b));
}