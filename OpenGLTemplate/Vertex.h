#pragma once
#include "GLM\glm.hpp"

namespace objConverter
{
	class Vertex
	{
	public:
		Vertex(int index, glm::vec3& position);
		~Vertex();

		int getIndex();
		float getLength();
		bool isSet();
		bool hasSameTextureAndNormal(int textureIndexOther, int normalIndexOther);
		void setTextureIndex(int textureIndex);
		void setNormalIndex(int normalIndex);
		glm::vec3& getPosition();
		int getTextureIndex();
		int getNormalIndex();
		Vertex* getDuplicateVertex();
		void setDuplicateVertex(Vertex* duplicateVertex);

	private:
		static const int NO_INDEX = -1;

		glm::vec3 position;
		int textureIndex = NO_INDEX;
		int normalIndex = NO_INDEX;
		Vertex* duplicateVertex;
		int index;
		float length;
	};
}
