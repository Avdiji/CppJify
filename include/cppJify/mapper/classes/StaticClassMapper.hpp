#pragma once

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
            explicit StaticClassMapper(const std::string& jpackage, const std::string& jclassname);

            /**
             * @brief Set the java-classes to be imported.
             *
             * @param cincludes A set of all the c-includes for this class.
             */
            void addCIncludes(const std::set<std::string>& cincludes);

            /**
             * @brief Set the java-classes to be imported.
             *
             * @param cincludes A set of all the c-includes for this class.
             */
            void addCIncludes(std::set<std::string>&& cincludes);

            /**
             * Generate the corresponding JNI-File for this class.
             * The output path resembles the given java-package structure.
             *
             * @param outputBase The base-directory of the output.
             */
            void generateJniFile(const std::string& outputBase) const;

            /**
             * Generate a string of all jni-functions to be mapped for this class.
             *
             * @return A string of all mapped Jni-functions.
             */
            const std::string getAllJniFunctions() const;

            /**
             * Generate a string of all jni-includes for this class.
             *
             * @return A string of all includes.
             */
            const std::string getAllIncludes() const;

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
                                           const std::string& jFunctionName)
            {
                const std::string mappedStaticFunction =
                    generator::jni::generateFunction<ReturnType, Params...>(cppFunctionName, jFunctionName, _jPackage, _jClassname);
                _mappedFunctionsJNI.insert(mappedStaticFunction);

                // TODO same for java

                return *this;
            }

        private:
            const std::string _jPackage;
            const std::string _jClassname;

            std::set<std::string> _cincludes;
            std::set<std::string> _mappedFunctionsJNI;
    };

}  // namespace cppJify::mapper::classes