#pragma once

#include <cppJify/mapper/JifyMapper.hpp>
#include <cppJify/utils/MacroUtils.hpp>

namespace cppJify::mapper {

    template <>
    class JifyMapper<void> {
        public:
            static const std::string CType() { return "void"; }
            static const std::string JniType() { return "void"; }
            static const std::string JavaType() { return "void"; }
            static const std::string In(const std::string& cVar, const std::string& jniVar, const std::string& id) {
                return "";  // no input mapping for void...
            }
            static const std::string Out(const std::string& functionCall) { return functionCall + ";"; }
    };

    template <>
    class JifyMapper<const void> {
        public:
            static const std::string CType() { return "const void"; }
            static const std::string JniType() { return "void"; }
            static const std::string JavaType() { return "void"; }
            static const std::string In(const std::string& cVar, const std::string& jniVar, const std::string& id) {
                return "";  // no input mapping for void...
            }
            static const std::string Out(const std::string& functionCall) { return functionCall + ";"; }
    };

}  // namespace cppJify::mapper
