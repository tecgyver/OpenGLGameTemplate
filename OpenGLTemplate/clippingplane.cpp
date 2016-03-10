#include <iostream>

#include "clippingplane.h"

ClippingPlane::ClippingPlane()
{
}

bool ClippingPlane::isCulled(const glm::vec3 &point)
{
    if(position.x * point.x + position.y * point.y + position.z * point.z + distance <= 0)
        return true;
    return false;

//    float distFromOrigin = glm::dot(point, position);
//    if (distFromOrigin + distance <= 0)
//        return true;
//    return false;
}
