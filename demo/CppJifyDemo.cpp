#pragma once

#include <cppJify/CppJify.hpp>
#include <cppJify/CppJifyConstants.hpp>
#include "delme.cpp"

class Foo {
    public:
        Foo() = default;
};
Foo getFoo(Foo foo) { return Foo(); }

int main() {
    try {
        using namespace cppJify;

        CppJify jify("nvd", "Tree");
        jify.bindFunction(&a, JIFY_RAW(a), "a");
        jify.include("C:/Dev_Avdiji/Development/CppJify/demo/delme.cpp");

        jify.generateApi();

    } catch (std::exception &e) { std::cout << e.what() << std::endl; }
    return 0;
}