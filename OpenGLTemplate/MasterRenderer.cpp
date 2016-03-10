#include "MasterRenderer.h"
#include "GLEW/glew.h"
#include "GLM/gtc/matrix_transform.hpp"

using namespace renderEngine;
using namespace models;
using namespace shaders;
using namespace entities;
using namespace terrains;

const float MasterRenderer::FOV = 70;
const float MasterRenderer::NEAR_PLANE = 0.1f;
const float MasterRenderer::FAR_PLANE = 1000.0f;
const float MasterRenderer::RED = 0.5f;
const float MasterRenderer::GREEN = 0.5f;
const float MasterRenderer::BLUE = 0.5f;

MasterRenderer::MasterRenderer(int _width, int _height, Camera &_camera, Loader& _loader)
    : camera(_camera), loader(_loader)
{
	enableBackfaceCulling();
	width = _width;
    height = _height;
    viewportSize = glm::vec2(_width,_height);
	createProjectionMatrix();

	entityShader = new StaticShader();
	entityShader->init();
	entityRenderer = new EntityRenderer(*entityShader, projectionMatrix);

	terrainShader = new TerrainShader();
	terrainShader->init();
	terrainRenderer = new TerrainRenderer(*terrainShader, projectionMatrix);
}

MasterRenderer::~MasterRenderer()
{
	delete entityShader;
	delete entityRenderer;
	delete terrainShader;
	delete terrainRenderer;
}

void MasterRenderer::cleanup()
{
	entityShader->cleanup();
	terrainShader->cleanup();
}

void MasterRenderer::prepare(std::vector<Terrain*> &terrainList, std::vector<Entity*> &entityList)
{
    //Source: http://www.racer.nl/reference/vfc_markmorley.htm
    {
        glm::mat4 vpMatrix = projectionMatrix * camera.viewMatrix;

        // Right clipping plane.
        frustum[0].position = glm::vec3(vpMatrix[0].w - vpMatrix[0].x, vpMatrix[1].w - vpMatrix[1].x, vpMatrix[2].w - vpMatrix[2].x);
        frustum[0].distance = vpMatrix[3].w - vpMatrix[3].x;
        // Left clipping plane.
        frustum[1].position = glm::vec3(vpMatrix[0].w + vpMatrix[0].x, vpMatrix[1].w + vpMatrix[1].x, vpMatrix[2].w + vpMatrix[2].x);
        frustum[1].distance = vpMatrix[3].w + vpMatrix[3].x;
        // Bottom clipping plane.
        frustum[2].position = glm::vec3(vpMatrix[0].w + vpMatrix[0].y, vpMatrix[1].w + vpMatrix[1].y, vpMatrix[2].w + vpMatrix[2].y);
        frustum[2].distance = vpMatrix[3].w + vpMatrix[3].y;
        // Top clipping plane.
        frustum[3].position = glm::vec3(vpMatrix[0].w - vpMatrix[0].y, vpMatrix[1].w - vpMatrix[1].y, vpMatrix[2].w - vpMatrix[2].y);
        frustum[3].distance = vpMatrix[3].w - vpMatrix[3].y;
        // Far clipping plane.
        frustum[4].position = glm::vec3(vpMatrix[0].w - vpMatrix[0].z, vpMatrix[1].w - vpMatrix[1].z, vpMatrix[2].w - vpMatrix[2].z);
        frustum[4].distance = vpMatrix[3].w - vpMatrix[3].z;
        // Near clipping plane.
        frustum[5].position = glm::vec3(vpMatrix[0].w + vpMatrix[0].z, vpMatrix[1].w + vpMatrix[1].z, vpMatrix[2].w + vpMatrix[2].z);
        frustum[5].distance = vpMatrix[3].w + vpMatrix[3].z;

        // Normalize, this is not always necessary...
        for (unsigned int i = 0; i < 6; i++)
        {
              float normFact = glm::length(frustum[i].position);
              frustum[i].distance = frustum[i].distance / normFact;
              frustum[i].position = frustum[i].position / normFact;
        }
    }

	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(RED, GREEN, BLUE, 1);

	for (auto* terrain : terrainList)
	{
		processTerrain(terrain);
	}
	for (auto* entity : entityList)
	{
		processEntity(entity);
	}
}

void MasterRenderer::enableBackfaceCulling()
{
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
}

void MasterRenderer::disableBackfaceCulling()
{
	glDisable(GL_CULL_FACE);
}

void MasterRenderer::processEntity(Entity* entity)
{
	TexturedModel* entityModel = entity->model;
	auto it = entitiesMap.find(entityModel);
	if (it != entitiesMap.end())
	{
		(*it).second.push_back(entity);
	}
	else
	{
		entitiesMap[entityModel].push_back(entity);
	}
}

void MasterRenderer::processTerrain(Terrain* terrain)
{
	terrainsList.push_back(terrain);
}

void MasterRenderer::renderScene(Light& sun, std::vector<Terrain*> &terrainList, std::vector<Entity*> &entityList)
{
	prepare(terrainList, entityList);

	terrainShader->start();
	terrainShader->loadSkyColor(RED, GREEN, BLUE);
	terrainShader->loadLight(sun);
	terrainShader->loadViewMatrix(camera);
	terrainRenderer->render(terrainsList);
	terrainShader->stop();

	entityShader->start();
	entityShader->loadSkyColor(RED, GREEN, BLUE);
	entityShader->loadLight(sun);
	entityShader->loadViewMatrix(camera);
	entityRenderer->render(entitiesMap);
	entityShader->stop();


	entitiesMap.clear();
	terrainsList.clear();
}

void MasterRenderer::createProjectionMatrix()
{
	projectionMatrix = glm::perspective(glm::radians(FOV), ((float)width) / height, NEAR_PLANE, FAR_PLANE);
}

//Source: http://www.racer.nl/reference/vfc_markmorley.htm
short MasterRenderer::isAABBinFrustum(AABB &aabb)
{
    short result = 2;
    for( int i = 0; i < 6; i++ )
    {
        glm::vec3 p = glm::vec3(aabb.min.x,aabb.min.y,aabb.min.z);
        if (frustum[i].position.x >= 0)
            p.x = aabb.max.x;
        if (frustum[i].position.y >=0)
            p.y = aabb.max.y;
        if (frustum[i].position.z >= 0)
            p.z = aabb.max.z;

        glm::vec3 n = glm::vec3(aabb.max.x,aabb.max.y,aabb.max.z);
        if (frustum[i].position.x >= 0)
            n.x = aabb.min.x;
        if (frustum[i].position.y >=0)
            n.y = aabb.min.y;
        if (frustum[i].position.z >= 0)
            n.z = aabb.min.z;

        // is the positive vertex outside?
        if (frustum[i].isCulled(p))
            return 0;
        // is the negative vertex outside?
        else if (frustum[i].isCulled(n))
            result = 1;
    }
    return result;
}

glm::vec2 MasterRenderer::projectToScreen(const glm::vec3 &pos)
{
    glm::vec4 projPos = projectionMatrix * camera.viewMatrix * glm::vec4(pos,1);
    if(projPos.w != 0.0f)
    {
        projPos = projPos / projPos.w;
    }
    return glm::vec2((projPos.x + 1.0f) / 2.0f * width,
                     (1.0f - projPos.y) / 2.0f * height);
}