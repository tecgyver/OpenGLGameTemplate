#include <iostream>
#include <fstream>
#include <sstream>

#include "OBJLoader.h"
#include "GLM/glm.hpp"
#include "DisplayManager.h"

#pragma comment(lib, "assimp.lib")

#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing fla

using namespace objConverter;
using namespace renderEngine;
using namespace models;

OBJLoader::OBJLoader()
{
}


OBJLoader::~OBJLoader()
{
}

ModelData* OBJLoader::loadObjModel(std::string& fileName, Loader& loader)
{
	fileName = "res/" + fileName + ".obj";
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(fileName,
		aiProcess_CalcTangentSpace |
		aiProcess_Triangulate |
		aiProcess_JoinIdenticalVertices |
		aiProcess_SortByPType);

	if (!scene)
	{
		std::cout << "Couldn't load model " << fileName << "!" << std::endl;
		system("PAUSE");
		exit(-1);
	}

	const int iVertexTotalSize = sizeof(aiVector3D) * 2 + sizeof(aiVector2D);

	int iTotalVertices = 0;

	std::vector<int> iMeshStartIndices;
	std::vector<int> iMeshSizes;
	std::vector<int> iMaterialIndices;
	int iNumMaterials;

	unsigned int vertexCount = 0;

	std::vector<float> vertices;
	std::vector<float> textureCoords;
	std::vector<float> normals;
	std::vector<int> indices;
	std::vector<std::string> texturePaths;

	for (int i = 0; i < scene->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[i];
		int iMeshFaces = mesh->mNumFaces;
		iMaterialIndices.push_back(mesh->mMaterialIndex);
		int iSizeBefore = vertexCount;
		iMeshStartIndices.push_back(iSizeBefore / iVertexTotalSize);
		for (int j = 0; j < iMeshFaces; j++)
		{
			const aiFace& face = mesh->mFaces[j];
			for (int k = 0; k < 3; k++)
			{
				aiVector3D pos = mesh->mVertices[face.mIndices[k]];
				aiVector3D uv = mesh->mTextureCoords[0][face.mIndices[k]];
				aiVector3D normal = mesh->HasNormals() ? mesh->mNormals[face.mIndices[k]] : aiVector3D(1.0f, 0.0f, 0.0f);
				//glm::vec3 glmNormal = glm::normalize(glm::vec3(normal.x, normal.y, normal.z);
				vertices.push_back(pos.x);
				vertices.push_back(pos.y);
				vertices.push_back(pos.z);
				textureCoords.push_back(uv.x);
				textureCoords.push_back(uv.y);
				normals.push_back(normal.x);
				normals.push_back(normal.y);
				normals.push_back(normal.z);
				indices.push_back(vertexCount / iVertexTotalSize);
				vertexCount += iVertexTotalSize;
			}
		}
		int iMeshVertices = mesh->mNumVertices;
		iTotalVertices += iMeshVertices;
		iMeshSizes.push_back((vertexCount - iSizeBefore) / iVertexTotalSize);
	}
	iNumMaterials = scene->mNumMaterials;

	std::vector<int> materialRemap(iNumMaterials);

	for (int i = 0; i < iNumMaterials; i++)
	{
		const aiMaterial* material = scene->mMaterials[i];
		int a = 5;
		int texIndex = 0;
		aiString path;  // filename

		if (material->GetTexture(aiTextureType_DIFFUSE, texIndex, &path) == AI_SUCCESS)
		{
			std::string sDir = fileName.substr(0, fileName.find_last_of("\\") + 1);
			std::string sTextureName = path.data;
			std::string sFullPath = sDir + sTextureName;
			int iTexFound = -1;
			for (int j = 0; j < texturePaths.size(); j++)
			{
				if (sFullPath == texturePaths[j])
				{
					iTexFound = j;
					break;
				}
			}
			if (iTexFound != -1)materialRemap[i] = iTexFound;
			else
			{
				materialRemap[i] = texturePaths.size();
				texturePaths.push_back(sFullPath);
			}
		}
	}

	for (int i = 0; i < iMeshSizes.size(); i++)
	{
		int iOldIndex = iMaterialIndices[i];
		iMaterialIndices[i] = materialRemap[iOldIndex];
	}

	return new ModelData(vertices, textureCoords, normals, indices, texturePaths);

	//std::ifstream in("res/" + fileName + ".obj", std::ios::binary | std::ios::ate);

	//std::vector<float> vertices;
	//std::vector<float> textures;
	//std::vector<float> normals;
	//std::vector<int> indices;

	//std::vector<Vertex*> tempVertices;
	//std::vector<glm::vec2> tempTextures;
	//std::vector<glm::vec3> tempNormals;

	//if (in.good())
	//{
	//	bool commandWord = true;
	//	unsigned char type = 0;
	//	std::string fileData;
	//	fileData.resize(in.tellg());
	//	in.close();
	//	std::ifstream file("res/" + fileName + ".obj");
	//	std::stringstream currentWord;
	//	fileData.assign((std::istreambuf_iterator<char>(file)),
	//		std::istreambuf_iterator<char>());

	//	int wordCount = 0;
	//	int faceCount = 0;
	//	glm::vec2 vec2;
	//	glm::vec3 vec3;
	//	glm::vec3 currentNorm;
	//	bool facesStarted = false;

	//	for (char& c : fileData)
	//	{
	//		if (c == ' ' || c == '\n')
	//		{
	//			commandWord = false;
	//			if (type != 5 && wordCount > 0)
	//			{
	//				switch (type)
	//				{
	//				case 1: //Vertex
	//					if (wordCount == 1)
	//					{
	//						vec3.x = std::stof(currentWord.str());
	//					}
	//					else if (wordCount == 2)
	//					{
	//						vec3.y = std::stof(currentWord.str());
	//					}
	//					else if (wordCount == 3)
	//					{
	//						vec3.z = std::stof(currentWord.str());
	//						Vertex* vert = new Vertex(tempVertices.size(), vec3);
	//						tempVertices.push_back(vert);
	//					}
	//				case 2: //texCoord
	//					if (wordCount == 1)
	//						vec2.x = std::stof(currentWord.str());
	//					else if (wordCount == 2)
	//					{
	//						vec2.y = std::stof(currentWord.str());
	//						tempTextures.push_back(vec2);
	//					}
	//					break;
	//				case 3: //texNorm
	//					if (wordCount == 1)
	//						vec3.x = std::stof(currentWord.str());
	//					else if (wordCount == 2)
	//						vec3.y = std::stof(currentWord.str());
	//					else if (wordCount == 3)
	//					{
	//						vec3.z = std::stof(currentWord.str());
	//						tempNormals.push_back(vec3);
	//					}
	//					break;
	//				case 4: //Face
	//					vec3.z = std::stoi(currentWord.str()) - 1;
	//					processVertex(vec3, tempVertices, indices);
	//					break;
	//				}
	//				//Cleanup
	//				currentWord.str("");
	//				currentWord.clear();
	//			}
	//			if (c == '\n')
	//			{
	//				commandWord = true;
	//				wordCount = 0;
	//				type = 0;
	//				continue;
	//			}
	//			wordCount++;
	//		}
	//		else if (c == '/')
	//		{
	//			if (type == 4)
	//			{
	//				switch (faceCount)
	//				{
	//				case 0:
	//					vec3.x = std::stoi(currentWord.str()) - 1;
	//					break;
	//				case 1:
	//					vec3.y = std::stoi(currentWord.str()) - 1;
	//					break;
	//				}
	//				faceCount++;
	//				//Cleanup
	//				currentWord.str("");
	//				currentWord.clear();
	//			}
	//		}
	//		else
	//		{
	//			//Not an interesting command/line
	//			if (type == 5)
	//				continue;
	//			if (commandWord)
	//			{
	//				if (type == 0 && c == 'v')
	//				{
	//					type = 1;
	//				}
	//				else if (type == 1 && c == 't')
	//				{
	//					type = 2;
	//				}
	//				else if (type == 1 && c == 'n')
	//				{
	//					type = 3;
	//				}
	//				else if (type == 0 && c == 'f')
	//				{
	//					type = 4;
	//					if (!facesStarted)
	//					{
	//						facesStarted = true;
	//					}
	//				}
	//				else
	//				{
	//					type = 5; // "Do not want" Flag
	//					continue;
	//				}
	//			}
	//			else
	//			{
	//				currentWord << c;
	//			}
	//		}
	//	}
	//	file.close();
	//}
	//in.close();
	//vertices.resize(tempVertices.size() * 3);
	//textures.resize(tempVertices.size() * 2);
	//normals.resize(tempVertices.size() * 3);
	//removeUnusedVertices(tempVertices);
	//float furthest = convertDataToArrays(tempVertices, tempTextures, tempNormals, vertices,
	//	textures, normals);
	//return new ModelData(vertices, textures, normals, indices, furthest);
	////return 0;
}

