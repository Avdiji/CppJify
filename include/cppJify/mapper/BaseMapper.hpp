#pragma once

#include <cppJify/mapper/JifyMapper.hpp>
#include <iostream>
namespace cppJify::mapper {

    // void
    const std::string JifyMapper<void>::CType() { return "void"; }
    const std::string JifyMapper<void>::JniType() { return "void"; }
    const std::string JifyMapper<void>::JavaType() { return "void"; }
    const std::string JifyMapper<void>::In(const size_t& p_argId, JNIEnv* env) { return ""; }
    const std::string JifyMapper<void>::Out(const std::string& p_func, JNIEnv* env) { return "\t " + p_func; }

    // int
    const std::string JifyMapper<int>::CType() { return "int"; }
    const std::string JifyMapper<int>::JniType() { return "jint"; }
    const std::string JifyMapper<int>::JavaType() { return "int"; }
    const std::string JifyMapper<int>::BoxedJavaType() { return "Integer"; }
    const std::string JifyMapper<int>::In(const size_t& p_argId, JNIEnv* env) {
        return utils::JIFY_TRANSFORM(JIFY_RAW(\t int $carg = (int)$jarg; \n), p_argId);
    }
    const std::string JifyMapper<int>::Out(const std::string& p_func, JNIEnv* env) {
        return utils::JIFY_TRANSFORM(

            JIFY_RAW(

                \t jint result = $func; \n
                \t return result; \n

                ),
            p_func

        );
    }
}  // namespace cppJify::mapper