#pragma once

#include <cppJify/generator/JavaGenerator.hpp>
#include <cppJify/generator/JniGenerator.hpp>
#include <filesystem>
#include <iostream>
#include <set>
#include <string>

namespace cppJify {

    const inline std::string CPP_JIFY_BASE_JNI_FILENAME = "CppJifyBase.cppjify.cpp";

    namespace mapper::classes {

        /**
         * @brief Mapper for Utility-classes, used to map non-member functions only.
         *
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
                virtual void addCIncludes(const std::set<std::string>& cincludes);

                /**
                 * @brief Append Customized JNI code, which will be added on top of the generated file.
                 * @param customJniCode The custom code as a collection of strings.
                 */
                virtual void appendCustomJniCode(const std::set<std::string>& customJniCode);

                /**
                 * @brief Append customized JNI code, which will be added on top of the generated file.
                 * @param customJniCode The custom code as a string.
                 */
                virtual void appendCustomJniCode(const std::string& customJniCode);

                /**
                 * @brief Set Java-classes to be imported.
                 *
                 * @param A set of all java-imports for this class.
                 */
                virtual void addJImports(const std::set<std::string>& jimports);

                /**
                 * Generate the corresponding JNI-File for this class.
                 * The output path resembles the given java-package structure.
                 *
                 * @param outputBase The base-directory of the output.
                 */
                virtual void generateJniFile(const std::string& outputBase) const;

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

            private:
                /**
                 * Generate a string of all jni-functions to be mapped for this class.
                 *
                 * @return A string of all mapped Jni-functions.
                 */
                virtual std::string getAllJniFunctions() const;

                /**
                 * Generate a string of all java-functions to be mapped for this class.
                 *
                 * @return A string of all mapped java-functions.
                 */
                virtual std::string getAllJavaFunctions() const;

                /**
                 * Generate a string of all jni-includes for this class.
                 *
                 * @return A string of all includes.
                 */
                virtual std::string getAllIncludes() const;

                /**
                 * Generate a string of all java-imports for this class.
                 *
                 * @return A string of all imports.
                 */
                virtual std::string getAllImports() const;

                /**
                 * Generate a string of all custom-jni-code for this class.
                 *
                 * @return A string of all the custom JNI-code.
                 */
                virtual std::string getAllCustomJniCode() const;

            protected:
                const std::string _jPackage;
                const std::string _jClassname;
                std::set<std::string> _mappedFunctionsJNI = {};

            private:
                std::set<std::string> _cincludes = {};
                std::set<std::string> _customJniCode = {};

                std::set<std::string> _jimports = {};
                std::set<std::string> _mappedFunctionsJava = {};
        };

    }  // namespace mapper::classes
}  // namespace cppJify