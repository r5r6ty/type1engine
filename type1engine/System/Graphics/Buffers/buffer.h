#pragma once
#include <GL/glew.h>

namespace Engine
{
	namespace Graphics
	{
		class Buffer
		{
		private:
			GLuint m_bufferID;
			GLuint m_componentcount;
		public:
			Buffer(GLfloat *data, GLsizei count, GLuint cc);
			~Buffer();
			void Bind() const;
			void UnBind() const;
			inline GLuint GetComponentCount() const { return m_componentcount; };
		};
	}
}