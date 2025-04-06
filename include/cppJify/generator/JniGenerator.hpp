#pragma once

#include <cppJify/blueprints/JniBlueprints.hpp>
#include <cppJify/blueprints/Placeholder.hpp>
#include <cppJify/generator/Generator.hpp>
#include <cppJify/mapper/JifyMapper.hpp>
#include <cppJify/utils/StringUtils.hpp>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

namespace cppJify::generator::jni {

    /**
     * @brief Generates a complete JNI function.
     *
     * Combines the JNI function signature and body to create a complete JNI function definition.
     * Uses the provided function name, package name, and class name to construct the JNI function.
     *
     * @tparam ReturnType The return type of the C++ function.
     * @tparam Params The parameter types of the C++ function.
     *
     * @param cppFunctionName The C++ function name to map.
     * @param jFunctionName The corresponding Java function name.
     * @param jPackage The package name in Java.
     * @param jClassname The class name in Java.
     * @return The complete JNI function as a formatted string.
     */
    template <class CallingType, class ReturnType, class... Params>
    std::string generateFunction(const std::string &cppFunctionName,
                                 const std::string &jFunctionName,
                                 const std::string &jPackage,
                                 const std::string &jClassname) {
        // signature
        const std::string functionSignature =
            generateFunctionSignature<CallingType, ReturnType, Params...>(cppFunctionName, jFunctionName, jPackage, jClassname);

        // body
        const std::string functionBody = generateFunctionBody<CallingType, ReturnType, Params...>(cppFunctionName);

        // result
        return functionSignature + functionBody;
    }

    //////////////////////////////////////// FUNCTION SIGNATURE ////////////////////////////////////////
    //////////////////////////////////////// FUNCTION SIGNATURE ////////////////////////////////////////
    //////////////////////////////////////// FUNCTION SIGNATURE ////////////////////////////////////////
    /**
     * @brief Generates a JNI function signature.
     *
     * Uses the C++ function signature to create a JNI function signature with mangled name and parameter list.
     *
     * @tparam ReturnType The return type of the C++ function.
     * @tparam Params The parameter types of the C++ function.
     *
     * @param cppFunctionName The original C++ function name.
     * @param jFunctionName The desired Java function name.
     * @param jPackage The package name in Java.
     * @param jClassname The class name in Java.
     * @return The formatted JNI function signature.
     */
    template <class CallingType, class ReturnType, class... Params>
    std::string generateFunctionSignature(const std::string &cppFunctionName,
                                          const std::string &jFunctionName,
                                          const std::string &jPackage,
                                          const std::string &jClassname) {
        // Get the JNI-Function signature blueprint
        std::string result = blueprints::jni::JIFY_BLUEPRINT_JNI_FUNC_SIGNATURE;
        result = utils::replaceAll(result, blueprints::jni::placeholder::IS_STATIC,
                                   std::is_same_v<CallingType, std::nullptr_t> ? "jclass clazz," : "jobject callingObject");

        // Replace the return type
        const std::string jniReturnType = mapper::JifyMapper<ReturnType>::JniType();
        result = utils::replaceAll(result, blueprints::jni::placeholder::RETURN_TYPE, jniReturnType);

        // Generate the function mangled name
        const std::string jniMangledname = generateMangledJNIFuncname<Params...>(jFunctionName, jPackage, jClassname);
        result = utils::replaceAll(result, blueprints::jni::placeholder::MANGLED_NAME, jniMangledname);

        // Generate parameter list
        const std::string parameterlist = generateParamList<LANGUAGE_TYPE::JNI, true, Params...>();
        result = utils::replaceAll(result, blueprints::jni::placeholder::PARAMS, parameterlist);

        return result;
    }

