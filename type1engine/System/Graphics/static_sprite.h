#pragma once
#include "renderable2D.h"

namespace Engine
{
	namespace Graphics
	{
		class StaticSprite : public Renderable2D
		{
		private:
			VertexArray *m_vertexarray;
			IndexBuffer *m_indexbuffer;
			Shader *m_shader;
		public:
			StaticSprite(glm::vec2 pos, glm::vec2 size, const glm::vec4 color, Shader *shader);
			~StaticSprite();

			inline const VertexArray *GetVAO() const { return m_vertexarray; };
			inline const IndexBuffer *GetIBO() const { return m_indexbuffer; };
			inline Shader *GetShader() const { return m_shader; };
		};
	}
}