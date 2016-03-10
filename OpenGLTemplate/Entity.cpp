#include "Entity.h"

using namespace entities;
using namespace models;

Entity::Entity(TexturedModel* _model, glm::vec3& _position, float _rotX, float _rotY, float _rotZ, float _scale)
{
	model = _model;
	position = _position;
	rotX = _rotX;
	rotY = _rotY;
	rotZ = _rotZ;
	scale = _scale;
}


Entity::~Entity()
{
}

void Entity::increasePosition(float dx, float dy, float dz)
{
	position.x += dx;
	position.y += dy;
	position.z += dz;
}

void Entity::increaseRotation(float dx, float dy, float dz)
{
	rotX += dx;
	rotY += dy;
	rotZ += dz;
}