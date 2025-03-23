#pragma once

#include <cppJify/generator/JniGenerator.hpp>
#include <iostream>
#include <set>
#include <string>

namespace cppJify::mapper::classes {

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
            explicit StaticClassMapper(const std::string& jpackage, const std::string& jclassname);

            /**
             * @brief Set the java-classes to be imported.
             *
             * @param jincludes A set of all the java-imports for this class.
             */
            void addJIncludes(const std::set<std::string>& jincludes);

            /**
             * @brief Set the java-classes to be imported.
             *
             * @param jincludes A set of all the java-imports for this class.
             */
            void addJIncludes(std::set<std::string>&& jincludes);

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
            const StaticClassMapper& mapFunction(ReturnType (*func)(Params...),
                                                 const std::string& cppFunctionName,
                                                 const std::string& jFunctionName) {
                const std::string mappedStaticFunction =
                    generator::jni::generateFunction<ReturnType, Params...>(cppFunctionName, jFunctionName, _jPackage, _jClassname);
                _mappedFunctions.insert(mappedStaticFunction);
                return *this;
            }

        private:
            const std::string _jPackage;
            const std::string _jClassname;

            std::set<std::string> _jincludes;
            std::set<std::string> _mappedFunctions;
    };

}  // namespace cppJify::mapper::classes