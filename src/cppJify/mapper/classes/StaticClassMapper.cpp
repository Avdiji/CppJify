#pragma once

#include <cppJify/generator/Placeholder.hpp>
#include <cppJify/generator/blueprints/JniBlueprints.hpp>
#include <cppJify/mapper/classes/StaticClassMapper.hpp>
#include <cppJify/utils/FilesystemUtils.hpp>
#include <cppJify/utils/StringUtils.hpp>
#include <sstream>

namespace cppJify::mapper::classes
{

    StaticClassMapper::StaticClassMapper(const std::string& jpackage, const std::string& jclassname)
        : _jPackage(jpackage), _jClassname(jclassname)
    {
    }

    //////////////////////////////////////// JNI ////////////////////////////////////////
    //////////////////////////////////////// JNI ////////////////////////////////////////
    //////////////////////////////////////// JNI ////////////////////////////////////////
    void StaticClassMapper::addCIncludes(const std::set<std::string>& cincludes) { _cincludes.insert(cincludes.begin(), cincludes.end()); }
    void StaticClassMapper::addCIncludes(std::set<std::string>&& cincludes) { _cincludes.merge(cincludes); }

    const std::string StaticClassMapper::getAllJniFunctions() const
    {
        std::ostringstream result;
        for (const auto& mappedFunction : _mappedFunctionsJNI) { result << mappedFunction << "\n"; }
        return result.str();
    }

    const std::string StaticClassMapper::getAllIncludes() const
    {
        std::ostringstream result;
        for (const auto& include : _cincludes) { result << "#include " << include << "\n"; }
        return result.str();
    }

    void StaticClassMapper::generateJniFile(const std::string& outputBase) const
    {
        // create output directory
        const std::string packagePath = "/" + utils::replaceAll(_jPackage, ".", "/");
        const std::string fullPath = outputBase + packagePath;

        // create filename
        const std::string filename = _jClassname + ".cppjify" + ".cpp";

        // compose all mapped jni-functions
        std::string content = generator::jni::blueprints::JIFY_BLUEPRINT_JNI_BASE;
        content = utils::replaceAll(content, generator::jni::placeholder::INCLUDES, getAllIncludes());
        content = utils::replaceAll(content, generator::jni::placeholder::CODE, getAllJniFunctions());

        utils::createFile(filename, content, fullPath);
    }
    //////////////////////////////////////// JNI ////////////////////////////////////////
    //////////////////////////////////////// JNI ////////////////////////////////////////
    //////////////////////////////////////// JNI ////////////////////////////////////////

    //////////////////////////////////////// JAVA ////////////////////////////////////////
    //////////////////////////////////////// JAVA ////////////////////////////////////////
    //////////////////////////////////////// JAVA ////////////////////////////////////////
    void StaticClassMapper::addJImports(const std::set<std::string>& jimports) { _jimports.insert(jimports.begin(), jimports.end()); }
    void StaticClassMapper::addJImports(std::set<std::string>&& jimports) { _jimports.merge(jimports); }

    const std::string StaticClassMapper::getAllJavaFunctions() const
    {
        std::ostringstream result;
        for (const auto& mappedFunction : _mappedFunctionsJava) { result << mappedFunction << "\n"; }
        return result.str();
    }

    const std::string StaticClassMapper::getAllImports() const
    {
        std::ostringstream result;
        for (const auto& import : _jimports) { result << "import " << import << ";\n"; }
        return result.str();
    }

    void StaticClassMapper::generateJavaFile(const std::string& outputBase) const
    {
        // create output directory
        const std::string packagePath = "/" + utils::replaceAll(_jPackage, ".", "/");
        const std::string fullPath = outputBase + packagePath;

        // create filename
        const std::string filename = _jClassname + ".java" + "";

        // compose all mapped jni-functions
        std::string content = generator::java::blueprints::JIFY_BLUEPRINT_JAVA_STATIC_CLASS_BASE;

        content = utils::replaceAll(content, generator::java::placeholder::PACKAGE, _jPackage);
        content = utils::replaceAll(content, generator::java::placeholder::IMPORTS, getAllImports());
        content = utils::replaceAll(content, generator::java::placeholder::CLASS_NAME, _jClassname);
        content = utils::replaceAll(content, generator::java::placeholder::CLASS_BODY, getAllJavaFunctions());

        utils::createFile(filename, content, fullPath);
    }
    //////////////////////////////////////// JAVA ////////////////////////////////////////
    //////////////////////////////////////// JAVA ////////////////////////////////////////
    //////////////////////////////////////// JAVA ////////////////////////////////////////

}  // namespace cppJify::mapper::classes