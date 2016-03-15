#pragma once

#include <map>

namespace renderEngine
{
class RenderController
{
public:
	RenderController();
	~RenderController();

	static bool showHelp;
	static bool showFPS;
	static bool showWireframe;
	static int minFilter;
	static int magFilter;
	static bool viewfrustumCullingDisabled;
	static bool transparencyDisabled;

	static void checkInput();

private:
	static std::map<int, bool> buttonState;

	static bool getKeyPressed(int key);
};

}