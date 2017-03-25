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
			//glm::vec4 m_color;
			unsigned int m_color;
			std::vector<glm::vec2> m_uv;
			Texture *m_texture;
		protected:
			Renderable2D() :m_texture(nullptr) { SetUVDefaults(); }
		public:
			Renderable2D(glm::vec3 postition, glm::vec2 size, unsigned int color)
				: m_postition(postition), m_size(size), m_color(color), m_texture(nullptr)
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

			void SetColor(unsigned int color) { m_color = color; };
			void SetColor(glm::vec4 color)
			{
				int r = int(color.r * 255.0f);
				int g = int(color.g * 255.0f);
				int b = int(color.b * 255.0f);
				int a = int(color.a * 255.0f);

				m_color = a << 24 | b << 16 | g << 8 | r;
			};
			
			inline const glm::vec3 &GetPosition() const { return m_postition; }
			inline const glm::vec2 &GetSize() const { return m_size; }
			inline const unsigned int &GetColor() const { return m_color; }
			inline const std::vector<glm::vec2> &GetUV() const { return m_uv; }
			inline const GLuint GetTID() const { return m_texture ? m_texture->GetTID() : 0; }
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