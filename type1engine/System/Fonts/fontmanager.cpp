#include "fontmanager.h"
#include <string.h>

namespace Engine
{
	namespace Fonts
	{
		std::map<unsigned int, Font*> FontManager::m_Fonts;

		void FontManager::Add(Font *font)
		{
			m_Fonts.insert(std::pair<unsigned int, Font*>(m_Fonts.size(), font));
		}

		Font *FontManager::GetFont(const char *name, unsigned int size)
		{
			// name 是 const char*，必须按内容比较（== 比的是指针）
			std::map<unsigned int, Font*>::iterator iter;
			for (iter = m_Fonts.begin(); iter != m_Fonts.end(); ++iter)
			{
				if (strcmp(name, iter->second->GetName()) == 0 && size == iter->second->GetSize())
				{
					return iter->second;
				}
			}
			std::cout << "Cannot find font -> Name: " << name << " Size: " << size << std::endl;
			ListFonts();
			exit(1);
		}

		void FontManager::ListFonts()
		{
			std::map<unsigned int, Font*>::iterator iter;
			std::cout << "List fonts(" << m_Fonts.size() << "):" << std::endl;
			for (iter = m_Fonts.begin(); iter != m_Fonts.end(); ++iter)
			{
				std::cout << "No." << iter->first << " Name: " << iter->second->GetName() << " Size: " << iter->second->GetSize() << " FilePath: " << iter->second->GetFilePath() << std::endl;
			}
		}

		void FontManager::Clean()
		{
			std::map<unsigned int, Font*>::iterator iter;
			for (iter = m_Fonts.begin(); iter != m_Fonts.end();)
			{
				delete iter->second;
				iter->second = NULL;
				m_Fonts.erase(iter++);
			}
		}
	}
}