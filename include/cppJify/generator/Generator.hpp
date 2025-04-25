#pragma once

#include <cppJify/helper/Helper.hpp>
#include <string>
#include <vector>

namespace cppJify::generator {

    /**
     * @brief Represents a JNI function parameter.
     *
     * A JNI function parameter consists of:
     *  - `paramType`: The JNI type (e.g., `jint`, `jstring`, etc.).
     *  - `paramName`: The parameter name (e.g., `arg0`, `arg1`).
     *  - `c_paramType`: The corresponding C++ type.
     *  - `c_paramName`: The C++ version of the parameter name.
     */
    struct FunctionParam {
            const std::string jni_paramType;
            const std::string jni_paramName;

            const std::string c_paramType;
            const std::string c_paramName;

            const std::string j_paramType;
            const std::string j_paramName;
    };

    /**
     * @brief Enum representing different programming language types.
     *
     * This enum is used to specify the target language or environment
     * for code generation, function mapping, or integration.
     *
     * The possible language types are:
     * - JAVA: Represents the Java programming language.
     * - JNI: Represents the Java Native Interface (JNI) layer.
     * - C: Represents the C programming language.
     *
     */
    enum LANGUAGE_TYPE { JAVA = 0, JNI = 1, C = 2 };

    /**
     * @brief Generates a list of JNI function parameters.
     *
     * Creates a list of JNI function parameters, including their types and names.
     *
     * @tparam Params The parameter types of the function.
     * @param counterStart The starting id of the paramname [DEFAULT = 0]
     *
     * @return A vector of JniParam structures.
     */
    template <class... Params>
    const std::vector<FunctionParam> generateParams(const int& counterStart = 0) {
        std::vector<FunctionParam> params;
        int counter = counterStart;
        (params.push_back(generateParam<Params, helper::is_unique_ptr<std::decay_t<Params>>::value>(counter++)), ...);
        return params;
    }

    /**
     * @brief Generates a single JniParam instance.
     *
     * Creates a JniParam instance containing the JNI and C++ type information for a parameter.
     *
     * @tparam Param The parameter type.
     * @param counter The index of the parameter.
     * @return A JniParam instance representing the parameter.
     */
    template <class Param, bool Move = false>
    const FunctionParam generateParam(const int& counter) {
        // JNI
        const std::string paramName = "arg" + std::to_string(counter);
        const std::string paramType = mapper::JifyMapper<Param>::JniType();

        // C
        std::string c_paramName = "c" + paramName;
        if (Move) { c_paramName = "std::move(" + c_paramName + ")"; }
        const std::string c_paramType = mapper::JifyMapper<Param>::CType();

        // Java
        const std::string j_paramName = paramName;
        const std::string j_paramType = mapper::JifyMapper<Param>::JavaType();

        return {paramType, paramName, c_paramType, c_paramName, j_paramType, j_paramName};
    }

    /**
     * @brief Generates a formatted list of function parameters.
     *
     * Generates a string representation of the parameter list, including types and names,
     * formatted according to JNI or C++ conventions.
     *
     * @tparam JNI_STYLE Whether to use JNI style naming.
     * @tparam WITH_TYPE Whether to include the type in the parameter list.
     * @tparam Params The parameter types of the function.
     *
     * @param counterStart The starting id of the param-names [DEFAULT = 0]
     *
     * @return A formatted parameter list as a string.
     */
    template <LANGUAGE_TYPE TYPE, bool WITH_TYPE, class... Params>
    const std::string generateParamList(const int& counterStart = 0) {
        const std::vector<FunctionParam> params = generateParams<Params...>(counterStart);

        // Generate parameter list
        std::ostringstream parameterlist;

        for (size_t i = 0; i < params.size(); ++i) {
            if (i > 0) { parameterlist << ", "; }

            const FunctionParam param = params[i];
            std::string paramName;
            std::string paramType;

            // clang-format off
            if(TYPE == LANGUAGE_TYPE::JNI) {
                paramName = param.jni_paramName;
                paramType = (WITH_TYPE ? param.jni_paramType + " ": "");

            } else if(TYPE == LANGUAGE_TYPE::C) {
                paramName = param.c_paramName;
                paramType = (WITH_TYPE ? param.c_paramType + " ": "");

            } else if (TYPE== LANGUAGE_TYPE::JAVA) {
                paramName = param.j_paramName;
                paramType = (WITH_TYPE ? param.j_paramType + " ": "");
            }
            // clang-format on

            parameterlist << paramType << paramName;
        }

        return parameterlist.str();
    }

}  // namespace cppJify::generator