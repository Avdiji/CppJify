#include <cppJify/CppJify.hpp>
#include <cppJify/blueprints/JavaBlueprints.hpp>
#include <cppJify/mapper/classes/StaticClassMapper.hpp>
#include <cppJify/utils/FilesystemUtils.hpp>
#include <memory>
#include <string>

namespace cppJify {

    std::shared_ptr<mapper::classes::StaticClassMapper> CppJify::mapUtilsClass(const std::string& jPackage, const std::string& jClassname) {
        auto mapper = std::make_shared<mapper::classes::StaticClassMapper>(jPackage, jClassname);
        _classMapper.insert(mapper);
        return mapper;
    }

    void CppJify::generateJavaApi(const std::string& outputPath) const {
        // create java base
        const std::string baseDir = outputPath + "/internal";
        utils::ensureDirectory(baseDir);
        utils::createFile("CppJifyBase.java", blueprints::JIFY_BLUEPRINT_JAVA_CPPJIFY_BASE_INTERFACE, baseDir);

        // generate api files
        for (const auto& staticClass : _classMapper) {
            staticClass->generateJniFile(outputPath);
            staticClass->generateJavaFile(outputPath);
        }
    }

}  // namespace cppJify