#pragma once

#include <cppJify/helper/Helper.hpp>
#include <cppJify/mapper/JifyMapper.hpp>
#include <cppJify/mapper/classes/StaticClassMapper.hpp>
#include <cppJify/utils/FilesystemUtils.hpp>
#include <utility>

namespace cppJify::mapper::classes {

    /**
     * Class maps concrete C++ classes to Java.
     */
    template <class T>
    class InstanceClassMapper : public StaticClassMapper {
        public:
            /**
             * Constructor
             *
             * Also responsible for registering T as a mapped class...
             *
             * @param jpackage The package of the generated java-class.
             * @param jclassname The name of the generated java-class.
             *
             */
            explicit InstanceClassMapper(const std::string& jpackage, const std::string& jclassname)
                : StaticClassMapper(std::move(jpackage), std::move(jclassname)) {
                registeredClasses[JifyMapper<T>::CType()] = jpackage + "." + jclassname;

                // create dealloc (close) function
                _mappedFunctionsJNI.insert(generator::jni::generateDeallocFunction<T>(jpackage, jclassname));
            }

            /**
             * Generate the corresponding Java-File for this class.
             * The output path resembles the given java-package structure.
             *
             * @param outputBase The base-directory of the output.
             */
            void generateJavaFile(const std::string& outputBase) const override {
                // create output directory
                const std::string packagePath = "/" + utils::replaceAll(_jPackage, ".", "/");
                const std::string fullPath = outputBase + packagePath;

                // create filename
                const std::string filename = _jClassname + ".java" + "";

                // compose all mapped jni-functions
                std::string content = blueprints::JIFY_BLUEPRINT_JAVA_INSTANCE_CLASS;

                content = utils::replaceAll(content, blueprints::placeholder::CUSTOM_CODE, getAllCustomJavaCode());
                content = utils::replaceAll(content, blueprints::placeholder::java::PACKAGE, _jPackage);
                content = utils::replaceAll(content, blueprints::placeholder::java::IMPORTS, getAllImports());
                content = utils::replaceAll(content, blueprints::placeholder::CLASSNAME, _jClassname);
                content = utils::replaceAll(content, blueprints::placeholder::CLASSBODY, getAllJavaFunctions());

                utils::createFile(filename, content, fullPath);
            }

            /**
             * @brief Method maps member Cpp-functions to Java.
             *
             * @tparam ReturnType The return type of the Cpp function.
             * @tparam Params The parameter of the Cpp function.
             *
             * @param cppFunctionName The actual name of the cpp function to be mapped.
             * @param jFunctionName The name of the generated java function.
             * @param accessSpecifier The acces specifier of the generated java function [DEFAULT = public]
             */
            template <class ReturnType, class... Params>
            InstanceClassMapper<T>& mapFunction(ReturnType (T::*func)(Params...),
                                                const std::string& cppFunctionName,
                                                const std::string& jFunctionName,
                                                const std::string& accessSpecifier = "public") {
                // create JNI-Func
                _mappedFunctionsJNI.insert(
                    generator::jni::generateFunction<T, ReturnType, Params...>(cppFunctionName, jFunctionName, _jPackage, _jClassname));

                // create Java-Func
                _mappedFunctionsJava.insert(
                    generator::java::generateFunctionSignature<false, true, ReturnType, Params...>(jFunctionName, accessSpecifier));

                return *this;
            }

            /**
             * @brief Map member functions with a LAMBDA.
             * @note This function is only meant to be used with a lambda and the JIFY_LAMBDA macro, using it otherwhise will result in
             * undefined behaviour.
             *
             * @tparam Callable The lambda.
             *
             * @param cppFunctionName The actual name of the cpp function to be mapped.
             * @param jFunctionName The name of the generated java function.
             * @param accessSpecifier The access specifier of the generated java function.
             *
             */
            template <class Callable>
            InstanceClassMapper<T>& mapFunction(const std::pair<Callable, std::string>& callable,
                                                const std::string& cppFunctionName,
                                                const std::string& jFunctionName,
                                                const std::string& accessSpecifier = "public") {
                // Extract the corresponding FunctionTypes
                using FunctionType = boost::callable_traits::function_type_t<std::decay_t<Callable>>;
                using DesiredFunctionType = helper::RemoveFirstArg<FunctionType>::type;
                using ReturnType = boost::callable_traits::return_type_t<FunctionType>;

                using FunctionPointerTypeBody = std::add_pointer_t<FunctionType>;
                using FunctionPointerType = std::add_pointer_t<DesiredFunctionType>;

                // Build the Function from the passed lambda (in order to be able to use it in JNI)
                // clang-format off
                const std::string funcWithoutCapture = utils::replaceAll(callable.second, "[]", "");
                const std::string lambdaFunction = JIFY_FMT(JIFY_RAW(\n\tstatic {} {} {}), JifyMapper<ReturnType>::CType(), cppFunctionName, funcWithoutCapture);
                // clang-format on

                appendCustomJniCode(lambdaFunction);
                return mapLambdaFunction(FunctionPointerType(nullptr), FunctionPointerTypeBody(nullptr), cppFunctionName, jFunctionName,
                                         accessSpecifier);
            }

            /**
             * Function creates a constructor with the passed parameter types as parameters.
             *
             * @tparam Params The parameter types of the constructor.
             */
            template <class... Params>
            InstanceClassMapper<T>& constructor() {
                _mappedFunctionsJNI.insert(generator::jni::generateAllocFunction<T, Params...>(_jPackage, _jClassname));

                _mappedFunctionsJava.insert(generator::java::generateConstructor<Params...>(_jClassname));
                _mappedFunctionsJava.insert(generator::java::generateFunctionSignature<true, true, long, Params...>("allocate", "private"));

                return *this;
            }

        private:
            /**
             * @brief Helper function maps a member function using a lambda.
             *
             * @tparam ReturnType The return type used for the generated signature.
             * @tparam Params The parameter types, used to build the jni signature.
             * @tparam ReturnTypeBody The Return type, used to build the jni functions body.
             * @tparam ParamsBody The parameter types, used to build the jni function body.
             *
             * @param cppFunctionName The actual name of the cpp function to be mapped.
             * @param jFunctionName The name of the generated java function.
             * @param accessSpecifier The access specifier of the generated java function.
             */
            template <class ReturnType, class... Params, class ReturnTypeBody, class... ParamsBody>
            InstanceClassMapper<T>& mapLambdaFunction(ReturnType (*func)(Params...),
                                                      ReturnTypeBody (*funcBody)(ParamsBody...),
                                                      const std::string& cppFunctionName,
                                                      const std::string& jFunctionName,
                                                      const std::string& accessSpecifier) {
                const std::string signature =
                    generator::jni::generateFunctionSignature<T, ReturnType, Params...>(jFunctionName, _jPackage, _jClassname);
                const std::string body = generator::jni::generateStaticFunctionBody<ReturnTypeBody, ParamsBody...>(cppFunctionName);

                _mappedFunctionsJNI.insert(signature + body);

                // create Java-Func
                _mappedFunctionsJava.insert(
                    generator::java::generateFunctionSignature<false, true, ReturnType, Params...>(jFunctionName, accessSpecifier));

                return *this;
            }
    };

}  // namespace cppJify::mapper::classes
