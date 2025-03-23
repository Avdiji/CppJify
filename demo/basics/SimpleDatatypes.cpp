#pragma once

#include <cppJify/mapper/BasicMapper.hpp>
#include <cppJify/CppJify.hpp>
#include <iostream>
#include <vector>

int fitor(int a, int b, int c)
{
    return 1;
}


int main()
{
    cppJify::CppJify cppJify;

    cppJify.createUtilsClass("", "");

    // auto classmapper = cppJify::mapper::classes::StaticClassMapper("com.myPackage", "myClass");
    // classmapper.mapFunction(fitor, "fitor", "fitor");
    return 0;
}
