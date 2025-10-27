#pragma once

#include <cmath>
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

	#define SW_DEBUGBREAK() __debugbreak()
#else
	#error Swallow only for windows
#endif

#ifndef SW_ENABLE_ASSERTS
	#define SW_ENABLE_ASSERTS
#endif

#define BIT(x) (1 << x)

#define SW_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

#define SW_EXPAND_MACRO(x) x
#define SW_STRINGFY_MACRO(x) #x
#define SW_CHARACTERLIZE_MACRO(x) #@x

namespace Swallow {

	template<class T>
	using Scope = std::unique_ptr<T>;

	template<class T, class ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<class T>
	using Ref = std::shared_ptr<T>;

	template<class T, class ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	constexpr T epsilon = static_cast<T>(1e-6);

	template<class T1, class T2>
	bool IsEqual(T1 a, T2 b,
		std::common_type_t<T1, T2> eps =
		epsilon<std::common_type_t<T1, T2>>)
	{
		using CommonType = std::common_type_t<T1, T2>;
		return std::fabs(static_cast<CommonType>(a) - static_cast<CommonType>(b)) < eps;
	}

	//template<class T>
	//bool IsEqual(T a, T b, T eps = epsilon)
	//{
	//	return std::fabs(a - b) < eps;
	//}
	
}

#include "Swallow/Core/Log.h"
#include "Swallow/Core/Assert.h"