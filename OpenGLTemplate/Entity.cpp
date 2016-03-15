#include "Entity.h"
#include "Maths.h"

using namespace entities;
using namespace models;
using namespace toolbox;

Entity::Entity(TexturedModel* _model, glm::vec3& _position, float _rotX, float _rotY, float _rotZ, float _scale, bool _staticEntity)
{
	model = _model;
	position = _position;
	rotX = _rotX;
	rotY = _rotY;
	rotZ = _rotZ;
	scale = _scale;
	staticEntity = _staticEntity;
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

void Entity::prepareModelMatrix()
{
	if (modelMatrixInitialized)
		return;
	modelMatrix = glm::mat4();
	Maths::createTransformationMatrix(modelMatrix, position, rotX, rotY, rotZ, scale);
	if (staticEntity)
	{
		modelMatrixInitialized = true;
		model->getRawModel()->aabb.getTransformed(modelMatrix, aabb);
	}
}