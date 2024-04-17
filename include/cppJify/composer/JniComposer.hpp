#pragma once

#include <set>
#include <sstream>
#include <string>
#include <vector>

namespace cppJify::composer {

    class JniComposer {
        public:
            explicit JniComposer(const std::string& p_javaPackage, const std::string& p_javaClassName);

            void composeFuncDecl(const std::string& p_funcName,
                                 const std::string& p_jniReturnType,
                                 const std::vector<std::string>& p_jniParamTypes,
                                 const bool use_jclass = true);

            void composeFuncBody(const std::string& p_in, const std::string& p_out);

        private:
            const std::string _javaPackage;
            const std::string _javaClassName;
            std::ostringstream _oss;

            std::set<std::string> _functionDeclarations;
            std::set<std::string> _includes;
    };

}  // namespace cppJify::composer