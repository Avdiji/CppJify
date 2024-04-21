#pragma once

#include <cppJify/CppJify.hpp>
#include <fstream>

namespace cppJify {

    CppJify::CppJify(const std::string& p_basePackage, const std::string& p_baseClassname)
        : _jniApi(p_basePackage, p_baseClassname) {
        include("jni.h");
        _jniApi.getOss() << "extern \"C\" {\n";
    }

    void CppJify::include(const std::string& p_cIncludePath) { _includes.insert(p_cIncludePath); }

    void CppJify::finalize() {
        std::ostringstream ossTmp(_jniApi.getOss().str() + "\n}\n");

        std::string includesStr;
        for (const std::string& include : _includes) { includesStr.append("#include \"" + include + "\"\n"); }
        includesStr.append("\n");

        ossTmp.str(includesStr + ossTmp.str());
        _jniApi.getOss().str(ossTmp.str());
    }

    void CppJify::generateApi() {
        finalize();
        std::ofstream JniOutFile(_jniApi.getClassname() + ".cpp");
        JniOutFile << _jniApi.getOss().str();

        JniOutFile.close();
    }

}  // namespace cppJify