#pragma once
#include "DisplayManager.h"

namespace input
{
	class Keyboard
	{
	public:
		Keyboard();
		~Keyboard();
		static bool getKeyPressed(int key);
	};
}