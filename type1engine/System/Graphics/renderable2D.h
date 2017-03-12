#pragma once
#include "../Graphics/Buffers/vertexarray.h"
#include "../Graphics/Buffers/indexbuffer.h"
#include "../Graphics/shader.h"
#include <glm/glm.hpp>

namespace Engine
{

	struct VertexData
	{
		glm::vec3 vertex;
		//glm::vec4 color;
		unsigned int color;
	};

	namespace Graphics
	{
		class Renderable2D
		{
		protected:
			glm::vec3 m_postition;
			glm::vec2 m_size;
			glm::vec4 m_color;
		public:
			Renderable2D(glm::vec3 postition, glm::vec2 size, glm::vec4 color)
				: m_postition(postition), m_size(size), m_color(color)
			{
			}
			virtual ~Renderable2D()
			{
			}
		public:
			inline const glm::vec3 GetPosition() const { return m_postition; };
			inline const glm::vec2 GetSize() const { return m_size; };
			inline const glm::vec4 GetColor() const { return m_color; };
		};
	}
}