    /**
     * @brief Generates the mangled JNI function name.
     *
     * @tparam Params The parameter types for the function.
     *
     * @param jFunctionName The Java function name.
     * @param jPackage The package name in Java.
     * @param jClassname The class name in Java.
     *
     * @return The mangled JNI function name.
     */
    template <class... Params>
    std::string generateMangledJNIFuncname(const std::string &jFunctionName, const std::string &jPackage, const std::string &jClassname) {
        // JNI-Conventions
        const std::string jniStylePackage = utils::replaceAll(jPackage, ".", "_");
        std::ostringstream mangledJFuncname;
        mangledJFuncname << "Java_" << jniStylePackage << "_" << jClassname << "_" << jFunctionName;

        // generate mangled function Params according to JNI-conventions
        std::ostringstream mangledJFuncnameParams;
        ((mangledJFuncnameParams << generateMangledJNIParams<Params>()), ...);

        const std::string paramStr = mangledJFuncnameParams.str();
        if (!paramStr.empty()) { mangledJFuncname << "__" << paramStr; }

        return mangledJFuncname.str();
    }

    /**
     * @brief Generates JNI mangled names for parameters.
     * @link https://docs.oracle.com/javase/1.5.0/docs/guide/jni/spec/design.html
     *
     * @tparam Param The parameter type.
     * @return The JNI mangled representation of the parameter.
     */
    template <class Param>
    std::string generateMangledJNIParams() {
        const std::unordered_map<std::string, std::string> primitiveJToJNITypeMap = {{"void", "V"}, {"boolean", "Z"}, {"byte", "B"},
                                                                                     {"char", "C"}, {"short", "S"},   {"int", "I"},
                                                                                     {"long", "J"}, {"float", "F"},   {"double", "D"}};

        std::string mangledName = mapper::JifyMapper<Param>::JavaType();
        auto it = primitiveJToJNITypeMap.find(mangledName);

        // Check for primitive type
        if (it != primitiveJToJNITypeMap.end()) { return it->second; }

        // handle objects
        mangledName = "L" + utils::replaceAll(mangledName, ".", "_");
        mangledName.append("_2");

        // TODO handle arrays...
        return mangledName;
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
     *
     * @return The generated body of the JNI function as a formatted string.
     */
    template <class CallingType, class ReturnType, class... Params>
    std::string generateFunctionBody(const std::string &cppFunctionName) {
        std::string result = blueprints::jni::JIFY_BLUEPRINT_JNI_FUNC_BODY;

        // JNI -> C++ conversions for all parameter
        int counter = 0;
        std::stringstream paramConversions;
        ((paramConversions << generateParamCConversion<Params>(counter++)), ...);
        result = utils::replaceAll(result, blueprints::jni::placeholder::C_CONVERSIONS, paramConversions.str());

        // determine whether the function is static or not...
        const bool isStatic = std::is_same_v<CallingType, std::nullptr_t>;
        result = utils::replaceAll(result, blueprints::jni::placeholder::C_CALLING_TYPE_CONVERSION,
                                   isStatic ? "" : "// Convert the calling type asap...");

        // generate return value of the passed returntype
        const std::string functionCall = (isStatic ? "" : "nativeCallingObject.") + cppFunctionName + "(" +
                                         generateParamList<LANGUAGE_TYPE::C, false, Params...>() + ")";
        result =
            utils::replaceAll(result, blueprints::jni::placeholder::C_RETURN_RESULT, mapper::JifyMapper<ReturnType>::Out(functionCall));

        return result;
    }

    /**
     * @brief Generates JNI to C++ parameter conversion code.
     *
     * This function generates the necessary C++ code to convert a JNI parameter to a native C++ type.
     *
     * @tparam Param The parameter type to be converted.
     * @param counter The index of the parameter.
     * @return A string containing the C++ conversion code for the given JNI parameter.
     */
    template <class Param>
    std::string generateParamCConversion(const int &counter) {
        FunctionParam param = generateParam<Param>(counter);
        std::ostringstream result;

        const std::string cVar = mapper::JifyMapper<Param>::CType() + " " + param.c_paramName;
        result << mapper::JifyMapper<Param>::In(cVar, param.paramName, std::to_string(counter)) << "\n\t\t";

        return result.str();
    }

    //////////////////////////////////////// FUNCTION BODY ////////////////////////////////////////
    //////////////////////////////////////// FUNCTION BODY ////////////////////////////////////////
    //////////////////////////////////////// FUNCTION BODY ////////////////////////////////////////

}  // namespace cppJify::generator::jni
