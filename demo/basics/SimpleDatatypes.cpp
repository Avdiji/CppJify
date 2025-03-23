#pragma once

#include <cppJify/CppJify.hpp>
#include <cppJify/mapper/BasicMapper.hpp>
#include <iostream>
#include <vector>

namespace abc {
    int fitor(int a, int b, int c) { return 1; }
}  // namespace abc

int main() {
    cppJify::CppJify cppJify;

    auto utilsClassMapper = cppJify.createUtilsClass("", "");
    utilsClassMapper->addJIncludes({});
    utilsClassMapper->mapFunction(abc::fitor, JIFY_RAW(abc::fitor), "jFitor")
        .mapFunction(abc::fitor, JIFY_RAW(abc::fitor), "jFitor")
        .mapFunction(abc::fitor, JIFY_RAW(abc::fitor), "jFitor")

        ;

    // auto classmapper = cppJify::mapper::classes::StaticClassMapper("com.myPackage", "myClass");
    // classmapper.mapFunction(fitor, "fitor", "fitor");
    return 0;
}
