#pragma once

#include <cppJify/CppJifyConstants.hpp>
#include <cppJify/composer/JniComposer.hpp>
#include <cppJify/utils/FilesystemUtils.hpp>
#include <cppJify/utils/StringUtils.hpp>

namespace cppJify::composer {

    JniComposer::JniComposer(const std::string& p_javaPackage, const std::string& p_javaClassName)
        : _javaPackage(p_javaPackage), _javaClassName(p_javaClassName) {
        include("jni.h");
        _oss << "\nextern \"C\" {\n";
    }

    void JniComposer::generateJniApi() {
        finalize();
        utils::createFile(_javaPackage, "JNI" + _javaClassName + ".cxx", _oss.str());
    }

    void JniComposer::finalize() {
        _oss << "\n}\n";
        const std::string tmpJniSrc = _oss.str();

        _oss.str("");
        for (const std::string& include : _includes) { _oss << "#include \"" << include << "\"\n"; }
        _oss.str(_oss.str() + tmpJniSrc);
    }

    void JniComposer::composeFuncDecl(const std::string& p_funcName,
                                      const std::string& p_jniReturnType,
                                      const std::string& p_jniParameterlist) {
        // Compose function Name (TODO proper suffix)
        std::string functionName;
        functionName.append(JIFY_JAVA_PREFIX)
            .append(_javaPackage)
            .append(".")
            .append(_javaClassName)
            .append(".")
            .append(p_funcName);
        utils::replaceAll(functionName, ".", "_");

        // Compose JNI function declaration
        std::string functionDeclaration;
        functionDeclaration.append("JNIEXPORT ")
            .append(p_jniReturnType)
            .append(" JNICALL ")
            .append(functionName)
            .append("(JNIEnv *env, jclass cls")
            .append(p_jniParameterlist)
            .append(")");

        // check for duplicates
        if (_functionDeclarations.count(functionDeclaration) > 0) {
            throw std::runtime_error("Duplicate function definition!");
        }

        _oss << functionDeclaration;
    }

    void JniComposer::composeFuncBody(const std::string& p_in, const std::string& p_out) {
        // TODO check, whether to build destructor
        std::string funcBody;
        funcBody.append("{\n").append(p_in).append(p_out).append("\n}\n\n");
        _oss << funcBody;
    }

    std::ostringstream& JniComposer::getOss() { return _oss; }

    const std::string& JniComposer::getClassname() const { return _javaClassName; }

}  // namespace cppJify::composer