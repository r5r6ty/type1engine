#pragma once
#include <glm/glm.hpp>
#include "../Graphics/Buffers/vertexarray.h"
#include "../Graphics/Buffers/indexbuffer.h"
#include "renderer2D.h"
#include "shader.h"
#include "texture.h"

namespace Engine
{

	struct VertexData
	{
		glm::vec3 vertex;
		glm::vec2 uv;
		float tid;
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
			std::vector<glm::vec2> m_uv;
			Texture *m_texture;
		protected:
			Renderable2D() { SetUVDefaults(); }
		public:
			Renderable2D(glm::vec3 postition, glm::vec2 size, glm::vec4 color)
				: m_postition(postition), m_size(size), m_color(color)
			{
				SetUVDefaults();
			}
			virtual ~Renderable2D()
			{
			}
			virtual void Submit(Renderer2D *renderer) const
			{
				renderer->Submit(this);
			}
			
			inline const glm::vec3 &GetPosition() const { return m_postition; };
			inline const glm::vec2 &GetSize() const { return m_size; };
			inline const glm::vec4 &GetColor() const { return m_color; };
			inline const std::vector<glm::vec2> &GetUV() const { return m_uv; };
			inline const GLuint GetTID() const { return m_texture == nullptr ? 0 : m_texture->GetTID(); };
		private:
			void SetUVDefaults()
			{
				m_uv.push_back(glm::vec2(0.0f, 0.0f));
				m_uv.push_back(glm::vec2(0.0f, 1.0f));
				m_uv.push_back(glm::vec2(1.0f, 1.0f));
				m_uv.push_back(glm::vec2(1.0f, 0.0f));
			}
		};
	}
}