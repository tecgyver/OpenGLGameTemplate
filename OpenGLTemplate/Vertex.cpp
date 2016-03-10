#include "Vertex.h"


using namespace objConverter;

Vertex::Vertex(int _index, glm::vec3& _position) : position(_position)
{
	index = _index;
	length = glm::length(_position);
}

Vertex::~Vertex()
{
}

int Vertex::getIndex(){
	return index;
}

float Vertex::getLength(){
	return length;
}

bool Vertex::isSet(){
	return textureIndex != NO_INDEX && normalIndex != NO_INDEX;
}

bool Vertex::hasSameTextureAndNormal(int textureIndexOther, int normalIndexOther){
	return textureIndexOther == textureIndex && normalIndexOther == normalIndex;
}

void Vertex::setTextureIndex(int _textureIndex){
	textureIndex = _textureIndex;
}

void Vertex::setNormalIndex(int _normalIndex){
	normalIndex = _normalIndex;
}

glm::vec3& Vertex::getPosition() {
	return position;
}

int Vertex::getTextureIndex() {
	return textureIndex;
}

int Vertex::getNormalIndex() {
	return normalIndex;
}

Vertex* Vertex::getDuplicateVertex() {
	return duplicateVertex;
}

void Vertex::setDuplicateVertex(Vertex* _duplicateVertex) {
	duplicateVertex = _duplicateVertex;
}