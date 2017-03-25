#pragma once
#include <iostream>
#define NOT_USING_FT_GL_NAMESPACE
#include <freetype-gl.h>

namespace Engine
{
	namespace Fonts
	{
		class Font
		{
		private:
			const char *m_Name;
			const char *m_FilePath;
			ftgl::texture_atlas_t *m_FTAtlas;
			ftgl::texture_font_t *m_FTFont;
			unsigned int m_Size;
		public:
			Font(const char *name, const char *file, unsigned int size);
			~Font();

			inline const ftgl::texture_atlas_t *GetAtlas() const { return m_FTAtlas; }
			inline ftgl::texture_font_t *GetFont() const { return m_FTFont; }
			inline const char *GetName() const { return m_Name; }
			inline const char *GetFilePath() const { return m_FilePath; }
			inline const unsigned int &GetSize() const { return m_Size; }
		};
	}
}