#include "RenderController.h"
#include "Keyboard.h"
#include "GLFW\glfw3.h"
#include "GLEW\glew.h"

#include <iostream>

using namespace renderEngine;
using namespace input;


bool RenderController::showHelp = false;
bool RenderController::showFPS = false;
bool RenderController::showWireframe = false;
int RenderController::minFilter = GL_LINEAR_MIPMAP_LINEAR;
int RenderController::magFilter = GL_LINEAR;
bool RenderController::viewfrustumCullingDisabled = false;
bool RenderController::transparencyDisabled = false;

std::map<int, bool> RenderController::buttonState;

RenderController::RenderController()
{
	buttonState[GLFW_KEY_F1] = false;
	buttonState[GLFW_KEY_F2] = false;
	buttonState[GLFW_KEY_F3] = false;
	buttonState[GLFW_KEY_F4] = false;
	buttonState[GLFW_KEY_F5] = false;
	buttonState[GLFW_KEY_F8] = false;
	buttonState[GLFW_KEY_F9] = false;
}


RenderController::~RenderController()
{
}

void RenderController::checkInput()
{
	if (getKeyPressed(GLFW_KEY_F1))
	{
		showHelp = !showHelp;
	}
	if (getKeyPressed(GLFW_KEY_F2))
	{
		showFPS = !showFPS;
	}
	if (getKeyPressed(GLFW_KEY_F3))
	{
		showWireframe = !showWireframe;
	}
	if (getKeyPressed(GLFW_KEY_F4))
	{
		if (magFilter == GL_LINEAR)
		{
			magFilter = GL_NEAREST;
			std::cout << "textureSamplingQuality NEAREST" << std::endl;
		}
		else
		{
			magFilter = GL_LINEAR;
			std::cout << "textureSamplingQuality LINEAR" << std::endl;
		}
	}
	if (getKeyPressed(GLFW_KEY_F5))
	{
		if (minFilter == GL_LINEAR_MIPMAP_LINEAR)
		{
			minFilter = GL_LINEAR;
			std::cout << "mipMapQuality OFF" << std::endl;
		}
		else if (minFilter == GL_LINEAR)
		{
			minFilter = GL_LINEAR_MIPMAP_NEAREST;
			std::cout << "mipMapQuality NEAREST" << std::endl;
		}
		else if (minFilter == GL_LINEAR_MIPMAP_NEAREST)
		{
			minFilter = GL_LINEAR_MIPMAP_LINEAR;
			std::cout << "mipMapQuality LINEAR" << std::endl;
		}
	}
	if (getKeyPressed(GLFW_KEY_F8))
	{
		viewfrustumCullingDisabled = !viewfrustumCullingDisabled;
	}
	if (getKeyPressed(GLFW_KEY_F9))
	{
		transparencyDisabled = !transparencyDisabled;
	}

}

bool RenderController::getKeyPressed(int key)
{
	if (buttonState[key])
	{
		if (!Keyboard::getKeyPressed(key))
		{
			buttonState[key] = false;
		}
	}
	else
	{
		if (Keyboard::getKeyPressed(key))
		{
			buttonState[key] = true;
			return true;
		}
	}
	return false;
}