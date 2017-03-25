#include "sound.h"

namespace Engine
{
	namespace Audios
	{
		void setFlagAndDestroyOnFinish(ga_Handle *in_handle, void *in_context)
		{
			gc_int32 *flag = (gc_int32*)(in_context);
			*flag = 1;
			ga_handle_destroy(in_handle);
		}

		void setFlagAndLoopOnFinish(ga_Handle *in_handle, void *in_context)
		{
			gc_int32 *flag = (gc_int32*)(in_context);
			*flag = 1;
			ga_handle_destroy(in_handle);
		}

		Sound::Sound(const char *name, const char * file)
			: m_Name(name), m_FilePath(file), m_Type(GetFileExtension(file)), m_Loop(false)
		{

			m_Sound = gau_load_sound_file(m_FilePath, m_Type.c_str());
			if (m_Sound != NULL)
			{
				printf("Opened: %s\n", m_FilePath);
			}
			else
			{
				printf("Could not open: %s\n", m_FilePath);
				exit(1);
			}
		}

		Sound::~Sound()
		{
			std::vector<SoundObject>::iterator iter = m_Handles.begin();
			for (; iter != m_Handles.end();)
			{
				if (iter->s_handle != NULL)
				{
					ga_handle_destroy(iter->s_handle);
				}
				iter = m_Handles.erase(iter);
			}
			std::vector <SoundObject>().swap(m_Handles);

			ga_sound_release(m_Sound);
		}

		void Sound::Inst()
		{
			gc_int32 quit = 0;
			SoundObject sdob;
			sdob.loopSrc = 0;
			//gau_SampleSourceLoop** p = &sdob.loopSrc;
			sdob.s_handle = gau_create_handle_sound(SoundManager::m_Mixer, m_Sound, &setFlagAndDestroyOnFinish, &quit, &sdob.loopSrc);
			sdob.s_Position = 0;
			m_Handles.push_back(sdob);

			m_Loop ? gau_sample_source_loop_set(sdob.loopSrc, -1, 0) : gau_sample_source_loop_clear(sdob.loopSrc);
			Play();
		}

		void Sound::Play()
		{
			for (unsigned int i = 0; i < m_Handles.size(); i++)
			{
				if (m_Handles[i].s_handle->state != 2)
				{
					ga_handle_play(m_Handles[i].s_handle);
					ga_handle_seek(m_Handles[i].s_handle, m_Handles[i].s_Position);
				}
			}
		}

		void Sound::SetLoop(bool l)
		{
			if (m_Loop != l)
			{
				m_Loop = l;
				for (unsigned int i = 0; i < m_Handles.size(); i++)
				{
						m_Loop ? gau_sample_source_loop_set(m_Handles[i].loopSrc, -1, 0) : gau_sample_source_loop_clear(m_Handles[i].loopSrc);
				}
			}
		}

		void Sound::Pause()
		{
			for (unsigned int i = 0; i < m_Handles.size(); i++)
			{
				ga_handle_stop(m_Handles[i].s_handle);
				m_Handles[i].s_Position = ga_handle_tell(m_Handles[i].s_handle, GA_TELL_PARAM_CURRENT);
			}
		}

		void Sound::Stop()
		{
			for (unsigned int i = 0; i < m_Handles.size(); i++)
			{
				ga_handle_destroy(m_Handles[i].s_handle);
				m_Handles[i].s_Position = 0;
			}
		}

		void Sound::DeleteFinishedHandle()
		{
			std::vector<SoundObject>::iterator iter = m_Handles.begin();
			for (; iter != m_Handles.end();)
			{
				if (iter->s_handle->finished != 0 || iter->s_handle->state == 4 || iter->s_handle->state == 5)
				{
					if (iter->s_handle != NULL)
					{
						ga_handle_destroy(iter->s_handle);
					}
					iter = m_Handles.erase(iter);
				}
				else
				{
					iter++;
				}
			}
		}
	}
}