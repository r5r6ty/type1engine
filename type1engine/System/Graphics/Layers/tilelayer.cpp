#include "tilelayer.h"
#include "../batchrenderer2D.h"
#include <glm/gtc/matrix_transform.hpp>

namespace Engine
{
	namespace Graphics
	{
		TileLayer::TileLayer(Shader *shader)
			: Layer(new BatchRenderer2D(), shader, glm::ortho(-16.0f, 16.0f, -9.0f, 9.0f, -1.0f, 1.0f))
		{

		}

		TileLayer::~TileLayer()
		{
		}
	}
}