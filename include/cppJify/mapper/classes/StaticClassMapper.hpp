#pragma once

#include <boost/callable_traits.hpp>
#include <cppJify/generator/JavaGenerator.hpp>
#include <cppJify/generator/JniGenerator.hpp>
#include <filesystem>
#include <iostream>
#include <set>
#include <string>
#include <utility>
namespace cppJify {

    const inline std::string CPP_JIFY_BASE_JNI_FILENAME = "CppJifyBase.cppjify.cpp";

    namespace mapper::classes {
        /**
         * @brief Mapper for Utility-classes, used to map non-member and/or static functions only.
         */
        class StaticClassMapper {
            public:
                /**
                 * @brief Constructor
                 *
                 * @param jpackage The package of the generated java-class.
                 * @param jclassname The name of the generated java-class.
                 */
                explicit StaticClassMapper(std::string jpackage, std::string jclassname);

                /**
                 * @brief Set Cpp files to be included.
                 *
                 * @param cincludes A set of all the c-includes for this class.
                 */
                void addCIncludes(const std::set<std::string>& cincludes);

                /**
                 * @brief Append Customized JNI code, which will be added on top of the generated file.
                 * @param customJniCode The custom code as a collection of strings.
                 */
                void appendCustomJniCode(const std::set<std::string>& customJniCode);

                /**
                 * @brief Append customized JNI code, which will be added on top of the generated file.
                 * @param customJniCode The custom code as a string.
                 */
                void appendCustomJniCode(const std::string& customJniCode);

                /**
                 * @brief Append Customized Java code, which will be added on top of the generated file.
                 * @param customJavaCode The custom code as a collection of strings.
                 */
                void appendCustomJavaCode(const std::set<std::string>& customJavaCode);

                /**
                 * @brief Append customized Java code, which will be added on top of the generated file.
                 * @param customJavaCode The custom code as a string.
                 */
                void appendCustomJavaCode(const std::string& customJavaCode);

                /**
                 * @brief Set Java-classes to be imported.
                 *
                 * @param A set of all java-imports for this class.
                 */
                void addJImports(const std::set<std::string>& jimports);

                /**
                 * Generate the corresponding JNI-File for this class.
                 * The output path resembles the given java-package structure.
                 *
                 * @param outputBase The base-directory of the output.
                 */
                void generateJniFile(const std::string& outputBase) const;

                /**
                 * Generate the corresponding Java-File for this class.
                 * The output path resembles the given java-package structure.
                 *
                 * @param outputBase The base-directory of the output.
                 */
                virtual void generateJavaFile(const std::string& outputBase) const;

                /**
                 * @brief Method maps non-member Cpp-functions to Java.
                 *
                 * @tparam ReturnType The return type of the Cpp function.
                 * @tparam Params The parameter of the Cpp function.
                 *
                 * @param cppFunctionName The actual name of the cpp function to be mapped.
                 * @param jFunctionName The name of the generated java function.
                 * @param accessSpecifier The access specifier of the generated java function [DEFAULT = public].
                 */
                template <class ReturnType, class... Params>
                StaticClassMapper& mapStaticFunction(ReturnType (*func)(Params...),
                                                     const std::string& cppFunctionName,
                                                     const std::string& jFunctionName,
                                                     const std::string& accessSpecifier = "public") {
                    // create JNI-Func
                    _mappedFunctionsJNI.insert(generator::jni::generateFunction<std::nullptr_t, ReturnType, Params...>(
                        cppFunctionName, jFunctionName, _jPackage, _jClassname));

                    // create Java-Func
                    _mappedFunctionsJava.insert(
                        generator::java::generateFunctionSignature<true, true, ReturnType, Params...>(jFunctionName, accessSpecifier));

                    return *this;
                }

                /**
                 * @brief Map non-member functions with a LAMBDA.
                 * @note This function is only meant to be used with a lambda and the JIFY_LAMBDA macro, using it otherwhise will result in
                 * undefined behaviour.
                 *
                 * @tparam Callable The lambda.
                 *
                 * @param cppFunctionName The actual name of the cpp function to be mapped.
                 * @param jFunctionName The name of the generated java function.
                 * @param accessSpecifier The access specifier of the generated java function.
                 *
                 */
                template <class Callable>
                StaticClassMapper& mapStaticFunction(const std::pair<Callable, std::string>& callable,
                                                     const std::string& cppFunctionName,
                                                     const std::string& jFunctionName,
                                                     const std::string& accessSpecifier = "public") {
                    // Extract the corresponding FunctionTypes
                    using FunctionType = boost::callable_traits::function_type_t<std::decay_t<Callable>>;
                    using ReturnType = boost::callable_traits::return_type_t<FunctionType>;
                    using FunctionPointerType = std::add_pointer_t<FunctionType>;

                    // Build the Function from the passed lambda (in order to be able to use it in JNI)
                    // clang-format off
                    const std::string funcWithoutCapture = utils::replaceAll(callable.second, "[]", "");
                    const std::string lambdaFunction = JIFY_FMT(JIFY_RAW(\n\tstatic {} {} {}), JifyMapper<ReturnType>::CType(), cppFunctionName, funcWithoutCapture);
                    // clang-format on

                    appendCustomJniCode(lambdaFunction);

                    return mapStaticFunction(FunctionPointerType(nullptr), cppFunctionName, jFunctionName, accessSpecifier);
                }

            protected:
                /**
                 * Generate a string of all java-imports for this class.
                 *
                 * @return A string of all imports.
                 */
                std::string getAllImports() const;

                /**
                 * Generate a string of all java-functions to be mapped for this class.
                 *
                 * @return A string of all mapped java-functions.
                 */
                std::string getAllJavaFunctions() const;

                /**
                 * Generate a string of all custom-java-code for this class.
                 *
                 * @return A string of all the custom Java-code.
                 */
                std::string getAllCustomJavaCode() const;

            private:
                /**
                 * Generate a string of all jni-functions to be mapped for this class.
                 *
                 * @return A string of all mapped Jni-functions.
                 */
                std::string getAllJniFunctions() const;

                /**
                 * Generate a string of all jni-includes for this class.
                 *
                 * @return A string of all includes.
                 */
                std::string getAllIncludes() const;

                /**
                 * Generate a string of all custom-jni-code for this class.
                 *
                 * @return A string of all the custom JNI-code.
                 */
                std::string getAllCustomJniCode() const;

            protected:
                const std::string _jPackage;
                const std::string _jClassname;

                std::set<std::string> _mappedFunctionsJNI = {};
                std::set<std::string> _mappedFunctionsJava = {};

            private:
                std::set<std::string> _cincludes = {};
                std::set<std::string> _jimports = {};

                std::set<std::string> _customJniCode = {};
                std::set<std::string> _customJavaCode = {};
        };

    }  // namespace mapper::classes
}  // namespace cppJify