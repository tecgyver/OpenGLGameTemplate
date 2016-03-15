#include "GuiRenderer.h"
#include "GLEW\glew.h"
#include "Maths.h"
#include "RenderController.h"


using namespace renderEngine;
using namespace toolbox;

GuiRenderer::GuiRenderer(Loader &loader)
{
	std::vector<float> positions = {
		-1, 1,
		-1, -1,
		1, 1,
		1, -1
	};
	mQuad = loader.loadToVAO(positions);
	shader.init();
}


GuiRenderer::~GuiRenderer()
{
}

void GuiRenderer::render(std::vector<guis::GuiTexture*> &guis)
{
	shader.start();
	glBindVertexArray(mQuad->getVaoID());
	glEnableVertexAttribArray(0);
	if (!RenderController::transparencyDisabled)
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glDisable(GL_DEPTH_TEST);
	}
	for (auto* gui : guis)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, gui->getTextureID());
		glm::mat4 matrix;
		Maths::createTransformationMatrix(gui->getPosition(), gui->getScale(), matrix);
		shader.loadTransformationMatrix(matrix);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, mQuad->getVertexCount());
	}
	if (!RenderController::transparencyDisabled)
	{
		glEnable(GL_DEPTH_TEST);
		glDisable(GL_BLEND);
	}
	glDisableVertexAttribArray(0);
	glBindVertexArray(0);
	shader.stop();
}

void GuiRenderer::cleanUp()
{
	shader.cleanup();
	delete mQuad;
}