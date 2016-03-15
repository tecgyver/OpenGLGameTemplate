#pragma once

#include "GLM/glm.hpp"

class ClippingPlane
{
public:
    ClippingPlane();

	glm::vec3 normal;
    float distance;

    bool isCulled(const glm::vec3 &point);
};
