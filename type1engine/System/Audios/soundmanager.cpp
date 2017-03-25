#include "soundmanager.h"

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
			for (unsigned int i = 0; i < m_Sounds.size(); i++)
			{
				if (name == m_Sounds[i]->GetName() && type == m_Sounds[i]->GetType())
				{
					return m_Sounds[i];
				}
			}
			std::cout << "Cannot find sound -> Name: " << name << " Type: " << type << std::endl;
			ListSounds();
			exit(1);
		}

		void SoundManager::DeleteSound(const char * name, const char * type)
		{
			for (unsigned int i = 0; i < m_Sounds.size(); i++)
			{
				if (name == m_Sounds[i]->GetName() && type == m_Sounds[i]->GetType())
				{
					delete m_Sounds[i];
					m_Sounds.erase(i);
				}
			}
		}

		void SoundManager::Update()
		{
			for (unsigned int i = 0; i < m_Sounds.size(); i++)
			{
				m_Sounds[i]->DeleteFinishedHandle();
			}

			gau_manager_update(m_Manager);
			//gc_thread_sleep(1);
		}

		void SoundManager::ListSounds()
		{
			std::cout << "List sounds(" << m_Sounds.size() << "):" << std::endl;
			for (unsigned int i = 0; i < m_Sounds.size(); i++)
			{
				std::cout << "No." << i << " Name: " << m_Sounds[i]->GetName() << " Type: " << m_Sounds[i]->GetType() << " FilePath: " << m_Sounds[i]->GetFilePath() << std::endl;
			}
		}

		void SoundManager::Clean()
		{
			for (unsigned int i = 0; i < m_Sounds.size(); i++)//delete object
			{
				delete m_Sounds[i];
				m_Sounds.erase(i);
			}

			gau_manager_destroy(m_Manager);
			gc_shutdown();
		}
	}
}