
#pragma once

#include <string>

namespace cppJify::blueprints::placeholder {

    inline const std::string CUSTOM_CODE = "{custom_code}";

    inline const std::string CLASSNAME = "{classname}";
    inline const std::string CLASSBODY = "{classbody}";
    inline const std::string BODY = "{body}";

    inline const std::string ACCESS_SPECIFIER = "{access_specifier}";
    inline const std::string STATIC_SPECIFIER = "{static_specifier}";
    inline const std::string NATIVE_SPECIFIER = "{native_specifier}";

    inline const std::string FUNCNAME = "{funcname}";
    inline const std::string MANGLED_FUNCNAME = "{mangled_funcname}";

    inline const std::string RETURN_TYPE = "{return_type}";
    inline const std::string RETURN_VALUE = "{return_value}";
    inline const std::string PARAMS = "{params}";
    inline const std::string PARAMS_NO_TYPE = "{params_no_type}";

    namespace java {
        inline const std::string PACKAGE = "{package}";
        inline const std::string IMPORTS = "{imports}";
    }  // namespace java

    namespace jni {
        inline const std::string PRAGMAONCE = "{pragmaonce}";
        inline const std::string INCLUDES = "{includes}";
        inline const std::string CPPJIFY_BASE_INCLUDE_PATH = "{cppjify_base_include_path}";
        inline const std::string CALLING_TYPE_CONVERSION_IN = "{calling_type_in_conversion}";
        inline const std::string CONVERSIONS_IN = "{conversions_in}";
        

    }  // namespace jni

}  // namespace cppJify::blueprints::placeholder

namespace cppJify::blueprints::jni::placeholder {
    inline const std::string INCLUDES = "$JIFY_JNI_INCLUDES";
    inline const std::string CPPJIFY_BASE_INCLUDE_PATH = "$JIFY_BASE_INCLUDE_PATH";
    inline const std::string CUSTOM_CODE = "$JIFY_JNI_CUTOM_CODE";
    inline const std::string CODE = "$JIFY_JNI_CODE";

    inline const std::string RETURN_TYPE = "$JIFY_JNI_FUNC_RETURN_TYPE";
    inline const std::string MANGLED_NAME = "$JIFY_JNI_FUNC_MANGLED_NAME";
    inline const std::string IS_STATIC = "$JIFY_JNI_FUNC_IS_STATIC";
    inline const std::string PARAMS = "$JIFY_JNI_FUNC_PARAMS";

    inline const std::string C_CALLING_TYPE_CONVERSION = "$JIFY_JNI_FUNC_BODDY_C_CALLING_TYPE_CONVERSION";

    inline const std::string C_CONVERSIONS = "$JIFY_JNI_FUNC_BODY_C_CONVERSIONS";
    inline const std::string C_RETURN_RESULT = "$JIFY_JNI_FUNC_BODY_C_RETURN_RESULT";
    inline const std::string C_FUNCTION_PARAMLIST = "$JIFY_JNI_FUNC_BODY_C_FUNCTION_PARAMLIST";

}  // namespace cppJify::blueprints::jni::placeholder

namespace cppJify::blueprints::java::placeholder {
    inline const std::string PACKAGE = "$JIFY_JAVA_PACKAGE";
    inline const std::string IMPORTS = "$JIFY_JAVA_IMPORTS";

    inline const std::string CLASS_NAME = "$JIFY_JAVA_CLASSNAME";
    inline const std::string CLASS_BODY = "$JIFY_JAVA_CLASS_BODY";

    inline const std::string FUNC_ACCESS_SPECIFIER = "$JIFY_JAVA_FUNC_ACCESS_SPECIFIER";
    inline const std::string FUNC_IS_STATIC = "$JIFY_JAVA_FUNC_IS_STATIC";
    inline const std::string FUNC_IS_NATIVE = "$JIFY_JAVA_FUNC_IS_NATIVE";
    inline const std::string FUNC_RETURN_VAL = "$JIFY_JAVA_FUNC_RETURN_VAL";
    inline const std::string FUNC_NAME = "$JIFY_JAVA_FUNC_NAME";
    inline const std::string FUNC_PARAMS = "$JIFY_JAVA_FUNC_PARAMS";
    inline const std::string FUNC_PARAMS_NO_TYPE = "$JIFY_JAVA_FUNC_PARAMS_NO_TYPE";

}  // namespace cppJify::blueprints::java::placeholder
