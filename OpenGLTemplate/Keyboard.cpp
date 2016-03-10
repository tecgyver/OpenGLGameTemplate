#include "Keyboard.h"

using namespace input;
using namespace renderEngine;

Keyboard::Keyboard()
{
}


Keyboard::~Keyboard()
{
}

bool Keyboard::getKeyPressed(int key)
{
	return glfwGetKey(DisplayManager::WINDOW, key);
}
