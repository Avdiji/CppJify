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
        const std::string filename = _jClassname + ".jni" + ".cpp";

        // compose all mapped jni-functions
        std::string content = generator::jni::blueprints::JIFY_BLUEPRINT_JNI_BASE;
        content = utils::replaceAll(content, generator::jni::placeholder::INCLUDES, getAllIncludes());
        content = utils::replaceAll(content, generator::jni::placeholder::CODE, getAllJniFunctions());

        utils::createFile(filename, content, fullPath);
    }
}  // namespace cppJify::mapper::classes