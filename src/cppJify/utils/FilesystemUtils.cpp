#include <cppJify/utils/FilesystemUtils.hpp>
#include <exception>
#include <filesystem>
#include <fstream>
#include <stdexcept>
#include <string>

namespace cppJify::utils
{

    void createFile(const std::string& filename, const std::string& content, const std::string& filepath)
    {
        try
        {
            ensureDirectory(filepath);

            const std::filesystem::path outputFilepath = std::filesystem::path(filepath) / filename;
            std::ofstream outputFile(outputFilepath);

            if (!outputFile) { throw std::runtime_error("Unable to create file: " + outputFilepath.string()); }

            outputFile << content;
        }
        catch (const std::exception& ex)
        {
            throw std::runtime_error("Error creating file '" + filename + "': " + ex.what());
        }
    }

    void ensureDirectory(const std::string& path)
    {
        try
        {
            const std::filesystem::path dirPath(path);
            if (!std::filesystem::exists(dirPath)) { std::filesystem::create_directories(dirPath); }
        }
        catch (const std::filesystem::filesystem_error& fse)
        {
            throw std::runtime_error("Unable to create directory at path '" + path + "': " + fse.what());
        }
    }

}  // namespace cppJify::utils
