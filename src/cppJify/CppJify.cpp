#pragma once
#include <cppJify/CppJify.hpp>

namespace cppJify {

    std::shared_ptr<mapper::classes::StaticClassMapper> CppJify::createUtilsClass(const std::string& jPackage,
                                                                                  const std::string& jClassname) {
        auto mapper = std::make_shared<mapper::classes::StaticClassMapper>(jPackage, jClassname);
        _staticClassMapper.insert(mapper);
        return mapper;
    }

    void CppJify::generateJavaApi(const std::string& outputPath) const{
        for(const auto& staticClass : _staticClassMapper) {
            staticClass->generateJniFile(outputPath);
            staticClass->generateJavaFile(outputPath);
        }
    }

}  // namespace cppJify