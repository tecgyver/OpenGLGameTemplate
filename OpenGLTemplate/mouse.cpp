#include "mouse.h"
#include "DisplayManager.h"

using namespace renderEngine;
using namespace input;

Mouse::Mouse()
{
}

Mouse::~Mouse()
{

}

void Mouse::getPosition(double* x, double* y)
{
    return glfwGetCursorPos(DisplayManager::WINDOW, x, y);
}

bool Mouse::getButtonPressed(int button)
{
    return glfwGetMouseButton(DisplayManager::WINDOW, button);
}
