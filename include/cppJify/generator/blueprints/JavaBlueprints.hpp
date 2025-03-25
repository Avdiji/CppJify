#pragma once

#include <cppJify/generator/Placeholder.hpp>
#include <cppJify/utils/MacroUtils.hpp>
#include <string>

/**
 * Namespace defines several code-snippets, which are being used to generate proper Java-Code.
 * Those snippets contain certain placeholders, which will be replaced by proper Java-Code.
 * The Blueprints work in conjunction with the JifyMapper.
 */
namespace cppJify::generator::java::blueprints
{
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
    // clang-format on

}  // namespace cppJify::generator::java::blueprints