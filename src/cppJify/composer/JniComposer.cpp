#pragma once

#include <cppJify/CppJifyConstants.hpp>
#include <cppJify/composer/JniComposer.hpp>
#include <cppJify/utils/StringUtils.hpp>

namespace cppJify::composer {

    JniComposer::JniComposer(const std::string& p_javaPackage, const std::string& p_javaClassName)
        : _javaPackage(p_javaPackage), _javaClassName(p_javaClassName) {}

    void JniComposer::composeFuncDecl(const std::string& p_funcName,
                                      const std::string& p_jniReturnType,
                                      const std::vector<std::string>& p_jniParamTypes,
                                      const bool use_jclass) {
        // Deconstruct the javaPackage to be usable in JNI
        std::string jniPackageString = _javaPackage;
        utils::replaceAll(jniPackageString, ".", "_");

        // Constructor a fitting JNI-Function name
        std::string jniFuncName;
        jniFuncName.append(JIFY_JAVA_PREFIX)
            .append(jniPackageString)
            .append("_")
            .append(_javaClassName)
            .append("_")
            .append(p_funcName)
            .append(JIFY_JNI_SUFFIX);

        // Construct the Parameterlist
        std::string paramList("JNIEnv* env, ");
        paramList.append(use_jclass ? "jclass cls" : "jobject obj");
        for (size_t i = 0; i < p_jniParamTypes.size(); ++i) {
            paramList.append(", ")
                .append(p_jniParamTypes.at(i))
                .append(" ")
                .append(JIFY_PLACEHOLDER_J_ARG)
                .append(std::to_string(i));
        }

        // Compose function Signature
        std::string functionDecl;
        functionDecl.append("JNIEXPORT ")
            .append(p_jniReturnType)
            .append(" JNICALL ")
            .append(jniFuncName)
            .append("(")
            .append(paramList)
            .append(")");

        // Check duplicate functionss
        if (_functionDeclarations.count(functionDecl) > 0) {
            throw std::runtime_error("Duplicate function definition!");
        }

        _oss << functionDecl;
        _functionDeclarations.insert(functionDecl);
    }

    void JniComposer::composeFuncBody(const std::string& p_in, const std::string& p_out) {
        // TODO check, whether to build destructor
        std::string funcBody;
        funcBody.append("{\n").append(p_in).append(p_out).append("\n}\n\n");
        _oss << funcBody;
    }

    std::ostringstream& JniComposer::getOss() { return _oss; }

    const std::string& JniComposer::getClassname() const {
        return _javaClassName;
    }

}  // namespace cppJify::composer