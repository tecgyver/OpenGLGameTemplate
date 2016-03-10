#include "Camera.h"
#include "Keyboard.h"
#include "Maths.h"
#include "GLM/gtx/transform.hpp"
#include "mouse.h"
#include "DisplayManager.h"
#include "MasterRenderer.h"

using namespace entities;
using namespace input;
using namespace toolbox;
using namespace renderEngine;

const float MOVESPEED = 5.f;
const float TURNSPEED_MOUSE = MasterRenderer::FOV / ((float)DisplayManager::WIDTH);
const float TURNSPEED_KEYBOARD = MasterRenderer::FOV / 2.f;

Camera::Camera(float _basePitch, float _baseYaw, float _baseRoll, bool _catchOnClick) : pitch(0), yaw(0), roll(0), basePitch(_basePitch), baseYaw(_baseYaw), baseRoll(_baseRoll), catchOnClick(_catchOnClick)
{
	update();
	up = glm::vec3(viewMatrix[0][1], viewMatrix[1][1], viewMatrix[2][1]);
	xAxis = glm::vec3(viewMatrix[0][0], viewMatrix[1][0], viewMatrix[2][0]);
	zAxis = glm::vec3(viewMatrix[0][2], viewMatrix[1][2], viewMatrix[2][2]);
	if (!catchOnClick)
	{
		catchMouse = true;
		DisplayManager::catchMouse();
		Mouse::getPosition(&mouseX, &mouseY);
	}
}


Camera::~Camera()
{
	DisplayManager::releaseMouse();
}

void Camera::move(float timePassed)
{
	glm::vec3 posChange(0, 0, 0);
	if (Keyboard::getKeyPressed(GLFW_KEY_W))
	{
		posChange -= back;
	}
	if (Keyboard::getKeyPressed(GLFW_KEY_S))
	{
		posChange += back;
	}
	if (Keyboard::getKeyPressed(GLFW_KEY_A))
	{
		posChange -= right;
	}
	if (Keyboard::getKeyPressed(GLFW_KEY_D))
	{
		posChange += right;
	}
	if (Keyboard::getKeyPressed(GLFW_KEY_SPACE))
	{
		posChange += up;
	}
	if (Keyboard::getKeyPressed(GLFW_KEY_LEFT_CONTROL))
	{
		posChange -= up;
	}

	if (glm::length(posChange) >= 0.9f)
		position += glm::normalize(posChange) * MOVESPEED * timePassed;

	if (Keyboard::getKeyPressed(GLFW_KEY_R))
	{
		//position.x = 0;
		//position.y = 0;
		//position.z = 0;
		//pitch = 0;
		//yaw = 0;
		//roll = 0;
	}

	if (catchOnClick && !catchMouse)
	{
		//Mouse input
		if (Mouse::getButtonPressed(GLFW_MOUSE_BUTTON_LEFT))
		{
			catchMouse = true;
			DisplayManager::catchMouse();
			Mouse::getPosition(&mouseX, &mouseY);
		}
		//Keyboard input
		else
		{
			if (Keyboard::getKeyPressed(GLFW_KEY_RIGHT))
			{
				yaw = fmodf(yaw + TURNSPEED_KEYBOARD * timePassed, 360.0f);
			}
			if (Keyboard::getKeyPressed(GLFW_KEY_LEFT))
			{
				yaw = fmodf(yaw - TURNSPEED_KEYBOARD * timePassed, 360.0f);
			}
			if (Keyboard::getKeyPressed(GLFW_KEY_UP))
			{
				pitch = pitch - TURNSPEED_KEYBOARD * timePassed;
				if (pitch < -90.f)
					pitch = -90.f;
			}
			if (Keyboard::getKeyPressed(GLFW_KEY_DOWN))
			{
				pitch = pitch + TURNSPEED_KEYBOARD * timePassed;
				if (pitch > 90.f)
					pitch = 90.f;
			}
		}
	}
	else
	{
		if (catchOnClick && !Mouse::getButtonPressed(GLFW_MOUSE_BUTTON_LEFT))
		{
			catchMouse = false;
			DisplayManager::releaseMouse();
		}
		else
		{
			float mouseXDiff = 0.f;
			float mouseYDiff = 0.f;
			mouseXDiff = -mouseX;
			mouseYDiff = -mouseY;
			Mouse::getPosition(&mouseX, &mouseY);
			mouseXDiff += mouseX;
			mouseYDiff += mouseY;
			yaw = fmodf(yaw + mouseXDiff * TURNSPEED_MOUSE, 360.0f);
			pitch = pitch + mouseYDiff * TURNSPEED_MOUSE;
			if (pitch < -90.f)
				pitch = -90.f;
			else if (pitch > 90.f)
				pitch = 90.f;
		}
	}

	update();
}

void Camera::update()
{
	viewMatrix = glm::mat4();
	Maths::createViewMatrix(viewMatrix, *this, xAxis, up, zAxis);
	right = glm::vec3(viewMatrix[0][0], viewMatrix[1][0], viewMatrix[2][0]);
	back = glm::vec3(viewMatrix[0][2], viewMatrix[1][2], viewMatrix[2][2]);
}
