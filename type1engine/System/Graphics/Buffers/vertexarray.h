#pragma once
#include <vector>
#include <GL/glew.h>
#include "buffer.h"

namespace Engine
{
	namespace Graphics
	{
		class VertexArray
		{
		private:
			GLuint m_arrayID;
			std::vector<Buffer*> m_buffers;
		public:
			VertexArray();
			~VertexArray();

			void AddBuffer(Buffer *buffer, GLuint index);
			void Bind() const;
			void UnBind() const;
		};
	}
}