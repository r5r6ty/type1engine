#pragma once
#include <cstddef>
#include "renderer2D.h"

namespace Engine
{
#define	RENDERER_MAX_SPRITES	60000
#define	RENDERER_VERTEX_SIZE	sizeof(VertexData)
#define	RENDERER_SPRITE_SIZE	RENDERER_VERTEX_SIZE * 4
#define	RENDERER_BUFFER_SIZE	RENDERER_SPRITE_SIZE * RENDERER_MAX_SPRITES
#define RENDERER_INDICES_SIZE	RENDERER_MAX_SPRITES * 6
#define SHADER_VERTEX_INDEX		0
#define SHADER_COLOR_INDEX		1
	namespace Graphics
	{
		class BatchRenderer2D : public Renderer2D
		{
		private:
			GLuint m_VAO;
			GLuint m_VBO;
			VertexData *m_buffer;
			IndexBuffer *m_IBO;
			GLsizei m_indexcount;
		public:
			BatchRenderer2D();
			~BatchRenderer2D();
			void Begin() override;
			void Submit(const Renderable2D *renderable2D) override;
			void End() override;
			void Flush() override;
		private:
			void init();
		};
	}
}