#pragma once

#include <cppJify/generator/JavaGenerator.hpp>
#include <cppJify/generator/JniGenerator.hpp>
#include <filesystem>
#include <iostream>
#include <set>
#include <string>

namespace cppJify::mapper::classes
{

    /**
     * @brief Mapper for Utility-classes, used to map non-member functions only.
     *
     */
    class StaticClassMapper
    {
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
             * @brief Set Cpp files to be included.
             *
             * @param cincludes A set of all the c-includes for this class.
             */
            void addCIncludes(std::set<std::string>&& cincludes);

            /**
             * @brief Set Java-classes to be imported.
             *
             * @param A set of all java-imports for this class.
             */
            void addJImports(const std::set<std::string>& jimports);

            /**
             * @brief Set Java-classes to be imported.
             *
             * @param A set of all java-imports for this class.
             */
            void addJImports(std::set<std::string>&& jimports);

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
            void generateJavaFile(const std::string& outputBase) const;

            /**
             * Generate a string of all jni-functions to be mapped for this class.
             *
             * @return A string of all mapped Jni-functions.
             */
            std::string getAllJniFunctions() const;

            /**
             * Generate a string of all java-functions to be mapped for this class.
             *
             * @return A string of all mapped java-functions.
             */
            std::string getAllJavaFunctions() const;

            /**
             * Generate a string of all jni-includes for this class.
             *
             * @return A string of all includes.
             */
            std::string getAllIncludes() const;

            /**
             * Generate a string of all java-imports for this class.
             *
             * @return A string of all imports.
             */
            std::string getAllImports() const;

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
            StaticClassMapper& mapNonMemberFunc(ReturnType (*func)(Params...),
                                                const std::string& cppFunctionName,
                                                const std::string& jFunctionName,
                                                const std::string& accessSpecifier = "public")
            {
                // create JNI-Func
                _mappedFunctionsJNI.insert(
                    generator::jni::generateFunction<true, ReturnType, Params...>(cppFunctionName, jFunctionName, _jPackage, _jClassname));

                // create Java-Func
                _mappedFunctionsJava.insert(
                    generator::java::generateFunctionSignature<true, true, ReturnType, Params...>(jFunctionName, accessSpecifier));

                return *this;
            }

        private:
            const std::string _jPackage;
            const std::string _jClassname;

            std::set<std::string> _cincludes = {};
            std::set<std::string> _mappedFunctionsJNI = {};

            std::set<std::string> _jimports = {};
            std::set<std::string> _mappedFunctionsJava = {};
    };

}  // namespace cppJify::mapper::classes