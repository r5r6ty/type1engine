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
			glEnableVertexAttribArray(SHADER_COLOR_INDEX);
			glVertexAttribPointer(SHADER_COLOR_INDEX, 4, GL_BYTE, GL_TRUE, RENDERER_VERTEX_SIZE, (const void*)(offsetof(VertexData, VertexData::color)));
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

		void BatchRenderer2D::Submit(const Renderable2D *renderable2D)
		{
			const glm::vec3 &position = renderable2D->GetPosition();
			const glm::vec2 &size = renderable2D->GetSize();
			const glm::vec4 &color = renderable2D->GetColor();

			int r = (int)(color.x * 255.0f);
			int g = (int)(color.y * 255.0f);
			int b = (int)(color.z * 255.0f);
			int a = (int)(color.w * 255.0f);

			unsigned int c = a << 24 | b << 16 | g << 8 | r;

			m_buffer->vertex = *m_m_transformationback * glm::vec4(position, 1.0f);
			m_buffer->color = c;
			m_buffer++;

			m_buffer->vertex = *m_m_transformationback * glm::vec4(position.x, position.y + size.y, position.z ,1.0f);
			m_buffer->color = c;
			m_buffer++;

			m_buffer->vertex = *m_m_transformationback * glm::vec4(position.x + size.x, position.y + size.y, position.z, 1.0f);
			m_buffer->color = c;
			m_buffer++;

			m_buffer->vertex = *m_m_transformationback * glm::vec4(position.x + size.x, position.y, position.z, 1.0f);
			m_buffer->color = c;
			m_buffer++;

			m_indexcount += 6;
		}

		void BatchRenderer2D::End()
		{
			glUnmapBuffer(GL_ARRAY_BUFFER);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}

		void BatchRenderer2D::Flush()
		{
			glBindVertexArray(m_VAO);
			m_IBO->Bind();
			glDrawElements(GL_TRIANGLES, m_indexcount, GL_UNSIGNED_INT, NULL);
			m_IBO->UnBind();
			glBindVertexArray(0);
			m_indexcount = 0;
		}
	}
}