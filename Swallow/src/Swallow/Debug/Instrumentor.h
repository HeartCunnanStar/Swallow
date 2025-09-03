#pragma once

#include "Swallow/Core/Log.h"

#include <string>
#include <chrono>
#include <algorithm>
#include <fstream>
#include <thread>

namespace Swallow
{
	struct PerformanceData
	{
		std::string name;
		long long start, end;
		uint32_t threadID;
	};

	struct InstrumentationSession
	{
		InstrumentationSession(const std::string& name) : name(name) {}
		std::string name;
	};

	class Instrumentor
	{
	public:
		Instrumentor() = default;

		void BeginSession(const std::string& name, const std::string& path)
		{
			m_os.open(path);
			if (!m_os.is_open())
			{
				SW_CORE_ERROR("cannot open the file: '{0}'", path);
				return;
			}
			WriteHeader();
			m_current_session = new InstrumentationSession(name);
		}

		void EndSession()
		{
			WriteFooter();
			m_os.close();
			delete m_current_session;
			m_current_session = nullptr;
			m_profile_count = 0;
		}

		void WriteProfile(const PerformanceData& data)
		{
			if (m_profile_count++ > 0)
				m_os << ',';

			std::string name = data.name;
			std::replace(name.begin(), name.end(), '"', '\'');

			m_os << "{";
			m_os << "\"cat\":\"function\",";
			m_os << "\"dur\":" << (data.end - data.start) << ',';
			m_os << "\"name\":\"" << name << "\",";
			m_os << "\"ph\":\"X\",";
			m_os << "\"pid\":0,";
			m_os << "\"tid\":" << data.threadID << ',';
			m_os << "\"ts\":" << data.start;
			m_os << "}";

			m_os.flush();
		}

		void WriteHeader()
		{
			m_os << "{\"otherData\": {},\"traceEvents\":[";
			m_os.flush();
		}

		void WriteFooter()
		{
			m_os << "]}";
			m_os.flush();
		}

		static Instrumentor& GetIns()
		{
			static Instrumentor* s_instance = new Instrumentor();
			return *s_instance;
		}

	private:
		InstrumentationSession* m_current_session = nullptr;
		std::ofstream m_os;
		int m_profile_count = 0;
	};

	class InstrumentationTimer
	{
	public:
		InstrumentationTimer(const char* name)
			: m_name(name), m_is_stopped(false)
		{
			m_start_timepoint = std::chrono::high_resolution_clock::now();
		}

		~InstrumentationTimer()
		{
			if (!m_is_stopped)
				Stop();
		}
		void Stop()
		{
			auto end_timepoint = std::chrono::high_resolution_clock::now();

			long long start = std::chrono::time_point_cast<std::chrono::microseconds>(m_start_timepoint).time_since_epoch().count();
			long long end = std::chrono::time_point_cast<std::chrono::microseconds>(end_timepoint).time_since_epoch().count();

			uint32_t threadID = std::hash<std::thread::id>{}(std::this_thread::get_id());
			Instrumentor::GetIns().WriteProfile({ m_name, start, end, threadID });

			m_is_stopped = true;
		}

	private:
		const char* m_name;
		std::chrono::time_point<std::chrono::steady_clock> m_start_timepoint;
		bool m_is_stopped;
	};
}

#define SW_PROFILE 1

#ifdef SW_PROFILE
#define SW_PROFILE_BEGIN_SESSION(name, path)	::Swallow::Instrumentor::GetIns().BeginSession(name, path)
#define SW_PROFILE_END_SESSION()				::Swallow::Instrumentor::GetIns().EndSession()
#define SW_PROFILE_SCOPE(name)					::Swallow::InstrumentationTimer timer##__LINE__(name)
#define SW_PROFILE_FUNCTION()					SW_PROFILE_SCOPE(__FUNCSIG__)
#else
#define SW_PROFILE_BEGIN_SESSION(name, path)
#define SW_PROFILE_END_SESSION()
#define SW_PROFILE_SCOPE(name)
#define SW_PROFILE_FUNCTION()
#endif