#include <iostream>

#include "clippingplane.h"

ClippingPlane::ClippingPlane()
{
}

bool ClippingPlane::isCulled(const glm::vec3 &point)
{
    float distFromOrigin = glm::dot(point, normal);
    if (distFromOrigin + distance <= 0)
        return true;
    return false;
}
