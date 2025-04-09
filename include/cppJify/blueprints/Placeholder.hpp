
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
    inline const std::string CALLING_TYPE = "{calling_type}";
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
