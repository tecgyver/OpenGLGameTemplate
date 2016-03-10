#pragma once

namespace textures
{
	class ModelTexture
	{
	public:
		ModelTexture(int id);
		~ModelTexture();
		int getID();

		float shineDamper;
		float reflectivity;
		bool hasTransparency;
		bool useFakeLighting;

	private:
		int textureID;
	};
}
