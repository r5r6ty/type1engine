#pragma once
#if 0
#include <Windows.h>

namespace Engine
{
	class Timer
	{

	private:
		LARGE_INTEGER m_start;
		double m_frequency;
	public:
		Timer()
		{
			LARGE_INTEGER frequency;
			QueryPerformanceFrequency(&frequency);
			m_frequency = 1.0 / frequency.QuadPart;
			QueryPerformanceCounter(&m_start);
		}

		void Reset()
		{
			QueryPerformanceCounter(&m_start);
		}

		float Elapsed()
		{
			LARGE_INTEGER current;
			QueryPerformanceCounter(&current);
			unsigned __int64 cycles = current.QuadPart - m_start.QuadPart;
			return (float)(cycles * m_frequency);
		}

	};
}
#else
#include <chrono>

namespace Engine
{
	class Timer
	{
	private:
		typedef std::chrono::high_resolution_clock hrClock;
		typedef std::chrono::duration<float, std::milli> milliseconds_type;
		std::chrono::time_point<hrClock> m_Start;
	public:
		Timer()
		{
			Reset();
		}

		void Reset()
		{
			m_Start = hrClock::now();
		}

		float Elapsed()
		{
			return std::chrono::duration_cast<milliseconds_type>(hrClock::now() - m_Start).count() / 1000;
		}
	};
}
#endif