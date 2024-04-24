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

            void generateApiFiles();

            void include(const std::string& p_cIncludePath);

            template <class ReturnType, class... Params>
            const CppJify& bindFunction(ReturnType (*func)(Params...),
                                        const std::string& p_actualFuncName,
                                        const std::string& p_desiredFuncName) {
                
                _jniApi.composeFunction<ReturnType, Params...>(p_actualFuncName, p_desiredFuncName);

                return *this;
            }

        private:
            composer::JniComposer _jniApi;
    };

}  // namespace cppJify