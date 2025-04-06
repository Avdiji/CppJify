#pragma once

#include <cppJify/CppJify.hpp>
#include <cppJify/mapper/BasicMapper.hpp>
#include <iostream>
#include <regex>
#include <vector>

namespace foo {

    int getInt(int a) { return a + 1; }

}

int main()
{
    
    cppJify::CppJify jify;
    auto cls = jify.mapUtilsClass("Demopackage", "Democlass");

    cls->addCIncludes({JIFY_RAW("../../../../../../demo/basics/SimpleDatatypes.cpp")});
    cls->mapStaticFunction(foo::getInt, JIFY_RAW(foo::getInt), "getInt");

    jify.generateJavaApi("base");
    return 0;
}