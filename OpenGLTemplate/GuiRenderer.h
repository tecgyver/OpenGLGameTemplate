#pragma once
#include "Loader.h"
#include "RawModel.h"
#include "GuiTexture.h"
#include "GuiShader.h"

namespace renderEngine
{
class GuiRenderer
{
public:
	GuiRenderer(Loader &loader);
	~GuiRenderer();

	void render(std::vector<guis::GuiTexture*> &guis);
	void cleanUp();

private:
	models::RawModel* mQuad;
	guis::GuiShader shader;
};

}