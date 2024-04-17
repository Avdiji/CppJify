#pragma once

#include <cppJify/CppJify.hpp>
#include <cppJify/CppJifyConstants.hpp>
#include <iostream>

void a(int a, char b, float c) {}

int main() {
    try{
    using namespace cppJify;

    CppJify jify("nvd", "Tree");
    jify.bindFunction(&a, JIFY_RAW(a), "a");
    // cppyJify::composer::JniComposer jnicomposer;
    // jnicomposer.finalize();
    }catch(std::exception &e) {
        std::cout << e.what() << std::endl;
    }
    return 0;
}