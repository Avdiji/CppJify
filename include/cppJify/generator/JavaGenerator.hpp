#pragma once

#include <cppJify/blueprints/JavaBlueprints.hpp>
#include <cppJify/blueprints/Placeholder.hpp>
#include <cppJify/mapper/JifyMapper.hpp>
#include <cppJify/utils/StringUtils.hpp>

namespace cppJify::generator::java {

    /**
     * @brief Generates a Java function signature string with specified attributes.
     *
     * This template function generates a formatted Java function signature using the provided function name,
     * access specifier, and attributes such as whether the function is static or native.
     *
     * @tparam IsStatic Boolean value indicating if the function is static.
     * @tparam IsNative Boolean value indicating if the function is native.
     * @tparam ReturnType The C++ return type to be mapped to a Java-compatible type.
     * @tparam Params Variadic template parameters representing function parameter types.
     * @param jFunctionName The name of the Java function to be generated.
     * @param accessSpecifier The access specifier (e.g., public, private, protected) for the function.
     * @return A formatted string representing the generated Java function signature.
     */
    template <bool IsStatic, bool IsNative, class ReturnType, class... Params>
    std::string generateFunctionSignature(const std::string& jFunctionName, const std::string& accessSpecifier) {
        std::string result = blueprints::JIFY_BLUEPRINT_JAVA_FUNC_SIGNATURE;

        result = utils::replaceAll(result, blueprints::placeholder::ACCESS_SPECIFIER, accessSpecifier);
        result = utils::replaceAll(result, blueprints::placeholder::STATIC_SPECIFIER, (IsStatic ? "static " : ""));
        result = utils::replaceAll(result, blueprints::placeholder::NATIVE_SPECIFIER, (IsNative ? "native " : ""));
        result = utils::replaceAll(result, blueprints::placeholder::RETURN_TYPE, mapper::JifyMapper<ReturnType>::JavaType());
        result = utils::replaceAll(result, blueprints::placeholder::FUNCNAME, jFunctionName);
        result = utils::replaceAll(result, blueprints::placeholder::PARAMS, generateParamList<LANGUAGE_TYPE::JAVA, true, Params...>());

        return result;
    }

    template <class... Params>
    std::string generateConstructorSignature(const std::string& jclassname) {
        std::string result = blueprints::JIFY_BLUEPRINT_JAVA_CONSTRUCTOR_SIGNATURE;

        result = utils::replaceAll(result, blueprints::placeholder::CLASSNAME, jclassname);

        const std::string params = generateParamList<LANGUAGE_TYPE::JAVA, true, Params...>();
        result = utils::replaceAll(result, blueprints::placeholder::PARAMS, params);

        const std::string paramsNoType = generateParamList<LANGUAGE_TYPE::JAVA, false, Params...>();
        result = utils::replaceAll(result, blueprints::placeholder::PARAMS_NO_TYPE, paramsNoType);

        return result;
    }

}  // namespace cppJify::generator::java