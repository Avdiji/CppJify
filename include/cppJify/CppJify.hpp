#pragma once

#include <cppJify/CppJifyConstants.hpp>
#include <cppJify/composer/JniComposer.hpp>
#include <cppJify/mapper/BaseMapper.hpp>
#include <set>
#include <string>
#include <vector>

namespace cppJify {

    /**
     * Class Handles the conversion of C++ code to Java.
     */
    class CppJify {
        public:
            explicit CppJify(const std::string& p_basePackage, const std::string& p_baseClassname);

            void generateApi();

            void finalize();

            void include(const std::string& p_cIncludePath);


            // TODO this can be used to create methods (given that you enable passing JavaComposers)
            template <class ReturnType, class... Params>
            const CppJify& bindFunction(ReturnType (*func)(Params...),
                                        const std::string& p_actualFuncName,
                                        const std::string& p_desiredFuncName) {
                // Return Types
                const std::string cReturnType = mapper::JifyMapper<ReturnType>::CType();
                const std::string jniReturnType = mapper::JifyMapper<ReturnType>::JniType();

                // Parameter types
                std::vector<std::string> cParamTypes;
                std::vector<std::string> jniParamTypes;

                // JNI in and out
                std::string jniIn;
                std::string jniOut;
                std::string funcPlaceholder(p_actualFuncName + "(");

                // collect corresponding parameter types
                int count = 0;
                ((cParamTypes.push_back(mapper::JifyMapper<Params>::CType()),
                  jniParamTypes.push_back(mapper::JifyMapper<Params>::JniType()),

                  jniIn.append(mapper::JifyMapper<Params>::In(count)),
                  funcPlaceholder.append(JIFY_PLACEHOLDER_C_ARG).append(std::to_string(count++) + ", ")),
                 ...);

                // compose the string replacing the $func placeholder
                if (!jniParamTypes.empty()) { funcPlaceholder.erase(funcPlaceholder.length() - 2, 2); }
                funcPlaceholder.append(")");

                // JNI-Binding - create Templated instead of fetching everything in here
                _jniApi.composeFuncDecl(p_desiredFuncName, jniReturnType, jniParamTypes);
                _jniApi.composeFuncBody(jniIn, mapper::JifyMapper<ReturnType>::Out(funcPlaceholder));

                return *this;
            }

        private:
            composer::JniComposer _jniApi;
            std::set<std::string> _includes;
    };

}  // namespace cppJify