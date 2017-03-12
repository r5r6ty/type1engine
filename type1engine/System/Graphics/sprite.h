#pragma once
#include "renderable2D.h"

namespace Engine
{
	namespace Graphics
	{
		class Sprite : public Renderable2D
		{
		private:
		public:
			Sprite(glm::vec2 pos, glm::vec2 size, const glm::vec4 color);
		};
	}
}