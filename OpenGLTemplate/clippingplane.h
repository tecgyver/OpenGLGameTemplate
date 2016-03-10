#pragma once

#include "GLM/glm.hpp"

class ClippingPlane
{
public:
    ClippingPlane();

    glm::vec3 position;
    float distance;

    bool isCulled(const glm::vec3 &point);
};
