#pragma once

#include <cppJify/CppJifyConstants.hpp>
#include <cppJify/composer/JniComposer.hpp>
#include <cppJify/jbinder/JavaBinder.hpp>
#include <cppJify/mapper/JifyDefaultMapper.hpp>
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

            // TODO this can be used to create methods (given that you enable passing JavaComposers)
            template <class ReturnType, class... Params>
            const CppJify& bindFunction(ReturnType (*func)(Params...),
                                        const std::string& p_actualFuncName,
                                        const std::string& p_desiredFuncName) {
                const std::string cReturnType = mapper::JifyDefaultMapper<ReturnType>::CType();
                const std::string jniReturnType = mapper::JifyDefaultMapper<ReturnType>::JniType();

                std::vector<std::string> cParamTypes;
                std::vector<std::string> jniParamTypes;
                std::string jniIn;
                std::string jniOut;
                std::string funcPlaceholder(p_actualFuncName + "(");

                int count = 0;
                ((cParamTypes.push_back(mapper::JifyDefaultMapper<Params>::CType()),
                  jniParamTypes.push_back(mapper::JifyDefaultMapper<Params>::JniType()),

                  jniIn.append(mapper::JifyDefaultMapper<Params>::In(count)),
                  funcPlaceholder.append(JIFY_PLACEHOLDER_C_ARG).append(std::to_string(count++) + ", ")),
                 ...);

                if (!funcPlaceholder.empty()) { funcPlaceholder.erase(funcPlaceholder.length() - 2, 2); }
                funcPlaceholder.append(")");

                // JNI-Binding
                _jniApi.composeFuncDecl(p_desiredFuncName, jniReturnType, jniParamTypes);
                _jniApi.composeFuncBody(jniIn, mapper::JifyDefaultMapper<ReturnType>::Out(funcPlaceholder));

                // Java-Base Class Binding
                // bind method as well as native method.
                // _javaBase.bindMethod()

                return *this;
            }

        private:
            composer::JniComposer _jniApi;
            jbinder::JavaBinder _javaBase;
            // std::set<jbinder::JavaClassBinder> _javaClasses;
    };

}  // namespace cppJify