#pragma once

#include <cppJify/blueprints/Placeholder.hpp>
#include <cppJify/utils/MacroUtils.hpp>
#include <string>

/**
 * Namespace defines several code-snippets, which are being used to generate proper Java-Code.
 * Those snippets contain certain placeholders, which will be replaced by proper Java-Code.
 * The Blueprints work in conjunction with the JifyMapper.
 */
namespace cppJify::blueprints::java {

    // clang-format off
    // BASE CPPJIFY INTERFACE
    inline const std::string JIFY_BLUEPRINT_JAVA_CPPJIFY_BASE_INTERFACE = JIFY_RAW(
        package com.cppjify;

        \n\npublic interface CppJifyBase {
            \n\tlong getNativeHandle();
        \n}
    );


    // BASE FOR UTILS-CLASS
    inline const std::string JIFY_BLUEPRINT_JAVA_STATIC_CLASS_BASE = JIFY_FMT(
        JIFY_RAW(
            package {};

            \n\n{}

            \n\npublic class {} {{
                
                \n\n\tprivate {}(){{}}
                \n{}
            \n}}
        ),

        placeholder::PACKAGE,
        placeholder::IMPORTS,
        placeholder::CLASS_NAME,
        placeholder::CLASS_NAME,
        placeholder::CLASS_BODY
    );

    inline const std::string JIFY_BLUEPRINT_JAVA_INSTANCE_CLASS_BASE = JIFY_FMT(
        JIFY_RAW(
            package {};

            \n\n{}

            \n\npublic class {} implements com.cppjify.CppJifyBase {{
                
                \n\tprivate long nativeHandle;
                \n\n\tprivate {}(final long nativeHandle) {{
                    \n\t\tthis.nativeHandle = nativeHandle;
                \n\t}}

                \n\n\t@Override 
                \n\tpublic long getNativeHandle(){{ return this.nativeHandle; }}
                \n{}
            \n}}
        ),
        placeholder::PACKAGE,
        placeholder::IMPORTS,
        placeholder::CLASS_NAME,
        placeholder::CLASS_NAME,
        placeholder::CLASS_BODY

    );

    // FUNCTION SIGNATURE
    inline const std::string JIFY_BLUEPRINT_JAVA_FUNC_SIGNATURE = JIFY_FMT(
        JIFY_RAW(
            \n\t{} {}{}{} {}({});
        ),
        placeholder::FUNC_ACCESS_SPECIFIER,
        placeholder::FUNC_IS_STATIC,
        placeholder::FUNC_IS_NATIVE,
        placeholder::FUNC_RETURN_VAL,
        placeholder::FUNC_NAME,
        placeholder::FUNC_PARAMS
    );


    inline const std::string JIFY_BLUEPRINT_JAVA_CONSTRUCTOR_SIGNATURE = JIFY_FMT(
        JIFY_RAW(
            \n\tpublic {}({}) {{ nativeHandle = allocate({}); }}
        ),
        placeholder::CLASS_NAME,
        placeholder::FUNC_PARAMS,
        placeholder::FUNC_PARAMS_NO_TYPE
    );
    // clang-format on

}  // namespace cppJify::blueprints::java