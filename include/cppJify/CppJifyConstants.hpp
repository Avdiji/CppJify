#pragma once

#define JIFY_OVERLOADED_FUNC(ReturnType, FUNC, ...) static_cast<ReturnType (*)(__VA_ARGS__)>(FUNC)
#define JIFY_RAW(code) std::string(#code)