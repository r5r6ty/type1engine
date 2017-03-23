#include "sprite.h"

namespace Engine
{
	namespace Graphics
	{
		Sprite::Sprite(glm::vec2 pos, glm::vec2 size, unsigned int color)
			: Renderable2D(glm::vec3(pos, 0), size, color)
		{
		}

		Sprite::Sprite(glm::vec2 pos, glm::vec2 size, Texture *texture)
			: Renderable2D(glm::vec3(pos, 0), size, 0x00000000)
		{
			m_texture = texture;
		}
	}
}