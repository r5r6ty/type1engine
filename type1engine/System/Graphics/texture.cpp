#include "texture.h""
#include <iostream>

namespace Engine
{
	namespace Graphics
	{
		Texture::Texture(const char *path)
			: m_path(path)
		{
			m_TID = Load();
		}

		Texture::~Texture()
		{
		}

		void Texture::Bind() const
		{
			glBindTexture(GL_TEXTURE_2D, m_TID);
		}

		void Texture::UnBind() const
		{
			glBindTexture(GL_TEXTURE_2D, 0);
		}

		GLuint Texture::Load()
		{
			BYTE *pixels = LoadImage(m_path, &m_width, &m_height);

			GLuint result;
			glGenBuffers(1, &result);
			glBindTexture(GL_TEXTURE_2D, result);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, GL_BGR, GL_UNSIGNED_BYTE, pixels);
			glBindTexture(GL_TEXTURE_2D, 0);

			return result;
		}
	}
}