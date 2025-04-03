
#pragma once

#include <string>

/**
 * @brief namespace contains JNI-specific Placeholders for the generator.
 */
namespace cppJify::generator::jni::placeholder
{
    inline const std::string INCLUDES = "$JIFY_JNI_INCLUDES";
    inline const std::string CUSTOM_CODE = "$JIFY_JNI_CUTOM_CODE";
    inline const std::string CODE = "$JIFY_JNI_CODE";

    inline const std::string RETURN_TYPE = "$JIFY_JNI_FUNC_RETURN_TYPE";
    inline const std::string MANGLED_NAME = "$JIFY_JNI_FUNC_MANGLED_NAME";
    inline const std::string IS_STATIC = "$JIFY_JNI_FUNC_IS_STATIC";
    inline const std::string PARAMS = "$JIFY_JNI_FUNC_PARAMS";

    inline const std::string C_CONVERSIONS = "$JIFY_JNI_FUNC_BODY_C_CONVERSIONS";

    inline const std::string C_RETURN_RESULT = "$JIFY_JNI_FUNC_BODY_C_RETURN_RESULT";
    inline const std::string C_FUNCTION_PARAMLIST = "$JIFY_JNI_FUNC_BODY_C_FUNCTION_PARAMLIST";

}  // namespace cppJify::generator::jni::placeholder

namespace cppJify::generator::java::placeholder
{
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

}  // namespace cppJify::generator::java::placeholder
