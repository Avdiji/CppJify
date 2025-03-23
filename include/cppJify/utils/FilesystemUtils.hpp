#pragma once

#include <string>

namespace cppJify::utils {

    /**
     * @brief Creates a file at the specified location with the given content.
     *
     * This function ensures that the specified directory exists before attempting to create the file.
     * If the directory does not exist, it will be created automatically.
     * The function will then open the file and write the specified content to it.
     *
     * If an error occurs during directory creation or file writing, the function throws a
     * standard runtime exception with a descriptive error message.
     *
     * @param filename The name of the file to be created.
     * @param content The content that will be written to the file.
     * @param filepath The path of the directory where the file will be located.
     *
     * @throws std::runtime_error if directory creation or file writing fails.
     */
    void createFile(const std::string& filename, const std::string& content, const std::string& filepath);

    /**
     * @brief Ensures the existence of a directory at the given path.
     *
     * This function checks whether the specified directory exists and, if not, creates it.
     * It guarantees that the directory path will be available for file operations afterward.
     *
     * @param path The path of the directory to be created or verified.
     *
     * @throws std::runtime_error if the directory creation fails.
     */
    void ensureDirectory(const std::string& path);
}  // namespace cppJify::utils