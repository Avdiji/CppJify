#pragma once

#include <cppJify/generator/Placeholder.hpp>
#include <cppJify/generator/blueprints/JniBlueprints.hpp>
#include <cppJify/mapper/JifyMapper.hpp>
#include <cppJify/utils/StringUtils.hpp>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

namespace cppJify::generator::jni
{

    /**
     * @brief Represents a JNI function parameter.
     *
     * A JNI function parameter consists of:
     *  - `paramType`: The JNI type (e.g., `jint`, `jstring`, etc.).
     *  - `paramName`: The parameter name (e.g., `arg0`, `arg1`).
     */
    struct JniParam
    {
            const std::string paramType;
            const std::string paramName;
    };

    /**
     * @brief Generates a complete JNI function, including the function signature and body.
     *
     * This function combines the generated JNI function signature and the function body to create
     * a complete JNI function definition. It utilizes the provided C++ function name, Java function name,
     * package name, and class name to construct the JNI function.
     *
     * @tparam ReturnType The return type of the C++ function.
     * @tparam Params The parameter types of the C++ function.
     *
     * @param cppFunctionName The actual name of the C++ function to be mapped to JNI.
     * @param jFunctionName The corresponding Java function name.
     * @param jPackage The package name of the Java class.
     * @param jClassname The class name where the Java function resides.
     *
     * @return A complete JNI function as a formatted string.
     */
    template <class ReturnType, class... Params>
    std::string generateFunction(const std::string& cppFunctionName,
                                 const std::string& jFunctionName,
                                 const std::string& jPackage,
                                 const std::string& jClassname)
    {
        // signature
        const std::string functionSignature =
            generateFunctionSignature<ReturnType, Params...>(cppFunctionName, jFunctionName, jPackage, jClassname);

        // body
        const std::string functionBody =
            generateFunctionBody<ReturnType, Params...>(cppFunctionName, jFunctionName, jPackage, jClassname);

        return functionSignature + functionBody;
    }

    //////////////////////////////////////// FUNCTION SIGNATURE ////////////////////////////////////////
    //////////////////////////////////////// FUNCTION SIGNATURE ////////////////////////////////////////
    //////////////////////////////////////// FUNCTION SIGNATURE ////////////////////////////////////////
    /**
     * @brief Generates a JNI function signature based on C++ function signature.
     *
     * Generates the JNI function signature, including return type, mangled name,
     * and parameter list, based on the provided C++ function signature.
     *
     * @tparam ReturnType The return type of the C++ function.
     * @tparam Params The parameter types of the C++ function.
     *
     * @param cppFunctionName The name of the original C++ function.
     * @param jFunctionName The desired name of the Java function.
     * @param jPackage The Java package where the function resides.
     * @param jClassname The name of the Java class.
     *
     * @return A complete JNI function signature.
     */
    template <class ReturnType, class... Params>
    std::string generateFunctionSignature(const std::string& cppFunctionName,
                                          const std::string& jFunctionName,
                                          const std::string& jPackage,
                                          const std::string& jClassname)
    {
        std::string result = blueprints::JIFY_BLUEPRINT_JNI_FUNC_SIGNATURE;

        // Replace the return type
        const std::string jniReturnType = mapper::JifyMapper<ReturnType>::JniType();
        result = utils::replaceAll(result, placeholder::jni::RETURN_TYPE, jniReturnType);

        // Generate the function mangled name
        const std::string jniMangledname = generateJMangledname<Params...>(jFunctionName, jPackage, jClassname);
        result = utils::replaceAll(result, placeholder::jni::MANGLED_NAME, jniMangledname);

        // Generate parameter list
        std::ostringstream parameterlist;
        const auto params = generateParams<Params...>();
        for (size_t i = 0; i < params.size(); ++i)
        {
            if (i > 0) { parameterlist << ", "; }
            parameterlist << params[i].paramType << " " << params[i].paramName;
        }
        result = utils::replaceAll(result, placeholder::jni::PARAMS, parameterlist.str());

        return result;
    }

    /**
     * @brief Generates the mangled JNI function name.
     *
     * Creates the JNI mangled function name for the given Java function, including
     * the package and class names.
     *
     * @tparam Params The parameter types of the Java function.
     *
     * @param jFunctionName The desired Java function name.
     * @param jPackage The Java package.
     * @param jClassname The Java class name.
     *
     * @return The mangled JNI function name.
     */
    template <class... Params>
    std::string generateJMangledname(const std::string& jFunctionName,
                                     const std::string& jPackage,
                                     const std::string& jClassname)
    {
        const std::string jniStylePackage = utils::replaceAll(jPackage, ".", "_");
        std::ostringstream mangledJFuncname;
        mangledJFuncname << "Java_" << jniStylePackage << "_" << jClassname << "_" << jFunctionName;

        std::ostringstream mangledJFuncnameParams;
        ((mangledJFuncnameParams << generateJManglednameParam<Params>()), ...);

        const std::string paramStr = mangledJFuncnameParams.str();
        if (!paramStr.empty()) { mangledJFuncname << "__" << paramStr; }

        return mangledJFuncname.str();
    }

