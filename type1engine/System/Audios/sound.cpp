#include "sound.h"

namespace Engine
{
	namespace Audios
	{
		// 播完由音频库回调：只置 DESTROYED 状态，内存随后在 gau_manager_update 的 dispatch 里释放。
		// 不能在这里碰 m_Handles（vector 只归主线程），也别往调用方的栈上写东西。
		void destroyOnFinish(ga_Handle *in_handle, void *in_context)
		{
			(void)in_context;
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
			for (unsigned int i = 0; i < m_Handles.size(); i++)
			{
				if (m_Handles[i].s_handle != NULL)
				{
					ga_handle_destroy(m_Handles[i].s_handle);
				}
			}
			m_Handles.clear();

			ga_sound_release(m_Sound);
		}

		void Sound::Inst()
		{
			SoundObject sdob;
			sdob.loopSrc = 0;
			sdob.s_handle = gau_create_handle_sound(SoundManager::m_Mixer, m_Sound, &destroyOnFinish, NULL, &sdob.loopSrc);
			sdob.s_Position = 0;
			m_Handles.push_back(sdob);

			m_Loop ? gau_sample_source_loop_set(sdob.loopSrc, -1, 0) : gau_sample_source_loop_clear(sdob.loopSrc);
			Play();
		}

		void Sound::Play()
		{
			for (unsigned int i = 0; i < m_Handles.size(); i++)
			{
				if (m_Handles[i].s_handle->state != 2) // GA_HANDLE_STATE_PLAYING
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

		// ga_handle_destroy 只是标记 DESTROYED，内存要等 dispatch 线程 ACK 后才释放；
		// 但 Play()/DeleteFinishedHandle 之后还会解引用句柄，所以这里必须把条目一并清掉。
		void Sound::Stop()
		{
			for (unsigned int i = 0; i < m_Handles.size(); i++)
			{
				ga_handle_destroy(m_Handles[i].s_handle);
			}
			m_Handles.clear();
		}

		void Sound::DeleteFinishedHandle()
		{
			// 句柄状态到 FINISHED/DESTROYED 后，释放由 gau_manager_update 的 dispatch 兜底，这里只移除条目。
			std::vector<SoundObject>::iterator iter = m_Handles.begin();
			for (; iter != m_Handles.end();)
			{
				if (iter->s_handle == NULL || iter->s_handle->finished != 0 ||
					iter->s_handle->state == 4 || iter->s_handle->state == 5) // FINISHED / DESTROYED
				{
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
