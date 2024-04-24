#pragma once

#include <filesystem>

namespace cppJify::utils {

    void createFile(const std::string& p_package, const std::string& p_filename, const std::string& p_content);
}  // namespace cppJify::utils