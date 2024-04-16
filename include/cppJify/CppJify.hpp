#pragma once

#include <cppJify/composer/IComposer.hpp>
#include <cppJify/mapper/JifyDefaultMapper.hpp>
#include <set>
#include <string>
namespace cppJify {

    /**
     * Class Handles the conversion of C++ code to Java.
     */
    class CppJify {
        public:
            /**
             * TODO:
             *      - createApi()
             *      - includeC()
             *      - finalize()
             *      - bindFunction should use
             */

            template <class ReturnType, class... Params>
            const CppJify& bindFunction(ReturnType (*func)(Params...),
                                        const std::string& p_actualFuncName,
                                        const std::string& p_desiredFuncName);

            template <class Classtype> // Create BaseClass of Classbinder, move Classbinder into its own file
            class ClassBinder {
                public:
                    /**
                     * TODO:
                     *      - bindMethod
                     *      - createJavaFile
                     *      - finalize
                     *      - bindStaticMethod
                     */

                    explicit ClassBinder(const std::string& p_className);

                    ClassBinder& package(const std::string& p_package);
                    ClassBinder& import(const std::string& p_import);

                private:
                    const std::string _className;
                    const std::string _package;
                    const composer::IComposer _classComposer;
            };

        private:
            const std::string _defaultClassName;
            const composer::IComposer _jniComposer;

    };

}  // namespace cppJify