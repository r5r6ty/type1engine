#include "batchrenderer2D.h"

namespace Engine
{
	namespace Graphics
	{
		BatchRenderer2D::BatchRenderer2D()
		{
			init();
		}

		BatchRenderer2D::~BatchRenderer2D()
		{
			delete m_IBO;
			glDeleteBuffers(1, &m_VBO);
		}

		void BatchRenderer2D::init()
		{
			glGenVertexArrays(1, &m_VAO);
			glBindVertexArray(m_VAO);

			glGenBuffers(1, &m_VBO);
			glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
			glBufferData(GL_ARRAY_BUFFER, RENDERER_BUFFER_SIZE, NULL, GL_DYNAMIC_DRAW);
			glEnableVertexAttribArray(SHADER_VERTEX_INDEX);
			glVertexAttribPointer(SHADER_VERTEX_INDEX, 3, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const void*)0);

			glEnableVertexAttribArray(SHADER_UV_INDEX);
			glVertexAttribPointer(SHADER_UV_INDEX, 2, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const void*)(offsetof(VertexData, VertexData::uv)));

			glEnableVertexAttribArray(SHADER_TID_INDEX);
			glVertexAttribPointer(SHADER_TID_INDEX, 1, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const void*)(offsetof(VertexData, VertexData::tid)));

			glEnableVertexAttribArray(SHADER_COLOR_INDEX);
			glVertexAttribPointer(SHADER_COLOR_INDEX, 4, GL_UNSIGNED_BYTE, GL_TRUE, RENDERER_VERTEX_SIZE, (const void*)(offsetof(VertexData, VertexData::color)));
			glBindBuffer(GL_ARRAY_BUFFER, 0);

			GLuint *indices = new GLuint[RENDERER_INDICES_SIZE];
			unsigned int offset = 0;
			unsigned int indexarray[6] = { 0,1,2,2,3,0 };
			for (unsigned int i = 0; i < RENDERER_INDICES_SIZE; i += 6)
			{
				for (unsigned int j = 0; j < 6; j++)
				{
					indices[i + j] = offset + indexarray[j];
				}
				offset += 4;
			}
			m_IBO = new IndexBuffer(indices, RENDERER_INDICES_SIZE);
			delete indices;

			glBindVertexArray(0);
		}

		void BatchRenderer2D::Begin()
		{
			glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
			m_buffer = (VertexData*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
		}

		void BatchRenderer2D::Submit(const Renderable2D *renderable)
		{
			const glm::vec3 &position = renderable->GetPosition();
			const glm::vec2 &size = renderable->GetSize();
			const unsigned int &color = renderable->GetColor();
			const std::vector<glm::vec2> &uv = renderable->GetUV();
			const GLuint tid = renderable->GetTID();

			float ts = 0.0f;
			if (tid > 0)
			{
				bool found = false;
				for (unsigned int i = 0; i < m_TextureSlots.size(); i++)
				{
					if (m_TextureSlots[i] == tid)
					{
						ts = (float)(i + 1);
						found = true;
						break;
					}
				}
				if (!found)
				{
					if (m_TextureSlots.size() >= 32)
					{
						End();
						Flush();
						Begin();
					}
					m_TextureSlots.push_back(tid);
					ts = (float)(m_TextureSlots.size());
				}
			}
			else
			{

			}

			m_buffer->vertex = *m_m_transformationback * glm::vec4(position, 1.0f);
			m_buffer->uv = uv[0];
			m_buffer->tid = ts;
			m_buffer->color = color;
			m_buffer++;

			m_buffer->vertex = *m_m_transformationback * glm::vec4(position.x, position.y + size.y, position.z ,1.0f);
			m_buffer->uv = uv[1];
			m_buffer->tid = ts;
			m_buffer->color = color;
			m_buffer++;

			m_buffer->vertex = *m_m_transformationback * glm::vec4(position.x + size.x, position.y + size.y, position.z, 1.0f);
			m_buffer->uv = uv[2];
			m_buffer->tid = ts;
			m_buffer->color = color;
			m_buffer++;

			m_buffer->vertex = *m_m_transformationback * glm::vec4(position.x + size.x, position.y, position.z, 1.0f);
			m_buffer->uv = uv[3];
			m_buffer->tid = ts;
			m_buffer->color = color;
			m_buffer++;

			m_indexcount += 6;
		}

		void BatchRenderer2D::DrawString(const char *text, const glm::vec3 &position, Font &font, unsigned int color)
		{
			using namespace ftgl;

			float ts = 0.0f;
			bool found = false;
			for (unsigned int i = 0; i < m_TextureSlots.size(); i++)
			{
				if (m_TextureSlots[i] == font.GetAtlas()->id)
				{
					ts = (float)(i + 1);
					found = true;
					break;
				}
			}
			if (!found)
			{
				if (m_TextureSlots.size() >= 32)
				{
					End();
					Flush();
					Begin();
				}
				m_TextureSlots.push_back(font.GetAtlas()->id);
				ts = (float)(m_TextureSlots.size());
			}

			float scaleX = 960.0f / 32.0f;
			float scaleY = 540.0f / 18.0f;

			float x = position.x;

			glBindTexture(GL_TEXTURE_2D, font.GetAtlas()->id);
			glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, font.GetAtlas()->width, font.GetAtlas()->height, GL_ALPHA, GL_UNSIGNED_BYTE, font.GetAtlas()->data);
			glBindTexture(GL_TEXTURE_2D, 0);
			
			ftgl::texture_font_t *ftfont = font.GetFont();
			for (unsigned int i = 0; i < strlen(text); ++i)
			{
				texture_glyph_t *glyph = texture_font_get_glyph(ftfont, text + i);
				if (glyph != NULL)
				{
					float kerning = 0.0f;
					if (i > 0)
					{
						kerning = texture_glyph_get_kerning(glyph, text + i - 1);
					}
					x += kerning / scaleX;

					float x0 = x + glyph->offset_x / scaleX;
					float y0 = position.y + glyph->offset_y / scaleY;
					float x1 = x0 + glyph->width / scaleX;
					float y1 = y0 - glyph->height / scaleY;

					float u0 = glyph->s0;
					float v0 = glyph->t0;
					float u1 = glyph->s1;
					float v1 = glyph->t1;

					m_buffer->vertex = *m_m_transformationback * glm::vec4(x0, y0, 0.0f ,1.0f);
					m_buffer->uv = glm::vec2(u0, v0);
					m_buffer->tid = ts;
					m_buffer->color = color;
					m_buffer++;

					m_buffer->vertex = *m_m_transformationback * glm::vec4(x0, y1, 0.0f, 1.0f);
					m_buffer->uv = glm::vec2(u0, v1);
					m_buffer->tid = ts;
					m_buffer->color = color;
					m_buffer++;

					m_buffer->vertex = *m_m_transformationback * glm::vec4(x1, y1, 0.0f, 1.0f);
					m_buffer->uv = glm::vec2(u1, v1);
					m_buffer->tid = ts;
					m_buffer->color = color;
					m_buffer++;

					m_buffer->vertex = *m_m_transformationback * glm::vec4(x1, y0, 0.0f, 1.0f);
					m_buffer->uv = glm::vec2(u1, v0);
					m_buffer->tid = ts;
					m_buffer->color = color;
					m_buffer++;

					m_indexcount += 6;

					x += glyph->advance_x / scaleX;
				}
				else
				{
					exit(1);
				}
			}
		}

		void BatchRenderer2D::End()
		{
			glUnmapBuffer(GL_ARRAY_BUFFER);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}

		void BatchRenderer2D::Flush()
		{
			for (unsigned int i = 0; i < m_TextureSlots.size(); i++)
			{
				glActiveTexture(GL_TEXTURE0 + i);
				glBindTexture(GL_TEXTURE_2D, m_TextureSlots[i]);
			}

			glBindVertexArray(m_VAO);
			m_IBO->Bind();
			glDrawElements(GL_TRIANGLES, m_indexcount, GL_UNSIGNED_INT, NULL);
			m_IBO->UnBind();
			glBindVertexArray(0);
			m_indexcount = 0;
		}
	}
}
