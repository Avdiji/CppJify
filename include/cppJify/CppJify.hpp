#pragma once

#include <cppJify/mapper/classes/StaticClassMapper.hpp>
#include <filesystem>
#include <memory>
#include <set>

namespace cppJify {

    /**
     * @brief Class Handles the mapping of C++ code to Java via JNI.
     *
     * This class is responsible for generating Java APIs from C++ code using the Java Native Interface (JNI).
     * It automates the creation of JNI code and the resulting Java API while managing C++ object lifetimes.
     *
     * @details The CppJify class helps bridge C++ code with Java by providing utility functions to create JNI-compatible
     * classes and methods..
     *
     * @note The generated Java API and JNI code are output to the specified file path.
     *
     * @version 1.0
     * @author Fitor Avdiji
     */
    class CppJify {
        public:
            /**
             * @brief Default Constructor
             */
            explicit CppJify() = default;

            /**
             * @brief Triggers the generation of the Java API and underlying JNI code.
             *
             * The API generation process consists of:
             * 1. Generating the JNI code that connects native C++ functions to Java.
             * 2. Generating the Java API code that exposes these functions to Java applications.
             *
             * @param outputPath The filesystem path where the generated files will be stored.
             * @return void
             */
            void generateJavaApi(const std::string& outputPath) const;

            /**
             * @brief Creates a Java utility class to map non-member C++ functions.
             *
             * This method is designed to create utility classes that represent non-member functions
             * or functions in namespaces that do not belong to specific C++ classes.
             *
             * @return A shared pointer to the created StaticClassMapper.
             */
            std::shared_ptr<mapper::classes::StaticClassMapper> createUtilsClass(const std::string& jPackage,
                                                                                 const std::string& jClassname);

        private:
            std::set<std::shared_ptr<mapper::classes::StaticClassMapper>> _staticClassMapper;
    };
}  // namespace cppJify