#pragma once

#include <cppJify/mapper/JifyMapper.hpp>

namespace cppJify::mapper::classes {

    template <class T>
    class InstanceClassMapper : public StaticClassMapper {
        public:
            /**
             * Constructor
             * 
             * Also responsible for registering T as a mapped class...
             */
            explicit InstanceClassMapper(const std::string& jpackage, const std::string& jclassname)
                : StaticClassMapper(std::move(jpackage), std::move(jclassname)) {
                registeredClasses[JifyMapper<T>::CType()] = jpackage + "." + jclassname;
            }

            /**
             * Generate the corresponding JNI-File for this class.
             * The output path resembles the given java-package structure.
             *
             * @param outputBase The base-directory of the output.
             */
            void generateJavaFile(const std::string& outputBase) const override {
                // TODO implement this...
            }

            /**
             * @brief Method maps member Cpp-functions to Java.
             *
             * @tparam ReturnType The return type of the Cpp function.
             * @tparam Params The parameter of the Cpp function.
             *
             * @param cppFunctionName The actual name of the cpp function to be mapped.
             * @param jFunctionName The name of the generated java function.
             */
            template <class ReturnType, class... Params>
            InstanceClassMapper<T>& mapFunction(ReturnType (T::*func)(Params...),
                                                const std::string& cppFunctionName,
                                                const std::string& jFunctionName,
                                                const std::string& accessSpecifier = "public") {
                // create JNI-Func
                _mappedFunctionsJNI.insert(
                    generator::jni::generateFunction<T, ReturnType, Params...>(cppFunctionName, jFunctionName, _jPackage, _jClassname));

                return *this;
            }

            // TODO proper constructor mapping...
            // TODO proper java mapping...
            // TODO proper jobject to nativeObject handling...
            // TODO proper ptr and ref handling for objects...
    };

}  // namespace cppJify::mapper::classes
