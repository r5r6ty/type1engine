#include "batchrenderer2D.h"

namespace Engine
{
	char *localeToUTF8(char *src)
	{
		static char *buf = NULL;
		if (buf)
		{
			free(buf);
			buf = NULL;
		}
		wchar_t *unicode_buf;
		int nRetLen = MultiByteToWideChar(CP_ACP, 0, src, -1, NULL, 0);
		unicode_buf = (wchar_t*)malloc((nRetLen + 1) * sizeof(wchar_t));
		MultiByteToWideChar(CP_ACP, 0, src, -1, unicode_buf, nRetLen);
		nRetLen = WideCharToMultiByte(CP_UTF8, 0, unicode_buf, -1, NULL, 0, NULL, NULL);
		buf = (char*)malloc(nRetLen + 1);
		WideCharToMultiByte(CP_UTF8, 0, unicode_buf, -1, buf, nRetLen, NULL, NULL);
		free(unicode_buf);
		return buf;
	}

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

			m_FTAtlas = ftgl::texture_atlas_new(512, 512, 1);
			m_FTFont = ftgl::texture_font_new_from_file(m_FTAtlas, 40, "Î¢ÈíÑÅºÚ.ttf");

			ftgl::texture_font_load_glyph(m_FTFont, "");
			glGenTextures(1, &m_FTAtlas->id);
			glBindTexture(GL_TEXTURE_2D, m_FTAtlas->id);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA, m_FTAtlas->width, m_FTAtlas->height,
				0, GL_ALPHA, GL_UNSIGNED_BYTE, m_FTAtlas->data);
			glBindTexture(GL_TEXTURE_2D, 0);
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
			const glm::vec4 &color = renderable->GetColor();
			const std::vector<glm::vec2> &uv = renderable->GetUV();
			const GLuint tid = renderable->GetTID();

			unsigned int c = 0;

			float ts = 0.0f;
			if (tid > 0)
			{
				bool found = false;
				for (int i = 0; i < m_TextureSlots.size(); i++)
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
				int r = int(color.x * 255.0f);
				int g = int(color.y * 255.0f);
				int b = int(color.z * 255.0f);
				int a = int(color.w * 255.0f);

				c = a << 24 | b << 16 | g << 8 | r;
			}

			m_buffer->vertex = *m_m_transformationback * glm::vec4(position, 1.0f);
			m_buffer->uv = uv[0];
			m_buffer->tid = ts;
			m_buffer->color = c;
			m_buffer++;

			m_buffer->vertex = *m_m_transformationback * glm::vec4(position.x, position.y + size.y, position.z ,1.0f);
			m_buffer->uv = uv[1];
			m_buffer->tid = ts;
			m_buffer->color = c;
			m_buffer++;

			m_buffer->vertex = *m_m_transformationback * glm::vec4(position.x + size.x, position.y + size.y, position.z, 1.0f);
			m_buffer->uv = uv[2];
			m_buffer->tid = ts;
			m_buffer->color = c;
			m_buffer++;

			m_buffer->vertex = *m_m_transformationback * glm::vec4(position.x + size.x, position.y, position.z, 1.0f);
			m_buffer->uv = uv[3];
			m_buffer->tid = ts;
			m_buffer->color = c;
			m_buffer++;

			m_indexcount += 6;
		}

		void BatchRenderer2D::ChangeText(const char *text)
		{

			ftgl::texture_font_load_glyph(m_FTFont, text);
			glBindTexture(GL_TEXTURE_2D, m_FTAtlas->id);
			glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, m_FTAtlas->width, m_FTAtlas->height, GL_ALPHA, GL_UNSIGNED_BYTE, m_FTAtlas->data);
			glBindTexture(GL_TEXTURE_2D, 0);

		}

		void BatchRenderer2D::DrawString(const char *text, const glm::vec3 &position, const glm::vec4 &color)
		{
			using namespace ftgl;

			int r = int(color.x * 255.0f);
			int g = int(color.y * 255.0f);
			int b = int(color.z * 255.0f);
			int a = int(color.w * 255.0f);

			unsigned int c = a << 24 | b << 16 | g << 8 | r;

			float ts = 0.0f;
			bool found = false;
			for (int i = 0; i < m_TextureSlots.size(); i++)
			{
				if (m_TextureSlots[i] == m_FTAtlas->id)
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
				m_TextureSlots.push_back(m_FTAtlas->id);
				ts = (float)(m_TextureSlots.size());
			}

			float scaleX = 960.0f / 32.0f;
			float scaleY = 540.0f / 18.0f;

			float x = position.x;
			
			for (int i = 0; i < strlen(text); ++i)
			{
				texture_glyph_t *glyph = texture_font_get_glyph(m_FTFont, text + i);
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
					m_buffer->color = c;
					m_buffer++;

					m_buffer->vertex = *m_m_transformationback * glm::vec4(x0, y1, 0.0f, 1.0f);
					m_buffer->uv = glm::vec2(u0, v1);
					m_buffer->tid = ts;
					m_buffer->color = c;
					m_buffer++;

					m_buffer->vertex = *m_m_transformationback * glm::vec4(x1, y1, 0.0f, 1.0f);
					m_buffer->uv = glm::vec2(u1, v1);
					m_buffer->tid = ts;
					m_buffer->color = c;
					m_buffer++;

					m_buffer->vertex = *m_m_transformationback * glm::vec4(x1, y0, 0.0f, 1.0f);
					m_buffer->uv = glm::vec2(u1, v0);
					m_buffer->tid = ts;
					m_buffer->color = c;
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
			for (int i = 0; i < m_TextureSlots.size(); i++)
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
