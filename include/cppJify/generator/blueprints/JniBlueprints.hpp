#pragma once

#include <jni.h>

#include <cppJify/generator/Placeholder.hpp>
#include <cppJify/utils/MacroUtils.hpp>
#include <string>

/**
 * Namespace defines several code-snippets, which are being used to generate proper JNI-Code.
 * Those snippets contain certian placeholders, which will be replaced by proper JNI-Code.
 * The Blueprints work in conjunction with the JifyMapper.
 */
namespace cppJify::generator::jni::blueprints
{

    // clang-format off

    // BASE
    inline const std::string JIFY_BLUEPRINT_JNI_BASE = JIFY_FMT(
        JIFY_RAW(
            #pragma once
            #include <jni.h>
            {}

            extern "C" {{
                {}
            }}
        ),
        placeholder::jni::INCLUDES,
        placeholder::jni::CODE
    );

    // FUNCTION SIGNATURE
    inline const std::string JIFY_BLUEPRINT_JNI_FUNC_SIGNATURE = JIFY_FMT(
        JIFY_RAW(
            JNIEXPORT {} JNICALL {}(JNIEnv * env, {})
        ),
            
        placeholder::jni::RETURN_TYPE,
        placeholder::jni::MANGLED_NAME,
        placeholder::jni::PARAMS
    );

    // clang-format on

    // FUNCTION BODY
    inline const std::string JIFY_BLUEPRINT_JNI_FUNC_BODY = JIFY_FMT(
        JIFY_RAW(
            \n{{\n
            
                \t{}

                \n\treturn {}({});
            
            \n}}\n

        ),
        placeholder::jni::C_CONVERSIONS,
        placeholder::jni::C_FUNCTION_CALL,
        placeholder::jni::C_FUNCTION_PARAMLIST
    );

}  // namespace cppJify::generator::jni::blueprints