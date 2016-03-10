#pragma once
#include "GLM/glm.hpp"

namespace entities
{
	class Camera
	{
	public:
        Camera(float _basePitch, float _baseYaw, float _baseRoll, bool catchOnClick);
		~Camera();

        const float basePitch;
        const float baseYaw;
        const float baseRoll;
        glm::vec3 position;
        float pitch = 0;
        float yaw = 0;
        float roll = 0;
        bool catchMouse = false;
		bool catchOnClick = false;

        glm::mat4 viewMatrix;

        glm::vec3 up = glm::vec3(0,1,0);
        glm::vec3 right = glm::vec3(1,0,0);
        glm::vec3 back = glm::vec3(0,0,1);
        glm::vec3 xAxis = glm::vec3(1,0,0);
        glm::vec3 zAxis = glm::vec3(0,0,1);

        void move(float timePassed);
    private:
        void update();

        double mouseX;
        double mouseY;
	};
}
