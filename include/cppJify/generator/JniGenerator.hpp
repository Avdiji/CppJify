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
     * @brief Generates a complete JNI allocation function.
     *
     * @tparam CallingType The type to be allocated.
     * @tparam Params The parameter types of the called constructor.
     *
     * @param jPackage The package name in Java.
     * @param jClassname The class name in Java.
     * @return The complete JNI function as a formatted string.
     */
    template <class CallingType, class... Params>
    const std::string generateAllocFunction(const std::string &jPackage, const std::string &jClassname) {
        std::string result = blueprints::jni::JIFY_BLUEPRINT_JNI_ALLOC_FUNC;

        // Signature...
        const std::string mangledJNIFuncname = generateMangledJNIFuncname<Params...>("allocate", jPackage, jClassname);
        const std::string signatureParamList = generateParamList<LANGUAGE_TYPE::JNI, true, Params...>();

        result = utils::replaceAll(result, blueprints::placeholder::MANGLED_FUNCNAME, mangledJNIFuncname);
        result = utils::replaceAll(result, blueprints::placeholder::PARAMS, signatureParamList.size() > 0 ? ", " + signatureParamList : "");

        // Body...
        // JNI -> C++ conversions for all parameter
        int counter = 0;
        std::stringstream paramConversions;
        ((paramConversions << generateParamCConversion<Params>(counter++)), ...);

        result = utils::replaceAll(result, blueprints::placeholder::jni::CONVERSIONS_IN, paramConversions.str());
        result = utils::replaceAll(result, blueprints::placeholder::CALLING_TYPE, mapper::JifyMapper<CallingType>::CType());
        result =
            utils::replaceAll(result, blueprints::placeholder::PARAMS_NO_TYPE, generateParamList<LANGUAGE_TYPE::C, false, Params...>());

        return result;
    }

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
        std::string functionSignature;
        std::string functionBody;

        if (std::is_same_v<CallingType, std::nullptr_t>) {
            functionSignature = generateStaticFunctionSignature<ReturnType, Params...>(jFunctionName, jPackage, jClassname);
            functionBody = generateStaticFunctionBody<ReturnType, Params...>(cppFunctionName);
        } else {
            functionSignature = generateFunctionSignature<CallingType, ReturnType, Params...>(jFunctionName, jPackage, jClassname);
            functionBody = generateFunctionBody<CallingType, ReturnType, Params...>(cppFunctionName);
        }

        // result
        return functionSignature + functionBody;
    }

    //////////////////////////////////////// FUNCTION SIGNATURE ////////////////////////////////////////
    //////////////////////////////////////// FUNCTION SIGNATURE ////////////////////////////////////////
    //////////////////////////////////////// FUNCTION SIGNATURE ////////////////////////////////////////

    template <class ReturnType, class... Params>
    std::string generateStaticFunctionSignature(const std::string &jFunctionName,
                                                const std::string &jPackage,
                                                const std::string &jClassname) {
        // pick the function signature blueprint
        std::string result = blueprints::jni::JIFY_BLUEPRINT_JNI_FUNC_SIGNATURE;

        // add jclass to params since the function is static
        result = utils::replaceAll(result, blueprints::placeholder::STATIC_SPECIFIER, "jclass clazz");

        // properly replace the return type
        const std::string jniReturnType = mapper::JifyMapper<ReturnType>::JniType();
        result = utils::replaceAll(result, blueprints::placeholder::RETURN_TYPE, jniReturnType);

        // generate the mangled name
        const std::string jniMangledname = generateMangledJNIFuncname<Params...>(jFunctionName, jPackage, jClassname);
        result = utils::replaceAll(result, blueprints::placeholder::MANGLED_FUNCNAME, jniMangledname);

        // set the parameterlist
        const std::string paramList = generateParamList<LANGUAGE_TYPE::JNI, true, Params...>();
        result = utils::replaceAll(result, blueprints::placeholder::PARAMS, paramList.size() > 0 ? ", " + paramList : paramList);

        return result;
    }

    /**
     * @brief Generates a JNI function signature.
     *
     * Uses the C++ function signature to create a JNI function signature with mangled name and parameter list.
     *
     * @tparam ReturnType The return type of the C++ function.
     * @tparam Params The parameter types of the C++ function.
     *
     * @param jFunctionName The desired Java function name.
     * @param jPackage The package name in Java.
     * @param jClassname The class name in Java.
     * @return The formatted JNI function signature.
     */
    template <class CallingType, class ReturnType, class... Params>
    std::string generateFunctionSignature(const std::string &jFunctionName, const std::string &jPackage, const std::string &jClassname) {
        // pick the function signature blueprint
        std::string result = blueprints::jni::JIFY_BLUEPRINT_JNI_FUNC_SIGNATURE;

        // add jobject calling object to params since the function is not static
        int paramCounter = 0;
        const FunctionParam callingParam = generateParam<CallingType>(paramCounter++);
        const std::string callingParamStr = (callingParam.jni_paramType + " " + callingParam.jni_paramName);
        result = utils::replaceAll(result, blueprints::placeholder::STATIC_SPECIFIER, callingParamStr);

        // Replace the return type
        const std::string jniReturnType = mapper::JifyMapper<ReturnType>::JniType();
        result = utils::replaceAll(result, blueprints::placeholder::RETURN_TYPE, jniReturnType);

        // Generate the function mangled name
        const std::string jniMangledname = generateMangledJNIFuncname<Params...>(jFunctionName, jPackage, jClassname);
        result = utils::replaceAll(result, blueprints::placeholder::MANGLED_FUNCNAME, jniMangledname);

        // Generate parameter list
        const std::string paramList = generateParamList<LANGUAGE_TYPE::JNI, true, Params...>(paramCounter);
        result = utils::replaceAll(result, blueprints::placeholder::PARAMS, paramList.size() > 0 ? ", " + paramList : paramList);

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

    template <class ReturnType, class... Params>
    std::string generateStaticFunctionBody(const std::string &cppFunctionName) {
        std::string result = blueprints::jni::JIFY_BLUEPRINT_JNI_STATIC_FUNC_BODY;

        // JNI -> C++ conversions for all parameter
        int counter = 0;
        std::stringstream paramConversions;
        ((paramConversions << generateParamCConversion<Params>(counter++)), ...);
        result = utils::replaceAll(result, blueprints::placeholder::jni::CONVERSIONS_IN, paramConversions.str());

        // generate return value of the passed returntype
        const std::string functionCall = cppFunctionName + "(" + generateParamList<LANGUAGE_TYPE::C, false, Params...>() + ")";
        result = utils::replaceAll(result, blueprints::placeholder::RETURN_VALUE, mapper::JifyMapper<ReturnType>::Out(functionCall));

        return result;
    }

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

        // JNI -> C++ conversion for the calling type
        int paramCounter = 0;
        const FunctionParam callingParam = generateParam<CallingType>(paramCounter);
        const std::string callingTypeConversion = generateParamCConversion<CallingType>(paramCounter++);
        result = utils::replaceAll(result, blueprints::placeholder::jni::CALLING_TYPE_CONVERSION_IN, callingTypeConversion);

        // generate return value of the passed returntype
        const std::string functionCall = callingParam.c_paramName + "." + cppFunctionName + "(" +
                                         generateParamList<LANGUAGE_TYPE::C, false, Params...>(paramCounter) + ")";

        // JNI -> C++ conversions for all other parameter
        std::stringstream paramConversions;
        ((paramConversions << generateParamCConversion<Params>(paramCounter++)), ...);
        result = utils::replaceAll(result, blueprints::placeholder::jni::CONVERSIONS_IN, paramConversions.str());

        result = utils::replaceAll(result, blueprints::placeholder::RETURN_VALUE, mapper::JifyMapper<ReturnType>::Out(functionCall));
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

        const std::string cVar = param.c_paramName;
        result << mapper::JifyMapper<Param>::In(cVar, param.jni_paramName, std::to_string(counter));

        return result.str();
    }

    //////////////////////////////////////// FUNCTION BODY ////////////////////////////////////////
    //////////////////////////////////////// FUNCTION BODY ////////////////////////////////////////
    //////////////////////////////////////// FUNCTION BODY ////////////////////////////////////////

}  // namespace cppJify::generator::jni
