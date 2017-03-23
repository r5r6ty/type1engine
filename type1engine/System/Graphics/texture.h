#pragma once
#include <GL/glew.h>
#include "../Utils/image_load.h"

namespace Engine
{
	namespace Graphics
	{
		class Texture
		{
		private:
			const char *m_path;
			GLuint m_TID;
			GLsizei m_width, m_height;
		public:
			Texture(const char *path);
			~Texture();
			void Bind() const;
			void UnBind() const;

			inline const GLuint GetTID() const { return m_TID; };
			inline const unsigned int GetWidth() const { return m_width; };
			inline const unsigned int GetHeight() const { return m_height; };
		private:
			GLuint Load();
		};
	}
}