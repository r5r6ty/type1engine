#include "fontmanager.h"

namespace Engine
{
	namespace Graphics
	{
		std::map<unsigned int, Font*> FontManager::m_Fonts;

		void FontManager::Add(Font *font)
		{
			m_Fonts.insert(std::pair<unsigned int, Font*>(m_Fonts.size(), font));
		}

		Font *FontManager::GetFont(const char *name, unsigned int size)
		{
			std::map<unsigned int, Font*>::iterator font_iter;
			for (font_iter = m_Fonts.begin(); font_iter != m_Fonts.end(); ++font_iter)
			{
				if (name == font_iter->second->GetName() && size == font_iter->second->GetSize())
				{
					return m_Fonts[font_iter->first];
				}
			}
			std::cout << "Cannot find font -> Name: " << name << " Size: " << size << std::endl;
			ListFonts();
			exit(1);
		}

		void FontManager::ListFonts()
		{
			std::map<unsigned int, Font*>::iterator font_iter;
			std::cout << "List fonts(" << m_Fonts.size() << "):" << std::endl;
			for (font_iter = m_Fonts.begin(); font_iter != m_Fonts.end(); ++font_iter)
			{
				std::cout << "No." << font_iter->first << " Name: " << font_iter->second->GetName() << " Size: " << font_iter->second->GetSize() << " FilePath: " << font_iter->second->GetFilePath() << std::endl;
			}
		}

		void FontManager::Clean()
		{
			std::map<unsigned int, Font*>::iterator font_iter;
			for (font_iter = m_Fonts.begin(); font_iter != m_Fonts.end(); ++font_iter)
			{
				m_Fonts.erase(font_iter->first);
			}
		}
	}
}