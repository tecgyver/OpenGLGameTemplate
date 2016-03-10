#pragma once
#include <string>

#include "GLM/glm.hpp"

namespace shaders
{
	class ShaderProgram
	{
	public:
		ShaderProgram(const std::string& vertexFile, const std::string& fragmentFile);
		~ShaderProgram();
		void init();
		void start();
		void stop();
		void cleanup();

	protected:
		virtual void bindAttributes() = 0;
		virtual void getAllUniformLocations() = 0;

        void bindAttribute(int attribute, const std::string &variableName);
        int getUniformLocation(const std::string& uniformName);
		void loadFloat(int location, float value);
        void loadVector(int location, const glm::vec3 &value);
		void loadBoolean(int location, bool value); 
        void loadMatrix(int location, const glm::mat4 &value);

	private:
		int programID;
		int vertexShaderID;
		int fragmentShaderID;

		int loadShader(const std::string& file, int type);
	};
}