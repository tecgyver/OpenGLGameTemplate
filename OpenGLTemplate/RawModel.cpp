#include "RawModel.h"

using namespace models;

RawModel::RawModel(int _vaoID, int _vertexCount)
{
	vaoID = _vaoID;
	vertexCount = _vertexCount;
}


RawModel::~RawModel()
{
}

const int& RawModel::getVaoID()
{
	return vaoID;
}

const int& RawModel::getVertexCount()
{
	return vertexCount;
}