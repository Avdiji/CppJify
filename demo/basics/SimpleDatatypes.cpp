#pragma once

#include <iostream>
#include <cppJify/mapper/JifyMapper.hpp>
#include <vector>

int main() {

    auto ctype = cppJify::mapper::JifyMapper<std::vector<std::string>>::CType();
    // auto jtype = cppJify::mapper::JifyMapper<std::vector<std::string>>::JavaType();



    std::cout << ctype << std::endl;
    // std::cout << jtype << std::endl;
    return 0;
}

