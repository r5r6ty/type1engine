#include "sprite.h"

namespace Engine
{
	namespace Graphics
	{
		Sprite::Sprite(glm::vec2 pos, glm::vec2 size, const glm::vec4 color)
			: Renderable2D(glm::vec3(pos, 0), size, color)
		{

		}
	}
}