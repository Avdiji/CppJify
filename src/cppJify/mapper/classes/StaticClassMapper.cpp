#pragma once
#include <cppJify/mapper/classes/StaticClassMapper.hpp>

namespace cppJify::mapper::classes {
    
    // Constructor
    StaticClassMapper::StaticClassMapper(const std::string& jpackage, const std::string& jclassname)
        : _jPackage(jpackage), _jClassname(jclassname) {}

    // addJIncludes copy/move
    void StaticClassMapper::addJIncludes(const std::set<std::string>& jincludes) {
        _jincludes.insert(jincludes.begin(), jincludes.end());
    }
    void StaticClassMapper::addJIncludes(std::set<std::string>&& jincludes) { _jincludes.merge(jincludes); }

}  // namespace cppJify::mapper::classes