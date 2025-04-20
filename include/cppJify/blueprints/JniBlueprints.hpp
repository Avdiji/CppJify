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

    // The base-file, which will be included into every generated jni file...
    inline const std::string JIFY_BLUEPRINT_JNI_CPPJIFY_BASE = JIFY_RAW(
        // TODO this can be moved from the blueprints as the cppJify project gets linked against anyways...
        {pragmaonce}

        \n\n#include <jni.h>
        \n\n#include <string>
        \n\n#include <memory>

        \n\nnamespace cppJify::helper {

            \n\n\ttemplate<class T>
            \n\tclass CppJifyPtrWrapper
            \n\t{
                \n\t\tpublic:
                    \n\t\t\texplicit CppJifyPtrWrapper(T* instance, bool owns = false) { _raw = instance; _owns = owns;}
                    \n\t\t\texplicit CppJifyPtrWrapper(std::shared_ptr<T> instance,  bool owns = false) { _shared = std::move(instance); _owns = owns; }
                    \n\t\t\texplicit CppJifyPtrWrapper(std::unique_ptr<T> instance,  bool owns = false) { _unique = std::move(instance); _owns = owns; }

                    \n\n\t\t\t~CppJifyPtrWrapper() { if(_raw && _owns) delete _raw; }

                    \n\n\t\t\toperator std::shared_ptr<T>() {
                        \n\t\t\t\tif(_shared) { return _shared; }
                        \n\t\t\t\tif(_raw && _owns) {
                            \n\t\t\t\t\t_shared = std::shared_ptr<T>(_raw);
                            \n\t\t\t\t\t_raw = nullptr;
                            \n\t\t\t\t\treturn _shared;
                        \n\t\t\t\t}
                        \n\t\t\t\tif(_unique) {
                            \n\t\t\t\t\t_shared = std::move(_unique);
                            \n\t\t\t\t\t_unique = nullptr;
                            \n\t\t\t\t\treturn _shared;
                        \n\t\t\t\t}
                        \n\t\t\t\tthrow std::runtime_error("Object is in a illegal state, unable to transfer ownership to shared_ptr");
                    \n\t\t\t}

                    \n\n\t\t\tT* get() {
                        \n\t\t\t\tif(_raw) return _raw;
                        \n\t\t\t\tif(_shared) return _shared.get();
                        \n\t\t\t\tif(_unique) return _unique.get();
                        \n\t\t\t\tthrow std::runtime_error("No Instance is being persisted in this wrapper");
                    \n\t\t\t}

                \n\n\t\tprivate:
                    \n\t\t\tbool _owns;
                    \n\t\t\tT* _raw = nullptr;
                    \n\t\t\tstd::shared_ptr<T> _shared = nullptr;
                    \n\t\t\tstd::unique_ptr<T> _unique = nullptr;
                    \n\t\t\tstd::weak_ptr<T> _weak;
            \n\t};

            \n\n\ttemplate <typename T>
            \n\tinline CppJifyPtrWrapper<T>* cppJifyObjectToPtr(JNIEnv* env, jobject obj) 
            \n\t{
                \n\t\tjclass cls = env->GetObjectClass(obj);
                \n\t\tjmethodID mid = env->GetMethodID(cls, "getNativeHandle", "()J");
                \n\t\treturn reinterpret_cast<CppJifyPtrWrapper<T>*>(env->CallLongMethod(obj, mid));
            \n\t}
            
            \n\n\ttemplate <typename T>
            \n\tinline jobject ptrToCppJifyObject(JNIEnv* env, const std::string &classname, CppJifyPtrWrapper<T>* ptr)
            \n\t{
                \n\t\tjclass cls = env->FindClass(classname.c_str());
                \n\t\tjmethodID constructor = env->GetMethodID(cls, "<init>", "(J)V");
                \n\t\treturn env->NewObject(cls, constructor, reinterpret_cast<jlong>(ptr));
            \n\t}
        \n}
    );


    // Base for every generated JNI-file
    inline const std::string JIFY_BLUEPRINT_JNI_BASE = JIFY_RAW(
        {pragmaonce}
    
        \n\n#include <jni.h>
        \n#include "{cppjify_base_include_path}"
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