    /**
     * @brief Generates the JNI mangled name for a single parameter type.
     *
     * Converts a given Java type to its corresponding JNI type representation.
     *
     * @tparam Param The type of the parameter.
     *
     * @return The JNI mangled representation of the parameter.
     */
    template <class Param>
    std::string generateJManglednameParam()
    {
        const std::unordered_map<std::string, std::string> primitiveJToJNITypeMap = {
            {"void", "V"}, {"boolean", "Z"}, {"byte", "B"},  {"char", "C"},  {"short", "S"},
            {"int", "I"},  {"long", "J"},    {"float", "F"}, {"double", "D"}};

        const std::string javaType = mapper::JifyMapper<Param>::JavaType();
        auto it = primitiveJToJNITypeMap.find(javaType);

        // Check for primitive type
        if (it != primitiveJToJNITypeMap.end()) { return it->second; }

        return "";  // TODO handle other cases...
    }
    //////////////////////////////////////// FUNCTION SIGNATURE ////////////////////////////////////////
    //////////////////////////////////////// FUNCTION SIGNATURE ////////////////////////////////////////
    //////////////////////////////////////// FUNCTION SIGNATURE ////////////////////////////////////////

    //////////////////////////////////////// FUNCTION BODY ////////////////////////////////////////
    //////////////////////////////////////// FUNCTION BODY ////////////////////////////////////////
    //////////////////////////////////////// FUNCTION BODY ////////////////////////////////////////
    /**
     * @brief Generates the body of a JNI function.
     *
     * This function constructs the body of a JNI function based on the provided C++ function name, Java function name,
     * package name, and class name. The body typically contains the native code and any necessary conversions
     * from JNI types to C++ types.
     *
     * The generated function body uses predefined blueprints and applies placeholder replacements
     * to generate the final code representation.
     *
     * @tparam ReturnType The return type of the C++ function.
     * @tparam Params The parameter types of the C++ function.
     *
     * @param cppFunctionName The actual name of the C++ function to be mapped to JNI.
     * @param jFunctionName The corresponding Java function name.
     * @param jPackage The package name of the Java class.
     * @param jClassname The class name where the Java function resides.
     *
     * @return The generated body of the JNI function as a formatted string.
     */
    template <class ReturnType, class... Params>
    std::string generateFunctionBody(const std::string& cppFunctionName,
                                     const std::string& jFunctionName,
                                     const std::string& jPackage,
                                     const std::string& jClassname)
    {
        std::string result = blueprints::JIFY_BLUEPRINT_JNI_FUNC_BODY;

        // JNI -> C++ conversions for all parameter
        int counter = 0;
        std::stringstream paramConversions;
        ((paramConversions << generateParamCConversion<Params>(counter++)), ...);

        result = utils::replaceAll(result, placeholder::jni::C_CONVERSIONS, paramConversions.str());

        return result;
    }

    template<class Param>
    std::string generateParamCConversion(const int& counter) {
        JniParam param = generateParam<Param>(counter);

        std::ostringstream result;
        result << mapper::JifyMapper<Param>::CType() << " c" << param.paramName << " = ";
        result << mapper::JifyMapper<Param>::In(param.paramName) << "\n\t";
        return result.str();
    }
    //////////////////////////////////////// FUNCTION BODY ////////////////////////////////////////
    //////////////////////////////////////// FUNCTION BODY ////////////////////////////////////////
    //////////////////////////////////////// FUNCTION BODY ////////////////////////////////////////

    /**
     * @brief Generates a list of JNI function parameters.
     *
     * Creates a list of JNI function parameters, including their types and names.
     *
     * @tparam Params The parameter types of the function.
     *
     * @return A vector of JniParam structures.
     */
    template <class... Params>
    std::vector<JniParam> generateParams()
    {
        std::vector<JniParam> params;
        int counter = 0;
        (params.push_back(generateParam<Params>(counter++)), ...);
        return params;
    }

      /**
     * @brief Generates a JniParam instance.
     *
     * @tparam Param The parameter type.
     *
     * @return An instasnce of JniParam.
     */
    template <class Param>
    JniParam generateParam(const int& counter) {
        return {mapper::JifyMapper<Param>::JniType(), "arg" + std::to_string(counter)};
    }

}  // namespace cppJify::generator::jni
