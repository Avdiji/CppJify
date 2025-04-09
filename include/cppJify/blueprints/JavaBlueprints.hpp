#pragma once

#include <cppJify/blueprints/Placeholder.hpp>
#include <cppJify/utils/MacroUtils.hpp>
#include <string>

/**
 * Namespace defines several code-snippets, which are being used to generate proper Java-Code.
 * Those snippets contain certain placeholders, which will be replaced by proper Java-Code.
 * The Blueprints work in conjunction with the JifyMapper.
 */
namespace cppJify::blueprints {
    // clang-format off

    // Base Java CppJify interface
    inline const std::string JIFY_BLUEPRINT_JAVA_CPPJIFY_BASE_INTERFACE = JIFY_RAW(
        package com.cppjify;

        \n\npublic interface CppJifyBase {
            \n\tlong getNativeHandle();
        \n}
    );


    // Base for every generated Java-Utils class
    inline const std::string JIFY_BLUEPRINT_JAVA_STATIC_CLASS = JIFY_RAW(
        package {package};

        \n\n{imports}

        \n\npublic class {classname} {
            \n\n\tprivate {classname} {}

            \n{classbody}
        \n}
    );


    // Base for every generated Java-Instance class
    inline const std::string JIFY_BLUEPRINT_JAVA_INSTANCE_CLASS = JIFY_RAW(
        package {package};
        
        \n\n{imports}

        \n\npublic class {classname} implements com.cppjify.CppJifyBase {
            \n\n\tprivate long nativeHandle;
            \n\tpublic long getNativeHandle() { return this.nativeHandle; }

            \n\n{classbody}
        \n}
    );


    // Base for every generated Java function signature
    inline const std::string JIFY_BLUEPRINT_JAVA_FUNC_SIGNATURE = JIFY_RAW(
        \n\t{access_specifier} {static_specifier}{native_specifier}{return_type} {funcname}({params});
    );

    // Base for every generated Java constructor
    inline const std::string JIFY_BLUEPRINT_JAVA_CONSTRUCTOR = JIFY_RAW(
        \n\tpublic {classname}({params}) { nativeHandle = allocate({params_no_type}); }
    );
    // clang-format on

}  // namespace cppJify::blueprints