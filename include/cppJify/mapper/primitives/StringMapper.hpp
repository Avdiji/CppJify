#pragma once

#include <cppJify/mapper/JifyMapper.hpp>
#include <cppJify/utils/MacroUtils.hpp>
#include <string>

namespace cppJify::mapper {

    // std::string
    template <>
    class JifyMapper<std::string> {
        public:
            static const std::string CType() { return "std::string"; }
            static const std::string JniType() { return "jstring"; }
            static const std::string JavaType() { return "java.lang.String"; }

            // clang-format off
            static const std::string In(const std::string& cVar, const std::string& jniVar, const std::string& id) {
                return JIFY_FMT(
                    JIFY_RAW(
                        const char* c_str{} = env->GetStringUTFChars({}, nullptr);
                        \n\t\t{} = std::string(c_str{});

                    ),
                    id, jniVar,
                    cVar, id

                );
            }
            // clang-format on
            static const std::string Out(const std::string& functionCall) {
                return JIFY_FMT(JIFY_RAW(return env->NewStringUTF({}.c_str());), functionCall);
            }
    };

    // const std::string
    template <>
    class JifyMapper<const std::string> {
        public:
            static const std::string CType() { return "const bool"; }
            static const std::string JniType() { return "jboolean"; }
            static const std::string JavaType() { return "boolean"; }
            static const std::string In(const std::string& cVar, const std::string& jniVar, const std::string& id) {
                return JIFY_FMT(JIFY_RAW({} = static_cast<const bool>({});), cVar, jniVar);
            }
            static const std::string Out(const std::string& functionCall) {
                return JIFY_FMT(JIFY_RAW(return static_cast<jboolean>({});), functionCall);
            }
    };

    // std::string& -> handle it like a regular std::string since the only other solution is to heap-allocate, which will cause memory
    // leaks...
    template <>
    class JifyMapper<std::string&> {
        public:
            static const std::string CType() { return "bool"; }
            static const std::string JniType() { return "jboolean"; }
            static const std::string JavaType() { return "boolean"; }
            static const std::string In(const std::string& cVar, const std::string& jniVar, const std::string& id) {
                return JIFY_FMT(JIFY_RAW({} = static_cast<bool>({});), cVar, jniVar);
            }
            static const std::string Out(const std::string& functionCall) {
                return JIFY_FMT(JIFY_RAW(return static_cast<bool>({});), functionCall);
            }
    };

    // const std::string&
    template <>
    class JifyMapper<const std::string&> {
        public:
            static const std::string CType() { return "const bool"; }
            static const std::string JniType() { return "jboolean"; }
            static const std::string JavaType() { return "boolean"; }
            static const std::string In(const std::string& cVar, const std::string& jniVar, const std::string& id) {
                return JIFY_FMT(JIFY_RAW({} = static_cast<const bool>({});), cVar, jniVar);
            }
            static const std::string Out(const std::string& functionCall) {
                return JIFY_FMT(JIFY_RAW(return static_cast<jboolean>({});), functionCall);
            }
    };

}  // namespace cppJify::mapper
