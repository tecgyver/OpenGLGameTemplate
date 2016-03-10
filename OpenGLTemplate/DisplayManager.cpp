#include "DisplayManager.h"
#include <iostream>

using namespace renderEngine;

GLFWwindow* DisplayManager::WINDOW = nullptr;
DisplayManager::DisplayManager()
{
}


DisplayManager::~DisplayManager()
{
}

void DisplayManager::createDisplay()
{
	// create window
	if (!glfwInit())
	{
		critError(std::string("GLFW init failed!"), -1);
	}

	glfwWindowHint(GLFW_REFRESH_RATE, FPS_CAP);
	WINDOW = glfwCreateWindow(WIDTH, HEIGHT, "", nullptr, nullptr);
	if (!WINDOW)
	{
		critError(std::string("GLFW create window failed!!"), -2);
	}
	glfwMakeContextCurrent(WINDOW);
	////Catch cursor
	//glfwSetInputMode(WINDOW, GLFW_CURSOR, GLFW_CURSOR_DISABLED);



	if (glewInit() != GLEW_OK)
	{
		critError(std::string("GLEW init failed!"), -3);
	}
	glewExperimental = true;



	glViewport(0, 0, WIDTH, HEIGHT);
}

void DisplayManager::catchMouse()
{
    glfwSetInputMode(WINDOW, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void DisplayManager::releaseMouse()
{
    glfwSetInputMode(WINDOW, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

void DisplayManager::updateDisplay()
{
	glfwSwapBuffers(WINDOW);
	glfwPollEvents();

	GLenum error;
	while ((error = glGetError()) != GL_NO_ERROR)
	{
		std::string errorText;
		switch (error) {
		case GL_INVALID_OPERATION:      errorText = "INVALID_OPERATION";      break;
		case GL_INVALID_ENUM:           errorText = "INVALID_ENUM";           break;
		case GL_INVALID_VALUE:          errorText = "INVALID_VALUE";          break;
		case GL_OUT_OF_MEMORY:          errorText = "OUT_OF_MEMORY";          break;
		case GL_INVALID_FRAMEBUFFER_OPERATION:  errorText = "INVALID_FRAMEBUFFER_OPERATION";  break;
		}

		std::cout << "GL Error detected!" << std::endl;
		std::cout << "Error: " << error << " -> " << errorText << std::endl;
	}
}

void DisplayManager::closeDisplay()
{
	if (WINDOW)
	{
		glfwDestroyWindow(WINDOW);
	}
	glfwTerminate();
}

void DisplayManager::critError(const std::string& errorMsg, int exitcode)
{
	closeDisplay();
	std::cout << errorMsg.c_str() << std::endl;
	system("PAUSE");
	exit(exitcode);
}

bool DisplayManager::windowShouldClose()
{
	return glfwWindowShouldClose(WINDOW);
}

void DisplayManager::setTitle(const std::string& title)
{
	glfwSetWindowTitle(WINDOW, title.c_str());
}