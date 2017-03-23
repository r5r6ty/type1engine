#pragma once
#include <map>
#include "font.h"

namespace Engine
{
	namespace Graphics
	{
		class FontManager
		{
		private:
			static std::map<unsigned int, Font*> m_Fonts;
		public:
			static void Add(Font *font);
			static Font *GetFont(const char *name, unsigned int size);
			static void ListFonts();
			static void Clean();
		private:
			FontManager();
		};
	}
}