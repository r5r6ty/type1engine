#include "font.h"

namespace Engine
{
	namespace Fonts
	{
		Font::Font(const char *name, const char *file, unsigned int size)
			: m_Name(name), m_FilePath(file), m_Size(size)
		{
			m_FTAtlas = ftgl::texture_atlas_new(512, 512, 1);
			m_FTFont = ftgl::texture_font_new_from_file(m_FTAtlas, m_Size, m_FilePath);
			if (m_FTFont != NULL)
			{
				printf("Opened: %s\n", m_FilePath);
			}
			else
			{
				printf("Could not open: %s\n", m_FilePath);
				exit(1);
			}
			glGenTextures(1, &m_FTAtlas->id);
			glBindTexture(GL_TEXTURE_2D, m_FTAtlas->id);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA, m_FTAtlas->width, m_FTAtlas->height,
				0, GL_ALPHA, GL_UNSIGNED_BYTE, m_FTAtlas->data);
			glBindTexture(GL_TEXTURE_2D, 0);
		}

		Font::~Font()
		{
			glDeleteTextures(1, &m_FTAtlas->id);
			m_FTAtlas->id = 0;
			ftgl::texture_atlas_delete(m_FTAtlas);
			ftgl::texture_font_delete(m_FTFont);
		}
	}
}