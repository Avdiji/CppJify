#pragma once

#include <cppJify/utils/FilesystemUtils.hpp>
#include <cppJify/utils/StringUtils.hpp>
#include <fstream>

namespace cppJify::utils {

    void createFile(const std::string& p_package, const std::string& p_filename, const std::string& p_content) {
        std::string packageStr(p_package);
        utils::replaceAll(packageStr, ".", "/");

        try {
            std::filesystem::create_directories(p_package);
        } catch (const std::filesystem::filesystem_error& fse) {
            std::throw_with_nested(std::runtime_error("Unable to create directory at given Path: " + p_package));
        }

        std::ofstream outputFile(p_package + "/" + p_filename);
        if (outputFile) {
            outputFile << p_content;
        } else {
            throw std::runtime_error("Unable to create File: " + p_filename);
        }

        outputFile.close();
    }

}  // namespace cppJify::utils