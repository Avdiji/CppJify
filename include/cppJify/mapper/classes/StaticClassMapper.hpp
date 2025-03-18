#pragma once

#include <set>
#include <string>

namespace cppJify::mapper::classes {

    /**
     * @brief Mapper for Utility-classes, used to map non-member functions only.
     *
     * @author Fitor Avdiji
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
             * @brief Getter
             * @return The package the java-class belongs to.
             */
            const std::string& getJPackage() const;

            /**
             * @brief Getter
             * @return The name of the java-class.
             */
            const std::string& getJClassName() const;

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
                // TODO: finish this...
                return *this;
            }

        private:
            const std::string _jpackage;
            const std::string _jclassname;

            std::set<std::string> _jincludes;
    };

}  // namespace cppJify::mapper::classes