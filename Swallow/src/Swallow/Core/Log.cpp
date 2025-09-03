#include "swpch.h"
#include "Log.h"

#include "spdlog/sinks/stdout_color_sinks.h"

namespace Swallow{

	Ref<spdlog::logger> Log::s_core_logger = nullptr;
	Ref<spdlog::logger> Log::s_client_logger = nullptr;

	void Log::Init()
	{
		// %^ - begin color range %$ - end color range
		spdlog::set_pattern("%^[%T] %n: %v%$");

		//spdlog::set_pattern("*** [%H:%M:%S %z] [thread %t] %v ***");

		s_core_logger = spdlog::stdout_color_mt("SWALLOW");
		s_core_logger->set_level(spdlog::level::trace);

		s_client_logger = spdlog::stderr_color_mt("APP");
		s_client_logger->set_level(spdlog::level::trace);
	}

}