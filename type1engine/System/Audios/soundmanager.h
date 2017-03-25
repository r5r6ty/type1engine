#pragma once
#include <map>
//#define GAU_THREAD_POLICY_MULTI 2
#include "sound.h"

namespace Engine
{
	namespace Audios
	{
		class SoundManager
		{
		private:
			friend class Sound;

			static gau_Manager *m_Manager;
			static ga_Mixer *m_Mixer;

			static std::map<unsigned int, Sound*> m_Sounds;
		public:
			static void init();
			static void Add(Sound *sound);
			static Sound *GetSound(const char *name, const char *type);
			static void DeleteSound(const char *name, const char *type);
			static void Update();
			static void ListSounds();
			static void Clean();

			static inline std::map<unsigned int, Sound*> &GetSoundManagerSounds() { return m_Sounds; }
		private:
			SoundManager();
		};
	}
}