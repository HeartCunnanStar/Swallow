#pragma once

#include <memory>

#include "Core.h"
#include "spdlog/spdlog.h"

namespace Swallow {

	class SWALLOW_API Log
	{
	public:
		Log() = default;
		~Log() = default;

		static void Init();

		inline static std::shared_ptr <spdlog::logger>& GetCoreLogger() { return spd_CoreLogger; }
		inline static std::shared_ptr <spdlog::logger>& GetClinetLogger() { return spd_ClientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_core_logger;
		static std::shared_ptr<spdlog::logger> s_client_logger;
	};

}

// core log marcos
#define SW_CORE_ERROR(...) ::Swallow::Log::GetCoreLogger()->error(__VA_ARGS__);
#define SW_CORE_WARN(...)  ::Swallow::Log::GetCoreLogger()->warn(__VA_ARGS__);
#define SW_CORE_INFO(...)  ::Swallow::Log::GetCoreLogger()->info(__VA_ARGS__);
#define SW_CORE_TRACE(...) ::Swallow::Log::GetCoreLogger()->trace(__VA_ARGS__);
#define SW_CORE_FATAL(...) ::Swallow::Log::GetCoreLogger()->fatal(__VA_ARGS__);

// client log marcos
#define SW_ERROR(...)	   ::Swallow::Log::GetClientLogger()->error(__VA_ARGS__);
#define SW_WARN(...)	   ::Swallow::Log::GetClientLogger()->warn(__VA_ARGS__);
#define SW_INFO(...)	   ::Swallow::Log::GetClientLogger()->info(__VA_ARGS__);
#define SW_TRACE(...)	   ::Swallow::Log::GetClientLogger()->trace(__VA_ARGS__);
#define SW_FATAL(...)	   ::Swallow::Log::GetClientLogger()->fatal(__VA_ARGS__);
