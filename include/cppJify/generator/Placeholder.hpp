
#pragma once

#include <string>

/**
 * @brief namespace contains JNI-specific Placeholders for the generator.
 */
namespace cppJify::generator::placeholder::jni
{
    inline const std::string INCLUDES = "$JIFY_JNI_INCLUDES";
    inline const std::string CODE = "$JIFY_JNI_CODE";

    inline const std::string RETURN_TYPE = "$JIFY_JNI_FUNC_RETURN_TYPE";
    inline const std::string MANGLED_NAME = "$JIFY_JNI_FUNC_MANGLED_NAME";
    inline const std::string PARAMS = "$JIFY_JNI_FUNC_PARAMS";

    inline const std::string C_CONVERSIONS = "$JIFY_JNI_FUNC_BODY_C_CONVERSIONS";
    
    inline const std::string C_FUNCTION_CALL = "$JIFY_JNI_FUNC_BODY_C_FUNCTION_CALL";
    inline const std::string C_FUNCTION_PARAMLIST = "$JIFY_JNI_FUNC_BODY_C_FUNCTION_PARAMLIST";


}  // namespace cppJify::generator::placeholder::jni
