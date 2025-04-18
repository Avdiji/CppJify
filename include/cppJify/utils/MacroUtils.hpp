#pragma once

#include <fmt/core.h>

/**
 * Macro returns a exact string-reflection of whatever is being inserted.
 */
#define JIFY_RAW(code) #code

/**
 * Shortcut for the fmt::format function.
 */
#define JIFY_FMT(...) fmt::format(__VA_ARGS__)

/**
 * Macro can be used to pass overloaded function to the CppJifyMapper.
 */
#define JIFY_OVERLOADED_FUNC(ReturnType, FUNC, ...) static_cast<ReturnType (*)(__VA_ARGS__)>(FUNC)

