#pragma once

#include <cppJify/mapper/JifyMapper.hpp>
#include <cppJify/utils/MacroUtils.hpp>
namespace cppJify::mapper {

    // int
    const std::string JifyMapper<int>::CType() { return "int"; }
    const std::string JifyMapper<int>::JniType() { return "jint"; }
    const std::string JifyMapper<int>::JavaType() { return "int"; }
    const std::string JifyMapper<int>::BoxedJavaType() { return "Integer"; }
    const std::string JifyMapper<int>::In(const std::string& paramName) { return JIFY_FMT(JIFY_RAW(static_cast<int>({});), paramName); }
    const std::string JifyMapper<int>::Out(const std::string& functionCall) {
        return JIFY_FMT(JIFY_RAW(static_cast<jint>({});), functionCall);
    }
}  // namespace cppJify::mapper