#pragma once

#include <cppJify/mapper/JifyMapper.hpp>
#include <cppJify/utils/MacroUtils.hpp>

namespace cppJify::mapper {

    // short
    template <>
    class JifyMapper<short> {
        public:
            static const std::string CType() { return "short"; }
            static const std::string JniType() { return "jshort"; }
            static const std::string JavaType() { return "short"; }
            static const std::string In(const std::string& cVar, const std::string& jniVar, const std::string& id) {
                return JIFY_FMT(JIFY_RAW(\n\t\tshort {} = static_cast<short>({});), cVar, jniVar);
            }
            static const std::string Out(const std::string& functionCall) {
                return JIFY_FMT(JIFY_RAW(return static_cast<jshort>({});), functionCall);
            }
    };

    // const short
    template <>
    class JifyMapper<const short> {
        public:
            static const std::string CType() { return "const short"; }
            static const std::string JniType() { return "jshort"; }
            static const std::string JavaType() { return "short"; }
            static const std::string In(const std::string& cVar, const std::string& jniVar, const std::string& id) {
                return JIFY_FMT(JIFY_RAW(\n\t\tconst short {} = static_cast<const short>({});), cVar, jniVar);
            }
            static const std::string Out(const std::string& functionCall) {
                return JIFY_FMT(JIFY_RAW(return static_cast<jshort>({});), functionCall);
            }
    };

    // short& -> handle it like a regular short since the only other solution is to heap-allocate, which will cause memory leaks...
    template <>
    class JifyMapper<short&> {
        public:
            static const std::string CType() { return "short"; }
            static const std::string JniType() { return "jshort"; }
            static const std::string JavaType() { return "short"; }
            static const std::string In(const std::string& cVar, const std::string& jniVar, const std::string& id) {
                return JIFY_FMT(JIFY_RAW(\n\t\tshort {} = static_cast<short>({});), cVar, jniVar);
            }
            static const std::string Out(const std::string& functionCall) {
                return JIFY_FMT(JIFY_RAW(return static_cast<jshort>({});), functionCall);
            }
    };

    // const short&
    template <>
    class JifyMapper<const short&> {
        public:
            static const std::string CType() { return "const short"; }
            static const std::string JniType() { return "jshort"; }
            static const std::string JavaType() { return "short"; }
            static const std::string In(const std::string& cVar, const std::string& jniVar, const std::string& id) {
                return JIFY_FMT(JIFY_RAW(\n\t\tconst short {} = static_cast<const short>({});), cVar, jniVar);
            }
            static const std::string Out(const std::string& functionCall) {
                return JIFY_FMT(JIFY_RAW(return static_cast<jshort>({});), functionCall);
            }
    };

}  // namespace cppJify::mapper
