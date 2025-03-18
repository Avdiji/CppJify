#pragma once

#include <filesystem>

namespace cppJify {

    /**
     * @brief Class Handles the mapping of C++ code to Java via JNI.
     *
     * @author Fitor Avdiji
     */
    class CppJify {
        public:
            /**
             * @brief Default Constructor
             */
            explicit CppJify();

            /**
             * @brief Method triggers the Api generation, which includes:CppJify
             * 
             * 1. The generation of the underlying JNI-code.
             * 
             * 2. The generation of the actual resulting Java-Api.
             * 
             * @param outputPath The outputPath of the generated files.
             */
            const void generateJavaApi(const std::filesystem::path& outputPath);
        private:
            

    };
}  // namespace cppJify