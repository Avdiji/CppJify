#pragma once

#include <cppJify/jbinder/JavaBinder.hpp>

namespace cppJify::jbinder {

    JavaBinder::JavaBinder(const std::string& p_packageName, const std::string& p_className)
        : _packageName(p_packageName), _className(p_className) {}

    bool JavaBinder::operator<(const JavaBinder& other) {
        const std::string thisClassPath(_packageName + "." + _className);
        const std::string otherClassPath(other._packageName + "." + other._className);

        return thisClassPath < otherClassPath;
    }
}  // namespace cppJify::jbinder