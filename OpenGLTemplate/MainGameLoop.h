#pragma once

namespace engineTester
{
	class MainGameLoop
	{
	public:
		MainGameLoop();
		~MainGameLoop();

		static void run();
		static float getRandomFloat(float min, float max, int decimals);
	};
}