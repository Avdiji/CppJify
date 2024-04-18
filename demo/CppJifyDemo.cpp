#pragma once

#include <cppJify/CppJify.hpp>
#include <cppJify/CppJifyConstants.hpp>
#include <iostream>

void a(int a, char b, float c) {}

class Foo {
    public:
        Foo() = default;
};
Foo getFoo(Foo foo) { return Foo(); }

int main() {
    try {
        using namespace cppJify;

        CppJify jify("nvd", "Tree");
        jify.bindFunction(&getFoo, JIFY_RAW(getFoo), "getFoo");

    } catch (std::exception &e) { std::cout << e.what() << std::endl; }
    return 0;
}