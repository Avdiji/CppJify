#include <cppJify/blueprints/JavaBlueprints.hpp>
#include <cppJify/blueprints/JniBlueprints.hpp>
#include <cppJify/blueprints/Placeholder.hpp>
#include <cppJify/mapper/classes/StaticClassMapper.hpp>
#include <cppJify/utils/FilesystemUtils.hpp>
#include <cppJify/utils/StringUtils.hpp>
#include <set>
#include <sstream>
#include <string>
#include <utility>

namespace cppJify::mapper::classes {

    StaticClassMapper::StaticClassMapper(std::string jpackage, std::string jclassname)
        : _jPackage(std::move(jpackage)), _jClassname(std::move(jclassname)) {}

    //////////////////////////////////////// JNI ////////////////////////////////////////
    //////////////////////////////////////// JNI ////////////////////////////////////////
    //////////////////////////////////////// JNI ////////////////////////////////////////
    void StaticClassMapper::addCIncludes(const std::set<std::string>& cincludes) { _cincludes.insert(cincludes.begin(), cincludes.end()); }
    
    void StaticClassMapper::appendCustomJniCode(const std::string& customJniCode) { _customJniCode.insert(customJniCode); }
    void StaticClassMapper::appendCustomJniCode(const std::set<std::string>& customJniCode) {
        _customJniCode.insert(customJniCode.begin(), customJniCode.end());
    }

    std::string StaticClassMapper::getAllJniFunctions() const {
        std::ostringstream result;
        for (const auto& mappedFunction : _mappedFunctionsJNI) { result << mappedFunction << "\n"; }
        return result.str();
    }

    std::string StaticClassMapper::getAllIncludes() const {
        std::ostringstream result;
        for (const auto& include : _cincludes) { result << "#include " << include << "\n"; }
        return result.str();
    }

    std::string StaticClassMapper::getAllCustomJniCode() const {
        std::ostringstream result;
        for (const auto& customCode : _customJniCode) { result << customCode << "\n"; }
        return result.str();
    }

    void StaticClassMapper::generateJniFile(const std::string& outputBase) const {
        // create output directory
        const std::string packagePath = "/" + utils::replaceAll(_jPackage, ".", "/");
        const std::string fullPath = outputBase + packagePath;

        // create filename
        const std::string filename = _jClassname + ".cppjify" + ".cpp";

        // compose all mapped jni-functions
        std::string content = blueprints::jni::JIFY_BLUEPRINT_JNI_BASE;
        content = utils::replaceAll(content, blueprints::placeholder::jni::PRAGMAONCE, "#pragma once");
        content = utils::replaceAll(content, blueprints::placeholder::jni::INCLUDES, getAllIncludes());
        content = utils::replaceAll(content, blueprints::placeholder::CUSTOM_CODE, getAllCustomJniCode());
        content = utils::replaceAll(content, blueprints::placeholder::BODY, getAllJniFunctions());

        // create the jni file for the class
        utils::createFile(filename, content, fullPath);
    }
    //////////////////////////////////////// JNI ////////////////////////////////////////
    //////////////////////////////////////// JNI ////////////////////////////////////////
    //////////////////////////////////////// JNI ////////////////////////////////////////

    //////////////////////////////////////// JAVA ////////////////////////////////////////
    //////////////////////////////////////// JAVA ////////////////////////////////////////
    //////////////////////////////////////// JAVA ////////////////////////////////////////
    void StaticClassMapper::addJImports(const std::set<std::string>& jimports) { _jimports.insert(jimports.begin(), jimports.end()); }

    void StaticClassMapper::appendCustomJavaCode(const std::string& customJavaCode) { _customJavaCode.insert(customJavaCode); }
    void StaticClassMapper::appendCustomJavaCode(const std::set<std::string>& customJavaCode) {
        _customJavaCode.insert(customJavaCode.begin(), customJavaCode.end());
    }

    std::string StaticClassMapper::getAllJavaFunctions() const {
        std::ostringstream result;
        for (const auto& mappedFunction : _mappedFunctionsJava) { result << mappedFunction << "\n"; }
        return result.str();
    }

    std::string StaticClassMapper::getAllImports() const {
        std::ostringstream result;
        for (const auto& import : _jimports) { result << "import " << import << ";\n"; }
        return result.str();
    }

    std::string StaticClassMapper::getAllCustomJavaCode() const {
        std::ostringstream result;
        for (const auto& customCode : _customJavaCode) { result << customCode << "\n"; }
        return result.str();
    }

    void StaticClassMapper::generateJavaFile(const std::string& outputBase) const {
        // create output directory
        const std::string packagePath = "/" + utils::replaceAll(_jPackage, ".", "/");
        const std::string fullPath = outputBase + packagePath;

        // create filename
        const std::string filename = _jClassname + ".java" + "";

        // compose all mapped jni-functions
        std::string content = blueprints::JIFY_BLUEPRINT_JAVA_STATIC_CLASS;

        content = utils::replaceAll(content, blueprints::placeholder::CUSTOM_CODE, getAllCustomJavaCode());
        content = utils::replaceAll(content, blueprints::placeholder::java::PACKAGE, _jPackage);
        content = utils::replaceAll(content, blueprints::placeholder::java::IMPORTS, getAllImports());
        content = utils::replaceAll(content, blueprints::placeholder::CLASSNAME, _jClassname);
        content = utils::replaceAll(content, blueprints::placeholder::CLASSBODY, getAllJavaFunctions());

        utils::createFile(filename, content, fullPath);
    }
    //////////////////////////////////////// JAVA ////////////////////////////////////////
    //////////////////////////////////////// JAVA ////////////////////////////////////////
    //////////////////////////////////////// JAVA ////////////////////////////////////////

}  // namespace cppJify::mapper::classes