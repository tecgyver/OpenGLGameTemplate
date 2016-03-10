#include <iostream>

#include "Loader.h"
#include "GLEW/glew.h"
#include "FREEIMAGE/FreeImage.h"

using namespace renderEngine;
using namespace models;

Loader::Loader()
{
}


Loader::~Loader()
{
}

RawModel* Loader::loadToVAO(std::vector<float>& positions, std::vector<float>& textureCoords, std::vector<float>& normals, std::vector<int>& indices)
{
	int vaoID = createVAO();
	bindIndicesBuffer(indices);

	long counter = 0;
	glm::vec3 min = glm::vec3(std::numeric_limits<float>::max(), std::numeric_limits<float>::max(), std::numeric_limits<float>::max());
	glm::vec3 max = glm::vec3(std::numeric_limits<float>::min(), std::numeric_limits<float>::min(), std::numeric_limits<float>::min());
	for (auto& position : positions)
	{
		switch (counter % 3)
		{
		case 0:
			min.x = glm::min(min.x, position);
			max.x = glm::max(max.x, position);
			break;
		case 1:
			min.y = glm::min(min.y, position);
			max.y = glm::max(max.y, position);
			break;
		case 2:
			min.z = glm::min(min.z, position);
			max.z = glm::max(max.z, position);
			break;
		}
		counter++;
	}
	storeDataInAttributeList(0, 3, positions);
	storeDataInAttributeList(1, 2, textureCoords);
	storeDataInAttributeList(2, 3, normals);
	unbindVAO();
	auto* model = new RawModel(vaoID, indices.size());
	model->aabb.min = min;
	model->aabb.max = max;
	model->aabb.size = max - min;
	return model;
}

RawModel* Loader::loadToVAO(std::vector<float>& positions)
{
	int vaoID = createVAO();
	storeDataInAttributeList(0, 2, positions);
	unbindVAO();
	auto* model = new RawModel(vaoID, positions.size() / 2);
	return model;
}

int Loader::createVAO()
{
	GLuint vaoID;
	glGenVertexArrays(1, &vaoID);
	vaos.push_back(vaoID);
	glBindVertexArray(vaoID);
	return vaoID;
}


void Loader::storeDataInAttributeList(int attributeNumber, int coordinateSize, std::vector<float>& data)
{
	GLuint vboID;
	glGenBuffers(1, &vboID);
	vbos.push_back(vboID);
	glBindBuffer(GL_ARRAY_BUFFER, vboID);
	glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), &data[0], GL_STATIC_DRAW);
	glVertexAttribPointer(attributeNumber, coordinateSize, GL_FLOAT, false, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Loader::bindIndicesBuffer(std::vector<int>& indices)
{
	GLuint vboID;
	glGenBuffers(1, &vboID);
	vbos.push_back(vboID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
}

int Loader::createEmptyVbo(int floatCount)
{
    GLuint vbo;
    glGenBuffers(1, &vbo);
    vbos.push_back(vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, floatCount * sizeof(float), 0, GL_DYNAMIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    return vbo;
}

void Loader::addInstancedAttribute(int vao, int vbo, int attribute, int dataSize, int instancedDataLength, unsigned int offset)
{
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBindVertexArray(vao);
    glVertexAttribPointer(attribute,dataSize,GL_FLOAT,false,instancedDataLength * sizeof(float), (GLvoid*)(offset * sizeof(float)));
    glVertexAttribDivisor(attribute, 1);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Loader::updateInstancedVbo(int vbo, int floatCount, int instanceDataCount, int maxInstanceDataCount, float* data)
{
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    //glBufferData(GL_ARRAY_BUFFER, maxInstanceDataCount * floatCount * sizeof(float), 0, GL_DYNAMIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, instanceDataCount * floatCount * sizeof(float), data);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

int Loader::loadTexture(std::string& filename, int glPixelType)
{
	try
	{
	//image format
	FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
	//pointer to the image, once loaded
	FIBITMAP *dib(0);
	//pointer to the image data
	BYTE* bits(0);
	//image width and height
	unsigned int width(0), height(0);
	//OpenGL's image ID to map to
	GLuint gl_texID;

	std::string filePath = "res/" + filename;
	const char* cFilePath = &filePath[0];

	//check the file signature and deduce its format
	fif = FreeImage_GetFileType(cFilePath, 0);
	//if still unknown, try to guess the file format from the file extension
	if (fif == FIF_UNKNOWN){
		fif = FreeImage_GetFIFFromFilename(cFilePath);
		//if still unkown, return failure

		if (fif == FIF_UNKNOWN){
			return false;
		}
	}


	//check that the plugin has reading capabilities and load the file
	if (FreeImage_FIFSupportsReading(fif)){

		dib = FreeImage_Load(fif, cFilePath);
		//if the image failed to load, return failure
		if (!dib){
			return false;
		}
	}


	//retrieve the image data
	bits = FreeImage_GetBits(dib);
	//get the image width and height
	width = FreeImage_GetWidth(dib);
	height = FreeImage_GetHeight(dib);
	//if this somehow one of these failed (they shouldn't), return failure
	if ((bits == 0) || (width == 0) || (height == 0))
		return false;

	//generate an OpenGL texture ID for this texture
	glGenTextures(1, &gl_texID);
	glActiveTexture(GL_TEXTURE0);
	//bind to the new texture ID
	glBindTexture(GL_TEXTURE_2D, gl_texID);
	//store the texture data for OpenGL use
	glTexImage2D(GL_TEXTURE_2D, 0, glPixelType, width, height,
		0, glPixelType, GL_UNSIGNED_BYTE, bits);

	glGenerateMipmap(GL_TEXTURE_2D);

	//Free FreeImage's copy of the data
	FreeImage_Unload(dib);

	textures.push_back(gl_texID);

	//return success
	return gl_texID;
	}
	catch (int e)
	{
		std::cout << "Error " << e << " while loading texture " << filename.c_str() << std::endl;
	}
}

void Loader::unbindVAO()
{
	glBindVertexArray(0);
}

void Loader::cleanup()
{
	GLuint current;
	for (auto& vao : vaos)
	{
		current = vao;
		glDeleteVertexArrays(1, &current);
	}
	for (auto& vbo : vbos)
	{
		current = vbo;
		glDeleteBuffers(1, &current);
	}
	for (auto& texture : textures)
	{
		current = texture;
		glDeleteTextures(1, &current);
	}
}