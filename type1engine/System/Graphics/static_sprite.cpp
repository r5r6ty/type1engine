#include "static_sprite.h"

namespace Engine
{
	namespace Graphics
	{
		StaticSprite::StaticSprite(glm::vec2 pos, glm::vec2 size, const glm::vec4 color, Shader *shader)
			: Renderable2D(glm::vec3(pos, 0.0f), size, 0xFFFFFFFF), m_shader(shader)
		{
			m_vertexarray = new VertexArray();

			GLfloat vertices[] =
			{
				0.0f, 0.0f, 0.0f,
				0.0f, size.y, 0.0f,
				size.x, size.y, 0.0f,
				size.x, 0.0f, 0.0f
			};

			GLfloat colors[] =
			{
				color.x, color.y, color.z, color.w,
				color.x, color.y, color.z, color.w,
				color.x, color.y, color.z, color.w,
				color.x, color.y, color.z, color.w
			};

			m_vertexarray->AddBuffer(new Buffer(vertices, 4 * 3, 3), 0);
			m_vertexarray->AddBuffer(new Buffer(colors, 4 * 4, 4), 1);

			GLuint indices[] = { 0, 1, 2, 2, 3, 0 };
			m_indexbuffer = new IndexBuffer(indices, 6);
		}

		StaticSprite::~StaticSprite()
		{

		}
	}
}