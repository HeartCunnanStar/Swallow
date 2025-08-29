#pragma once

#include <memory>

#ifdef SW_PLATFORMS_WINDOWS
	#ifdef SW_DYNAMIC_LINK
		#if defined(SW_BUILD_DLL)
			#define SWALLOW_API __declspec(dllexport)
		#else
			#define SWALLOW_API __declspec(dllimport)
		#endif
	#else 
		#define SWALLOW_API
	#endif
#else
	#error Swallow only for windows
#endif

#ifndef SW_ENABLE_ASSERTS
	#define SW_ENABLE_ASSERTS
#endif

// notice that in define sentences : there shouldn't be any space after "\" 

#ifdef SW_ENABLE_ASSERTS
#define SW_ASSERT(x, ...) do {							    \
		if(!(x)) {											\
			SW_ERROR("Assertion Failed: {0}", __VA_ARGS__); \
			__debugbreak();									\
		}													\
	} while (0)
#define SW_CORE_ASSERT(x, ...) do {					        \
		if(!(x)) {											\
			SW_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); \
			__debugbreak();									\
		}													\
	} while (0)
#else
#define SW_ASSERT(x, ...)
#define SW_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define SW_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

namespace Swallow {

	template<class T>
	using Scope = std::unique_ptr<T>;

	template<typename T>
	using Ref = std::shared_ptr<T>;

}
