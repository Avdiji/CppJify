#pragma once

#include <fmt/core.h>

#define JIFY_RAW(code) #code
#define JIFY_FMT(...) fmt::format(__VA_ARGS__)

#define JIFY_OVERLOADED_FUNC(ReturnType, FUNC, ...) static_cast<ReturnType (*)(__VA_ARGS__)>(FUNC)
