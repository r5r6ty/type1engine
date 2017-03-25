#pragma once
#include <iostream>
#include <gorilla\gau.h>
#include <algorithm> 
#include "soundmanager.h"
#include "../Utils/fileutils.h"

namespace Engine
{
	namespace Audios
	{
		struct SoundObject
		{
			ga_Handle* s_handle;
			unsigned int s_Position;
			gau_SampleSourceLoop* loopSrc;
		};

		class Sound
		{
		private:
			const char *m_Name;
			const char *m_FilePath;
			std::string m_Type;

			bool m_Loop;
			//unsigned int m_Position;
			ga_Sound *m_Sound;
			std::vector<SoundObject> m_Handles;
		public:
			Sound(const char *name, const char *file);
			~Sound();

			void Inst();
			void Play();
			void SetLoop(bool l);
			void Pause();
			void Stop();
			void DeleteFinishedHandle();

			inline const char *GetName() const { return m_Name; }
			inline const char *GetFilePath() const { return m_FilePath; }
			inline const std::string &GetType() const { return m_Type; }
;
			inline const std::vector<SoundObject> &GetHandles() const { return m_Handles; }

			inline const bool &GetLoopSet() const { return m_Loop; }

			friend void setFlagAndLoopOnFinish(ga_Handle *in_handle, void *in_context);
		};
	}
}