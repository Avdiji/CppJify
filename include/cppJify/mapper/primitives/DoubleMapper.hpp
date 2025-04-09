#pragma once

#include <cppJify/mapper/JifyMapper.hpp>
#include <cppJify/utils/MacroUtils.hpp>

namespace cppJify::mapper {

    // double
    template <>
    class JifyMapper<double> {
        public:
            static const std::string CType() { return "double"; }
            static const std::string JniType() { return "jdouble"; }
            static const std::string JavaType() { return "double"; }
            static const std::string In(const std::string& cVar, const std::string& jniVar, const std::string& id) {
                return JIFY_FMT(JIFY_RAW(\n\t\tdouble {} = static_cast<double>({});), cVar, jniVar);
            }
            static const std::string Out(const std::string& functionCall) {
                return JIFY_FMT(JIFY_RAW(return static_cast<jdouble>({});), functionCall);
            }
    };

    // const double
    template <>
    class JifyMapper<const double> {
        public:
            static const std::string CType() { return "const double"; }
            static const std::string JniType() { return "jdouble"; }
            static const std::string JavaType() { return "double"; }
            static const std::string In(const std::string& cVar, const std::string& jniVar, const std::string& id) {
                return JIFY_FMT(JIFY_RAW(\n\t\tconst double {} = static_cast<const double>({});), cVar, jniVar);
            }
            static const std::string Out(const std::string& functionCall) {
                return JIFY_FMT(JIFY_RAW(return static_cast<jdouble>({});), functionCall);
            }
    };

    // double& -> handle it like a regular double since the only other solution is to heap-allocate, which will cause memory leaks...
    template <>
    class JifyMapper<double&> {
        public:
            static const std::string CType() { return "double"; }
            static const std::string JniType() { return "jdouble"; }
            static const std::string JavaType() { return "double"; }
            static const std::string In(const std::string& cVar, const std::string& jniVar, const std::string& id) {
                return JIFY_FMT(JIFY_RAW(\n\t\tdouble {} = static_cast<double>({});), cVar, jniVar);
            }
            static const std::string Out(const std::string& functionCall) {
                return JIFY_FMT(JIFY_RAW(return static_cast<jdouble>({});), functionCall);
            }
    };

    // const double&
    template <>
    class JifyMapper<const double&> {
        public:
            static const std::string CType() { return "const double"; }
            static const std::string JniType() { return "jdouble"; }
            static const std::string JavaType() { return "double"; }
            static const std::string In(const std::string& cVar, const std::string& jniVar, const std::string& id) {
                return JIFY_FMT(JIFY_RAW(\n\t\tconst double {} = static_cast<const double>({});), cVar, jniVar);
            }
            static const std::string Out(const std::string& functionCall) {
                return JIFY_FMT(JIFY_RAW(return static_cast<jdouble>({});), functionCall);
            }
    };

}  // namespace cppJify::mapper
