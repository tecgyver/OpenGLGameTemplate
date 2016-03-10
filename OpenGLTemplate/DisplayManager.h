#pragma once
#include <string>

#include "GLEW/glew.h"
#include "GLFW/glfw3.h"

namespace renderEngine {
	class DisplayManager
	{
	public:
		DisplayManager();
		~DisplayManager();

		static const int WIDTH = 1024;
		static const int HEIGHT = 768;
		static GLFWwindow* WINDOW;

		static void createDisplay();
		static void updateDisplay();
		static void closeDisplay();
		static bool windowShouldClose();
        static void setTitle(const std::string &title);
        static void catchMouse();
        static void releaseMouse();
    private:
		static const int FPS_CAP = 120;

        static void critError(const std::string &errorMsg, int exitcode);
	};
}
