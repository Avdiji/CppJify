#pragma once

#include <cppJify/CppJify.hpp>
#include <cppJify/mapper/BasicMapper.hpp>
#include <iostream>
#include <regex>
#include <vector>

namespace abc
{
    int fitor(int a, int b, int c) { return 1; }
    int fitor(int a) { return 2; }
}  // namespace abc

int main()
{
    cppJify::CppJify cppJify;


    auto utilsClassMapper = cppJify.createUtilsClass("com.myPackage", "MyClass");
    utilsClassMapper->addCIncludes({JIFY_RAW("MyInclude"), JIFY_RAW("MyInclude1"), JIFY_RAW("MyInclude2"), JIFY_RAW("MyInclude3")});
    utilsClassMapper->mapNonMemberFunc(JIFY_OVERLOADED_FUNC(int, abc::fitor, int, int, int), JIFY_RAW(abc::fitor), "jFitor");

    auto utilsClassMapper2 = cppJify.createUtilsClass("com.myPackage2", "MyClass2");
    utilsClassMapper2->addCIncludes({JIFY_RAW("MyInclude"), JIFY_RAW("MyInclude1"), JIFY_RAW("MyInclude2"), JIFY_RAW("MyInclude3")});
    utilsClassMapper2->mapNonMemberFunc(JIFY_OVERLOADED_FUNC(int, abc::fitor, int, int, int), JIFY_RAW(abc::fitor), "jFitor");

    cppJify.generateJavaApi("myOutput");

    return 0;
}