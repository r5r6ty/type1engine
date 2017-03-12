#include "indexbuffer.h"

namespace Engine
{
	namespace Graphics
	{
		IndexBuffer::IndexBuffer(GLuint *data, GLsizei count)
		{
			m_count = count;
			glGenBuffers(1, &m_bufferID);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_bufferID);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLuint), data, GL_STATIC_DRAW);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		}

		IndexBuffer::~IndexBuffer()
		{
			glDeleteBuffers(1, &m_bufferID);
		}

		void IndexBuffer::Bind() const
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_bufferID);
		}

		void IndexBuffer::UnBind() const
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		}
	}
}