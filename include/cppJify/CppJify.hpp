#pragma once

#include <string>
#include <filesystem>

namespace cppJify {

    /**
     * Class Handles the mapping of C++ code to Java via JNI.
     *
     * @author Fitor Avdiji
     */
    class CppJify {
        public:
            /**
             * Constructor
             *
             * @param basePackage The Java-Package of the base-class of the generated Java Code.
             * @param baseClassname The Classname of the Java-class, which contains all functions, which are not bound
             * to a class.
             */
            explicit CppJify(const std::string& basePackage, const std::string& baseClassname);

            /**
             * @brief Method maps non-member Cpp-functions to Java.
             * 
             * @tparam ReturnType The return type of the Cpp function.
             * @tparam Params The parameter of the Cpp function.
             * 
             * @param cppFunctionName The actual name of the cpp function to be mapped.
             * @param jFunctionName The name of the generated java function.
             */
            template <class ReturnType, class... Params>
            const CppJify& mapFunction(ReturnType (*func)(Params...),
                                       const std::string& cppFunctionName,
                                       const std::string& jFunctionName);


            /**
             * @brief Method triggers the Api generation, which includes:CppJify
             * 1. The generation of the underlying JNI-code.
             * 2. The generation of the actual resulting Java-Api.
             * 
             * @param outputPath The outputPath of the generated files.
             */
            const void generateJavaApi(const std::filesystem::path& outputPath);
        private:
            

    };
}  // namespace cppJify