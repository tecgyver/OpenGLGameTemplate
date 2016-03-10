#include "GuiShader.h"
#include "Maths.h"
#include "GLEW\glew.h"

using namespace guis;
using namespace shaders;
using namespace toolbox;



const std::string GuiShader::VERTEX_FILE = std::string("shaders/guiVertexShader.txt");
const std::string GuiShader::FRAGMENT_FILE = std::string("shaders/guiFragmentShader.txt");
GuiShader::GuiShader()
	: ShaderProgram(VERTEX_FILE, FRAGMENT_FILE)
{
}


GuiShader::~GuiShader()
{
}

void GuiShader::bindAttributes()
{
	bindAttribute(0, std::string("position"));
}

void GuiShader::getAllUniformLocations()
{
	location_transformationMatrix = getUniformLocation(std::string("transformationMatrix"));
}

void GuiShader::loadTransformationMatrix(glm::mat4& matrix)
{
	loadMatrix(location_transformationMatrix, matrix);
}