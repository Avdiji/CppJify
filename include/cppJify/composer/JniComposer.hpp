#pragma once

#include <cppJify/mapper/BaseMapper.hpp>
#include <set>
#include <sstream>
#include <string>
#include <vector>

namespace cppJify::composer {

    class JniComposer {
        public:
            explicit JniComposer(const std::string& p_javaPackage, const std::string& p_javaClassName);

            void include(const std::string& p_cInclude) { _includes.insert(p_cInclude); }

            void finalize();

            void generateJniApi();

            template <class ReturnType, class... Params>
            void composeFunction(const std::string& p_actualFuncName, const std::string& p_desiredFuncName) {
                // fetch JNI-Return type
                const std::string jniReturnType(mapper::JifyMapper<ReturnType>::JniType());
                std::string jniParameterlist;

                // generate Java <-> C++ code.
                std::string jniIn;
                std::string jniOut(p_actualFuncName + "(");

                int count = 0;
                ((
                     // Generate parameterlist for function declaration
                     jniParameterlist.append(", ")
                         .append(mapper::JifyMapper<Params>::JniType())
                         .append(" ")
                         .append(JIFY_PLACEHOLDER_J_ARG)
                         .append(std::to_string(count)),

                     // Generate Java -> C++ mapping
                     jniIn.append(mapper::JifyMapper<Params>::In(count)),

                     // Prepare C++ -> Java mapping
                     jniOut.append(JIFY_PLACEHOLDER_C_ARG).append(std::to_string(count++) + ", ")),
                 ...);

                // finalize out
                if (count > 0) { jniOut.erase(jniOut.length() - 2, 2); }
                jniOut.append(")");
                jniOut = mapper::JifyMapper<ReturnType>::Out(jniOut);

                // compose jni function
                composeFuncDecl(p_desiredFuncName, jniReturnType, jniParameterlist);
                composeFuncBody(jniIn, jniOut);
            }

            [[nodiscard]] std::ostringstream& getOss();

            [[nodiscard]] const std::string& getClassname() const;

        private:
            void composeFuncDecl(const std::string& p_funcName,
                                 const std::string& p_jniReturnType,
                                 const std::string& p_jniParameterlist);

            void composeFuncBody(const std::string& p_in, const std::string& p_out);

        private:
            const std::string _javaPackage;
            const std::string _javaClassName;
            std::ostringstream _oss;
            std::set<std::string> _functionDeclarations;
            std::set<std::string> _includes;
    };

}  // namespace cppJify::composer