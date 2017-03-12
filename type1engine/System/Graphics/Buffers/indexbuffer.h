#pragma once
#include <GL/glew.h>

namespace Engine
{
	namespace Graphics
	{
		class IndexBuffer
		{
		private:
			GLuint m_bufferID;
			GLuint m_count;
		public:
			IndexBuffer(GLuint *data, GLsizei count);
			~IndexBuffer();

			void Bind() const;
			void UnBind() const;

			inline GLuint GetCount() const { return m_count; };
		};
	}
}