//void OBJLoader::processVertex(glm::vec3& vertex, std::vector<Vertex*>& vertices, std::vector<int>& indices)
//{
//	int index = vertex.x;
//	Vertex* currentVertex = vertices[index];
//
//	if (!currentVertex->isSet())
//	{
//		currentVertex->setTextureIndex(vertex.y);
//		currentVertex->setNormalIndex(vertex.z);
//		indices.push_back(index);
//	}
//	else
//	{
//		dealWithAlreadyProcessedVertex(currentVertex, vertex.y, vertex.z, indices,
//			vertices);
//	}
//	/*vec2 = tempTextures[vec3.y];
//	textures[currentVertexPointer * 2] = vec2.x;
//	textures[currentVertexPointer * 2 + 1] = vec2.y;
//
//	currentNorm = tempNormals[vec3.z];
//	normals[currentVertexPointer * 3] = currentNorm.x;
//	normals[currentVertexPointer * 3 + 1] = currentNorm.y;
//	normals[currentVertexPointer * 3 + 2] = currentNorm.z;
//	faceCount = 0;*/
//}
//
//void OBJLoader::dealWithAlreadyProcessedVertex(Vertex* previousVertex, int newTextureIndex,
//	int newNormalIndex, std::vector<int>& indices, std::vector<Vertex*>& vertices)
//{
//	if (previousVertex->hasSameTextureAndNormal(newTextureIndex, newNormalIndex))
//	{
//		indices.push_back(previousVertex->getIndex());
//	}
//	else
//	{
//		Vertex* anotherVertex = previousVertex->getDuplicateVertex();
//		if (anotherVertex)
//		{
//			dealWithAlreadyProcessedVertex(anotherVertex, newTextureIndex, newNormalIndex,
//				indices, vertices);
//		}
//		else
//		{
//			Vertex* duplicateVertex = new Vertex(vertices.size(), previousVertex->getPosition());
//			duplicateVertex->setTextureIndex(newTextureIndex);
//			duplicateVertex->setNormalIndex(newNormalIndex);
//			previousVertex->setDuplicateVertex(duplicateVertex);
//			vertices.push_back(duplicateVertex);
//			indices.push_back(duplicateVertex->getIndex());
//		}
//
//	}
//}
//
//float OBJLoader::convertDataToArrays(std::vector<Vertex*>& vertices, std::vector<glm::vec2>& textures,
//	std::vector<glm::vec3>& normals, std::vector<float>& verticesArray, std::vector<float>& texturesArray,
//	std::vector<float>& normalsArray)
//{
//	float furthestPoint = 0;
//	for (int i = 0; i < vertices.size(); i++)
//	{
//		Vertex* currentVertex = vertices[i];
//		if (currentVertex->getLength() > furthestPoint)
//		{
//			furthestPoint = currentVertex->getLength();
//		}
//		auto& position = currentVertex->getPosition();
//		auto& textureCoord = textures[currentVertex->getTextureIndex()];
//		auto& normalVector = normals[currentVertex->getNormalIndex()];
//		verticesArray[i * 3] = position.x;
//		verticesArray[i * 3 + 1] = position.y;
//		verticesArray[i * 3 + 2] = position.z;
//		texturesArray[i * 2] = textureCoord.x;
//		texturesArray[i * 2 + 1] = 1 - textureCoord.y;
//		normalsArray[i * 3] = normalVector.x;
//		normalsArray[i * 3 + 1] = normalVector.y;
//		normalsArray[i * 3 + 2] = normalVector.z;
//	}
//	return furthestPoint;
//}
//
//void OBJLoader::removeUnusedVertices(std::vector<Vertex*>& vertices)
//{
//	for (Vertex* vertex : vertices){
//		if (!vertex->isSet()){
//			vertex->setTextureIndex(0);
//			vertex->setNormalIndex(0);
//		}
//	}
//}