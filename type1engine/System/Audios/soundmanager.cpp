#include "soundmanager.h"
#include <string.h>

namespace Engine
{
	namespace Audios
	{
		gau_Manager *SoundManager::m_Manager = nullptr;
		ga_Mixer *SoundManager::m_Mixer = nullptr;
		std::map<unsigned int, Sound*> SoundManager::m_Sounds;

		void SoundManager::init()
		{
			gc_initialize(0);
			m_Manager = gau_manager_create();
			m_Mixer = gau_manager_mixer(m_Manager);
		}

		void SoundManager::Add(Sound *sound)
		{
			m_Sounds.insert(std::pair<unsigned int, Sound*>(m_Sounds.size(), sound));
		}

		Sound *SoundManager::GetSound(const char *name, const char *type)
		{
			// name 是 const char*，必须按内容比较（== 比的是指针）
			for (std::map<unsigned int, Sound*>::iterator iter = m_Sounds.begin(); iter != m_Sounds.end(); ++iter)
			{
				if (strcmp(name, iter->second->GetName()) == 0 && type == iter->second->GetType())
				{
					return iter->second;
				}
			}
			std::cout << "Cannot find sound -> Name: " << name << " Type: " << type << std::endl;
			ListSounds();
			exit(1);
		}

		void SoundManager::DeleteSound(const char * name, const char * type)
		{
			for (std::map<unsigned int, Sound*>::iterator iter = m_Sounds.begin(); iter != m_Sounds.end();)
			{
				if (strcmp(name, iter->second->GetName()) == 0 && type == iter->second->GetType())
				{
					delete iter->second;
					m_Sounds.erase(iter++);
				}
				else
				{
					++iter;
				}
			}
		}

		void SoundManager::Update()
		{
			// 删除后键会有空洞，不能用 m_Sounds[i] 取（operator[] 会插 nullptr）
			for (std::map<unsigned int, Sound*>::iterator iter = m_Sounds.begin(); iter != m_Sounds.end(); ++iter)
			{
				iter->second->DeleteFinishedHandle();
			}

			gau_manager_update(m_Manager);
			//gc_thread_sleep(1);
		}

		void SoundManager::ListSounds()
		{
			std::cout << "List sounds(" << m_Sounds.size() << "):" << std::endl;
			for (std::map<unsigned int, Sound*>::iterator iter = m_Sounds.begin(); iter != m_Sounds.end(); ++iter)
			{
				std::cout << "No." << iter->first << " Name: " << iter->second->GetName() << " Type: " << iter->second->GetType() << " FilePath: " << iter->second->GetFilePath() << std::endl;
			}
		}

		void SoundManager::Clean()
		{
			for (std::map<unsigned int, Sound*>::iterator iter = m_Sounds.begin(); iter != m_Sounds.end(); ++iter)
			{
				delete iter->second;
			}
			m_Sounds.clear();

			gau_manager_destroy(m_Manager);
			gc_shutdown();
		}
	}
}
