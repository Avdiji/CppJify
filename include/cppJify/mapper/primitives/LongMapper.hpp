#pragma once

#include <cppJify/mapper/JifyMapper.hpp>
#include <cppJify/utils/MacroUtils.hpp>

namespace cppJify::mapper {

    // long
    template <>
    class JifyMapper<long> {
        public:
            static const std::string CType() { return "long"; }
            static const std::string JniType() { return "jlong"; }
            static const std::string JavaType() { return "long"; }
            static const std::string In(const std::string& cVar, const std::string& jniVar, const std::string& id) {
                return JIFY_FMT(JIFY_RAW(\n\t\tlong {} = static_cast<long>({});), cVar, jniVar);
            }
            static const std::string Out(const std::string& functionCall) {
                return JIFY_FMT(JIFY_RAW(return static_cast<jlong>({});), functionCall);
            }
    };

    // const long
    template <>
    class JifyMapper<const long> {
        public:
            static const std::string CType() { return "const long"; }
            static const std::string JniType() { return "jlong"; }
            static const std::string JavaType() { return "long"; }
            static const std::string In(const std::string& cVar, const std::string& jniVar, const std::string& id) {
                return JIFY_FMT(JIFY_RAW(\n\t\tconst long {} = static_cast<const long>({});), cVar, jniVar);
            }
            static const std::string Out(const std::string& functionCall) {
                return JIFY_FMT(JIFY_RAW(return static_cast<jlong>({});), functionCall);
            }
    };

    // long& -> handle it like a regular long since the only other solution is to heap-allocate, which will cause memory leaks...
    template <>
    class JifyMapper<long&> {
        public:
            static const std::string CType() { return "long"; }
            static const std::string JniType() { return "jlong"; }
            static const std::string JavaType() { return "long"; }
            static const std::string In(const std::string& cVar, const std::string& jniVar, const std::string& id) {
                return JIFY_FMT(JIFY_RAW(\n\t\tlong {} = static_cast<long>({});), cVar, jniVar);
            }
            static const std::string Out(const std::string& functionCall) {
                return JIFY_FMT(JIFY_RAW(return static_cast<jlong>({});), functionCall);
            }
    };

    // const long&
    template <>
    class JifyMapper<const long&> {
        public:
            static const std::string CType() { return "const long"; }
            static const std::string JniType() { return "jlong"; }
            static const std::string JavaType() { return "long"; }
            static const std::string In(const std::string& cVar, const std::string& jniVar, const std::string& id) {
                return JIFY_FMT(JIFY_RAW(\n\t\tconst long {} = static_cast<const long>({});), cVar, jniVar);
            }
            static const std::string Out(const std::string& functionCall) {
                return JIFY_FMT(JIFY_RAW(return static_cast<jlong>({});), functionCall);
            }
    };

}  // namespace cppJify::mapper
