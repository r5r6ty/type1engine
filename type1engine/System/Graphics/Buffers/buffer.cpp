#include "buffer.h"

namespace Engine
{
	namespace Graphics
	{
		Buffer::Buffer(GLfloat *data, GLsizei count, GLuint cc)
		{
			m_componentcount = cc;
			glGenBuffers(1, &m_bufferID);
			glBindBuffer(GL_ARRAY_BUFFER, m_bufferID);
			glBufferData(GL_ARRAY_BUFFER, count * sizeof(GLfloat), data, GL_STATIC_DRAW);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}

		Buffer::~Buffer()
		{
			glDeleteBuffers(1, &m_bufferID);
		}

		void Buffer::Bind() const
		{
			glBindBuffer(GL_ARRAY_BUFFER, m_bufferID);
		}

		void Buffer::UnBind() const
		{
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}
	}
}