#include "vertexarray.h"

namespace Engine
{
	namespace Graphics
	{
		VertexArray::VertexArray()
		{
			glGenVertexArrays(1, &m_arrayID);
		}

		VertexArray::~VertexArray()
		{
			for (unsigned int i = 0; i < m_buffers.size(); i++)
			{
				delete m_buffers[i];
			}
			glDeleteVertexArrays(1, &m_arrayID);
		}

		void VertexArray::AddBuffer(Buffer *buffer, GLuint index)
		{
			Bind();
			buffer->Bind();
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index, buffer->GetComponentCount(), GL_FLOAT, GL_FALSE, 0, 0);
			buffer->UnBind();
			UnBind();
		}
		void VertexArray::Bind() const
		{
			glBindVertexArray(m_arrayID);
		}
		void VertexArray::UnBind() const
		{
			glBindVertexArray(0);
		}
	}
}