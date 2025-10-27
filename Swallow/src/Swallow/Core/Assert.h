#pragma once

#include "Swallow/Core/Core.h"
#include "Swallow/Core/Log.h"
#include <filesystem>

#ifdef SW_ENABLE_ASSERTS

    #define SW_INTERNAL_ASSERT_IMPL(type, check, msg, ...) do { \
        if(!(check)) {                                          \
            SW##type##ERROR(msg, __VA_ARGS__);                  \
            SW_DEBUGBREAK();                                    \
        }                                                       \
    } while(0)

    #define SW_INTERNAL_ASSERT_WITH_MSG(type, check, ...) \
        SW_INTERNAL_ASSERT_IMPL(type, check, "Assertion failed: {0}", __VA_ARGS__)

    #define SW_INTERNAL_ASSERT_NO_MSG(type, check) do { \
        auto assert_file = std::filesystem::path(__FILE__).filename().string(); \
        SW_INTERNAL_ASSERT_IMPL(type, check, "Assertion '{0}' failed at {1}:{2}", SW_STRINGFY_MACRO(check), assert_file, __LINE__); \
    } while(0)

    #define SW_INTERNAL_ASSERT_GET_MACRO(_1, _2, NAME, ...) NAME

    // depends on args' cnt to choose which one to use
    #define SW_INTERNAL_ASSERT_CHOOSER(...) \
        SW_EXPAND_MACRO(SW_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__, SW_INTERNAL_ASSERT_WITH_MSG, SW_INTERNAL_ASSERT_NO_MSG))

    #define SW_ASSERT(...) SW_EXPAND_MACRO( SW_INTERNAL_ASSERT_CHOOSER(__VA_ARGS__)(_, __VA_ARGS__) )
    #define SW_CORE_ASSERT(...) SW_EXPAND_MACRO( SW_INTERNAL_ASSERT_CHOOSER(__VA_ARGS__)(_CORE_, __VA_ARGS__) )
#else
    #define SW_ASSERT(...)
    #define SW_CORE_ASSERT(...)
#endif