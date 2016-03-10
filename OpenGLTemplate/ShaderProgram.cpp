#include <iostream>
#include <fstream>

#include "ShaderProgram.h"
#include "GLEW/glew.h"
#include "GLM/gtc/type_ptr.hpp"

using namespace shaders;
ShaderProgram::ShaderProgram(const std::string& vertexFile, const std::string& fragmentFile)
{
	vertexShaderID = loadShader(vertexFile, GL_VERTEX_SHADER);
	fragmentShaderID = loadShader(fragmentFile, GL_FRAGMENT_SHADER);
	programID = glCreateProgram();
	glAttachShader(programID, vertexShaderID);
	glAttachShader(programID, fragmentShaderID);
}

ShaderProgram::~ShaderProgram()
{
}

void ShaderProgram::getAllUniformLocations()
{
}

void ShaderProgram::bindAttributes()
{
}

void ShaderProgram::init()
{
	bindAttributes();
	glLinkProgram(programID);
	glValidateProgram(programID);
	getAllUniformLocations();
}

void ShaderProgram::loadFloat(int location, float value)
{
	glUniform1f(location, value);
}

void ShaderProgram::loadVector(int location, const glm::vec3& value)
{
	glUniform3f(location, value.x, value.y, value.z);
}

void ShaderProgram::loadBoolean(int location, bool value)
{
	glUniform1f(location, value);
}

void ShaderProgram::loadMatrix(int location, const glm::mat4& value)
{
	glUniformMatrix4fv(location, 1, false, glm::value_ptr(value));
}

int ShaderProgram::getUniformLocation(const std::string &uniformName)
{
	return glGetUniformLocation(programID, uniformName.c_str());
}

void ShaderProgram::start()
{
	glUseProgram(programID);
}

void ShaderProgram::stop()
{
	glUseProgram(0);
}

void ShaderProgram::cleanup()
{
	stop();
	glDetachShader(programID, vertexShaderID);
	glDetachShader(programID, fragmentShaderID);
	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);
	glDeleteProgram(programID);
}

void ShaderProgram::bindAttribute(int attribute, const std::string& variableName)
{
	glBindAttribLocation(programID, attribute, &variableName[0]);
}

int ShaderProgram::loadShader(const std::string& file, int type)
{
	std::ifstream shaderFile(file);

	if (shaderFile.good())
	{
		std::string code = std::string(
			std::istreambuf_iterator<char>(shaderFile),
			std::istreambuf_iterator<char>());

		shaderFile.close();

		int handle = glCreateShader(type);
		if (handle == 0)
		{
			std::cout << "Creating shader " << file << " failed!" << std::endl;
			system("PAUSE");
			exit(-1);
		}

		const char* codePtr = code.c_str();
		glShaderSource(handle, 1, &codePtr, nullptr);
		glCompileShader(handle);

		//Error checking code from https://www.opengl.org/wiki/Shader_Compilation
		GLint isCompiled = 0;
		glGetShaderiv(handle, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(handle, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			GLchar* errorLog = new char[maxLength];
			glGetShaderInfoLog(handle, maxLength, &maxLength, &errorLog[0]);

			std::cout << "Compiling shader " << file << " failed!" << std::endl;
			std::cout << errorLog << std::endl;
			delete[] errorLog;
			system("PAUSE");
			// Exit with failure.
			exit(-1);
		}
		return handle;
	}
	else
	{
		std::cout << "Loading shader-file " << file << " failed!" << std::endl;
		system("PAUSE");
		exit(-1);
	}
}