#pragma once

#include <jni.h>

#include <cppJify/blueprints/Placeholder.hpp>
#include <cppJify/utils/MacroUtils.hpp>
#include <string>

/**
 * Namespace defines several code-snippets, which are being used to generate proper JNI-Code.
 * Those snippets contain certian placeholders, which will be replaced by proper JNI-Code.
 * The Blueprints work in conjunction with the JifyMapper.
 */
namespace cppJify::blueprints::jni {

    // clang-format off

    // Base CPPJIFY-File...
    inline const std::string JIFY_BLUEPRINT_CPPJIFY_BASE = JIFY_FMT(
        JIFY_RAW(
            {}
            \n// Custom code here
        ),
        "#pragma once"
    );

    // BASE
    inline const std::string JIFY_BLUEPRINT_JNI_BASE = JIFY_FMT(
        JIFY_RAW(
            {}
            \n#include <jni.h>
            \n#include "{}"
            \n\n{}

            \nextern "C" {{
                \n\n{}

                \n\n{}
            \n}}
        ),
        "#pragma once",
        placeholder::CPPJIFY_BASE_INCLUDE_PATH,
        placeholder::INCLUDES,
        placeholder::CUSTOM_CODE,
        placeholder::CODE
    );

    // FUNCTION SIGNATURE
    inline const std::string JIFY_BLUEPRINT_JNI_FUNC_SIGNATURE = JIFY_FMT(
        JIFY_RAW(
            \tJNIEXPORT {} JNICALL {}(JNIEnv * env, {} {})
        ),
            
        placeholder::RETURN_TYPE,
        placeholder::MANGLED_NAME,
        placeholder::IS_STATIC,
        placeholder::PARAMS
    );


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

    // clang-format on

}  // namespace cppJify::blueprints::jni