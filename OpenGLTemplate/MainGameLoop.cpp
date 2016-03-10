#include <cstdlib> 
#include <ctime>

#include "MainGameLoop.h"
#include "DisplayManager.h"
#include "Loader.h"
#include "EntityRenderer.h"
#include "StaticShader.h"
#include "ModelTexture.h"
#include "TexturedModel.h"
#include "Entity.h"
#include "OBJLoader.h"
#include "MasterRenderer.h"
#include "Terrain.h"
#include "FrameBuffer.h"
#include "GuiTexture.h"
#include "GuiRenderer.h"

using namespace engineTester;
using namespace objConverter;
using namespace renderEngine;
using namespace models;
using namespace textures;
using namespace entities;
using namespace terrains;
using namespace guis;

MainGameLoop::MainGameLoop()
{
}


MainGameLoop::~MainGameLoop()
{
}

void MainGameLoop::run()
{
	srand((unsigned)time(0));

	DisplayManager::createDisplay();
	DisplayManager::setTitle(std::string("My first display!"));

	Loader loader;

	std::vector<Entity*> entitiesList;
	std::vector<Terrain*> terrainList;
	std::vector<GuiTexture*> guis;

	ModelTexture* terrainTexture = new ModelTexture(loader.loadTexture(std::string("grass.png"), GL_RGB));
	int size = 1;
	for (int x = -(size - 1) / 2; x <= (size - 1) / 2; x++)
	{
		for (int z = -(size - 1) / 2; z <= (size - 1) / 2; z++)
		{
			terrainList.push_back(new Terrain(x, z, loader, terrainTexture));
		}
	}

	ModelData* grassData = OBJLoader::loadObjModel(std::string("grassModel"), loader);
	RawModel* grassModel = loader.loadToVAO(grassData->getVertices(), grassData->getTextureCoords(), grassData->getNormals(), grassData->getIndices());
	ModelTexture* grassTexture = new ModelTexture(loader.loadTexture(std::string("grassTexture.png"), GL_RGBA));
	grassTexture->hasTransparency = true;
	grassTexture->useFakeLighting = true;
	grassTexture->shineDamper = 0;
	grassTexture->reflectivity = 0;

	TexturedModel* texturedGrassModel = new TexturedModel(grassModel, grassTexture);
	for (auto* terrain : terrainList)
	{
		for (int i = 0; i < 0; i++)
		{
			auto* entity = new Entity(texturedGrassModel, glm::vec3(0, 0, 0), 0, 0, 0, 0.5f);
			//entity->position = glm::vec3(0, 1, 1);
			//terrain->placeRandom(entity);
			entitiesList.push_back(entity);
		}
	}

	ModelData* fernData = OBJLoader::loadObjModel(std::string("fern"), loader);
	RawModel* fernModel = loader.loadToVAO(fernData->getVertices(), fernData->getTextureCoords(), fernData->getNormals(), fernData->getIndices());
	ModelTexture* fernTexture = new ModelTexture(loader.loadTexture(std::string("fern.png"), GL_RGBA));
	fernTexture->hasTransparency = true;
	fernTexture->useFakeLighting = true;
	fernTexture->shineDamper = 0;
	fernTexture->reflectivity = 0;

	TexturedModel* texturedFernModel = new TexturedModel(fernModel, fernTexture);
	for (auto* terrain : terrainList)
	{
		for (int i = 0; i < 0; i++)
		{
			auto* entity = new Entity(texturedFernModel, glm::vec3(0, 0, 0), 0, 0, 0, 0.2f);
			//entity->position = glm::vec3(0, 1, 1);
			//terrain->placeRandom(entity);
			entitiesList.push_back(entity);
		}
	}

	ModelData* treeData = OBJLoader::loadObjModel(std::string("tree"), loader);
	RawModel* treeModel = loader.loadToVAO(treeData->getVertices(), treeData->getTextureCoords(), treeData->getNormals(), treeData->getIndices());
	ModelTexture* treeTexture = new ModelTexture(loader.loadTexture(std::string("tree.png"), GL_RGBA));
	treeTexture->shineDamper = 0;
	treeTexture->reflectivity = 0;

	TexturedModel* texturedTreeModel = new TexturedModel(treeModel, treeTexture);
	for (auto* terrain : terrainList)
	{
		for (int i = 0; i < 0; i++)
		{
			auto* entity = new Entity(texturedTreeModel, glm::vec3(0, 0, 0), 0, 0, 0, 3.0f);
			//entity->position = glm::vec3(0, 1, 1);
			//terrain->placeRandom(entity);
			entitiesList.push_back(entity);
		}
	}


	Light light(glm::vec3(0, 500, 0), glm::vec3(1, 1, 1));

	Camera camera(0, 0, 0, false);
	camera.position = glm::vec3(0, 0, 10);

	clock_t startTime = clock();
	clock_t currentTime = startTime;
	float timePassed;

	ModelData* dragonData = OBJLoader::loadObjModel(std::string("dragon"), loader);
	RawModel* dragonModel = loader.loadToVAO(dragonData->getVertices(), dragonData->getTextureCoords(), dragonData->getNormals(), dragonData->getIndices());
	dragonModel->modelColor = glm::vec3(0.8f, 0.6f, 0.0f);
	TexturedModel* texturedDragonModel = new TexturedModel(dragonModel, NULL);
	Entity* dragonEntity = new Entity(texturedDragonModel, glm::vec3(0, 0, 0), 0, 0, 0, 1.f);
	entitiesList.push_back(dragonEntity);

	MasterRenderer renderer(DisplayManager::WIDTH, DisplayManager::HEIGHT, camera, loader);

	GuiRenderer guiRenderer(loader);

	while (!DisplayManager::windowShouldClose())
	{
		timePassed = ((float)(clock() - currentTime)) / CLOCKS_PER_SEC;
		currentTime = clock();
		camera.move(timePassed);

		renderer.renderScene(light, terrainList, entitiesList);
		guiRenderer.render(guis);

		DisplayManager::updateDisplay();
	}
	guiRenderer.cleanUp();
	renderer.cleanup();
	loader.cleanup();

	delete texturedGrassModel;
	delete terrainTexture;
	delete grassTexture;
	for (auto* entity : entitiesList)
		delete entity;
	for (auto* terrain : terrainList)
		delete terrain;
	for (auto* gui : guis)
		delete gui;
	DisplayManager::closeDisplay();
}