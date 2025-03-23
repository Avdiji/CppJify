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
            \n#include <jni.h>
            \n\n{}

            \nextern "C" {{
                \n\n{}
            \n}}
        ),
        placeholder::INCLUDES,
        placeholder::CODE
    );

    // FUNCTION SIGNATURE
    inline const std::string JIFY_BLUEPRINT_JNI_FUNC_SIGNATURE = JIFY_FMT(
        JIFY_RAW(
            \tJNIEXPORT {} JNICALL {}(JNIEnv * env, {})
        ),
            
        placeholder::RETURN_TYPE,
        placeholder::MANGLED_NAME,
        placeholder::PARAMS
    );

    // clang-format on

    // FUNCTION BODY
    inline const std::string JIFY_BLUEPRINT_JNI_FUNC_BODY = JIFY_FMT(
        JIFY_RAW(
            \n\t{{\n
            
                \t\t{}

                \n\t\t{}
            
            \n\t}}\n

        ),
        placeholder::C_CONVERSIONS,
        placeholder::C_RETURN_RESULT
    );

}  // namespace cppJify::generator::jni::blueprints