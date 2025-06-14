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

    // Base for every generated JNI-file
    inline const std::string JIFY_BLUEPRINT_JNI_BASE = JIFY_RAW(
        {pragmaonce}
    
        \n\n#include <jni.h>
        \n\n{includes}
    
        \n\nextern "C" {
            \n{custom_code}
    
            \n\n{body}
        }
    );

    // Function signature of every generated JNI-function
    inline const std::string JIFY_BLUEPRINT_JNI_FUNC_SIGNATURE = JIFY_RAW(
        \n\tJNIEXPORT {return_type} JNICALL {mangled_funcname}(JNIEnv *env, {static_specifier}{params})
    );


    // Body of every generated static JNI-function (functions that map to static java functions)
    inline const std::string JIFY_BLUEPRINT_JNI_STATIC_FUNC_BODY = JIFY_RAW(
        \n\t{
            \t\t{conversions_in}

            \n\n\t\t{return_value}
        \n\t}
    );

    // Body of every generated JNI-function
    inline const std::string JIFY_BLUEPRINT_JNI_FUNC_BODY = JIFY_RAW(
        \n\t{
            {calling_type_in_conversion}
            \n{conversions_in}
            
            \n\n\t\t{return_value}
        \n\t}
    );

    // Code for every generated allocate function
    inline const std::string JIFY_BLUEPRINT_JNI_ALLOC_FUNC = JIFY_RAW(
        \n\tJNIEXPORT jlong JNICALL {mangled_funcname}(JNIEnv *env, jclass clazz{params})
        \n\t{
            {conversions_in}

            \n\n\t\t{calling_type} *nativeObject = new {calling_type}({params_no_type});
            \n\t\tcppJify::helper::CppJifyPtrWrapper<{calling_type}>* nativeObjectWrapper = new cppJify::helper::CppJifyPtrWrapper<{calling_type}>(nativeObject, true);
            \n\t\tjlong nativeHandle = reinterpret_cast<jlong>(nativeObjectWrapper);
            \n\t\treturn nativeHandle;
        \n\t}
    );

    // Code for every generated close (deallocate) function
    inline const std::string JIFY_BLUEPRINT_JNI_DEALLOC_FUNC = JIFY_RAW(
        \n\tJNIEXPORT void JNICALL {mangled_funcname}(JNIEnv *env, jobject arg0)
        \n\t{
            {calling_type_in_conversion}
            \n\t\tdelete carg0;
        \n\t}
    );
    // clang-format on

}  // namespace cppJify::blueprints::jni